#include <coecsl.h>
#include "i2c.h"
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Clock.h>

#define I2C_ACCESS_TIMEOUT 100
#define I2C_TIMEOUT 50

int CompassNew;

unsigned char Compassbuff[4];
int I2Cbusy = 0;


volatile char I2Ctxbuffer[64];
#pragma DATA_ALIGN(I2Ctxbuffer,64);





volatile int getIRs_err = 0;
volatile int getI2C_err = 0;

unsigned long task_state = 0;

extern unsigned long noi2c;
extern unsigned long timeint;




//---------------------------------------------------------------------------
// Example: InitI2CGpio: 
//---------------------------------------------------------------------------
// This function initializes GPIO pins to function as I2C pins
//
// Each GPIO pin can be configured as a GPIO pin or up to 3 different
// peripheral functional pins. By default all pins come up as GPIO
// inputs after reset.  
// 
// Caution: 
// Only one GPIO pin should be enabled for SDAA operation.
// Only one GPIO pin shoudl be enabled for SCLA operation. 
// Comment out other unwanted lines.

void InitI2CGpio(void)
{

   EALLOW;
/* Enable internal pull-up for the selected pins */
// Pull-ups can be enabled or disabled disabled by the user.  
// This will enable the pullups for the specified pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPBPUD.bit.GPIO32 = 0;    // Enable pull-up for GPIO32 (SDAA)
	GpioCtrlRegs.GPBPUD.bit.GPIO33 = 0;	   // Enable pull-up for GPIO33 (SCLA)

/* Set qualification for selected pins to asynch only */
// This will select asynch (no qualification) for the selected pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPBQSEL1.bit.GPIO32 = 3;  // Asynch input GPIO32 (SDAA)
    GpioCtrlRegs.GPBQSEL1.bit.GPIO33 = 3;  // Asynch input GPIO33 (SCLA)

/* Configure SCI pins using GPIO regs*/
// This specifies which of the possible GPIO pins will be I2C functional pins.
// Comment out other unwanted lines.

	GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 1;   // Configure GPIO32 for SDAA operation
	GpioCtrlRegs.GPBMUX1.bit.GPIO33 = 1;   // Configure GPIO33 for SCLA operation
	
    EDIS;
}



int i2c_stdsend(int I2Caddress, unsigned char *buf, int length){
	
	unsigned long starttime;
	int i;

	// Wait for Busy Bit.  Reset I2C if timed out.
	starttime = Clock_getTicks();
	while ( ((I2caRegs.I2CSTR.all & 0x1000) == 0x1000) || (I2Cbusy == 1) ){
		Task_yield();
		if ( (Clock_getTicks() - starttime) > I2C_ACCESS_TIMEOUT ) {
			I2caRegs.I2CSTR.all = 0x1000; 		    
	    	I2caRegs.I2CMDR.all = 0x0; // reset I2C
	    	return 1;
		}
	}

	// setup i2c
	I2Cbusy = 1;
	I2caRegs.I2CMDR.all = 0x0; // reset I2C
	I2caRegs.I2CSAR = I2Caddress;
	I2caRegs.I2CCNT = length;
	I2caRegs.I2CMDR.all = 0x2E20;           // 8 bits/data byte, free data format disabled, START byte disabled,
			                                // I2C module enabled, DLB disabled, nonrepeat mode,
			                                // 7-bit addressing, transmitter mode, MST, STP condition,
			                                // STT condition

	// send data
	for (i = 0; i < length; i++) {
		starttime = Clock_getTicks();
		I2caRegs.I2CDXR = buf[i];			// Trasmit data shifted to I2CXSR immediately

		// Wait for XRDY bit to equal 1.  Flag not busy and return.
		while ( (I2caRegs.I2CSTR.all & 0x10) == 0x0 ) {
			Task_yield();
			if ( (Clock_getTicks() - starttime) > I2C_TIMEOUT ) {
				I2caRegs.I2CSTR.all = 0x1000; 		    
				I2caRegs.I2CMDR.all = 0x0; // reset I2C
				I2Cbusy = 0;
				return 1;
			}
		}
	}
	I2Cbusy = 0;
	return 0;
}

int i2c_stdrecv(int I2Caddress, unsigned char addr, unsigned char *buf, int length)
{
	unsigned long starttime;
	int i;

	// Wait for Busy Bit.  Reset I2C if timed out.
	starttime = Clock_getTicks();
	while ( ((I2caRegs.I2CSTR.all & 0x1000) == 0x1000) || (I2Cbusy == 1) ){
		Task_yield();
		if ( (Clock_getTicks() - starttime) > I2C_ACCESS_TIMEOUT ) {
			I2caRegs.I2CSTR.all = 0x1000; 		    
	    	I2caRegs.I2CMDR.all = 0x0; // reset I2C
	    	return 1;
		}
	}

	// send address byte
	I2Cbusy = 1;
	I2caRegs.I2CMDR.all = 0x0; 		// reset I2C
	I2caRegs.I2CCNT = 0x1;  		// Receive one data byte
	I2caRegs.I2CSAR = I2Caddress;	// Set address
	I2caRegs.I2CMDR.all = 0x2620;	// 8 bits/data byte, free data format disabled, START byte disabled,
			                        // I2C module enabled, DLB disabled, nonrepeat mode,
			                        // 7-bit addressing, transmitter mode, MST, STP condition auto cleared,
			                        // STT condition
	I2caRegs.I2CDXR = addr;			// Set transmit register

	starttime = Clock_getTicks();
	while ( (I2caRegs.I2CSTR.all & 0x10) == 0x0 ) {
		Task_yield();
		if ((Clock_getTicks() - starttime) > I2C_TIMEOUT) {
			I2caRegs.I2CSTR.all = 0x1000; 		    
			I2caRegs.I2CMDR.all = 0x0; // reset I2C
			I2Cbusy = 0;
			return 1;
		}
	}

	// recieve data
	I2caRegs.I2CCNT = length;
	I2caRegs.I2CMDR.all = 0x2C20;	// 8 bits/data byte, free data format disabled, START byte disabled,
			                        // I2C module enabled, DLB disabled, nonrepeat mode,
			                        // 7-bit addressing, receiver mode, MST, STP condition,
			                        // STT condition

	for (i = 0; i < length; i++) {
		starttime = Clock_getTicks();
		// Wait for RRDY bit to equal 1 then read register
		while ( (I2caRegs.I2CSTR.all & 0x08) == 0x0 ) {
			Task_yield();
			if ( (Clock_getTicks() - starttime) > I2C_TIMEOUT ) {
				I2caRegs.I2CSTR.all = 0x1000; 		    
				I2caRegs.I2CMDR.all = 0x0; // reset I2C
				I2Cbusy = 0;
				return 1;
			}
		}
		buf[i] = I2caRegs.I2CDRR;
	}
	I2Cbusy = 0;
	return 0;
}


// initial I2C0 to communicate at 100Kbit per second
void Init_i2c(void) {
	
	
	// I2C code
	I2caRegs.I2CMDR.all = 0x0;  	// put in reset state
	I2caRegs.I2COAR = 0x0; 			// Master device so no address
	I2caRegs.I2CIER.all = 0x0;  	// No Interrupts
	I2caRegs.I2CSTR.all = 0x301F; 	// clear all possible ints and stats
	while( (I2caRegs.I2CSTR.all & 0x1000) == 0x1000) {
    	I2caRegs.I2CSTR.all = 0x1000;
    }
    I2caRegs.I2CPSC.all = 0x0;		// No prescaler
	I2caRegs.I2CCLKL = 0x400;		// Set SCL to ~70kHz
	I2caRegs.I2CCLKH = 0x400;
	I2caRegs.I2CCNT = 0x0;          // Init count to zero

}


void compassTask(void) {

	volatile int CompassTemp=0;

	Task_sleep(1000);



	while (1) {
		//GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
		//GpioDataRegs.GPASET.bit.GPIO31 = 1;
		if ((task_state%10)==0){
			//compass send or receive
			if ((task_state%20)==0){
				i2c_stdrecv(0x21,0,Compassbuff,2);
				CompassTemp = (((int) Compassbuff[0]) << 8) + Compassbuff[1];
				CompassNew = CompassTemp;
			} else {
				Compassbuff[0] = 'A';
				i2c_stdsend(0x21,Compassbuff,1);
			}
		}

		//GpioDataRegs.GPATOGGLE.bit.GPIO31 = 1;
		task_state++;
		Task_sleep(10);
	}

}


