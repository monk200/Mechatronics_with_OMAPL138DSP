#ifndef MCBSP_COM_H_
#define MCBSP_COM_H_

#define VALID_28XTO67X 0xaaaa5555

#define FLAG28X_NEWIR_BIT0 0x1
#define FLAG28X_NEWCOMPASS_BIT1 0x2
#define FLAG28X_NEWTCPIPDATA 0x4

#ifdef RUNNING_ON_OMAPL138

typedef union LCDchars_tag {
	Uint32 array32[6];
	Uint16 array16[12];
	char chararray[24];
} LCDchars;

#else

typedef union LCDchars_tag {
	Uint32 array32[6];
	Uint16 array16[12];
} LCDchars;

#endif


typedef struct mcbsp28xdata_tag {
	Uint32 validcode;
	Uint32 flags;
	float SPI_ENC[4];
	float DSC_ENC[2];
	float ADC[18];
	float IR[5];
	float compass;
	float switchstate;
	float GYRO[2];
	float F28335_EXTRA[4];
} mcbsp28xdata;

#define NUM_28XCOMWORDS 39 // cannot be greater than 64

typedef union mcbsp28x_com_tag {
	 mcbsp28xdata data;
	 Uint32 darray[NUM_28XCOMWORDS];
} mcbsp28x_com;


#define VALID_67XTO28X 0xa0a05050

#define FLAGL138_PICONTRL_MODE_BIT0 0x1  // if 1 PWM[2] values ignored
										// if 0 PWM[2] values applied
#define FLAGL138_NEWLCDLINE1_BIT1 0x2
#define FLAGL138_NEWLCDLINE2_BIT2 0x4
#define FLAGL138_NEWSERVOS 0x8

typedef struct mcbspL138data_tag {
	Uint32 validcode;
	Uint32 flags;
	float vref;
	float turn;
	float PWM[8];
	float DAC[2];
	LCDchars lcdline1;
	LCDchars lcdline2;
} mcbspL138data;

#define NUM_L138COMWORDS 26

typedef union mcbspL138_com_tag {
	 mcbspL138data data;
	 Uint32 darray[NUM_L138COMWORDS];
} mcbspL138_com;


#endif
