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
#include "netapi.h"

#include "BasicOptitrackComm.h"
#include "omapl138_gpiofuncs.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)

#define DELAYTIME 100000

#define SERVER_BACKLOG 1
#define UDP_PORT 3500
#define MSG_BUFFER 1024
//#define PACKET_SIZE 12*4
#define PACKET_SIZE 4*3*4+2*4 //4*3*4+1*4

#define ENABLE_VB 0

#include "../../sharedmem_com/sharedmem.h"

sharedmemstruct* myshared;
//sharedmemstruct2* myoptishared;

//sharedmemstruct2 linuxLocations[NUM_TRACKABLES];

//extern void __clear_cache (char*, char*);

volatile GPIOregs* mygpio;

//int numTXChars = 0;
//volatile int PageSize = 0;
//char tmpbuf[LINUX_COMSIZE];


#define INBUFFSIZE (256)
#define OUTBUFFSIZE (INBUFFSIZE + 2)

//volatile unsigned int delaycount = 0;

int fd;
void *map_base;  //, *virt_addr;
off_t target;

void *map_baseGPIO, *virt_addrGPIO;
unsigned int *myGPIO;

//char inbuf[INBUFFSIZE];
//unsigned char outbuf[OUTBUFFSIZE];
int accepted_skt;
long counter = 0;

unsigned int printpause = 0;

int recvd;		// Bytes received from socket
char mesg[MSG_BUFFER]; 	// Buffer to hold message from socket

int robotID = -1;
//unsigned int ip1 = 0;
//unsigned int ip2 = 0;
//int small_packet_size = 0;

// 1/31/2013
char inbuf[INBUFFSIZE+2];
unsigned char outbuf[OUTBUFFSIZE];
int accepted_skt;
int TCPIPtransmissionerror = 0;		// Initialize transmission error count
int TCPIPbeginnewdata = 0;
int TCPIPdatasize = 0;
int numTXChars = 0;
#define INBUFFSIZE (256)
#define OUTBUFFSIZE (INBUFFSIZE + 2)
char TCPIPMessageArray[INBUFFSIZE + 2];

int gs_exit = 0;
int firsttime = 1;
int tcpip_connected = 0;



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
	close(gs_udpcoms_skt);
	if(gs_udpcoms_skt > 0) close(gs_udpcoms_skt);
	return;
}


/*
* init_server()
*   Starts up listening socket
*/
int init_server()
{
	int on = 1;
	
	// Communications sockets
	
	if (ENABLE_VB) {
		// tcp:
		gs_coms_skt = tcpsock();  
		if (setsockopt(gs_coms_skt, SOL_SOCKET,SO_REUSEADDR, (char*)&on, sizeof(on)) < 0) {
			printf("Error Reusing Socket\n");
		}	
		sockbind(gs_coms_skt, gs_port_coms);
		socklisten(gs_coms_skt);
		printf("TCP Listening on port %d\n.",gs_port_coms);
		sock_set_nonblocking(gs_coms_skt);  // was blocking
	}
	
	// udp: 
	if (firsttime) {
		gs_udpcoms_skt = udpsock();
		sock_set_nonblocking(gs_udpcoms_skt);      
		sockbind(gs_udpcoms_skt, UDP_PORT);
		printf("UDP Listening on port %d\n.", UDP_PORT);
	}
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
					
					// 1/31/2013				
					/*				if (GPIO_getOutput(mygpio,DATA_FROM_LINUX_BANK,DATA_FROM_LINUX_FLAG)  == 0) {  // is DSP ready for new data
					for (j=0;j<TCPIPdatasize;j++) {
						myshared->DSPRec_buf[j] = TCPIPMessageArray[j];
					}
					myshared->DSPRec_size = TCPIPdatasize;
					GPIO_setOutput(mygpio,DATA_FROM_LINUX_BANK,DATA_FROM_LINUX_FLAG,OUTPUT_HIGH);
				}
				*/
					//writeFromMainFlag = 1;
					TCPIPbeginnewdata = 0;	// Reset the flag
					TCPIPdatasize = 0;	// Reset the number of chars collected
				}	
			}
		}
	} else {
		printf("numrecChars = %d\n", numrecChars);
		printf("\nResetting\n");
		gs_quit = 1;
		tcpip_connected = 0;
		close(gs_coms_skt);
	}

	


	// call this kill when kill string is sent
	//      gs_killapp(0);

	return;
}


int run_client()
{
	int i = 0;
	int j = 0;
	//long boolean = -1; // run while loop while this is true
	//int valid = 0; // indicates whether the last packet recv'd is valid
	static struct sockaddr_in cliaddr;
	unsigned int len = sizeof(cliaddr);
	int mem_counter = 0;
	
	/*unsigned long valid_ot = 0;
	unsigned long valid_ip0 = 0;
	unsigned long valid_ip1 = 0;
	unsigned long valid_ip2 = 0;
	unsigned long valid_ot_prev = 0;
	unsigned long valid_ip0_prev = 0;
	unsigned long valid_ip1_prev = 0;
	unsigned long valid_ip2_prev = 0;
	unsigned char printstat = 0;
	unsigned char printstat_prev = 0;*/

	sigset_t sigio_set; 
	struct sigaction saio;           // definition of signal action 
	static struct sockaddr_in addr;  

	// Accept new connection
/*	if (tcpip_connected == 0) {
		accepted_skt = connaccept(gs_coms_skt, &addr);
		if (accepted_skt > 0) {
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
			tcpip_connected = 1;
		}
	}*/
	while (!gs_quit) {
		sched_yield();
		
		// Accept new connection
		if ((tcpip_connected == 0) && (ENABLE_VB)) {
			accepted_skt = connaccept(gs_coms_skt, &addr);
			if (accepted_skt > 0) {
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
				tcpip_connected = 1;
			}
		}


		// read from the socket
		recvd = recvfrom(gs_udpcoms_skt,mesg,MSG_BUFFER,0,(struct sockaddr *)&cliaddr,&len);
		
		// data from optitrack python program
		if(recvd == packet_size)
		{
			//valid_ot++;
			float dat[(packet_size/4)];
			void * ptr = mesg;

			for(i=0; i < (packet_size/4); i++)
			{
				dat[i] = *((float *)ptr);
				ptr += sizeof(float);
			}

			if (printpause > 30) {
				printf("OptiData: %.3f %.3f %.3f %.0f %.0f\n",dat[0],dat[1],dat[2],dat[3],dat[4]);
				printpause = 0;
			}
			printpause++;
			
			if (GPIO_getOutput(mygpio,OPTITRACKDATA_FROM_LINUX_BANK,OPTITRACKDATA_FROM_LINUX_FLAG) == 0)
			{
				for (j=0;j<packet_size/4;j++)
				{
					myshared->Optitrackdata[j] = dat[j];
					//myshared->RobotID = robotID;
				}
				GPIO_setOutput(mygpio,OPTITRACKDATA_FROM_LINUX_BANK,OPTITRACKDATA_FROM_LINUX_FLAG,OUTPUT_HIGH);
			}	

		} 
		
		// check if DSP is ready for new kalman position data
		/*			if (GPIO_getOutput(mygpio,CONTINUOUSDATA_TO_LINUX_BANK,CONTINUOUSDATA_TO_LINUX_FLAG) == 0) {
			// fill shared mem struct with received kalman filtered position data in local (linux) memory
			for (i = 0;i<NUM_TRACKABLES;i++) { 
				if (i != robotID) {
					myoptishared[i].tx = linuxLocations[i].tx;
					myoptishared[i].ty = linuxLocations[i].ty;
				}
			}
			
			// read THIS robot's kalman filtered position from the DSP
			linuxLocations[robotID].tx = myoptishared[robotID].tx;
			linuxLocations[robotID].ty = myoptishared[robotID].ty;
			
			//printf("Sending: %d %.1f %.1f\n",robotID,myoptishared[robotID].tx,myoptishared[robotID].ty);
			
			// I could do this better maybe
			// Pack THIS robot's kal. pos. data into a unsigned char array and send to other robots
			float send_dat[(small_packet_size/4)];
			void * send_ptr = send_dat;
			
			send_dat[0] = (float)robotID;
			send_dat[1] = linuxLocations[robotID].tx;
			send_dat[2] = linuxLocations[robotID].ty;
			
			for(i=0; i < (small_packet_size); i++)
			{
				mesg[i] = *((char *)send_ptr);
				send_ptr += sizeof(char);
			}
			
			
			// send out trackableID's kal filtered location
			sendto(gs_udpcoms_skt,mesg,small_packet_size,0,(struct sockaddr *)&dest_addr1,sizeof(dest_addr1));
			sendto(gs_udpcoms_skt,mesg,small_packet_size,0,(struct sockaddr *)&dest_addr2,sizeof(dest_addr2));
			
			// set flag that linux has updated position data for the DSP
			GPIO_setOutput(mygpio,CONTINUOUSDATA_TO_LINUX_BANK,CONTINUOUSDATA_TO_LINUX_FLAG,OUTPUT_HIGH);
		}  // end if GPIO flag set */	

		
	} // end while !gs_quit
}




/*
* main()
*   process command line input
*/
int main (int argc, char **argv)
{
	int index = 0;
	printf("Echo Program\n");
	
	if((fd = open("/dev/mem", O_RDWR | O_SYNC)) == -1) {
		printf("/dev/mem could not be opened.\n");
		exit(1);
	} else {
		printf("/dev/mem opened.\n");
	}
	fflush(stdout);
	
	
	target = 0x01E26000;
	//Map one page for shared memory structure
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
	//Map one page for shared memory structure
	map_base = mmap(0, 3*MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
	if(map_base == (void *) -1) {
		printf("Memory map failed.\n");
	} else {
		printf("Shared Struct mapped at address %p.\n", map_base);
	}
	fflush(stdout);

	//virt_addr = map_base + (target & MAP_MASK);
	
	myshared = (sharedmemstruct *) map_base;
	
	
	/*target = 0x80002000;
	//Map one page for shared memory structure
	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target);
	if(map_base == (void *) -1) {
		printf("Memory map failed.\n");
	} else {
		printf("Shared Opti Struct mapped at address %p.\n", map_base);
	}
	fflush(stdout);*/

	//virt_addr = map_base + (target & MAP_MASK);
	
	//myoptishared= (sharedmemstruct2 *) map_base;

	/*if ( (PageSize = sysconf(_SC_PAGE_SIZE)) < 0)
	{
		perror("sysconf() Error=");
	}
	else
		printf("PageSize = %d",PageSize);*/

	/*target = DATA_FROM_LINUX_MEM;
	map_base = mmap(0, MAP_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, target & ~MAP_MASK);
	if(map_base == (void *) -1)
	{
		printf("Memory map failed.\n");
	} else {F28335ProjectCreator
		printf("Shared union mapped at address %p.\n", map_base);
	}
	fflush(stdout);

	//virt_addr = map_base + (target & MAP_MASK);
	
	fromlinuxshared = (fromlinuxunion *) map_base;*/
	
	GPIO_setOutput(mygpio,OPTITRACKDATA_FROM_LINUX_BANK,OPTITRACKDATA_FROM_LINUX_FLAG,OUTPUT_LOW);
	
	// Only set up GPIOs for data exchange / VB if ENABLE_VB is set
	if (ENABLE_VB) {
		GPIO_setOutput(mygpio,VBDATA_TO_LINUX_BANK,DATA_TO_LINUX_FLAG,OUTPUT_HIGH);
		GPIO_setOutput(mygpio,VBDATA_FROM_LINUX_BANK,DATA_FROM_LINUX_FLAG,OUTPUT_LOW);
	}
	
	
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

	// init local linux locations
	/*for (index = 0;index<NUM_TRACKABLES;index++) {
		linuxLocations[index].tx = 0.0;
		linuxLocations[index].ty = 0.0;
		myoptishared[index].tx = 0.0;
		myoptishared[index].ty = 0.0;
	}*/

	// set flag telling DSP that linux needs new kalman pos. data for THIS robot
	
	
	// For GE423 we don't need to set ID/number of agents
	/*if (argc > 2)
	{
		num_agents = atoi(argv[1]);
		robotID = atoi(argv[2]);
		printf("Set num_agents: %d\n",num_agents);
		printf("Set Robot ID: %d\n",robotID);
	}
	else
	{
		printf("Please set the number of robots and robot ID.\n");
		return;
	}*/

	
	// For GE423 we don't need to send data to other robots
	// read from args which IPs we want THIS robot to send to 192.168.1.ip1/2
/*	if ((argc-3) == (num_agents-1)) {
		ip1 = atoi(argv[3]);
		ip2 = atoi(argv[4]);
	}*/

	packet_size = 5*4;  // x,y,theta,number,framecount
	printf("Packet size is: %d\n",packet_size);

	if (ENABLE_VB) {
		printf("Setting signal handler...\n");
		signal(SIGKILL, gs_killapp);
		signal(SIGINT, gs_killapp);
		printf("...OK\n");
	}
	
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

		if (ENABLE_VB) {
			printf("Accepting connections...\n");
		}
		run_client();
	}

	if(munmap((void*) mygpio, MAP_SIZE) == -1) {
		printf("Memory unmap failed.\n");	
	}
	if(munmap((void*) myshared, MAP_SIZE) == -1) {
	  printf("Memory unmap failed.\n");	
	}
}


