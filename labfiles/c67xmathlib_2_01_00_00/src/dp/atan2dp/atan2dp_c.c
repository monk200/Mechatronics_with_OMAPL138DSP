/* ======================================================================= */
/* atan2dp_c.c - double precision floating point arctanget two argument    */
/*              optimized  C implementation (w/ intrinsics) single sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


#include "atan2dp_c.h"


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

double atandp_ci(double a)
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
double  sqrt3 = 1.73205080756887729353e+0 ;       /* sqrt(3)      */
double  iims3 = 2.6794919243112270647e-1 ;        /* 2 - sqrt(3)  */
double  F, G, H, R, RN, RD ;
int     N, Sign ;



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

double atan2dp_c(double a, double b)
{



double   HalfPI= 1.57079632679489661923 ;
double   PI    = 3.14159265358979323846 ;
double   X,Y,Z,W, res ;


        Y = a ;
        X = b ;
        Z = divdpMod_ci(Y, X) ;
        W = atandp_ci(Z) ;
        res = W ;
        if (X < 0.0) //(M == 1)
        {
                res = PI + W ;
                if (W > 0.0) res = W - PI ;
        }
        
        
        if (X == 0.0f ) res = (Y>0.0f? HalfPI:-HalfPI); 
		if (Y == 0.0f ) res = 0.0f;
        
        return (res) ;

}

/* ======================================================================== */
/*  End of file: atan2dp_i.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
