/* ======================================================================= */
/* rsqrtsp_c.h - single precision floating point reciprocal sqrt           */
/*             optimized  C implementation (w/ intrinsics) single sample   */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "rsqrtsp_c.h"

float rsqrtsp_c(float a)
{


/*                                   (2 ^ +126)*4          (2 ^ -126)   */
float   arg,X0,X1,X2,X3,Zero=0.0,TWO=2.0,Big=8.5070592e37*TWO*TWO,Small=1.17549435e-38 ; ;

        
        arg = fabsf(a) ;
		X0 = _rsqrsp(arg);
		X1 = arg*X0;
		
		X3 = 1.5 - (X1)*(X0*0.5);
        X1 = X0*X3;
		X2 = X1*(1.5 - (arg*X1)*(X1*0.5));
		
		if (arg<Small) X2 = _itof(0x7fffffff);
		if (arg>Big) X2 = Zero;
		
		return (X2); 

}


/* ======================================================================== */
/*  End of file: rsqrtsp_c.h                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
