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

#ifndef RSQRTDP_I_H_
#define RSQRTDP_I_H_ 1

static inline double rsqrtdp_i(double a)
{

double   arg,X0,X1,X2,X3,TWO=2.0,Big=4.5e+307,Small=0.445e-307 ; ;

        
        arg = _fabs(a) ;
		X0 = _rsqrdp(arg);
		
        X1 = X0*(1.5 - (arg*X0)*(X0*0.5));
		X2 = X1*(1.5 - (arg*X1)*(X1*0.5));
		X3 = X2*(1.5 - (arg*X2)*(X2*0.5));


		if (arg<Small) X3 = _itof(0x7FFFFFFF);
		if (arg>(Big*TWO)) X3 = _itof(0);


		return X3;
}

#endif


/* ======================================================================== */
/*  End of file: rsqrtsp_i.h                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
