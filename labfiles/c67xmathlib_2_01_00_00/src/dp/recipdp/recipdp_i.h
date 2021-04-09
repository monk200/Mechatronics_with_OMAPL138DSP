/* ======================================================================= */
/* recipdp_i.h - double precision floating point reciprocal                */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */ 

static inline double recipdp_i(double a)
{

double  X,XX, Y, Zero=0, TWO=2.0, MTWO=-2.0, Big=4.5e+307, Small=0.445e-307 ;

        Y = _fabs(a) ;
        X = _rcpdp(a) ;
        
        X = X*( TWO - a*X ) ;
        XX = X*( TWO - a*X ) ;
		X = XX*( TWO - a*XX );
        
        
       if (Y < Small) {
                X = (Big*TWO);
                if (a < Zero) X = (Big*MTWO) ;  /* Div by Small returns MAX     */
                      }
        
        
        if (Y > Big) X = (Zero) ;         /* Div by MAX returns 0 */

        return (X) ;           /* returns DP FP value = 1.0 / A */

}

/* ======================================================================== */
/*  End of file: recipsp_i.h                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


