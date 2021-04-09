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
#include "SaveScratchToFile.h"
#include "omapl138_gpiofuncs.h"
#include "../../sharedmem_com/sharedmem.h"

#define MAP_SIZE 4096UL
#define MAP_MASK (MAP_SIZE - 1)
#define DELAYTIME 100000

void writescratchtofile(sharedmemstruct* myshared);

sharedmemstruct* myshared;  // pointer to shared memory stucture used to communicate between Linux and the OMAPL138's DSP

volatile GPIOregs* mygpio;  // pointer to GPIO registers so Linux can control GPIO Pins

int fd;  // variables used to map to physical memory addresses
void *map_base;
off_t target;

char filename[300];

/*
 * main()
 *   process command line input
 */
int main (int argc, char **argv)
{
		
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
    
if (argc ==2) {
    printf("Name of data file: %s.txt\n",argv[1]);
    sprintf(filename,"%s.txt",argv[1]);
  }
  
  
GPIO_setOutput(mygpio,DATAFORFILE_TO_LINUX_BANK,DATAFORFILE_TO_LINUX_FLAG,OUTPUT_HIGH);
  
  while (GPIO_getOutput(mygpio,DATAFORFILE_TO_LINUX_BANK,DATAFORFILE_TO_LINUX_FLAG) == 1) {
	  usleep(5);
  }
  
  writescratchtofile(myshared);
   
}

void writescratchtofile(sharedmemstruct* myshared){
	FILE *f;

	int i = 0;

	
	f = fopen(filename,"w");

	for(i=0; i<500; i++)
	{
	    fprintf(f,"%d %f\n",i,myshared->scratch[i]);
	}
	fclose(f);
}

