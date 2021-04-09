/* ======================================================================= */
/* divdp_i.h - double precision divide                                     */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

static inline double divdp_i(double a, double b)
{


/*                                   (2 ^ +126)*4          (2 ^ -126)   */
double  X, Y, Zero=0, TWO=2.0, MTWO=-2.0, Big=4.5e+307, Small=0.445e-307 ;


        Y = _fabs(b) ;
        X = _rcpdp(b) ;
        
        X = X*( TWO - b*X ) ;
        X = X*( TWO - b*X ) ;
		X = X*( TWO - b*X );
        
        
		// a*X = a*(1/b)
		X = a*X;

       if (Y < Small) {
                X = (Big*TWO);
                if (b < Zero) X = (Big*MTWO) ;  /* Div by Small returns MAX     */
       }
        
        
        if (Y > Big) X = (Zero) ;         /* Div by MAX returns 0 */

        return (X) ;           /* returns DP FP value = 1.0 / A */

}



/* ======================================================================== */
/*  End of file: divdp_i.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


