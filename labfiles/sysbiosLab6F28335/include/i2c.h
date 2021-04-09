#ifndef I2C_H_
#define I2C_H_

#include <DSP2833x_Device.h>

void InitI2CGpio(void);
void readCompassTSK(void);
int i2c_stdsend(int I2Caddress, unsigned char *buf, int length);
int i2c_stdrecv(int I2Caddress, unsigned char addr, unsigned char *buf, int length);
void Init_i2c(void);
void SendStr2_I2C(char *buffer,int size);
void Init_LCD(unsigned char contrast);
int atmel_set_rcservo(int first, int count, unsigned char *buf);
int atmel_get_ir(int first, int count, unsigned char *buf);
int atmel_get_adc(int first, int count, unsigned char *buf);
int atmel_get_all(unsigned char *buf);
int atmel_get_version(unsigned char *buf);
int atmel_set_mode(unsigned char mode);
void atmel_IRs_task(void);
void atmel_RCservo_task(void);

#endif /*I2C_H_*/
