#ifndef __28335_SPI_H_
#define __28335_SPI_H_

#include <DSP2833x_Device.h>


// Function prototypes
void init_SPI(void);
void SPI_RXint(void);
void start_SPI(void);
void writeDAC7564(float dac1,float dac2);

#endif /*28335_SPI_H_*/
