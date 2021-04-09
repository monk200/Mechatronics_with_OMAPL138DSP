/* ======================================================================= */
/* rsqrtdp_c.c - double precision floating point recip sqrt                */
/*              optimized  C implementation (w/ intrinsics) single sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "rsqrtdp_c.h"


double rsqrtdp_c(double a)
{

double   arg,X0,X1,X2,X3,Zero=0.0,TWO=2.0,Big=4.5e+307,Small=0.445e-307 ;

        
        arg = fabs(a) ;
		X0 = _rsqrdp(arg);
		
        X1 = X0*(1.5 - (arg*X0)*(X0*0.5));
		X2 = X1*(1.5 - (arg*X1)*(X1*0.5));
		X3 = X2*(1.5 - (arg*X2)*(X2*0.5));


		if (arg<Small) X3 = _itof(0x7FFFFFFF);
		if (arg>(Big*TWO)) X3 = _itof(0);


		return X3;
}

/* ======================================================================== */
/*  End of file: rsqrtdp_c.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
