/* ======================================================================= */
/* expsp_c.c - single precision floating point exp                         */
/*              optimized  C implementation (w/ intrinsics) single sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "expsp_c.h"

// lookup tables	
	/* kTable:  2^(0/4), 2^(1/4), 2^(2/4), 2^(3/4) */
static double kTable[4] = {1.0, 1.189207115, 1.414213562, 1.681792831}; 

	/* jTable:  2^(0/16), 2^(1/16), 2^(2/16), 2^(3/16) */
static double jTable[4] = {1.0, 1.044273782, 1.090507733, 1.138788635}; 


float expsp_c(float a)
{

	
	float	c0 = 0.1667361910f;
	float	c1 = 0.4999999651f;
	float	c2 = 0.9999998881f;
	double	dT;
	int		J;
	int		K;
	float	lnbase = 1.0f;
	float	log2_base_x16 = 1.442695041 * 16.0;
	int		N;
	float	P1 = 0.04331970214844;
	float	P2 = 1.99663646e-6;
	float	pol;
	float	r;
	float	r2;
	float	r3;
	double	resdp;
	unsigned int	Ttemp;


	/* Get N such that |N - x*16/ln(2)| is minimized */
	N = (int) (a * log2_base_x16 +.5f);
	
	if(( a * log2_base_x16)<-0.5f){
		N--;
	}

	/* Argument reduction, r, and polynomial approximation pol(r) */
	r = (a - P1 * (float) N) - P2 * (float) N;
	r2 = r * r;
	r3 = r * r2;
 
	pol = (r * c2) + ((r3 * c0) + (r2 * c1));
 
	/* Get index for ktable and jtable */
	K = _extu(N, 28, 30);
	J = N & 0x3;
	dT = kTable[K] * jTable[J];

	/* scale exponent to adjust for 2^M */
	Ttemp = _hi(dT) + (unsigned int) ((N >> 4) << 20);
	dT = _itod( Ttemp, _lo(dT));

	resdp = (dT * (1.0 + pol));
	
	if(_extu(_ftoi(a * lnbase), 1, 24) < 114){
		resdp = (1.0f + a * lnbase);               /* early exit for small a*/
	}

	/* Check if result would be +Inf. In that case,  */
	/* return 0x7f7fffff instead                     */
	if((a * lnbase)>88.722831726f){
		resdp = (_itof(0x7f7fffff));
	} 

	return((float) resdp);
}


/* ======================================================================== */
/*  End of file: expsp_c.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

