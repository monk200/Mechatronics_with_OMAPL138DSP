/*
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/**
 *
 *  \brief  Template application tasks file:
 *          This template application exercises multiple tasks and
 *          peripherals. The different task functions are run under
 *          separate Tasks in TI BIOS.
 *          The appTasksCreate function creates the different tasks.
 *          More tasks can be added in this function as required.
 */


/* Standard header files */
#include <string.h>

/* XDCtools Header files */
#include <xdc/std.h>
#include <xdc/cfg/global.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Error.h>


/* BIOS Header files */
#include <ti/sysbios/BIOS.h>
#include <xdc/runtime/Error.h>

/* TI-RTOS Header files */
#include <ti/drv/spi/SPI.h>
#include <ti/drv/spi/soc/SPI_soc.h>
#include <ti/drv/spi/src/SPI_osal.h>

/* GPIO Header files */
#include <ti/drv/gpio/GPIO.h>
#include <ti/drv/gpio/soc/GPIO_v1.h>

#include <ti/board/board.h>

#ifdef SPI_DMA_ENABLE
#include <ti/osal/CacheP.h>

/* EDMA3 Header files */
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/sdo/edma3/rm/sample/bios6_edma3_rm_sample.h>
#endif

/* McSPI Test Header Files*/
#include "MCSPI_Test_Ryan.h"
#include "mcbspAsSpi_com.h"



/* Local template app header file */
#include "app.h"


extern float uleft;
extern float uright;
/**********************************************************************
 ************************** Function prototypes ***********************
 **********************************************************************/
void biosTaskCreate(ti_sysbios_knl_Task_FuncPtr taskFunctionPtr,
                    char *taskName, int taskPriority, int stackSize);

/* Task functions */
void gpio_toggle_led_task(UArg arg0, UArg arg1);
void uart_task(UArg arg0, UArg arg1);
void spi_test_task(UArg arg0, UArg arg1);
void i2c_eeprom_read_and_display_task(UArg arg0, UArg arg1);
/* Add any additional task function prototypes here */

//MCSPI Test Ryan
void McSPISetUp(uint32_t base_address, uint8_t InterruptMode);
void McSPIStartTransfer(uint32_t base_address, uint8_t InterruptMode);
void McSPIInitializeBuffers(void);
void sampleDelay(int32_t delay);
void McSPIMSPolledModeTransfer(uint32_t base_address);
void McSPIMSInterruptModeTransfer(uint32_t base_address);
//End MCSPI Test Ryan




/**********************************************************************
 ************************** Global Variables **************************
 **********************************************************************/
volatile uint32_t g_endTestTriggered = 0;


/*McSPI Test Ryan GV's   */
float pwm1 = 0;
float dec1 = 0;
float u = 0;

uint32_t dataToSlave;


uint8_t           lastTransferComplete = 1;
uint32_t          gChNum  = 0;
uint32_t           length = 0;
uint32_t           dataFromSlave;
uint32_t           rxBuffer[McSPI_DATA_COUNT + 10];
uint32_t           txBuffer[McSPI_DATA_COUNT + 10];

uint32_t          *p_rx;
uint32_t          *p_tx;

volatile uint8_t  flagTx    = 0;
volatile uint8_t  flagRx    = 0;
volatile uint8_t  flagSlvTx = 0;
volatile uint8_t  flagSlvRx = 0;
char              gMainMenuOption = '1';


//uint32_t           CS0dataToSend[McSPI_DATA_COUNT+10];
//uint32_t           CS1dataToSend[McSPI_DATA_COUNT+10];
//uint32_t           CS2dataToSend[McSPI_DATA_COUNT+10];
//uint32_t           CS3dataToSend[McSPI_DATA_COUNT+10];
//uint32_t           CS0dataReceived[McSPI_DATA_COUNT+10];
//uint32_t           CS1dataReceived[McSPI_DATA_COUNT+10];
//uint32_t           CS2dataReceived[McSPI_DATA_COUNT+10];
//uint32_t           CS3dataReceived[McSPI_DATA_COUNT+10];
mcbspL138_com CS0dataToSend;
mcbspL138_com CS1dataToSend;
mcbspL138_com CS2dataToSend;
mcbspL138_com CS3dataToSend;

mcbsp28x_com CS0dataReceived;
mcbsp28x_com CS1dataReceived;
mcbsp28x_com CS2dataReceived;
mcbsp28x_com CS3dataReceived;

uint8_t           CS0size = McSPI_DATA_COUNT;
uint8_t           CS1size = McSPI_DATA_COUNT;
uint8_t           CS2size = McSPI_DATA_COUNT;
uint8_t           CS3size = McSPI_DATA_COUNT;

uint32_t RyanTestVar = 0;

//End McSPI Test Ryan


int Dan_toggle = 0;
void Dan1(void) {
    if (Dan_toggle == 0) {
        GPIO_write(TEST_LED_GPIO_INDEX, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED0, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED1, GPIO_PIN_VAL_HIGH);
        GPIO_write(GPIO_DAN_LED2, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED3, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED5, GPIO_PIN_VAL_HIGH);
        Dan_toggle = 1;
    } else {
        GPIO_write(TEST_LED_GPIO_INDEX, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED0, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED1, GPIO_PIN_VAL_LOW);
        GPIO_write(GPIO_DAN_LED2, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED3, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_LOW);
//       GPIO_write(GPIO_DAN_LED5, GPIO_PIN_VAL_LOW);
        Dan_toggle = 0;
    }

}


int Dan2_toggle = 0;
void Dan2(void) {
    if (Dan2_toggle == 0) {
//        GPIO_write(TEST_LED_GPIO_INDEX, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED0, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED1, GPIO_PIN_VAL_HIGH);
//       GPIO_write(GPIO_DAN_LED2, GPIO_PIN_VAL_HIGH);
        GPIO_write(GPIO_DAN_LED3, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_HIGH);
//        GPIO_write(GPIO_DAN_LED5, GPIO_PIN_VAL_HIGH);
        Dan2_toggle = 1;
    } else {
//        GPIO_write(TEST_LED_GPIO_INDEX, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED0, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED1, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED2, GPIO_PIN_VAL_LOW);
        GPIO_write(GPIO_DAN_LED3, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED4, GPIO_PIN_VAL_LOW);
//        GPIO_write(GPIO_DAN_LED5, GPIO_PIN_VAL_LOW);
        Dan2_toggle = 0;
    }

}




//McSPI Test Ryan Function Definitions

void sampleDelay(int32_t delay)
{
    volatile int32_t i, j;

    for (i = 0; i < delay; i++)
    {
        for (j = 0; j < 100; j++) ;
    }
}//also unused by mcspi but remains for its debugging usefulness

void McSPISetUp(uint32_t base_address, uint8_t InterruptMode)
{


//By default, this function sets up all 4 channels for the given base address

    uint8_t first_channel = 0;
    uint8_t last_channel = 3;
    int ch_iter = 0;

    uint32_t status = 1U; // FALSE

    /* Reset the McSPI instance.*/
    McSPIReset(base_address);

    /* CLOCKACTIVITY bit - OCP and Functional clocks are maintained           */
    /* SIDLEMODE     bit - Ignore the idle request and configure in normal mode
     */
    /* AUTOIDLE      bit - Disable (OCP clock is running free, no gating)     */
    MCSPISysConfigSetup(base_address, MCSPI_CLOCKS_OCP_ON_FUNC_ON,
                        MCSPI_SIDLEMODE_NO, MCSPI_WAKEUP_DISABLE,
                        MCSPI_AUTOIDLE_OFF);

    /* Enable chip select pin.*/
    McSPICSEnable(base_address);

    /* Enable master mode of operation.*/
    McSPIMasterModeEnable(base_address);

    //Iterate over all channels b/w first and last channel to set up each of them.
    for(ch_iter = first_channel; ch_iter<=last_channel; ch_iter++){
        /* Perform the necessary configuration for master mode. */
        status = McSPIMasterModeConfig(base_address, MCSPI_MULTI_CH,
                                       MCSPI_TX_RX_MODE,
                                       MCSPI_DATA_LINE_COMM_MODE_6,     //mode 6 means that D0 is transmit and D1 is recieve
                                       ch_iter);

        if (0 == status)
        {
            //UARTConfigPuts(uartBaseAddr,"\nMcSPI1 - Communication not supported by SPIDAT[1:0]",-1);
        }

        /* Configure the McSPI bus clock depending on clock mode. */
        McSPIClkConfig(base_address, MCSPI_IN_CLK, MCSPI_OUT_FREQ, ch_iter,
                       MCSPI_CLK_MODE_0);

        /* Configure the word length.*/
        McSPIWordLengthSet(base_address, MCSPI_WORD_LENGTH(32), ch_iter);

        /* Set polarity of SPIEN to low.*/
        McSPICSPolarityConfig(base_address,
                              (MCSPI_CH0CONF_EPOL_ACTIVELOW <<
                               MCSPI_CH0CONF_EPOL_SHIFT), ch_iter);

        /* Disable the transmitter FIFO of McSPI peripheral.*/
        McSPITxFIFOConfig(base_address, MCSPI_TX_FIFO_DISABLE, ch_iter);

        /* Disable the receiver FIFO of McSPI peripheral.*/
        McSPIRxFIFOConfig(base_address, MCSPI_RX_FIFO_DISABLE, ch_iter);

        //Enable the Channel
        McSPIChannelEnable(base_address, ch_iter);
    }
     //Clear the Interrupt
        McSPIIntStatusClear(base_address,0x04);   //Clear all ch0 interrupt flags
    if(InterruptMode){
         //Enable the Interrupt
        McSPIIntEnable(base_address, 0x04);         //enable only the interrupt on CS0 if InterruptMode is chosenf
    }


}


void McSPIInitializeBuffers(void)
{
//    CS0dataToSend[0] = 0x01; //pwmnum
//    CS0dataToSend[1] = (short)pwm1>>8; //MSB
//    CS0dataToSend[2] = ((short)pwm1); //LSB
//    CS0dataToSend[3] = ((short)dec1); //LSB of Dec1 which is the actual value
//

    //Setting the data that should be sent to f28335.

    CS0dataToSend.data.validcode = VALID_67XTO28X;
    CS0dataToSend.data.flags = 1;
    CS0dataToSend.data.PWM[0] =uleft;  //left
    CS0dataToSend.data.PWM[1] =uright; // right
    CS0dataToSend.data.PWM[2] =7.0;  // 7 is RCservo approx half way
    CS0dataToSend.data.PWM[3] =7.0;
    CS0dataToSend.data.PWM[4] =7.0;
    CS0dataToSend.data.PWM[5] =7.0;
    CS0dataToSend.data.PWM[6] =7.0;
    CS0dataToSend.data.PWM[7] =7.0;
    CS0dataToSend.data.PWM[8] =7.0;
    CS0dataToSend.data.PWM[9] =7.0;
    CS0dataToSend.data.DAC[0]=1.1;
    CS0dataToSend.data.DAC[1]=1.2;
    CS0dataToSend.data.DAC[2]=CS0dataReceived.data.ADC[1]*3.0/4095.0;
    CS0dataToSend.data.DAC[3]=CS0dataReceived.data.ADC[3]*3.0/4095.0;

//    CS0dataToSend.darray[0] = 0xAAAA5555;      //validation code
//    CS0dataToSend.darray[1] = 0x00000001;      //flag
//    CS0dataToSend.darray[2] = 2;               //PWM1
//    CS0dataToSend.darray[3] = 3;               //PWM2
//    CS0dataToSend.darray[4] = 4;               //PWM3
//    CS0dataToSend.darray[5] = 5;               //PWM4
//    CS0dataToSend.darray[6] = 6;               //PWM5
//    CS0dataToSend.darray[7] = 7;               //PWM6
//    CS0dataToSend.darray[8] = 8;               //PWM7
//    CS0dataToSend.darray[9] = 9;               //PWM8
//    CS0dataToSend.darray[10] = 10;              //PWM9
//    CS0dataToSend.darray[11] = 11;              //PWM10
//    CS0dataToSend.darray[12] = 12;               //DAC1
//    CS0dataToSend.darray[13] = 13;               //DAC2
//    CS0dataToSend.darray[14] = CS0dataReceived.darray[7];               //DAC3
//    CS0dataToSend.darray[15] = CS0dataReceived.darray[9];               //DAC4

    int index;
    for (index = 0; index < McSPI_DATA_COUNT; index++){
        CS1dataToSend.darray[index]=CS0dataToSend.darray[index];
        CS2dataToSend.darray[index]=CS0dataToSend.darray[index];
        CS3dataToSend.darray[index]=CS0dataToSend.darray[index];
    }

//    uint32_t index = 0;
//
//    for (index = 0; index < McSPI_DATA_COUNT; index++)
//    {
//        /* Initialize the txBuffer McSPI1 with a known pattern of data */
//        txBuffer[index] = (uint8_t) index;
//        /* Initialize the rxBuffer McSPI1 with 0 */
//        rxBuffer[index] = (uint8_t) 0;
//    }
//    for (index = 0; index < McSPI_DATA_COUNT; index++)
//    {
//        /* Initialize the txBuffer McSPI1 with a known pattern of data */
//        txSlvBuffer[index] = (uint8_t) index;
//        /* Initialize the rxBuffer McSPI1 with 0 */
//        rxSlvBuffer[index] = 0;
//    }
}


void McSPIStartTransfer(uint32_t base_address, uint8_t InterruptMode)
{
    lastTransferComplete = 0;           //this flag ensures that mutiple transfers dont happen at once. set to zero at the start of a transfer.
    //Begin by putting all the CS0data into the TX and RX arrays
    int i=0;
    for(i=0; i<McSPI_DATA_COUNT; i++){
        txBuffer[i] = CS0dataToSend.darray[i];      //put the send data into the txBuffer
    }
    gChNum = 0;                                     //start on channel 0
    length = CS0size;                               //number of words to send
    if(InterruptMode){
        McSPIMSInterruptModeTransfer(base_address);
    }
    else{
        McSPIMSPolledModeTransfer(base_address);
    }
}
int32_t dummy = 0;
void McSPIMSPolledModeTransfer(uint32_t base_address){

    int i;
    uint32_t          channelStatus = 0;
    volatile uint32_t timeout1      = 0xFFFFU;


    p_tx    = txBuffer;
    p_rx    = rxBuffer;


    while (0 != length)
    {
                    //TIMEOUTS IN THE NEXT 2 FUNCTIONS WERE JUST USED AS BREAK STATEMENTS FOR ERRORS. THEY SHOULD BE TAKEN OUT.

        timeout1      = 0xFFFF;
        channelStatus = McSPIChannelStatusGet(base_address, gChNum);
        if (1 == (channelStatus & MCSPI_CH0STAT_RXS_MASK))              //if there is already a receive register, read it and clear the register, it is garbage data
        {
            dummy = McSPIReceiveData(base_address, 0);
            McSPIIntStatusClear(base_address,0x04);
        }
        McSPITransmitData(base_address, (uint32_t) (*p_tx++), gChNum);  //TRANSMISSION

        timeout1      = 0xFFFF;
        channelStatus = McSPIChannelStatusGet(base_address, gChNum);
        while (0 == (channelStatus & MCSPI_CH0STAT_RXS_MASK))           //as soon as the recieve register is ready, begin reading the data
        {
            channelStatus = 0;
            channelStatus = McSPIChannelStatusGet(base_address, gChNum);
            --timeout1;
            if (0 == timeout1)
            {
                while (1) ;
            }
        }
        *p_rx++ = McSPIReceiveData(base_address, 0);                    //*p_rx is a pointer to the location of rxBuffer. This line reads the data in from the RX register into the variable rxBuffer
        channelStatus = McSPIChannelStatusGet(base_address, gChNum);
        length--;
        McSPIIntStatusClear(base_address,0x05);
    }
    lastTransferComplete = 1;                                           //outside the while loop, we've finished with the transfer, make sure to set this flag so the next transfer can happen
    for(i=0;i<McSPI_DATA_COUNT;i++){
        CS0dataReceived.darray[i] = rxBuffer[i];                        //move data from rxBuffer into a relavant data structure.
    }
}


void McSPIMSInterruptModeTransfer(uint32_t base_address)
{
    uint32_t          channelStatus = 0;
    volatile uint32_t timeout1      = 0xFFFFU;
    p_tx    = txBuffer;
    p_rx    = rxBuffer;

    timeout1      = 0xFFFF;
    channelStatus = McSPIChannelStatusGet(base_address, gChNum);

    //wait while a transfer is still occurring.
    while (0 == (channelStatus & MCSPI_CH0STAT_TXS_MASK))
    {
        channelStatus = 0;
        channelStatus = McSPIChannelStatusGet(base_address, gChNum);
        --timeout1;
        if (0 == timeout1)
        {
            //Transfer Timeout Reached... Error occurring
            while (1) ;
        }
    }

    McSPIIntStatusClear(base_address,0x04);   //Clear the ch0 receive interrupt flags
    McSPIIntEnable(base_address, 0x04);         //enable only the receive interrupt on CS0
    McSPITransmitData(base_address, (uint32_t) (*p_tx++), gChNum);
}

