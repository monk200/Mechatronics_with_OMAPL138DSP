/* ======================================================================= */
/* cosdp_c.c - double precision floating point cosine                      */
/*              optimized  C implementation (w/ intrinsics) single sample  */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */



#include "cosdp_c.h"


double cosdp_c(double a)
{

double  InvPI = 0.31830988618379067154 ;
double  C1    = 3.1416015625 ;
double  C2    =-8.908910206761537356617e-6 ;
double  r8    = 2.7204790957888846175e-15 ;
double  r7    =-7.6429178068910467734e-13 ;
double  r6    = 1.6058936490371589114e-10 ;
double  r5    =-2.5052106798274584544e-8 ;
double  r4    = 2.7557319210152756119e-6 ;
double  r3    =-1.9841269841201840457e-4 ;
double  r2    = 8.3333333333331650314e-3 ;
double  r1    =-1.6666666666666665052e-1 ;

/*                               2^30                   2^-20   */
double  MAX=1.073741824e+09;//, One  =1.0, Zero=0.0,  MIN=9.536743164054e-7 ;
double  Sign = 1, X, Z, F, F2, G, R ;
int     N ;

double  HalfPI= 1.57079632679489661923 ;

        a = fabs(a)+HalfPI;
        F = a;
        if (F > MAX) F = HalfPI ;             		/* quick exit option */
        

        X = F * InvPI ;                  	/* X = Y * (1/PI)  */
        N = _spint(X);
        Z = (N) ;                        	/* Z = double (N)  */
        if ( (N&1) != 0 ) Sign = -Sign ; 	/* neg. quadrants  */

        /* This is faster but may not be as accurate    */
        /*                F = F - (Z*PI) ;              */
        F = (F - (Z*C1)) - (Z*C2) ;
        
        R = fabs(F) ;
        F2 = F*F ;
        G = F2*F2;
        
        //split up this polynomial
        //R = (((((((r8*G+r7)*G+r6)*G+r5)*G+r4)*G+r3)*G+r2)*G+r1)*G 
        R = (((G*r8 + r6)*G + r4)*G + r2)*G;
		X = (((G*r7 + r5)*G + r3)*G + r1)*F2;
		R = R + X;
        G = (F + F*R)*Sign;  

        


        return ( G ) ;              

}


/* ======================================================================== */
/*  End of file: cosdp_c.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
