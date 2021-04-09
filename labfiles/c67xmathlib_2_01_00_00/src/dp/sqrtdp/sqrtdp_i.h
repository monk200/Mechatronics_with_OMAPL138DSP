/* ======================================================================= */
/* sqrtdp_i.h - double precision floating point sqrt                       */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */  


static inline double sqrtdp_i(double a)
{


 
double   arg,X0,X1,X2,X4,Zero=0.0;//,X3,TWO=2.0,Big=4.5e+307,Small=0.445e-307; 
int upper, exp;
 		
		
 		arg = a;
       	upper = _clr(_hi(arg),31,31);
		arg = _itod(upper, _lo(arg));
		X0 = _rsqrdp(arg);
		
        X1 = X0*(1.5 - (arg*X0)*(X0*0.5));
		X2 = X1*(1.5 - (arg*X1)*(X1*0.5));
		X4 = arg*X2*(1.5 - (arg*X2)*(X2*0.5));
		exp = _extu(_hi(a),1,21);
		if (exp>(2046)) X4 = Zero;
		


		return X4;
}

/* ======================================================================== */
/*  End of file: sqrtsp_i.h                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
