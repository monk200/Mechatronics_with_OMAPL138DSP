/* LCD.H: This code is designed to act as a low-level LCD-serial driver
	interface for higher-level programming.

	WRITTEN BY : Paul Miller <pamiller@uiuc.edu>
	$Id: lcd.h,v 1.2 2003/08/08 18:50:32 paul Exp $
*/

#ifndef __LCD_H__
#define __LCD_H__

#include <coecsl.h>
#include <28335_serial.h>

void init_lcd(serial_t *s, int contrast);
void lcd_off(void);
void lcd_on(int minutes);
void lcd_clear(void);
void lcd_printf(int row, char *fmt, ...);

extern serial_t *LCD_serial;

#endif /* __LCD_H__ */
