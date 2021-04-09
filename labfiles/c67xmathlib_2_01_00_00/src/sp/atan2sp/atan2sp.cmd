/* ======================================================================= */
/* atan2.cmd -- Linker command file                                        */
/*                                                                         */
/* Rev 0.0.2                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2009 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

-c
-heap  0x1000
-stack 0x1000

/* MODULE MEM */
MEMORY {
   CACHE_L2RAM : origin = 0x11800000,  len = 0x40000
   CACHE_L1P   : origin = 0x11e00000,  len = 0x8000
   CACHE_L1D   : origin = 0x11f00000,  len = 0x8000
   L3RAM       : origin = 0x80000000,  len = 0x20000
   SDRAM       : origin = 0xC0000000,  len = 0x8000000
}

SECTIONS
{
    vectors            :> SDRAM
    .cinit             :> SDRAM
    .text              :> SDRAM
	text			   :> SDRAM
    .stack             :> SDRAM
    .bss               :> SDRAM
    .const             :> SDRAM
    .data              :> SDRAM
    .far               :> SDRAM
    .switch            :> SDRAM
    .sysmem            :> SDRAM
    .tables            :> SDRAM
    .cio               :> SDRAM
    .fardata           :> SDRAM
    
    GROUP (NEAR_DP_RELATIVE)
    {
       .neardata
       .rodata
       .bss
      }>SDRAM
}

/* ======================================================================== */
/*  End of file: atan2sp.cmd                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
