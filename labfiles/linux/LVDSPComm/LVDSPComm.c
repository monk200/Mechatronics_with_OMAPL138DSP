#include <stdio.h>
#include <stdlib.h>                          
#include <math.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <ctype.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/mman.h>

#include "LVDSPComm.h"
#include "omapl138_gpiofuncs.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#include "../../sharedmem_com/sharedmem.h"

sharedmemstruct* myshared;

volatile GPIOregs* mygpio;
int TCPIPtransmissionerror = 0;		// Initialize transmission error count
int TCPIPbeginnewdata = 0;
int TCPIPdatasize = 0;

int numTXChars = 0;
char tmpbuf[LINUX_COMSIZE+2]; // +2 for making sure Null character gets copied to Shared RAM


#define INBUFFSIZE (256)
#define OUTBUFFSIZE (INBUFFSIZE + 2)
char TCPIPMessageArray[INBUFFSIZE + 2];

int fd;
void *map_base;  //, *virt_addr;
off_t target;

//void *map_baseGPIO, *virt_addrGPIO;
//unsigned int *myGPIO;

char inbuf[INBUFFSIZE+2];
unsigned char outbuf[OUTBUFFSIZE];
int accepted_skt;







/*  
 * gs_killapp()
 *   ends application safely
 *
 */
void gs_killapp(int s)
{
  printf("\nTerminating\n");
  gs_quit = 1;
  gs_exit = 1;
  close(gs_coms_skt);
  return;
}
 


/*
 * init_server()
 *   Starts up listening socket
 */
int init_server()
{
  int on = 1;

  // Communications sockets,
  // tcp:
  gs_coms_skt = tcpsock();  
  
  if (setsockopt(gs_coms_skt, SOL_SOCKET,SO_REUSEADDR, (char*)&on, sizeof(on)) < 0) {
	 printf("Error Reusing Socket\n");
  }
  sockbind(gs_coms_skt, gs_port_coms);
  socklisten(gs_coms_skt);
  printf("Listening on port %d\n.",gs_port_coms);
  sock_set_blocking(gs_coms_skt);
}

void sd_signal_handler_IO (int status)
{
  int i,j;

  int numrecChars = 0;

	
  for (i=0;i<64;i++) {
    inbuf[i] = '\0';
  }

  numrecChars = read(accepted_skt, inbuf, 64); 
  if (numrecChars > 0)  {
	for (i=0;i<numrecChars;i++) {
		if (!TCPIPbeginnewdata) {// Only true if have not yet begun a message
			if (253 == (unsigned char)inbuf[i]) {// Check for start char
				TCPIPdatasize = 0;		// amount of data collected in message set to 0
				TCPIPbeginnewdata = 1;		// flag to indicate we are collecting a message
			}
		} else {	// Filling data
			// Dont go too large... limit message to 256 chars  this can be made larger if you change inbuf size
			if ((TCPIPdatasize < INBUFFSIZE) && ((unsigned char)inbuf[i] != 255)) {	
				TCPIPMessageArray[TCPIPdatasize] = inbuf[i];				
				TCPIPdatasize++;
			} else {  // too much data or 255 char received
				if ((unsigned char)inbuf[i] != 255) {// check if end character recvd
					// Not received
					TCPIPtransmissionerror++;
					printf("TXerrors = %d\n",TCPIPtransmissionerror);
				} 
				// Whether or not message terminated correctly, send data to other tasks
				TCPIPMessageArray[TCPIPdatasize] = '\0'; 	// Null terminate the string
				TCPIPdatasize++;  // increment by one so that the Null is copied to shared memory
				printf("Received String:%s\n",TCPIPMessageArray);
				
				if (GPIO_getOutput(mygpio,LVDATA_FROM_LINUX_BANK,LVDATA_FROM_LINUX_FLAG)  == 0) {  // is DSP ready for new data
					for (j=0;j<TCPIPdatasize;j++) {
						myshared->DSPRec_buf[j] = TCPIPMessageArray[j];
					}
					myshared->DSPRec_size = TCPIPdatasize;
					GPIO_setOutput(mygpio,LVDATA_FROM_LINUX_BANK,LVDATA_FROM_LINUX_FLAG,OUTPUT_HIGH);
				}


				TCPIPbeginnewdata = 0;	// Reset the flag
				TCPIPdatasize = 0;	// Reset the number of chars collected
			}	


		}

	}
  } else {
  printf("numrecChars = %d\n",numrecChars);
  printf("\nReseting\n");
  gs_quit = 1;
  close(gs_coms_skt);

  } 
	     
  // call this kill when kill string is sent
  //      gs_killapp(0);
  

  return;
}




/*
 * run_server()
 *   This function runs until the server quits and it:
 *
 *   1. accepts incoming TCP connections
 *   2. reads from ready sockets and writes incoming messages
 *      to the serial port / controls devices
 *   3. reads from serial port and prints
 */
int run_server()
{
  

	sigset_t sigio_set; 
	struct sigaction saio;           /* definition of signal action */
	static struct sockaddr_in addr;  
	int i;

	// Accept new connection
	accepted_skt = connaccept(gs_coms_skt, &addr);
	// We don't wanna block either source
	sock_set_nonblocking(accepted_skt);
	int flags = fcntl(accepted_skt, F_GETFL,0);
	fcntl (accepted_skt,F_SETFL,flags|FASYNC);
	fcntl(accepted_skt, F_SETOWN, getpid());

	sigemptyset(&sigio_set);
	sigaddset(&sigio_set,SIGIO); 
	saio.sa_handler = sd_signal_handler_IO;
	saio.sa_flags = SA_SIGINFO;
	sigemptyset(&saio.sa_mask);
	saio.sa_mask = sigio_set;
	if (sigaction(SIGIO,&saio,NULL)) {
		printf("Error in sigaction()\n");
		return 1;
	}

	if (accepted_skt>0) {
		printf("Connection accepted from %d.%d.%d.%d\n",
		(addr.sin_addr.s_addr&0x000000ff),      
		(addr.sin_addr.s_addr&0x0000ff00)>>8,
		(addr.sin_addr.s_addr&0x00ff0000)>>16,
		(addr.sin_addr.s_addr&0xff000000)>>24);
	}
	printf(".\n");
	while (!gs_quit) {
		sched_yield();
		if  (GPIO_getOutput(mygpio,LVDATA_TO_LINUX_BANK,LVDATA_TO_LINUX_FLAG) == 0) { // New Response data from DSP    
			
			if (myshared->DSPSend_size > LINUX_COMSIZE) myshared->DSPSend_size = LINUX_COMSIZE;
			for (i=0;i<myshared->DSPSend_size;i++) {
				tmpbuf[i] = myshared->DSPSend_buf[i];
			}
			
			tmpbuf[i] = '\0';  // Should already be in array but doesn't hurt to add another Null at the end.  
			
			printf("Send String:%s\n",tmpbuf);
			numTXChars = sprintf(((char *) outbuf),"%s\r\n",tmpbuf);

			write(accepted_skt, outbuf, numTXChars);
			
			GPIO_setOutput(mygpio,LVDATA_TO_LINUX_BANK,LVDATA_TO_LINUX_FLAG,OUTPUT_HIGH);	    
		}
	    
	}
}




/*
 * main()
 *   process command line input
 */
int main (int argc, char **argv)
{
  int index = 0;
  int firsttime = 1;
  printf("Echo Program\n");
	
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
        printf("/dev/mem could not be opened.\n");
        exit(1);
    } else {
        printf("/dev/mem opened.\n");
    }

    fflush(stdout);
    
    target = 0x01E26000;
    /* Map one page for shared memory structure*/
    map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);
    if(map_base == (void *) -1) {
        printf("Memory map failed.\n");
    } else {
        printf("gpio Struct mapped at address %p.\n", map_base);
    }

    fflush(stdout);
    //virt_addr = (void*)((unsigned long int)map_base + (target & MAP_MASK));	
    mygpio = (GPIOregs *) map_base;
    

    target = 0x80000000;
    /* Map one page for shared memory structure*/
    map_base = mmap(0, 3*MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
    if(map_base == (void *) -1) {
        printf("Memory map failed.\n");
    } else {
        printf("Shared Struct mapped at address %p.\n", map_base);
    }

    fflush(stdout);

    //virt_addr = map_base + (target & MAP_MASK);
	
    myshared = (sharedmemstruct *) map_base;
    
 
	GPIO_setOutput(mygpio,LVDATA_TO_LINUX_BANK,LVDATA_TO_LINUX_FLAG,OUTPUT_HIGH);  // Set = linux is ready for data from DSP
	GPIO_setOutput(mygpio,LVDATA_FROM_LINUX_BANK,LVDATA_FROM_LINUX_FLAG,OUTPUT_LOW);  // Clear = linux will write data for shared memory for DSP
	
/*    while (GPIO_getOutput(mygpio,GPIO_BANK1,GPIO_PIN3) == 1) {	    
	printf("Waiting\n"); 
    }

    GPIO_setOutput(mygpio,GPIO_BANK1,GPIO_PIN3,OUTPUT_HIGH);
    printf("x=%.1f,y=%.1f,pix=%.1f\n",myshared->obj_x,myshared->obj_y,myshared->numpix);		
    while (GPIO_getOutput(mygpio,GPIO_BANK1,GPIO_PIN3) == 1) {	    
//	printf("Waiting\n"); 
    }

    GPIO_setOutput(mygpio,GPIO_BANK1,GPIO_PIN3,OUTPUT_HIGH);
    printf("x=%.1f,y=%.1f,pix=%.1f\n",myshared->obj_x,myshared->obj_y,myshared->numpix);
    while (GPIO_getOutput(mygpio,GPIO_BANK1,GPIO_PIN3) == 1) {	    
//	printf("Waiting\n"); 
    }

    GPIO_setOutput(mygpio,GPIO_BANK1,GPIO_PIN3,OUTPUT_HIGH);
    printf("x=%.1f,y=%.1f,pix=%.1f\n",myshared->obj_x,myshared->obj_y,myshared->numpix);
*/  

  if (argc ==2) {
    printf("using port %s\n",argv[1]);
    gs_port_coms = atoi(argv[1]);
  }

  printf("Setting signal handler...\n");
  signal(SIGKILL, gs_killapp);
  signal(SIGINT, gs_killapp);
  printf("...OK\n");
  while (!gs_exit) {
	gs_quit = 0;
	
	if (!firsttime) {
		printf("Waiting 2 Seconds to make sure socket data is cleaned from the network.\n");
		sleep(2);
	}
	
	printf("Initializing listening connection...\n");
	init_server();
	firsttime = 0;
	printf("...OK\n");

	printf("Accepting connections...\n");
	run_server();
  }
  
  if(munmap((void*) mygpio, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  }

  if(munmap((void*) myshared, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  }

}


