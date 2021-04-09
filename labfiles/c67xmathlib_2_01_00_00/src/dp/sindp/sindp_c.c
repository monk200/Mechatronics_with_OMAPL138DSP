/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      cosdp -- Double Precision Cosine                                    */
/*                                                                          */
/*S AUTHOR                                                                 S*/
/*S     Roshan Gummattira                                                  S*/
/*S                                                                        S*/
/*S REVISION HISTORY                                                       S*/
/*S     10-Sep-2002 Initial revision . . . . . . . . . . .  Autogen        S*/
/*S                                                                        S*/
/*  USAGE                                                                   */
/*      This function is C callable, and is called according to this        */
/*      C prototype:                                                        */
/*                                                                          */
/*      double cos                                                          */
/*      (                                                                   */
/*        double a  // Argument 1   //                                      */
/*      );                                                                  */
/*                                                                          */
/*  DESCRIPTION                                                             */
/*      This kernel returns the double precision cosine of the              */
/*      floating point argument a expressed in radians. The return          */
/*      value is in the range of [-1,+1].                                   */
/*                                                                          */
/*  TECHNIQUES                                                              */
/*                                                                          */
/*  SOURCE                                                                  */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2002 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
//#pragma CODE_SECTION(sindp_c, ".text:instrinsic");

#include "sindp_i.h"

/* ======================================================================== */
/*S Place file level definitions here.                                     S*/
/* ======================================================================== */

#include <math.h>

double sindp_c(double a)
{

/* ======================================================================== */
/*S Place source code here.                                                S*/
/* ======================================================================== */
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
//double  PI    = 3.14159265358979323846 ;
//double  HalfPI= 1.57079632679489661923 ;
/*                               2^30                   2^-20   */
double  MAX=1.073741824e+09, Zero = 0.0;//, One  =1.0, Zero=0.0,  MIN=9.536743164054e-7 ;
double  Sign = 1, X, Z, F, F2, G, R ;
// double  Y ;
int     N ;

//double  HalfPI= 1.57079632679489661923 ;

        //a = fabs(a)+HalfPI;
        //Sign = One;
        F = a;//fabs(a) ;

        //if (a < Zero) Sign = -Sign ;
        //if (F < MIN) return(a) ;      */          /* quick exit option */
        if (F > MAX) F = Zero ;             		/* quick exit option */

        
        //if (F > HalfPI)                     		/* need argument reduction ? */
        //{
                X = F * InvPI ;                  	/* X = Y * (1/PI)  */
                //N = (X+0.5) ;                    	/* N = integer part of X   */
                N = _spint(X);
                Z = (N) ;                        	/* Z = double (N)  */
                if ( (N&1) != 0 ) Sign = -Sign ; 	/* neg. quadrants  */

        /* This is faster but may not be as accurate    */
        /*                F = F - (Z*PI) ;              */

                F = (F - (Z*C1)) - (Z*C2) ;
        //}
        
 
        R = fabs(F) ;
		//if (R < MIN) return(R*Sign) ;   /* sin(arg1 < MIN) returns arg1  */
        F2 = F*F ;
        G = F2*F2;
        
        R = (((G*r8 + r6)*G + r4)*G + r2)*G;
		X = (((G*r7 + r5)*G + r3)*G + r1)*F2;
		R = R + X;
        G = (F + F*R)*Sign;  

        //R = (((((((r8*G+r7)*G+r6)*G+r5)*G+r4)*G+r3)*G+r2)*G+r1)*G ;pipelined this polynomial
        //R = r8*G+r7;
		//R = R*G+r6;
		//R = R*G+r5;
		//R = R*G+r4;
		//R = R*G+r3;
		//R = R*G+r2;
		//R = R*G+r1;
		//R = R*G;
          
        
        //if (a < MIN) G = a*Sign;
        return ( G ) ;           
        
}
