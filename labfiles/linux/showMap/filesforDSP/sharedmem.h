#ifndef _SHAREDMEM_H_
#define _SHAREDMEM_H_

#ifdef RUNNING_ON_OMAPL138
#include "evmomapl138_vpif.h"
#endif

#define SHARED_MEM 0x80000000
#define LINUX_IMAGE_OFFSET 0x80000
#define LCD_IMAGE_OFFSET 0x93000
#define LCD_MEM_OFFSET 0xA6000
#define SMALL_IMAGE_DATA_MEM 0x800029c0
#define IMAGE_DATA_MEM 0x80007400

/*
Five LEDS
								GPIO6.8
								GPIO6.9
								GPIO6.10
								GPIO6.11
								GPIO6.12

Maybe used by USB				GPIO6.13

COLOR LCD RESET  				GPIO7.8
RED LED  						GPIO7.9
BLUE LED 						GPI07.10
GREEN LED 						GPIO7.11
LCD Pushbutton1  				GPIO7.12
LCD Pushbutton2  				GPIO7.13

Flags:
DATA_FROM_LINUX 				GPIO0.0
DATA_TO_LINUX 					GPIO0.1
VBDATA_FROM_LINUX				GPIO0.2 and now LVDATA_FROM_LINUX
VBDATA_TO_LINUX					GPIO0.3 and now LVDATA_TO_LINUX

*****NEW FLAGS FOR LINUX ASTAR PATH AND MAP*****
ASTAR_COMMAND					GPIO0.4
ASTAR_FAILED					GPIO0.5
ASTAR_DONE						GPIO0.6

currently I set GPIO0.0 to 6 as GPIO inputs first and then I set them to McBSP1 pins after linux has booted.  

LINUX_BOOTED					GPIO1.14
IMAGE_TO_LINUX 					GPIO1.2
OPTITRACKDATA_FROM_LINUX		GPIO1.3
DATAFORFILE_TO_LINUX 			GPIO1.4


Unused and can be used for flags:
GPIO0.4
GPIO0.5
GPIO0.6

GPIO1.0
GPIO1.1
GPIO1.5
GPIO1.8
GPIO1.9
GPIO1.10
GPIO1.11
GPIO1.12
GPIO1.13

There are more unused on GPIO4 but I don't think we will need them.

*/

#define IMAGE_TO_LINUX_FLAG GPIO_PIN2
#define IMAGE_TO_LINUX_BANK GPIO_BANK1

#define OPTITRACKDATA_FROM_LINUX_FLAG GPIO_PIN3
#define OPTITRACKDATA_FROM_LINUX_BANK GPIO_BANK1

#define DATA_FROM_LINUX_FLAG GPIO_PIN0
#define DATA_FROM_LINUX_BANK GPIO_BANK0

#define VBDATA_FROM_LINUX_FLAG GPIO_PIN2
#define VBDATA_FROM_LINUX_BANK GPIO_BANK0
// LabView using same as VB 
#define LVDATA_FROM_LINUX_FLAG GPIO_PIN2
#define LVDATA_FROM_LINUX_BANK GPIO_BANK0


#define DATA_TO_LINUX_FLAG GPIO_PIN1
#define DATA_TO_LINUX_BANK GPIO_BANK0

#define VBDATA_TO_LINUX_FLAG GPIO_PIN3
#define VBDATA_TO_LINUX_BANK GPIO_BANK0
// LabView using same as VB 
#define LVDATA_TO_LINUX_FLAG GPIO_PIN3
#define LVDATA_TO_LINUX_BANK GPIO_BANK0

#define DATAFORFILE_TO_LINUX_FLAG GPIO_PIN4
#define DATAFORFILE_TO_LINUX_BANK GPIO_BANK1

#define LINUX_BOOTED_FLAG GPIO_PIN14
#define LINUX_BOOTED_BANK GPIO_BANK1

// 0x80007400 + 3*176*144
#define THRES_IMAGE_MEM 0x80019D00

#define LINUX_COMSIZE 256

#define NUM_FLOATS_FROM_LINUX_TO_DSP 20
#define NUM_FLOATS_TO_LINUX_FROM_DSP 20

#define OPTITRACKDATASIZE 3+2 // x, y, heading, trackableID, framecount

#define ASTAR_COMMAND_FLAG GPIO_PIN4 // Request from OMAP138 to run astar algorithm
#define ASTAR_COMMAND_BANK GPIO_BANK0
 
#define ASTAR_FAILED_FLAG GPIO_PIN5 // astar algorithm in progress
#define ASTAR_FAILED_BANK GPIO_BANK0

#define ASTAR_DONE_FLAG GPIO_PIN6 // astar algorithm Completed
#define ASTAR_DONE_BANK GPIO_BANK0

//typedef struct sharedmemstruct {
//	volatile int DSPRec_size;
//	volatile char DSPRec_buf[LINUX_COMSIZE+2];  // +2 for possible extra Null char if large amounts of data sent
//	volatile int DSPSend_size;
//	volatile char DSPSend_buf[LINUX_COMSIZE+2];
//	volatile float Floats_to_DSP[NUM_FLOATS_FROM_LINUX_TO_DSP];
//	volatile float Floats_from_DSP[NUM_FLOATS_TO_LINUX_FROM_DSP];
//	volatile float Optitrackdata[OPTITRACKDATASIZE];
//	volatile int RobotID;
//} sharedmemstruct;


// Max length of sharedmemstruct can be 0x29c0 bytes
typedef struct sharedmemstruct {
	volatile float obj_x;
	volatile float obj_y;
	volatile float numpix;
	volatile float tcpip1;
	volatile float tcpip2;
	volatile float tcpip3;
	volatile float tcpip4;
	volatile int DSPRec_size;
	volatile char DSPRec_buf[LINUX_COMSIZE+2];  // +2 for possible extra Null char if large amounts of data sent
	volatile int DSPSend_size;
	volatile char DSPSend_buf[LINUX_COMSIZE+2];
	volatile float Floats_to_DSP[NUM_FLOATS_FROM_LINUX_TO_DSP];
	volatile float Floats_from_DSP[NUM_FLOATS_TO_LINUX_FROM_DSP];
	volatile float Optitrackdata[OPTITRACKDATASIZE];
	volatile float scratch[500];
	//2732
	
	//*****Astar Variables*****
	volatile char sharedAstarMap[176];
	volatile float sharedLadarDataX[228];
	volatile float sharedLadarDataY[228];
	volatile float sharedLadarDistance[228];
	volatile int sharedPathRow[100];
	volatile int sharedPathCol[100];
	volatile int sharedPathLen;
	volatile int sharedRobotRow;
	volatile int sharedRobotCol;
	volatile int sharedDestRow;
	volatile int sharedDestCol;
	volatile int astarTrigger;
	volatile int newLadar;
	//5568

	// 8300 total
	
	// If the sharedmemstruct ever exceeds 8192, then need to multiply map size by 3.
	
} sharedmemstruct;


#endif   /* _SHAREDMEM_H_ */

