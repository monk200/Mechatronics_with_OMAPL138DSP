* ======================================================================= *
* rsqrtsp.asm - single precision floating point reciprocal sqrt           *
*              optimized hand ASM single sample                           *
* Rev 0.0.1                                                               *
*                                                                         *
* ----------------------------------------------------------------------- *
*            Copyright (c) 2010 Texas Instruments, Incorporated.          *
*                           All Rights Reserved.                          *
* ======================================================================= *
        
        .if     __TI_EABI__
           .asg    rsqrtsp, _rsqrtsp
        .endif
        .global _rsqrtsp
        
			  
        .if (OVERRIDE_RTS = 1)
        .global _rsqrtf
	    .endif 
        
_rsqrtf       			  ; rts entry labels
_rsqrtsp:                 ; find 1/square root of arg1 all in SP FP

        extu    .S1     A4,1,24,A1      ; get exponent field
||      zero    .L2     b5:B4           ; 1.5:0
||      mvk     .S2     0xff,B0         ; Max.exp.

        clr     .S1     A4,31,31,A4     ; force + sign (abs. of arg1)
||      set     .S2     B4,23,23,B4     ; one in exp. field = 0x0080_0000
        cmplt   .L2x    A1,B0,B0        ; is exp1<255=0xff?

        rsqrsp  .S1     A4,A0           ; X0 = TLU to 8-bits
||      or      .l1x    a1,b0,a1        ; exp1=0 | exp1=255

  [a1]  mpysp   .M1     A4,a0,A3        ; arg1*X0 if 0 < exp1 < 0xff
||[!a1] set     .s1     a4,0,30,a4      ; ans = 0x7fff_ffff (exp1=0)
||[!a1] b       .s2     b3              ; quick exit (exp1=0 or 0xff)

        sub     .L2x    A0,b4,b6        ; x0/2
        set     .S2     B5,22,29,B5     ; 1.5 in SP FP = 0x3fc0_0000
  [!b0] zero    .d1     a4              ; ans = 0 if exp1=0xff = 255

  [a1]  mpysp   .M1x    a3,b6,A5        ; (arg1*X0) * (X0/2)
        nop             1               ; end of b b3 quick exit
        nop             2               ; wait for mpysp

        subsp   .L1x    B5,A5,A2        ; 1.5 - (arg1*X0)*(X0/2)
        nop             3               ; wait for subsp

        mpysp   .M1     A0,A2,A0        ; X1 = X0*(1.5 - (arg1*X0)*(X0/2) )
        nop             3               ; wait for mpysp

        mpysp   .M1     A0,a4,A3        ; arg1*X1
        sub     .L2x    A0,b4,b6        ; x1/2
        nop             2               ; wait for mpysp

        mpysp   .M1     A3,b6,A5        ; (arg1*X1) * (X1/2)
        nop             3               ; wait for mpysp

        subsp   .L1x    B5,A5,A2        ; 1.5 - (arg1*X1)*(X1/2)
        nop             1
        b       .S2     b3              ; normal return
        nop             1               ; wait for subsp

        mpysp   .M1     A0,A2,A4        ; ans=X2 = X1*{1.5 - (arg1*X1)*(X1/2)} 
        nop             3               ; wait for mpysp ans in register
        .end
;--------------------End of SP FP 1/sqrt(arg1)----------------------------


                .end

* ======================================================================== *
*  End of file: rsqrtsp_h.asm                                              *
* ------------------------------------------------------------------------ *
*          Copyright (C) 2010 Texas Instruments, Incorporated.             *
*                          All Rights Reserved.                            *
* ======================================================================== *
