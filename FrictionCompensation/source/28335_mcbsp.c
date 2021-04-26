
#include <coecsl.h>
#include "28335_mcbsp.h"
#include "mcbsp_com.h"
#include "28335_spi.h"

long McBSPb_int_count = 0;
unsigned int nocomm = 0;

#pragma DATA_SECTION(TXBuff, ".dmaram")
mcbsp28x_com TXBuff;
int McBSPB_rdy = 1;
#pragma DATA_SECTION(RXBuff, ".dmaram")
mcbspL138_com RXBuff;

int McBSP_RecGoodData_ReadyTX = 0;

long McBSP_COMerr = 0;

int newOMAPdata = 0;
int PIVEL_enable = 1;
float mcbsp_vref = 0.0;
float mcbsp_turn = 0.0;
float mcbsp_pwm1 = 0.0;
float mcbsp_pwm2 = 0.0;
//float mcbsp_pwm3 = 0.0;
//float mcbsp_pwm4 = 0.0;
float mcbsp_dac1 = 0.0;
float mcbsp_dac2 = 0.0;

extern int switchstate;
extern unsigned long timeint;

void McBSP_TX_INTCH1_ISR(void) {
	McBSPB_rdy = 1;
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // To receive more interrupts from this PIE group, acknowledge this interrupt
}

void McBSP_RX_INTCH2_ISR(void) {

	McBSPb_int_count++;
	char tempbuff[30];
	int i;

	if (RXBuff.data.validcode == VALID_67XTO28X) {

		if (newOMAPdata == 0) {
			// This masking checks if the float values received are finite.  If NaN of INF, they are ignored.
			if (((*(unsigned long *)(&RXBuff.data.vref)) & 0xFF800000) != 0xFF800000) mcbsp_vref = RXBuff.data.vref;
			if (((*(unsigned long *)(&RXBuff.data.turn)) & 0xFF800000) != 0xFF800000) mcbsp_turn = RXBuff.data.turn;
			if (((*(unsigned long *)(&RXBuff.data.PWM[0])) & 0xFF800000) != 0xFF800000) mcbsp_pwm1 = RXBuff.data.PWM[0];
			if (((*(unsigned long *)(&RXBuff.data.PWM[1])) & 0xFF800000) != 0xFF800000) mcbsp_pwm2 = RXBuff.data.PWM[1];
			if (((*(unsigned long *)(&RXBuff.data.PWM[2])) & 0xFF800000) != 0xFF800000) RCSERVO_out(EPWM3, RXBuff.data.PWM[2]);
			if (((*(unsigned long *)(&RXBuff.data.PWM[3])) & 0xFF800000) != 0xFF800000) RCSERVO_out(EPWM3B, RXBuff.data.PWM[3]);
			if (((*(unsigned long *)(&RXBuff.data.PWM[4])) & 0xFF800000) != 0xFF800000) RCSERVO_out(EPWM4, RXBuff.data.PWM[4]);
			if (((*(unsigned long *)(&RXBuff.data.PWM[5])) & 0xFF800000) != 0xFF800000) RCSERVO_out(EPWM4B, RXBuff.data.PWM[5]);
			if (((*(unsigned long *)(&RXBuff.data.PWM[6])) & 0xFF800000) != 0xFF800000) RCSERVO_out(EPWM5, RXBuff.data.PWM[6]);
			if (((*(unsigned long *)(&RXBuff.data.DAC[0])) & 0xFF800000) != 0xFF800000) mcbsp_dac1 = RXBuff.data.DAC[0];
			if (((*(unsigned long *)(&RXBuff.data.DAC[1])) & 0xFF800000) != 0xFF800000) mcbsp_dac2 = RXBuff.data.DAC[1];

			if ((RXBuff.data.flags & FLAGL138_PICONTRL_MODE_BIT0)>0) {
				PIVEL_enable = 1;
			} else {
				PIVEL_enable = 0;
			}
			
//			writeDAC7564(mcbsp_dac1,mcbsp_dac2);  // removes 1ms delay from DAC echo
			
			newOMAPdata = 1;
		}
		if (RXBuff.data.flags & FLAGL138_NEWLCDLINE1_BIT1) {
			for (i=0;i<12;i++) {
				tempbuff[2*i] = RXBuff.data.lcdline1.array16[i] & 0xFF;
				tempbuff[2*i+1] = (RXBuff.data.lcdline1.array16[i] >> 8) & 0xFF;
			}
			//SendStr2_I2C(tempbuff,24);
			serial_send(&SerialC,tempbuff,24);
		}
		if (RXBuff.data.flags & FLAGL138_NEWLCDLINE2_BIT2) {
			for (i=0;i<12;i++) {
				tempbuff[2*i] = RXBuff.data.lcdline2.array16[i] & 0xFF;
				tempbuff[2*i+1] = (RXBuff.data.lcdline2.array16[i] >> 8) & 0xFF;
			}
			//SendStr2_I2C(tempbuff,24);
			serial_send(&SerialC,tempbuff,24);
		}
		
		nocomm = timeint;
	} else {
		McBSP_COMerr++;
	}


	McBSP_RecGoodData_ReadyTX = 1;
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // To receive more interrupts from this PIE group, acknowledge this interrupt

	EALLOW;
	DmaRegs.CH2.CONTROL.bit.RUN = 1;           // Start DMA Receive from McBSP-B
	EDIS;
}

