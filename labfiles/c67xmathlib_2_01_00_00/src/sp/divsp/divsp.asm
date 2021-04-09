* ======================================================================= *
* divsp.asm - single precision floating point divide                      *
*              optimized hand ASM single sample                           *
* Rev 0.0.1                                                               *
*                                                                         *
* ----------------------------------------------------------------------- *
*            Copyright (c) 2010 Texas Instruments, Incorporated.          *
*                           All Rights Reserved.                          *
* ======================================================================= *
     .if     __TI_EABI__
           .asg    divsp, _divsp
        .endif
	.global _divsp   ; entry label
    .if (OVERRIDE_RTS = 1)
	.global __divf
	.endif
    
__divf: 
_divsp:						             ; entry to SP FP divide subroutine
                       

           rcpsp   .S2     B4,B5        ; x1 = 1/arg2 [8-bits]
	   
           zero    .L1     A3           ; A3 = 0               
	   
           mpysp   .M2     B4,B5,B6     ; B6 = arg2 * x1 
	   
           extu    .S2     B4,1,24,B0   ; is exp2 = 0 ?    
           set     .S1     A3,30,30,A3  ; A3 = 2.0 in SP FP (0x4000_0000)
	   nop             1

           subsp   .L2X    A3,B6,B6     ; B6 = 2.0 - (arg2*x1)
	   nop             3
	   
           mpysp   .M2     B5,B6,B5     ; x2 = x1*(2 - arg2*x1) [16-bits]
	   nop             3
	   
           mpysp   .M2     B4,B5,B6     ; B6 = arg2 * x2 
	   nop             3
	   
           subsp   .L2X    A3,B6,B6     ; B6 = 2.0 - (arg2*x2) 
	   nop             3
	   
           mpysp   .M2     B5,B6,B5     ; x3 = x2*(2 - arg2*x2) [32-bits]
	   nop             1
           b       .S2     b3           ; normal return
	   nop             1
   
   [B0]    mpysp   .M1     A4,B5,A4     ; ans = arg1*(x3) where x3 = 1/arg2
|| [!B0]   set     .S1     A4,0,30,A4   ; return exp/mant = all 1s (div.by 0)
 
           nop             3            ; wait for A4 in register
	   
	   .end
;---------------------End of DIVSP0.asm--------------------------------------

* ======================================================================== *
*  End of file: divsp.asm                                                  *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2010 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== * 
