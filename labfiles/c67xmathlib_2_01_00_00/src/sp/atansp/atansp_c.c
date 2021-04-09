/* ======================================================================= */
/* atansp_c.c - single precision floating point cosine                     */
/*              Optimized  C Implementation (w/ Intrinsics) Single Sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "atansp_i.h"


float atanf_atan2f_sr1(float g, float pih, int s, int bn, int an);
float atanf_atan2f_sr2(float a, int at2, float numer);
float atanf_atan2f_sr2(float b, int at2, float a)
{

	float	bg;
	float	g;

	/* calculate 1/b and multiply by a if called from atan2f */
	g = _rcpsp(b);
	g = g*(2.0f - b*g);
	bg = b*g;
	if(at2) g = g*a;
	g = g*(2.0f - bg);	
	return(g);
}


float atanf_atan2f_sr1(float g, float pih, int s, int bn, int an)
{

	float	c1 =  0.00230158202f;
	float	c2 = -0.01394551000f;
	float	c3 =  0.03937087815f;
	float	c4 = -0.07235669163f;
	float	c5 =  0.10521499322f;
	float	c6 = -0.14175076797f;
	float	c7 =  0.19989300877f;
	float	c8 = -0.33332930041f;
	float 	coef;
	float	g2;
	float	g4;
	float	g6;
	float	g8;
	float	g10;
	float	g12;
	int 	ns_nbn;
	float	pol;
	float	tmp1;
	float	tmp2;

	/* get coef based on the flags */
	coef = pih;
	if(!s) coef = 3.1415927f;
    ns_nbn = s | bn;
    if(!ns_nbn) coef = 0;
    if(an) coef = -coef;
 
	/* calculate polynomial */
	g2 = g*g;
	g4 = g2*g2;
	g6 = g2*g4;
	g8 = g4*g4;
	g10 = g6*g4;
	g12 = g8*g4;

	tmp1 =  ((c5 * g8) + (c6 * g6)) + ((c7 * g4) + (c8 * g2));
	tmp2 =  (((c1 * g4 + c2 * g2) + c3) * g12) + (c4 * g10);

	pol = tmp1 + tmp2;
	pol =  pol*g + g;

	return( s ? (coef - pol) : (coef + pol));
}



float atansp_c(float a)
{


	int neg =0;
	int rec =0;
	float  g;
	float res;
	int expo;
	float pih = 1.570796326794f;
   
	if(a<0){
		neg =1;   /* flag for a negative */
	}

	/* get a's exponent */
    expo = _extu(_ftoi(a), 1, 24);

	/* quick return for huge or tiny input values */
    if (expo < (127-13)) return(a);
    if (expo > (127+25)) return(a>0 ? pih : -pih);
    
    /* if |a|>1.05 call div sub routine before calculate polynomial */
	if( _fabsf(a) < 1.05f){
		g = a;
	}
	else {
		rec = 1;
    	g = atanf_atan2f_sr2(a, 0, 0.0f);
	}
	/* call polynomial sub routine */
	res =  atanf_atan2f_sr1(g, 1.57079632679f, rec, 0, neg);
	return (res);


}

/* ======================================================================== */
/*  End of file: atansp_c.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
