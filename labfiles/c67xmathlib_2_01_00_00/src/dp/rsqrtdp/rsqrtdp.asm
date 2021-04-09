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
                    .asg    rsqrtdp, _rsqrtdp
                    .asg    errno, _errno
         .endif

        .global _rsqrtdp                ; entry labels
        .if (OVERRIDE_RTS = 1)
        .global _rsqrt
	    .endif 




;-------------------------------------------------------------------------+
;       Copyright 1998 by Texas Instruments Inc.  All rights reserved.    |
;-------------------------------------------------------------------------+
;       rsqrtdp.asm    Syd Poland    06-24-98  'C67xx DSPs (12-7-99 mod)  |
;       a5:a4 = a5:a4                                                     |
;         ans = 1/Square Root (|arg1|)        DP FP reciprocal SqRt Sub   |
;         ans = all 1s (exp/mant) if biased exp1 = 0                      |
;         ans = 0 if biased exp1 = 0x7ff = 2047                           |
;		where arg1 => 2^(-1022) = 2.225e-308 	biased exp1 > 0   |
;-------------------------------------------------------------------------+
;       9/15/00 mods for biased exp1 = 1                                  |
;-------------------------------------------------------------------------+
;--------------------------------------------------------------------------
;arg1H   .set    a5      ; input DP FP argument1 register pair
;arg1L   .set    a4
;ansH    .set    a5      ; output DP FP answer register pair
;ansL    .set    a4
;VH      .set    a1      ; arg1/2 register pair
;VL      .set    a0
;KH      .set    b5      ; constant 1.5 register pair
;KL      .set    b4
;xH      .set    a7      ; xn register pair
;xL      .set    a6
;tH      .set    a9      ; temp register pair
;tL      .set    a8
;exp1    .set    a2      ; exp1 = 0 switch
;----------------------------------------------------------------------------
_rsqrt:                                  ; entry in rts6701 library (12-7-99 mod)
_rsqrtdp:                                ; entry to DP FP recip. square root function

        extu    .S1     A5,1,21,A2              ; get exponent 1 field                  
||      zero    .D2     B1                      ; V = 0
||      mvk     .s2     0x7ff,b2                ; max biased exp = 2047

  [!a2] b       .s2     b3                      ; quick exit (exp1=0)
        clr     .S1     A5,31,31,A5             ; force arg1 sign bit to +
||      cmplt   .l2x    a2,b2,b2                ; exp1 < 0x7ff ?

   [a2] rsqrdp  .S1     A5:A4, A7:A6            ; x1 = TLU (1/arg1) [8-bits]
||[!a2] or      .l1     a4,-1,a4                ; ans = 1s )exp1=0)
||[!b2] b       .s2     b3                      ; quick exit (exp1=0x7ff)
||[!b2] zero    .d1     a4                      ; ans = 0 (exp1=0x7ff)

  [!A2] set     .s1     A5,0,30,a5              ; ans = 1s (exp/mant) exp1=1
||[!b2] zero    .l1     a5                      ; ans = 0 (exp1=0x7ff)

   [a2] mpydp   .M1     A5:A4, A7:A6, A9:A8     ; t = (arg1) * x1 if 1<exp1=<0x7ff
||      set     .S2     b1,20,20,b1             ; V = 1 in exponent field

        zero    .L2     B5:b4                   ; K = 0
        set     .S2     B5,19,29,B5             ; 1.5 in DP FP (0x3ff8_0000)
                                                ; end b b3 (exp1=0)
        sub     .L2x    a7,b1,b7                ; w = x1 * 0.5 = x1 / 2
                                                ; end b b3 exit (exp1=0x7ff)
        mv      .L2x    a6,b6
        nop             4
        mpydp   .M1x    b7:b6, A9:A8, A9:A8     ; t = [(arg1*x1)] * (x1/2)
        nop             8
        subdp   .L1x    B5:B4, A9:A8, A9:A8     ; t = 1.5-[(arg1*x1)*(x1/2)]
        nop             5
        mpydp   .M1     A7:A6, A9:A8, A7:A6     ; x2=x1*{1.5-(arg1*x1)*(x1/2)}
        nop             8

        mpydp   .M1     A5:A4, A7:A6, A9:A8     ; t = (arg1) * x2
        sub     .L2x    a7,b1,b7                ; w = x2 * 0.5 = x2 / 2
        mv      .L2x    a6,b6
        nop             6
        mpydp   .M1x    b7:b6, A9:A8, A9:A8     ; t = [(arg1*x2)] * (x2/2)
        nop             8
        subdp   .L1x    B5:B4, A9:A8, A9:A8     ; t = 1.5-[(arg1*x2)*(x2/2)]
        nop             5
        mpydp   .M1     A7:A6, A9:A8, A7:A6     ; x3=x2*{1.5-(arg1*x2)*(x2/2)}
        nop             8

        mpydp   .M1     A5:A4, A7:A6, A9:A8     ; t = (arg1) * x3
        sub     .L2x    a7,b1,b7                ; w = x3 * 0.5 = x3 / 2
        mv      .L2x    a6,b6
        nop             6
        mpydp   .M1x    b7:b6, A9:A8, A9:A8     ; t = [(arg1*x3)] * (x3/2)
        nop             8
        subdp   .L1x    B5:B4, A9:A8, A9:A8     ; t = 1.5-[(arg1*x3)*(x3/2) ]
        nop             5
        mpydp   .M1     A7:A6, A9:A8, A5:A4     ; ans=x3*{1.5-(arg1*x3)*(x3/2)}

        nop             3
        b       .S2     b3                      ; normal return
        nop             5                       ; wait for ans in reg. pair
        .end
;--------------End of DP FP reciprocal Square Root-----------------------------


* ======================================================================== *
*  End of file: rsqrtdp.asm                                                *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2010 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== *
