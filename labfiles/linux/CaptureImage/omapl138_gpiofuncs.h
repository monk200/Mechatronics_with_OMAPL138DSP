/*
 * libwebsockets - small server side websockets and web server implementation
 *
 * Copyright (C) 2010 Andy Green <andy@warmcat.com>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation:
 *  version 2.1 of the License.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#ifndef __OMAPL138_GPIOFUNCS_H__
#define __OMAPL138_GPIOFUNCS_H__

#ifdef __cplusplus
extern "C" {
#endif

#define ERR_NO_ERROR (0)
#define ERR_INVALID_PARAMETER (4)

#define GPIO_BANK0            (0)
#define GPIO_BANK1            (1)
#define GPIO_BANK2            (2)
#define GPIO_BANK3            (3)
#define GPIO_BANK4            (4)
#define GPIO_BANK5            (5)
#define GPIO_BANK6            (6)
#define GPIO_BANK7            (7)
#define GPIO_BANK8            (8)
#define MAX_GPIO_BANK_NUM     (9)

#define GPIO_PIN0             0x1
#define GPIO_PIN1             0x2
#define GPIO_PIN2             0x4
#define GPIO_PIN3             0x8
#define GPIO_PIN4             0x10
#define GPIO_PIN5             0x20
#define GPIO_PIN6             0x40
#define GPIO_PIN7             0x80
#define GPIO_PIN8             0x100
#define GPIO_PIN9             0x200
#define GPIO_PIN10            0x400
#define GPIO_PIN11            0x800
#define GPIO_PIN12            0x1000
#define GPIO_PIN13            0x2000
#define GPIO_PIN14            0x4000
#define GPIO_PIN15            0x8000
#define MAX_GPIO_PIN_NUM      0x8001

#define GPIO_OUTPUT           (0)
#define GPIO_INPUT            (1)

#define OUTPUT_LOW            (0)
#define OUTPUT_HIGH           (1)

typedef struct GPIOregs {
	volatile unsigned long revid;
	volatile unsigned long rsrv1;
	volatile unsigned long binten;
	volatile unsigned long rsrv2; 
	volatile unsigned long dir01;
	volatile unsigned long out_data01;
	volatile unsigned long set_data01;
	volatile unsigned long clr_data01;
	volatile unsigned long in_data01;
	volatile unsigned long set_ris_trig01;
	volatile unsigned long clr_ris_trig01;
	volatile unsigned long set_fal_trig01;
	volatile unsigned long clr_fal_trig01;
	volatile unsigned long intstat01;
	volatile unsigned long dir23;
	volatile unsigned long out_data23;
	volatile unsigned long set_data23;
	volatile unsigned long clr_data23;
	volatile unsigned long in_data23;
	volatile unsigned long set_ris_trig23;
	volatile unsigned long clr_ris_trig23;
	volatile unsigned long set_fal_trig23;
	volatile unsigned long clr_fal_trig23;
	volatile unsigned long intstat23;
	volatile unsigned long dir45;
	volatile unsigned long out_data45;
	volatile unsigned long set_data45;
	volatile unsigned long clr_data45;
	volatile unsigned long in_data45;
	volatile unsigned long set_ris_trig45;
	volatile unsigned long clr_ris_trig45;
	volatile unsigned long set_fal_trig45;
	volatile unsigned long clr_fal_trig45;
	volatile unsigned long intstat45;
	volatile unsigned long dir67;
	volatile unsigned long out_data67;
	volatile unsigned long set_data67;
	volatile unsigned long clr_data67;
	volatile unsigned long in_data67;
	volatile unsigned long set_ris_trig67;
	volatile unsigned long clr_ris_trig67;
	volatile unsigned long set_fal_trig67;
	volatile unsigned long clr_fal_trig67;
	volatile unsigned long intstat67;
	volatile unsigned long dir8;
	volatile unsigned long out_data8;
	volatile unsigned long set_data8;
	volatile unsigned long clr_data8;
	volatile unsigned long in_data8;
	volatile unsigned long set_ris_trig8;
	volatile unsigned long clr_ris_trig8;
	volatile unsigned long set_fal_trig8;
	volatile unsigned long clr_fal_trig8;
	volatile unsigned long intstat8;
} GPIOregs;

unsigned long GPIO_setDir(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num, unsigned char in_dir);
unsigned long GPIO_setOutput(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num, unsigned char in_dir);
unsigned long GPIO_getInput(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num);
unsigned long GPIO_getOutput(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num);
unsigned long GPIO_toggleBit(volatile GPIOregs *mygpio, unsigned long in_bank, unsigned long in_pin_num);

#ifdef __cplusplus
}
#endif

#endif
