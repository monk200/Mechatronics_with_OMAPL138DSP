* ======================================================================= *
* divdp.asm - double precision floating point divide                      *
*              optimized hand ASM single sample                           *
* Rev 0.0.1                                                               *
*                                                                         *
* ----------------------------------------------------------------------- *
*            Copyright (c) 2010 Texas Instruments, Incorporated.          *
*                           All Rights Reserved.                          *
* ======================================================================= *
        .if     __TI_EABI__
           .asg    divdp, _divdp
        .endif
        .global _divdp   ; entry labels
		.if (OVERRIDE_RTS = 1)
	    .global __divd
                                 
	    .endif

__divd: 						 ; entry in rts6701 library
_divdp:                         ; ans = arg1 / arg2 (all DP FP)

        rcpdp   .S2     B5:B4, B7:B6            ; x1 = 1/arg2 [8-bits]     
||      zero    .L1     A7                      ; MS word = 0
||      zero    .D1     A6                      ; LS word = 0

        set     .S1     A7,30,30,A7             ; DP FP 2.0 (0x4000_0000)

        mpydp   .M2     B5:B4, B7:B6, B9:B8     ; t = arg2 * x1
||      extu    .S2     B5,1,21,B2              ; exp2 = 0 ?
        nop             8

        subdp   .L2x    A7:A6, B9:B8, B9:B8     ; t = 2.0 - (arg2*x1)
        nop             5

        mpydp   .M2     B7:B6, B9:B8, B7:B6     ; x2 = x1*(2-arg2*x1)
        nop             8

        mpydp   .M2     B5:B4, B7:B6, B9:B8     ; t = arg2 * x2
        nop             8

        subdp   .L2x    A7:A6, B9:B8, B9:B8     ; t = 2.0 - (arg2*x2)
        nop             5

        mpydp   .M2     B7:B6, B9:B8, B7:B6     ; x3 = x2*(2-arg2*x2)
        nop             8

        mpydp   .M2     B5:B4, B7:B6, B9:B8     ; t = arg2 * x3
        nop             8

        subdp   .L2x    A7:A6, B9:B8, B9:B8     ; t = 2.0 - (arg2*x3)
        nop             5

        mpydp   .M2     B7:B6, B9:B8, B7:B6     ; x4 = x3*(2-arg2*x3)
        nop             8

  [B2]  mpydp   .M1x    A5:A4, B7:B6, A5:A4     ; ans = arg1 * x4
||[!B2] set     .S1     A5,0,30,A5              ; exp/mant = all 1s (exp2=0)    
||[!B2] or      .L1     -1,A4,A4                ; lower mantissa = all 1s

        nop             3
        b       .S2     b3                      ; normal function return
        nop             5                       ; wait for ans in reg. pair

        .end
;-----------------End of DIVDP0.asm-----------------------------------------

* ======================================================================== *
*  End of file: divdp.asm                                                  *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2010 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== * 
