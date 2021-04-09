/* ======================================================================= */
/* logsp_c.c - single precision floating point log                         */
/*             optimized  C implementation (w/ intrinsics) single sample   */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */



#include "logsp_i.h"

double logtable[8] = {0, -.1177830356,
						-.2231435513,
						-.3184537311,
						-.4054651081,
						-.4855078157,
						-.5596157879,
						-.6286086594};


float logsp_c(float a)
{


	double	ln2  =  0.693147180559945;
	float	c1 = -0.2302894f;
	float	c2 =  0.1908169f;
	float	c3 = -0.2505905f;
	float	c4 =  0.3333164f;
	float	c5 = -0.5000002f;

	unsigned int	T_index;
	
	double dr;
	double frcpax;
	int N;
	float pol;
	float r;
	float r2;
	float r3;
	float r4;
	double rcp;
	double res;
	double T;
	
 /* r = x * frcpa(x) -1 */
    rcp = _rcpdp((double) a);
	frcpax = _itod(_clr(_hi(rcp),0,16), 0);
	dr = frcpax * (double) a  - 1.0; 

 /* Polynomial p(r) that approximates ln(1+r) - r  */
    r = (float) dr;
	r2 = r*r;
	r3 = r*r2;
	r4 = r2*r2; 
	
	pol = c5 * r2 + ((c4 * r3) + ((c2 * r + c3) + c1 * r2) * r4);
 
 /* Reconstruction: result = T + r + p(r) */

	N = _extu(_hi(frcpax), 1, 21) - 1023;

	T_index = _extu(_hi(frcpax), 12, 29);

	T = logtable[T_index] - ln2 * (double) N;

	res = (dr  + T) + (double) (pol);

	if (a<0) res = -3.40282347e+38;

	return (res);


}

/* ======================================================================== */
/*  End of file: logsp_c.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
