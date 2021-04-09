/* ======================================================================= */
/* atansp_c.c - double precision floating point cosine                     */
/*              Optimized  C Implementation (w/ Intrinsics) Single Sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


#include "atandp_c.h"




double divdpMod_ci(double a, double b)
{

double  X, TWO=2.0;



        X = _rcpdp(b) ;
        
        X = X*( TWO - b*X ) ;
        X = X*( TWO - b*X ) ;
		X = X*( TWO - b*X );
        
        
		//a*X = a*(1/b)
		X = a*X;



        return (X) ;           /* returns DP FP value = 1.0 / A */

}

double atandp_c(double a)
{

double  V[4]  = { 0.0,
                  		 5.2359877559829887308e-1,
                  		 1.57079632679489661923,
                  		 1.04719755119659774615 }   ;


double  MIN   = 1.490116119384e-8 ;           /* 2^-26        */
double  p0    =-1.3688768894191926929e+1 ;
double  p1    =-2.0505855195861651981e+1 ;
double  p2    =-8.4946240351320683534e+0 ;
double  p3    =-8.3758299368150059274e-1 ;
double  q0    = 4.1066306682575781263e+1 ;
double  q1    = 8.6157349597130242515e+1 ;
double  q2    = 5.9578436142597344465e+1 ;
double  q3    = 1.5024001160028576121e+1 ;
// double  q4    = 1.0 ;
double  sqrt3 = 1.73205080756887729353e+0 ;       /* sqrt(3)      */
double  iims3 = 2.6794919243112270647e-1 ;        /* 2 - sqrt(3)  */
double  F, G, H, R, RN, RD ;
int     N, Sign ;

// double   X, Y, W, Z ;
// int      M ;
// double   HalfPI= 1.57079632679489661923 ;
// double   PI    = 3.14159265358979323846 ;
// double   One   = 1.0 ;
// double   ZERO  = 0.0 ;

        Sign = 0 ;
        F = a ;
        N = 0 ;
        if (F < 0.0)   { F = -F ; Sign = 1 ; } 
        if (F > 1.0)   { F = divdpMod_ci(1,F); N = 2 ; }
        if (F > iims3) { N=N+1 ; F = divdpMod_ci((F * sqrt3 - 1.0), (F + sqrt3)) ; } 
        H = F ;
        if (H < 0.0) H = -H ;
        if (H > MIN)
        {
                G = H*H ;
                RN = (((p3*G + p2)*G + p1)*G + p0)*G  ;
                RD = (((G + q3)*G + q2)*G + q1)*G + q0 ;
                R = divdpMod_ci(RN, RD) ;
                F = (F + F*R) ;
        }
        if (N > 1) F = -F ;
        H = F + V[N] ;
        if (Sign == 1) H = -H ;
        return ( H ) ;

}

/* ======================================================================== */
/*  End of file: atandp_c.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
