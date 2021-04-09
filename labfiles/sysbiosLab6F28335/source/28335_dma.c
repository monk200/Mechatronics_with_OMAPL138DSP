// Data used in F28335's DMA must be placed in L4 through L7 RAM
	// From project c file
		//#pragma DATA_SECTION(sdata, ".myram")
		//#pragma DATA_SECTION(rdata, ".myram")
		//Uint16 sdata[8];
		//Uint16 rdata[8];
	// From linker file
		//SECTIONS
		//{
   		//	.adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD
   		//	.myram			: > DMARAM,		PAGE = 1
		//}
	// From BIO MEM
		// L1SARAM: base = 0x009000, len = 0x6c00, heap = 0x0600
		// DMARAM:  base = 0x00fc00, len = 0x0400, heap = 0x0200

#include "28335_dma.h"
#include "mcbsp_com.h"


// Init_dma_mcbspTX
// Set up DMA for sending 6 (32 bits) transfers
// pass an array's starting address say (Uint32)(&myarray[0])
void init_dma_mcbsp(Uint32 src_address,Uint32 dst_address)
{
		
	EALLOW;
	  
	  SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 1;		// Enable clock to DMA
	  
	  DmaRegs.DMACTRL.bit.HARDRESET = 1;		// Put DMA into reset state
	  DmaRegs.DEBUGCTRL.bit.FREE = 1;			// Allow DMA to run free on emulation suspend
	  
	  asm(" NOP");						   // Only 1 NOP needed per Design
	
	  // Channel 1, McBSPB transmit
	  DmaRegs.CH1.BURST_SIZE.all = 1;		// 2 word/burst
	  DmaRegs.CH1.SRC_BURST_STEP = 0xFFFF;		// increment 1 16-bit addr. btwn words
	  DmaRegs.CH1.DST_BURST_STEP = 1;		// increment 1 16-bit addr. btwn words
	  DmaRegs.CH1.TRANSFER_SIZE = NUM_28XCOMWORDS-1;		// Interrupt every 6 bursts/transfer
	  DmaRegs.CH1.SRC_TRANSFER_STEP = 3;	// Move to next word in buffer after each word in a burst
	  DmaRegs.CH1.DST_TRANSFER_STEP = 0xFFFF;	// Go back to DXR2
	  DmaRegs.CH1.SRC_ADDR_SHADOW = src_address+1;	// Start address = buffer
	  DmaRegs.CH1.SRC_BEG_ADDR_SHADOW = src_address+1;		    // Not needed unless using wrap function
	  DmaRegs.CH1.DST_ADDR_SHADOW = (Uint32)(&McbspbRegs.DXR2.all);		// Start address = McBSPA DXR2
	  DmaRegs.CH1.DST_BEG_ADDR_SHADOW = (Uint32)(&McbspbRegs.DXR2.all);	// Not needed unless using wrap function
	  DmaRegs.CH1.CONTROL.bit.SYNCCLR = 1;		// Clear sync flag
	  DmaRegs.CH1.CONTROL.bit.ERRCLR = 1;		// Clear sync error flag
	  DmaRegs.CH1.DST_WRAP_SIZE = 0xFFFF;		// Put to maximum - don't want destination wrap
	  DmaRegs.CH1.SRC_WRAP_SIZE = 0xFFFF;		// Put to maximum - don't want source wrap
	  DmaRegs.CH1.MODE.bit.ONESHOT = 0;			// Oneshot disabled
	  DmaRegs.CH1.MODE.bit.CONTINUOUS = 0;		// Continous disabled
	  DmaRegs.CH1.MODE.bit.SYNCE = 0;         		// No sync signal
	  DmaRegs.CH1.MODE.bit.SYNCSEL = 0;       		// No sync signal
	  DmaRegs.CH1.MODE.bit.DATASIZE = 0;			// 16-bit data size transfers
	  DmaRegs.CH1.MODE.bit.CHINTE = 1;			// Enable channel interrupt
	  DmaRegs.CH1.MODE.bit.CHINTMODE = 1;		// Interrupt at end of transfer
	  DmaRegs.CH1.MODE.bit.PERINTE = 1;			// Enable peripheral interrupt event
	  DmaRegs.CH1.MODE.bit.PERINTSEL = DMA_MXREVTB;		// Peripheral interrupt select = McBSP-B Transmit Buffer Empty
	  DmaRegs.CH1.CONTROL.bit.PERINTCLR = 1;  	// Clear any spurious interrupt flags




	 
	  // Channel 2, McBSPB Receive
	  DmaRegs.CH2.BURST_SIZE.all = 1;		// 2 words/burst
	  DmaRegs.CH2.SRC_BURST_STEP = 0xFFFF;		// Decrement 1 to DDR2
	  DmaRegs.CH2.DST_BURST_STEP = 1;	    // Increment 1 16-bit addr. btwn words
	  DmaRegs.CH2.TRANSFER_SIZE = NUM_L138COMWORDS-1;		// Interrupt every 4 bursts/transfer
	  DmaRegs.CH2.SRC_TRANSFER_STEP = 1;	// Increment  back to DRR1
	  DmaRegs.CH2.DST_TRANSFER_STEP = 1;	// Move to next word in buffer after each word in a burst
	  DmaRegs.CH2.SRC_ADDR_SHADOW = (Uint32) &McbspbRegs.DRR1.all;			// Start address = McBSPA DRR
	  DmaRegs.CH2.SRC_BEG_ADDR_SHADOW = (Uint32) &McbspbRegs.DRR1.all;		// Not needed unless using wrap function
	  DmaRegs.CH2.DST_ADDR_SHADOW = dst_address;		// Start address = Receive buffer (for McBSP-A)
	  DmaRegs.CH2.DST_BEG_ADDR_SHADOW = dst_address;	// Not needed unless using wrap function
	  DmaRegs.CH2.CONTROL.bit.SYNCCLR = 1;		// Clear sync flag
	  DmaRegs.CH2.CONTROL.bit.ERRCLR = 1;		// Clear sync error flag
	  DmaRegs.CH2.DST_WRAP_SIZE = 0xFFFF;		// Put to maximum - don't want destination wrap
	  DmaRegs.CH2.SRC_WRAP_SIZE = 0xFFFF;		// Put to maximum - don't want source wrap
	  
      DmaRegs.CH2.MODE.bit.ONESHOT = 0;			// Oneshot disabled
	  DmaRegs.CH2.MODE.bit.CONTINUOUS = 0;		// Continous disabled
	  DmaRegs.CH2.MODE.bit.SYNCE = 0;         		// No sync signal
	  DmaRegs.CH2.MODE.bit.SYNCSEL = 0;       		// No sync signal
	  DmaRegs.CH2.MODE.bit.DATASIZE = 0;			// 16-bit data size transfers
	  	  
	  DmaRegs.CH2.MODE.bit.CHINTE = 1;			// Enable channel interrupt
	  DmaRegs.CH2.MODE.bit.CHINTMODE = 1;		// Interrupt at end of transfer
	  DmaRegs.CH2.MODE.bit.PERINTE = 1;			// Enable peripheral interrupt event
	  DmaRegs.CH2.MODE.bit.PERINTSEL = DMA_MREVTB;	    // Peripheral interrupt select = McBSP-B Receive Buffer Full
	  DmaRegs.CH2.CONTROL.bit.PERINTCLR = 1;  	// Clear any spurious interrupt flags
	   	
	EDIS;
  
  	PieCtrlRegs.PIEIER7.bit.INTx1 = 1;			// Enable DMA CH1 interrupt in PIE
  	PieCtrlRegs.PIEIER7.bit.INTx2 = 1;			// Enable DMA CH2 interrupt in PIE

	IFR &= ~PIEACK_GROUP7;						// Make sure no ints pending on block 7
	IER |= PIEACK_GROUP7;						// Enable CPU Interrupt
	
	IFR &= ~M_INT7;  // Make sure no ints pending.
	IER |= M_INT7; // Enable CPU Interrupt for DMA CH1 that is set to McBSP TX
}




void start_dma (void)
{
	EALLOW;
  
	DmaRegs.CH1.CONTROL.bit.RUN = 1;	         // Start DMA Transmit from McBSP-B

	EDIS;
}



/*
// INT7.1 DMA Ch1 - transmit
void local_D_INTCH1_ISR(void)
{
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // To receive more interrupts from this PIE group, acknowledge this interrupt
}

// INT7.2 DMA Ch2 - receive
void local_D_INTCH2_ISR(void)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7; // To receive more interrupts from this PIE group, acknowledge this interrupt
	
	int i;
	for (i=0; i<8; i++){
       sdata[i] += 1;      	   
	}
}

*/

