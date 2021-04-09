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
#include "TurnOnLEDS.h"
#include "omapl138_gpiofuncs.h"
#include "../../sharedmem_com/sharedmem.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)
#define DELAYTIME 100000

// functions declared at bottom of this file
int mygetch(void);
void gs_killapp(int s);
int init_server(void);
void sd_signal_handler_IO (int status);
int run_server(void);
void writefloats_sharedmem_5times(void);

sharedmemstruct* myshared;  // pointer to shared memory stucture used to communicate between Linux and the OMAPL138's DSP

volatile GPIOregs* mygpio;  // pointer to GPIO registers so Linux can control GPIO Pins
int TCPIPtransmissionerror = 0;		// Initialize transmission error count
int TCPIPbeginnewdata = 0;
int TCPIPdatasize = 0;
int numTXChars = 0;

char tmpbuf[LINUX_COMSIZE];

long tcpipcount = 0;

#define INBUFFSIZE (256)
#define OUTBUFFSIZE (INBUFFSIZE + 2)
volatile char TCPIPMessageArray[INBUFFSIZE];
volatile char tempReadbackToCleanCache[INBUFFSIZE];
volatile int tempReadbackSize;

volatile unsigned int delaycount = 0;

int fd;  // variables used to map to physical memory addresses
void *map_base;
off_t target;

char inbuf[INBUFFSIZE];  // TCPIP input and output buffers
unsigned char outbuf[OUTBUFFSIZE];
int accepted_skt;

float DSPFloats[NUM_FLOATS_FROM_LINUX_TO_DSP];  // temporay variables used in the communication with DSP core    
volatile float tempFloats[NUM_FLOATS_FROM_LINUX_TO_DSP];




/*
 * main()
 *   process command line input
 */
int main (int argc, char **argv)
{
  int index = 0;
  char buffer[200];  // used by fgets to read character string typed by user.
  char mychar;
  int inputdone = 0;
  float tempfloat = 0;
  float DVel = 0;
  float turn = 0.0;
	
	
/* ****************************************************************/
/*  Memory map to physical memory spaces of the GPIO control registers and shared memory space */	
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
/* ******************************************************************/

  if (argc ==2) {
      
    if (strlen(argv[1]) == 5) {
	    GPIO_setDir(mygpio, GPIO_BANK6, GPIO_PIN8, 0);
	    GPIO_setDir(mygpio, GPIO_BANK6, GPIO_PIN9, 0);
	    GPIO_setDir(mygpio, GPIO_BANK6, GPIO_PIN10, 0);
	    GPIO_setDir(mygpio, GPIO_BANK6, GPIO_PIN11, 0);
	    GPIO_setDir(mygpio, GPIO_BANK6, GPIO_PIN12, 0);
	    printf("Turning GPIO 6.8: ");
            if (argv[1][0] == '1') {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN8, 1);
		printf("ON ");    
	    } else {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN8, 0);
		printf("OFF ");    
	    }
	    printf("GPIO 6.9: ");
            if (argv[1][1] == '1') {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN9, 1);
		printf("ON ");		    
	    } else {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN9, 0);
		printf("OFF ");		    
	    }
	    printf("GPIO 6.10: ");	    
            if (argv[1][2] == '1') {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN10, 1);
		printf("ON ");		    
	    } else {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN10, 0);
		printf("OFF ");		    
	    }
	    printf("GPIO 6.11: ");	    
            if (argv[1][3] == '1') {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN11, 1);
		printf("ON ");		    
	    } else {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN11, 0);
		printf("OFF ");		    
	    }
	    printf("GPIO 6.12: ");	    
            if (argv[1][4] == '1') {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN12, 1);
		printf("ON\n");		    
	    } else {
		GPIO_setOutput(mygpio, GPIO_BANK6, GPIO_PIN12, 0);
		printf("OFF\n");		    
	    }
	    
    } else {
	    printf("Format:  TurnOnLEDS 11111 will turn on All LEDS\n");
	    printf("Format:  TurnOnLEDS 00000 will turn off All LEDS\n");
	    printf("Format:  TurnOnLEDS 10101 will turn 3 on 2 off\n");
	    printf("Format:  1 for on 0 for off, must enter five 1's or 0's\n");
    }

  } else {
	    printf("Format:  TurnOnLEDS 11111 will turn on All LEDS\n");
	    printf("Format:  TurnOnLEDS 00000 will turn off All LEDS\n");
	    printf("Format:  TurnOnLEDS 10101 will turn 3 on 2 off\n");
	    printf("Format:  1 for on 0 for off, must enter five 1's or 0's\n");  
  }
    
  if(munmap((void*) mygpio, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  }
  if(munmap((void*) myshared, MAP_SIZE) == -1) {
    printf("Memory unmap failed.\n");	
  } 

}


