/* ======================================================================= */
/* exp10sp_c.c - single precision floating point exp base 10               */
/*              optimized  C implementation (w/ intrinsics) single sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "exp10sp_c.h"



float exp10sp_c(float a)
{



/* ======================================================================== */
/*S Place source code here.                                                S*/
/* ======================================================================== */
float  Zeroe=0.0, Halfe=0.5 ;
float  epse = 9.313225746e-10 ;           /* [2^-29] / 2  */
// float   srHalfe=0.707106781 ;
// float  MINe = 1.17549435e-38 ;
float  LnMine = -87.33654475 ;
float  MAXe = 3.40282347e+38, LnMaxe =  88.72283905 ;

float  a0e= 2.499999995e-1  ;
float  a1e= 4.1602886268e-3 ;
float  b0e= 0.5  ;
float  b1e= 4.9987178778e-2 ;
float  CC1E= 0.693359375  ;       /* 355/512      */
float  CC2E=-2.12194440055e-4 ;  /* lne(2) - 355/512     */
float  Ln2E =1.442695040889 ;    /* ln(base 2) of e  */
// float  c10E=0.434294481903251 ; /* ln(base 10) of e  */
float  k10e=2.302585093    ;    /* log (base e) of 10  */
//float  k2e =0.69314718056  ;    /* log (base e) of  2  */

float  Ye,Ze,Xe,We,Re,Se,Be,Ce,De, Recip ;
int    Ne ; 



		
		a = k10e*a;
        Ye = a ;
		Ze = Ye ;
        if (Ze < Zeroe) Ze = -Ye ;          /* Z = |Y| */
  
        if (Ze < epse)    Ye = 0 ;   /* < epsilon returns unity */
        Ce = Ye*Ln2E ;                      /* base e --> base 2 argument */           
        Ne =_spint(Ce);// _extu(_spint(Ce+0.5),0,0); // _ext(Ce,1,0) ;                 /* get unbiased exponent as an int */

        Se = Ne ;                          /* float(int N) */
        Xe = (Ye - Se*CC1E) - Se*CC2E ;      /*  range reduction  */ 
                                          
        We = Xe*Xe ;

        Be = b1e*We + b0e ;                /* denominator  */
        De = (a1e*We + a0e)*Xe ;           /* numerator  */
        

        Recip = _rcpsp(Be-De);
		Recip = Recip*( 2 - (Be-De)*Recip ) ;
        Recip = Recip*( 2 - (Be-De)*Recip ) ;
        Re = Halfe + ( De * Recip ) ;
            
		Se =  _itof(_extu(Ne+128,23,0));

        Ce = Re*Se ;                       /* scale by power of 2  */ 
        
        if (Ye < LnMine)  Ce = Zeroe  ; /* < LnMin returns 0  */
        if (Ye > LnMaxe)  Ce = MAXe  ;  /* > LnMax returns MAX  */

        
        return Ce ;

}


/* ======================================================================== */
/*  End of file: exp10sp_c.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
