;       lneasm.asm      Syd Poland      11-01-99  use w/logdpc.c & flog.c
;______________________________________________________________________________
;extern int    gtexp(double)  ;
;extern double fxexp(double)  ;
;extern double setnmx(double) ;
;______________________________________________________________________________
        .global _gtexp          ; return unbiased DP exponent as "int"
        .global _fxexp          ; return biased DP exp = 1022 (if non-zero)
        .global _setnmx         ; returns neg. max DP FP # = 0xffef_ffff_ffff_ffff
;______________________________________________________________________________
        .text                   ; program
;______________________________________________________________________________
_gtexp:                         ; get DP exp. as unbiased "int."
        b       b3
        mv      a4,b4           ; copy arg1 to arg2
		mv		a5,b5
        extu    a5,1,21,a4      ; biased DP exp. as int.
		mvkl	1022,a5		 
        sub     a4,a5,a4        ; unbiased exp. as a signed integer
;______________________________________________________________________________
_fxexp:                         ; return DP FP # with biased exp=1022
        b       b3              
||      extu    a5,1,21,a1      ; exp1 = ? (0 forces a DP FP 0) ?

        clr     a5,20,31,a5     ; clr exp & sign fields
        zero    b5
        mvklh   0x3fe0,b5 
        or      a5,b5,a5        ; exp = 0x3fe = 1022 in exp. field, sign=0

  [!a1] sub.l1  a5,a5,a5
||[!a1] sub.d1  a4,a4,a4        ; force 0 if exp1=0
;______________________________________________________________________________        
_setnmx                         ; returns neg. max DP FP # < Infinity.
        b       b3                              
        set     a4,0,31,a4      ; set ans = 0xffef_ffff_ffff_ffff
        mvkl    -1,a5           ; a5 = all ones
        clr     a5,20,20,a5     ; turn off bit 20 [exp = 0x7fe = 2046] 
        nop     2               ; wait for { b b3 } 

        .end
;______________________________________________________________________________
