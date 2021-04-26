/* LCD.C: This code is designed to act as a low-level LCD-serial driver
	interface for higher-level programming.

	WRITTEN BY : Paul Miller <pamiller@uiuc.edu>
	$Id: lcd.c,v 1.4 2003/08/08 18:50:17 paul Exp $
*/

#include <lcd.h>

#define LCD_COLUMNS		20

serial_t *LCD_serial = NULL;


//#pragma CODE_SECTION(init_lcd, "initfuncs");
void init_lcd(serial_t *s, int contrast)
{
	char str[50];
	int i;

	LCD_serial = s;
	init_serial(LCD_serial,19200,NULL);

	i = 0;
	str[i++] = 0xFE;
	str[i++] = 0x60;	// auto repeat off

	str[i++] = 0xFE;
	str[i++] = 0x44;	// auto line wrap off

	str[i++] = 0xFE;
	str[i++] = 0x52;	// auto scroll off

	str[i++] = 0xFE;
	str[i++] = 0x4F;	// auto transmitt keypress off

	str[i++] = 0xFE;
	str[i++] = 0x58;	// clear display

	str[i++] = 0xFE;
	str[i++] = 0x45;	// clear key buffer

	str[i++] = 0xFE;
	str[i++] = 0x50;	// set contrast
	str[i++] = contrast;

	str[i++] = 0xFE;
	str[i++] = 0x4B;	// cursor off

	str[i++] = 0xFE;
	str[i++] = 0x4D;	// cursor right

	str[i++] = 0xFE;
	str[i++] = 0x54;	// cursor blink off

	serial_send(LCD_serial,str,i);
}

void lcd_off(void)
{
	char str[2] = {0xFE, 0x46};
	serial_send(LCD_serial,str,2);
}

void lcd_on(int minutes)
{
	char str[3] = {0xFE, 0x42, 0};
	if (minutes > 100) {
		str[2] = 100;
	} else if (minutes > 0) {
		str[2] = minutes;
	}
	serial_send(LCD_serial,str,3);
}

void lcd_clear(void)
{
	char str[2] = {0xFE, 0x58};
	serial_send(LCD_serial,str,2);
}

void lcd_printf(int row, char *fmt, ...)
{
	va_list ap;
	char buf[2*LCD_COLUMNS];
	int i;

	buf[0] = 0xFE;
	buf[1] = 'G';
	buf[2] = 1;
	buf[3] = row;

	va_start(ap,fmt);
	i = vsprintf(buf+4,fmt,ap) + 4;
	va_end(ap);

	for (; i < LCD_COLUMNS+4; i++) buf[i] = ' ';

	serial_send(LCD_serial,buf,LCD_COLUMNS+4);
}

