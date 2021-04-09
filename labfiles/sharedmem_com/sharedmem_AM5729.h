#ifndef _SHAREDMEM_H_
#define _SHAREDMEM_H_

// OCMC_RAM1 starting at 256KB  
#define SHARED_MEM 0x40340000

#define LINUX_IMAGE_OFFSET 0x80000
#define LCD_IMAGE_OFFSET 0x93000
#define LCD_MEM_OFFSET 0xA6000
#define SMALL_IMAGE_DATA_MEM 0x800029c0
#define IMAGE_DATA_MEM 0x80007400

/*
six LEDS
								GPIO2.5
								GPIO2.6
								GPIO2.8
								GPIO2.19
								GPIO2.20
								GPIO2.24

3 switches						GPIO2.26
								GPIO2.27
								GPIO2.28
								
HWI interrupt GPIO2.25 could be switch but not currently

COLOR LCD RESET  				?

Flags:
DATA_FROM_LINUX 				GPIO2.0
DATA_TO_LINUX 					GPIO2.1
VBDATA_FROM_LINUX				GPIO2.2 
VBDATA_TO_LINUX					GPIO2.3

*****NEW FLAGS FOR LINUX ASTAR PATH AND MAP*****
ASTAR_COMMAND					GPIO2.4
ASTAR_FAILED					GPIO8.0
ASTAR_DONE						GPIO8.23 

LINUX_BOOTED					GPIO7.3
IMAGE_TO_LINUX 					GPIO7.5
OPTITRACKDATA_FROM_LINUX		GPIO7.6
DATAFORFILE_TO_LINUX 			GPIO7.17


Unused and can be used for flags:
GPIO7.30
GPIO7.31


*/

#define IMAGE_TO_LINUX_FLAG7_5 5

#define OPTITRACKDATA_FROM_LINUX_FLAG7_6 6

#define DATA_FROM_LINUX_FLAG2_0 0

#define LVDATA_FROM_LINUX_FLAG2_2 2

#define DATA_TO_LINUX_FLAG2_1 1

#define LVDATA_TO_LINUX_FLAG2_3 3

#define DATAFORFILE_TO_LINUX_FLAG7_17 17

#define ASTAR_COMMAND_FLAG2_4 4
 
#define ASTAR_FAILED_FLAG8_0 0

#define ASTAR_DONE_FLAG8_23 23

#define LINUX_BOOTED_FLAG7_3 3

// 0x80007400 + 3*176*144
//#define THRES_IMAGE_MEM 0x80019D00

#define LINUX_COMSIZE 256

#define NUM_FLOATS_FROM_LINUX_TO_DSP 20
#define NUM_FLOATS_TO_LINUX_FROM_DSP 20

#define OPTITRACKDATASIZE 3+2 // x, y, heading, trackableID, framecount

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

