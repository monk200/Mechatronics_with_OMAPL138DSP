/*
 *  ======== main.c ========
 */

#include <coecsl.h>
#include "28335_dma.h"
#include "28335_spi.h"
#include "28335_inits.h"
#include "mcbsp_com.h"
#include "i2c.h"
#include "user_PIFuncs.h"
#include "user_include.h"



#include <xdc/std.h>

#include <xdc/runtime/Error.h>
#include <xdc/runtime/System.h>

#include <ti/sysbios/BIOS.h>

#include <ti/sysbios/knl/Task.h>



extern Uint16 RamfuncsLoadStart;
extern Uint16 RamfuncsLoadEnd;
extern Uint16 RamfuncsRunStart;


void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    {
       *DestAddr++ = *SourceAddr++;
    }
    return;
}


void updateData(void);
void sendData(void);

extern volatile int new_irdata_i2c;
extern int adc1_i2c;
extern int adc2_i2c;
extern int adc3_i2c;
extern int adc4_i2c;
extern int adc5_i2c;
extern int adc6_i2c;
extern int adc7_i2c;
extern int adc8_i2c;
extern int CompassNew;
extern int ir1_i2c,ir2_i2c,ir3_i2c,ir4_i2c,ir5_i2c;

extern int SPIenc_state;
extern long SPIenc1_reading;
extern long SPIenc2_reading;
extern long SPIenc3_reading;
extern long SPIenc4_reading;

extern unsigned int nocomm;
extern int newOMAPdata;
extern int PIVEL_enable;
extern float mcbsp_vref;
extern float mcbsp_turn;
extern float mcbsp_pwm1;
extern float mcbsp_pwm2;
extern float mcbsp_dac1;
extern float mcbsp_dac2;
extern long McBSP_COMerr;
extern int McBSP_RecGoodData_ReadyTX;
extern long McBSPb_int_count;
extern int McBSPB_rdy;
extern mcbsp28x_com TXBuff;
extern mcbspL138_com RXBuff;

unsigned long timeint = 0;
unsigned long noi2c = 0;
int toggleUSonic = 1;

float gyro_x = 0;
float gyro_y = 0;

float Enc1_rad = 0; // Left motor encoder
float Enc2_rad = 0; // Right motor encoder
float Enc3_rad = 0;
float Enc4_rad = 0;

int switchstate = -2;

int newF28335_Extra = 0;
float F28335_Extra1 = 0.0;
float F28335_Extra2 = 0.0;
float F28335_Extra3 = 0.0;
float F28335_Extra4 = 0.0;

int raw_adc_A0 = 0; // ADC A0 - Gyro_X -400deg/s to 400deg/s  Pitch
int raw_adc_A1 = 0; // ADC A1 - Gyro_4X -100deg/s to 100deg/s  Pitch
int raw_adc_A2 = 0; // ADC A2 -    Gyro_4Z -100deg/s to 100deg/s  Yaw
int raw_adc_A3 = 0; // ADC A3 - Gyro_Z -400deg/s to 400 deg/s  Yaw
int raw_adc_A4 = 0; // ADC A4 - Analog IR1
int raw_adc_A5 = 0; // ADC A5 -    Analog IR2
int raw_adc_A6 = 0; // ADC A6 - Analog IR3
int raw_adc_A7 = 0; // ADC A7 - Analog IR4
int raw_adc_B0 = 0; // ADC B0 - External ADC Ch4 (no protection circuit)
int raw_adc_B1 = 0; // ADC B1 - External ADC Ch1
int raw_adc_B2 = 0; // ADC B2 - External ADC Ch2
int raw_adc_B3 = 0; // ADC B3 - External ADC Ch3
int raw_adc_B4 = 0; // ADC B4 - USONIC1
int raw_adc_B5 = 0; // ADC B5 - USONIC2
int raw_adc_B6 = 0;
int raw_adc_B7 = 0;


float omap_vref = 0;
float omap_turn = 0;
float omap_pwm1 = 0;
float omap_pwm2 = 0;
float omap_dac1 = 0;
float omap_dac2 = 0;
int omap_PIVEL_enable = 0;

eqep_t enc1;
eqep_t enc2;
float value_enc1 = 0;
float value_enc2 = 0;

unsigned char dogReset = 0;

extern float v1;
extern float v2;





/*
 *  ======== main ========
 */
Int main()
{ 
    // disable interrupts
    DINT;
    IER = 0x0000;
    IFR = 0x0000;

    unsigned long delay;
    // load code from flash memory into ram

    MemCopy(&RamfuncsLoadStart,&RamfuncsLoadEnd,&RamfuncsRunStart);

    // initialize system (clocks, etc.)
    InitSysCtrl();
//    InitPll(PLL,2);

    // Initialize flash memory for 3 wait states.  Programmers Note:  We modified TI's default function to 3 wait states
    InitFlash();

    // power-up ADCs
    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;
    for (delay = 1000000L; delay; delay--) nop();
    AdcRegs.ADCTRL3.bit.ADCPWDN = 1;
    for (delay = 1000L; delay; delay--) nop();

    // reconfigure clocks
    EALLOW;
    SysCtrlRegs.HISPCP.all = 0x0000;
    SysCtrlRegs.LOSPCP.all = 0x0000;
    EDIS;


    //  Init and zero encoders
    init_EQEP(&enc1, EQEP1, 3000, 1, 0.0);
    init_EQEP(&enc2, EQEP2, 3000, -1, 0.0);
    EQep1Regs.QPOSCNT = 0;
    EQep2Regs.QPOSCNT = 0;

    // Initialize PWMs
    init_PWM(EPWM1);
    init_PWM(EPWM2);
    init_PWM_AS_RCSERVO(EPWM3B);  // sets up EPWM3A and EPWM3B for RCservo
    init_PWM_AS_RCSERVO(EPWM4B); // sets up EPWM4A and EPWM4B for RCservo
    init_PWM_AS_RCSERVO(EPWM5);  // sets up EPWM5A for RCservo

    // System initializations
    pre_init();

    // initialize serial port A to 115200 baud
    init_serial(&SerialA,115200,NULL);
    // initialize serial port B to 57600 baud
    init_serial(&SerialB,57600,NULL);
    // initialize serial port C to 19200 baud
    init_serial(&SerialC,19200,NULL);

    EALLOW;  // set up LED GPIOs
        GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;
        GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
        GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;
        GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;
        GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
        GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;
        GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;
        GpioDataRegs.GPBSET.bit.GPIO34 = 1;
        GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;

        // set up GPIO3 for amp enable or disable
        GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0;
        GpioDataRegs.GPACLEAR.bit.GPIO3 = 1;
        GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;

    EDIS;

    init_dma_mcbsp( (Uint32)&TXBuff.darray[0],(Uint32)&RXBuff.darray[0]);
    InitMcbspbGpio();
    InitMcbspb();
    InitMcbspb32bit();
    init_SPI();
    InitI2CGpio();
    Init_i2c();

    // Add your inits here
    // Configure ADC (see SPRU060B)
    AdcRegs.ADCMAXCONV.all = 7;       // Convert 8 channels in SEQ1 (0-4)
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 1;  // Set up simultaneous conversion mode
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;   // Cascaded mode
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0; // Setup ADCINA0 as 1st SEQ conv.
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 1; // Setup ADCINA1 as 2nd SEQ conv.
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 2; // Setup ADCINA2 as 3rd  SEQ conv.
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 3; // Setup ADCINA3 as 4th  SEQ conv.
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 4; // Setup ADCINA4 as 5th conversion
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 5; // Setup ADCINA5 as 6th conversion
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 6; // Setup ADCINA6 as 7th conversion
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 7; // Setup ADCINA7 as 8th conversion

    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;  // Enable SEQ1 interrupt (every EOS) --pp. 2-5 (bit 11)
    AdcRegs.ADCTRL1.bit.ACQ_PS = 4;        // Current guess at the sample hold timing --sect. 1.4
    AdcRegs.ADCTRL3.bit.ADCCLKPS = 9;      // Current guess at the ADCCLK value 4.16MHz --sect. 1.4.1
    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1 see pp 2-5
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit see pp 2-14
    //-------------------------------------------------------------
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
    PieCtrlRegs.PIEIER1.bit.INTx6 = 1;

    IFR &= ~M_INT1;  // Make sure no ints pending.
    IER |= M_INT1; // Enable CPU Interrupt 1 for ADC

    // Finalize inits and start DMA/McBSP
    post_init();

    EnableDog();


    BIOS_start();    /* does not return */
    return(0);
}

void start_dataCollection(void) {

    // Start SPI
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;
}

void adc_cisr(void) {

    raw_adc_A0 = AdcMirror.ADCRESULT0;  // ADC A0 - Gyro_Y
    raw_adc_B0 = AdcMirror.ADCRESULT1;  // ADC B0 - External ADC Ch4 (no protection circuit)
    raw_adc_A1 = AdcMirror.ADCRESULT2;  // ADC A1 - Gyro_4Y
    raw_adc_B1 = AdcMirror.ADCRESULT3;  // ADC B1 - External ADC Ch1
    raw_adc_A2 = AdcMirror.ADCRESULT4;  // ADC A2 - Gyro_4X
    raw_adc_B2 = AdcMirror.ADCRESULT5;  // ADC B2 - External ADC Ch2
    raw_adc_A3 = AdcMirror.ADCRESULT6;  // ADC A3 - Gyro_X
    raw_adc_B3 = AdcMirror.ADCRESULT7;  // ADC B3 - External ADC Ch3
    raw_adc_A4 = AdcMirror.ADCRESULT8;  // ADC A4 - Analog IR1
    raw_adc_B4 = AdcMirror.ADCRESULT9;  // ADC B4 - USONIC1
    raw_adc_A5 = AdcMirror.ADCRESULT10; // ADC A5 - Analog IR2
    raw_adc_B5 = AdcMirror.ADCRESULT11; // ADC B5 - USONIC2
    raw_adc_A6 = AdcMirror.ADCRESULT12; // ADC A6 - Analog IR3
    raw_adc_B6 = AdcMirror.ADCRESULT13; // ADC B6 - SV1 (Daughter Card / No Connection)
    raw_adc_A7 = AdcMirror.ADCRESULT14; // ADC A7 - Analog IR4
    raw_adc_B7 = AdcMirror.ADCRESULT15; // ADC B7 - SV1 (Daughter Card / No Connection)

    start_SPI();
    // Reinitialize for next ADC sequence - see SPRU060B
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;         // Reset SEQ1 see pp 2-5
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;       // Clear INT SEQ1 bit see pp 2-14
    //-------------------------------------------------------------
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;   // Acknowledge interrupt to PIE
}

//int whattoprint = 1;
void control(void) {

    if (CheckDog()==1) {
        dogReset = 60;
    }

    updateData();

    // Add your code here in between updateData and sendData
    if (omap_PIVEL_enable) {
        PIVelControl(omap_vref,omap_turn);
    }
    if ((dogReset == 0) && ((timeint%500)==0)) {
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
    } else if (((timeint%50)==0) && (dogReset>0)) {
        GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;
        dogReset--;
    }

    // code for pulsing Usonic measurements
    if(timeint%75 == 0) {
        if (toggleUSonic) {
            GpioDataRegs.GPASET.bit.GPIO30 = 1; // pulse GPIO30 (Ultrasonic on ADCB4) high for 150ms (less noise)
            toggleUSonic = 0;
        } else{
            GpioDataRegs.GPASET.bit.GPIO31 = 1; // pulse GPIO31 (Ultrasonic on ADCB4)
            toggleUSonic = 1;
        }
    } else {
        GpioDataRegs.GPACLEAR.bit.GPIO30 = 1;
        GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;
    }
    // end pulsing Usonic

    sendData();

    // Add this to check if OMAP DSP stops communicating with F28335
    // Usually not necessary
    /*if ((timeint - nocomm)>100) {  // if MCBSP comm stops, print to LCD screen
        if ((timeint%200)==0) {
            LCDPrintfLine(1,"No Communication");
            LCDPrintfLine(2,"McBSP_COMerr=%ld",McBSP_COMerr);
        }
    }*/


//    if (timeint%250 == 0) {
//        if (whattoprint == 1) {
//            LCDPrintfLine(1,"%.1f,%.1f",Enc1_rad,Enc2_rad);
//            LCDPrintfLine(2,"%d,%d,%d,%d",raw_adc_A0,raw_adc_A1,raw_adc_A2,raw_adc_A3); //gyro
//        } else if (whattoprint == 2) {
//            LCDPrintfLine(1,"%d,%d,%d,%d,",raw_adc_A4,raw_adc_A5,raw_adc_B4,raw_adc_B5); // IR and USonic
//            LCDPrintfLine(2,"%d,%d ,%d",raw_adc_B1,raw_adc_B2,CompassNew);  // Blue and Orange banana
//
//        }
//
//    }

    timeint++;

    // Service the WatchDog
    ServiceDog();

}

void updateData(void) {

    value_enc1 = EQEP_read(&enc1);
    value_enc2 = EQEP_read(&enc2);

    Enc1_rad = ((float) SPIenc1_reading)*(TWOPI/(2000.0f)); // left encoder
    Enc1_rad = -Enc1_rad;
    Enc2_rad = ((float) SPIenc2_reading)*(TWOPI/(2000.0f)); // right encoder
    Enc3_rad = ((float) SPIenc3_reading)*(TWOPI/(2000.0f));
    Enc4_rad = ((float) SPIenc4_reading)*(TWOPI/(2000.0f));


    switchstate = (int)((0x000F & ~(((GpioDataRegs.GPBDAT.all & 0x0C000000)>>24) | ((GpioDataRegs.GPBDAT.all & 0x00030000)>>16))));

    if (newOMAPdata) {
        omap_vref = mcbsp_vref;
        omap_turn = mcbsp_turn;
        omap_pwm1 = mcbsp_pwm1;
        omap_pwm2 = mcbsp_pwm2;
        omap_dac1 = mcbsp_dac1;
        omap_dac2 = mcbsp_dac2;
        omap_PIVEL_enable = PIVEL_enable;
        newOMAPdata = 0;
    }

}

void sendData(void) {

    if (McBSPB_rdy == 1) {
        TXBuff.data.validcode = VALID_28XTO67X;
        TXBuff.data.DSC_ENC[0] = value_enc1;
        TXBuff.data.DSC_ENC[1] = value_enc2;
        TXBuff.data.SPI_ENC[0] = (float) Enc1_rad;
        TXBuff.data.SPI_ENC[1] = (float) Enc2_rad;
        TXBuff.data.SPI_ENC[2] = (float) Enc3_rad;
        TXBuff.data.SPI_ENC[3] = (float) Enc4_rad;
        TXBuff.data.compass = (float)CompassNew;
        TXBuff.data.switchstate = (float)switchstate;
        TXBuff.data.ADC[0] = (float)raw_adc_A0;
        TXBuff.data.ADC[1] = (float)raw_adc_B0;
        TXBuff.data.ADC[2] = (float)raw_adc_A1;
        TXBuff.data.ADC[3] = (float)raw_adc_B1;
        TXBuff.data.ADC[4] = (float)raw_adc_A2;
        TXBuff.data.ADC[5] = (float)raw_adc_B2;
        TXBuff.data.ADC[6] = (float)raw_adc_A3;
        TXBuff.data.ADC[7] = (float)raw_adc_B3;
        TXBuff.data.ADC[8] = (float)raw_adc_A4;
        TXBuff.data.ADC[9] = (float)raw_adc_B4;
        TXBuff.data.ADC[10] = (float)raw_adc_A5;
        TXBuff.data.ADC[11] = (float)raw_adc_B5;
        TXBuff.data.ADC[12] = (float)raw_adc_A6;
        TXBuff.data.ADC[13] = (float)raw_adc_A7;
        TXBuff.data.ADC[14] = 0; // Reserved   was (float)atmel_adc1;
        TXBuff.data.ADC[15] = 0; // Reserved   was (float)atmel_adc2;
        TXBuff.data.ADC[16] = 0; // Reserved   was (float)atmel_adc3;
        TXBuff.data.ADC[17] = 0; // Reserved   was (float)atmel_adc4;
        TXBuff.data.IR[0] = 0; // Reserved   was (float)atmel_ir1;
        TXBuff.data.IR[1] = 0; // Reserved   was (float)atmel_ir2;
        TXBuff.data.IR[2] = 0; // Reserved   was (float)atmel_ir3;
        TXBuff.data.IR[3] = 0; // Reserved   was (float)atmel_ir4;
        TXBuff.data.IR[4] = 0; // Reserved   was (float)atmel_ir5;
        TXBuff.data.GYRO[0] = (float)gyro_x;
        TXBuff.data.GYRO[1] = (float)gyro_y;
        TXBuff.data.F28335_EXTRA[0] = (float)F28335_Extra1;
        TXBuff.data.F28335_EXTRA[1] = (float)F28335_Extra2;
        TXBuff.data.F28335_EXTRA[2] = (float)F28335_Extra3;
        TXBuff.data.F28335_EXTRA[3] = (float)F28335_Extra4;

        if (McBSP_RecGoodData_ReadyTX == 1) {
            McBSPB_rdy = 0;
            start_dma();
            McBSP_RecGoodData_ReadyTX = 0;
        }
    }
}


