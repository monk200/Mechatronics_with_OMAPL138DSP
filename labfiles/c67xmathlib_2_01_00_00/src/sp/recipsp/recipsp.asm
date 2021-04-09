* ======================================================================= *
* recipsp.asm - single precision floating point reciprocal                *
*              optimized hand ASM single sample                           *
* Rev 0.0.1                                                               *
*                                                                         *
* ----------------------------------------------------------------------- *
*            Copyright (c) 2010 Texas Instruments, Incorporated.          *
*                           All Rights Reserved.                          *
* ======================================================================= *
        
        .if     __TI_EABI__
           .asg    recipsp, _recipsp
        .endif
        .global _recipsp                ; entry labels
        .if (OVERRIDE_RTS = 1)
        .global _recipf
	    .endif 

_recipf:                                 ; entry in rts67xx library [not specified]
_recipsp:                                ; entry to SP FP reciprocal subroutine

           rcpsp   .S1     A4,A5        ; x1 = 1/A4 [8-bits]
	   
           zero    .L1     A3           ; two = 0
	   
           mpysp   .M1     A4,A5,A6     ; tmp = arg1 * x1 
 ||        mvkl    .S1     0xff,A2      ; maximum exponent = 255
	   
           extu    .S1     A4,1,24,A1   ; is exp1 = 0 ?    

           set     .S1     A3,30,30,A3  ; two = 2.0 in SP FP (0x4000_0000)

           xor     .L1     A1,A2,A2     ; check for exp1=255=0xff

           subsp   .L1     A3,A6,A6     ; tmp = 2.0 - (arg1*x1)

           nop             3
	   
           mpysp   .M1     A5,A6,A5     ; x2 = x1*(2 - arg1*x1) [16-bits]

           nop             3
	   
           mpysp   .M1     A4,A5,A6     ; tmp = arg1 * x2 

           nop             3

   [A2]    subsp   .L1     A3,A6,A6     ; tmp = 2.0 - (arg1*x2) 

   [!A2]   zero    .D1     A5           ; force xn=0 for exp=255=0xff           

           b       .S2     b3           ; normal return           

   [!A2]   zero    .D1     A6           ; force tmp=0 for exp=255=0xff

   [A1]    mpysp   .M1     A5,A6,A4     ; x3 = x2*(2 - arg1*x2) [32-bits]

           nop             2
  
   [!A1]   set     .S1     A4,0,30,A4   ; return exp/mant = all 1s (div.by 0)
	   
	   .end
;------------------End of RECIPSP0.asm---------------------------------------


* ======================================================================== *
*  End of file: recipsp_h.asm                                              *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2010 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== *
