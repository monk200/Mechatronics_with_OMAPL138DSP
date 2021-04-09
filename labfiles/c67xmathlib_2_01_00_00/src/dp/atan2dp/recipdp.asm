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
           .asg    recipdp, _recipdp
        .endif

        .global _recipdp                ; entry labels
        .if (OVERRIDE_RTS = 1)
        .global _recip
	    .endif 



;---------------------------------------------------------------------------+
; name = recipdp.asm in Fast67 library		7/12/00		            |
;---------------------------------------------------------------------------+
;       RECIPDP0.asm                   10-12-99        for TMS320C67xx DSPs |
;                                                                           |
;       a5:a4 = 1.0 / a5:a4                                                 |
;         ans = 1.0 / arg1         DP FP reciprocal subroutine              |
;                                                                           |
;         ans = all 1s (exp/mant) if arg1 = 0 or arg1's exponent = 0        |
;         ans = 0 if arg1's exponent = 2047 = 0x7ff (maximum exponent)      |
;---------------------------------------------------------------------------+

;---------------------------------------------------------------+
;arg1H   .set    a5      ; input DP FP argument1 register pair  |
;arg1L   .set    a4                                             |
;ansH    .set    a5      ; output DP FP answer register pair    |
;ansL    .set    a4                                             |
;xH      .set    a7      ; x register pair                      |
;xL      .set    a6                                             |
;twoH    .set    b5      ; DP FP 2.0 constant register pair     |
;twoL    .set    b4                                             |
;tH      .set    a9      ; DP FP temporaty register pair        |
;tL      .set    a8                                             |
;V       .set    a2      ; divide by 0 switch                   |
;Z       .set    a1      ; test for maximum exponent switch     |
;---------------------------------------------------------------+


_recip:                                 ; entry in rts67xx library [not specified]
_recipdp:                        ; ans = 1.0 / arg1  (all DP FP) 


;-----------------End of RECIPDP0.asm-----------------------------------------
        rcpdp   .S1     A5:A4, A7:A6            ; x1 = 1/arg1 [8-bits]     
||      zero    .L2     B5                      ; MS word = 0
||      zero    .D2     B4                      ; LS word = 0

        set     .S2     B5,30,30,B5             ; DP FP 2.0 (0x4000_0000)

        mpydp   .M1     A5:A4, A7:A6, A9:A8     ; t = arg1 * x1
        mvkl    .S1     0x7ff,A1                ; Maximum exponent
        extu    .S1     A5,1,21,A2              ; exp1 = 0 ?
        xor     .L1     A2,A1,A1                ; Max.Exp.?
        nop             5

        subdp   .L1x    B5:B4, A9:A8, A9:A8     ; t = 2.0 - (arg1*x1)
        nop             5

        mpydp   .M1     A7:A6, A9:A8, A7:A6     ; x2 = x1*(2-arg1*x1)
        nop             8

        mpydp   .M1     A5:A4, A7:A6, A9:A8     ; t = arg1 * x2
        nop             8

        subdp   .L1x    B5:B4, A9:A8, A9:A8     ; t = 2.0 - (arg1*x2)
        nop             5

        mpydp   .M1     A7:A6, A9:A8, A7:A6     ; x3 = x2*(2-arg1*x2)
        nop             8

        mpydp   .M1     A5:A4, A7:A6, A9:A8     ; t = arg1 * x3
        nop             8

  [A1]  subdp   .L1x    B5:B4, A9:A8, A9:A8     ; t = 2.0 - (arg1*x3)
 [!A1]  zero    .D1     A9                      ; set t=0 for Max.Exp
 [!A1]  zero    .D1     A8
 [!A1]  zero    .D1     A7                      ; set x=0 for Max.Exp
 [!A1]  zero    .D1     A6                      ; for ans = 0.0
        nop             1

  [A2]  mpydp   .M1     A7:A6, A9:A8, A5:A4     ; ans = x3*(2-arg1*x3)

 [!A2]  set     .S1     A5,0,30,A5              ; exp/mant = all 1s (exp1=0)    
 [!A2]  or      .L1     -1,A4,A4                ; lower mantissa = all 1s

        nop             1                       ; used for mpydp/b to b3 exit
        b       .S2     b3                      ; normal function return
        nop             5                       ; wait for ans in reg. pair


                .end

* ======================================================================== *
*  End of file: recipdp.asm                                                *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2010 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== *
