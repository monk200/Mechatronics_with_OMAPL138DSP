/*
 * TI Booting and Flashing Utilities
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
 

-b
/* -boot */
/* -map C:\dan\omapl138\GE423Sp17\mystuff\SYSBIOShex\out2bootbin.map */
-map out2bootbin.map

ROMS
{
  SPIFLASH: org = 0x0, len=0x40000
}

SECTIONS
{
.vecs: BOOT
.cinit: BOOT
.text: BOOT
.const: BOOT
.const.1: BOOT
.const.2: BOOT
.const.3: BOOT
.const.4: BOOT
.const.5: BOOT
.const.6: BOOT
.switch: BOOT
.switch.1: BOOT
.switch.2: BOOT
.switch.3: BOOT
.switch.4: BOOT
.switch.5: BOOT
.switch.6: BOOT
}

