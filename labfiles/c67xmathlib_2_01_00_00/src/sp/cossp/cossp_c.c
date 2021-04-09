/* ======================================================================= */
/* cossp_i.c - single precision floating point cosine                      */
/*              optimized  C implementation (w/ intrinsics) single sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "cossp_c.h"


float cossp_c(float a)
{

/*                   2^20          1/(*2^12)  */
float Zero=0.0, MAX=1048576.0, MIN=2.4414062e-4;//, One=1.0 ;
float  Sign=1, X, Y, Z, F, G, R, InvPI=0.318309886183791 ;
float  s4= 2.601903036e-6, s3=-1.980741872e-4 ;
float  s2= 8.333025139e-3, s1=-1.666665668e-1 ;
float  C1= 3.140625,       C2= 9.67653589793e-4 ;
int    N ;
float	HalfPI=1.5707963268 ;

        a = fabsf(a)+HalfPI;
        Y = a ;
		if (Y > MAX)  Y = HalfPI;

        X = Y * InvPI ;                         /* X = Y * (1/PI)  */
        N = _spint(X) ;                         /* N = integer part of X  */
        Z = N ;                                 /* Z = float (N)  */
        if ( (N&1) != 0 )  Sign = -Sign  ;      /* quad. 3 or 4   */

/* This is faster but not as accurate   */
/*        F = Y - (Z*PI) ;      */

        F = (Y - (Z*C1)) - (Z*C2) ;      
        R = F ;
        if (F < Zero) R = -R ;
        if (R < MIN)  return(R*Sign)  ;
        G = F*F ;
        R = (((s4*G+s3)*G+s2)*G+s1)*G ;
        return ( (F + F*R)*Sign ) ;
}

/* ======================================================================== */
/*  End of file: cossp_i.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

