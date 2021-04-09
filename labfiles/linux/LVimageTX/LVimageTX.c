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

#include "LVimageTX.h"
#include "omapl138_gpiofuncs.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#include "../../sharedmem_com/sharedmem.h"

sharedmemstruct* myshared;

volatile GPIOregs* mygpio;
volatile unsigned char* myimage;



int fd;
void *map_base;  //, *virt_addr;
off_t target;

//void *map_baseGPIO, *virt_addrGPIO;
//unsigned int *myGPIO;

char inbuf[256];
unsigned char outbuf[19*4096];  //77824 bigger than 3*176*144 = 76 032 //outbuf[GS_DEV_MTU];  
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
  close(gs_coms_skt);
  return;
}
 

/*
 * init_server()
 *   Starts up listening socket
 */
int init_server()
{
  // Communications sockets,
  // tcp:
  gs_coms_skt = tcpsock();  
  sockbind(gs_coms_skt, gs_port_coms);
  socklisten(gs_coms_skt);
  printf("Listening on port %d\n.",gs_port_coms);
  sock_set_blocking(gs_coms_skt);
}

void sd_signal_handler_IO (int status)
{
  int i;
  int donecheck;
  int tmpChar1 = 0;
  int tmpChar2 = 0;

  for (i=0;i<64;i++) {
    inbuf[i] = '\0';
  }
  if (read(accepted_skt, inbuf, 64))  {
  
    if ((inbuf[0] == 'I') && (inbuf[1] == '1')) {
      while (GPIO_getOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG) == 1) {}
	      
      memcpy(&outbuf,(void *)(&myimage[0]),76032);      
      GPIO_setOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG,OUTPUT_HIGH);
	      
      write(accepted_skt, outbuf, 10000);
    } else if ((inbuf[0] == 'I') && (inbuf[1] == '2')) {
      write(accepted_skt, outbuf+10000, 10000);
    } else if ((inbuf[0] == 'I') && (inbuf[1] == '3')) {
      write(accepted_skt, outbuf+20000, 10000);
    } else if ((inbuf[0] == 'I') && (inbuf[1] == '4')) {
      write(accepted_skt, outbuf+30000, 10000);
    } else if ((inbuf[0] == 'I') && (inbuf[1] == '5')) {
     write(accepted_skt, outbuf+40000, 10000);
   } else if ((inbuf[0] == 'I') && (inbuf[1] == '6')) {
      write(accepted_skt, outbuf+50000, 10000);
    } else if ((inbuf[0] == 'I') && (inbuf[1] == '7')) {
     write(accepted_skt, outbuf+60000, 10000);
    } else if ((inbuf[0] == 'I') && (inbuf[1] == '8')) {	
      write(accepted_skt, outbuf+70000, 6032);
    } else if ((inbuf[0] == 'K') && (inbuf[1] == 'i')) {
      gs_killapp(0);
    } else if ((inbuf[0] == 'F') && (inbuf[1] == 'a')) {
	  tmpChar1 = inbuf[2];
	  tmpChar2 = inbuf[3];
	  tmpChar1 = inbuf[4];
	  tmpChar2 = inbuf[5];
	  tmpChar1 = inbuf[6];
	  tmpChar2 = inbuf[7];
    }      
  } else {
    printf("Exiting\n");
	gs_quit = 1;
	close(gs_coms_skt);
  }
  
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
  }
}




/*
 * main()
 *   process command line input
 */
int main (int argc, char **argv)
{
  int index = 0;
  int i = 0;
  printf("Vision IP sample program\n");
	
    if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
        printf("/dev/mem could not be opened.\n");
        exit(1);
    } else {
        printf("/dev/mem opened.\n");
    }
    fflush(stdout);
    
   target = 0xC3F80000;
    /* Map one page for shared memory structure*/
    map_base = mmap(0, MAP_SIZE*19, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);//(target & ~MAP_MASK));
    if(map_base == (void *) -1) {
        printf("Memory map failed.\n");
    } else {
        printf("image Struct mapped at address %p.\n", map_base);
    }
    fflush(stdout);
    //virt_addr = (void*)((unsigned long int)map_base + (target & MAP_MASK));
    myimage = (unsigned char *) map_base;
    
    

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

    myshared = (sharedmemstruct *) map_base;
    
    GPIO_setOutput(mygpio,IMAGE_TO_LINUX_BANK,IMAGE_TO_LINUX_FLAG,OUTPUT_HIGH);  // Set = linux is ready for new image from DSP
 
//    for (i=0;i<100;i++) {
//	    while (GPIO_getOutput(mygpio,CONTINUOUSDATA_TO_LINUX_BANK,CONTINUOUSDATA_TO_LINUX_FLAG) == 1) {	    
//	    }
//	    
//	    printf("x=%.1f,y=%.1f,pix=%.1f\n",myshared->obj_x,myshared->obj_y,myshared->numpix);		
//	    
//	    GPIO_setOutput(mygpio,CONTINUOUSDATA_TO_LINUX_BANK,CONTINUOUSDATA_TO_LINUX_FLAG,OUTPUT_HIGH);
//    }
	    
    
  if (argc ==2) {
    printf("using port %s\n",argv[1]);
    gs_port_coms = atoi(argv[1]);
  }
  printf("Setting signal handler...\n");
  signal(SIGKILL, gs_killapp);
  signal(SIGINT, gs_killapp);
  printf("...OK\n");

  printf("Initializing listening connection...\n");
  init_server();
  printf("...OK\n");

  printf("Accepting connections...\n");
  run_server();
  
  if(munmap((void*) myimage, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  }
  if(munmap((void*) mygpio, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  }
  if(munmap((void*) myshared, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  }
}


