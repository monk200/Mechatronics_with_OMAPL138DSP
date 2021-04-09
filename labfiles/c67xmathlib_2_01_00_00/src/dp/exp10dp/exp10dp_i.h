/* ======================================================================= */
/* exp10dp_i.h - double precision floating point exp base 10               */
/*              optimized inlined C Implementation (w/ Intrinsics)         */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef EXP10DP_I_
#define EXP10DP_I_ 1


static inline double divdpMod_ci4(double a, double b)
{

double  X, TWO=2.0;



        X = _rcpdp(b) ;
        
        X = X*( TWO - b*X ) ;
        X = X*( TWO - b*X ) ;
		X = X*( TWO - b*X );
        
        
		// a*X = a*(1/b)
		X = a*X;



        return (X) ;           /* returns DP FP value = 1.0 / A */

}



static inline double exp10dp_i(double a)
{


double Halfe = 0.5; // Zeroe = 0.0, Onee = 1.0;
double Maxe  =    1.7976931348623157e+308 ;
double LnMaxe=  709.7827138470578 ;
double  a0e= 0.249999999999999993;
double  a1e= 0.694360001511792852e-2 ;
double  a2e= 0.165203300268279130e-4;
double  b0e= 0.5 ;
double  b1e= 0.555538666969001188e-1 ;
double  b2e= 0.495862884905441294e-3 ; 
double  c1e= 0.693359375  ;                /*  355/512      */
double  C2e=-2.1219444005469058277e-4 ;
double L2e = 1.4426950408889634074  ;      /* log (base  2) of e   */ 
double  Ln10=2.302585092994046 ;


double  Ye,Xe,We,Re,Se,Be,Ce,De;
int     Ne, upper; 


        Ye = Ln10*a;
        Ce = Ye*L2e ;                     /* base e --> base 2 argument */           
        Ne = _dpint(Ce) ;                 /* get unbiased exponent as an int */
        Se = Ne ;                         /* double(int N) */ 
  
        Xe = (Ye - Se*c1e) - Se*C2e ;         /*  range reduction  */ 

        We = Xe*Xe ;

        Be = (b2e*We + b1e)*We + b0e ;                  /* denominator  */
        De = ((a2e*We + a1e)*We + a0e)*Xe ;             /* numerator  */
        
        Re = Halfe + divdpMod_ci4( De, (Be-De) ) ;
   
        upper = 1024 + Ne;
        upper = _extu(upper,20,0); 
        Se = _itod(upper,0x00000000);
		Ce = Re*Se ;                       /* scale by power of 2  */ 
       
        if (a > LnMaxe)  Ce = (Maxe)  ;  /* > LnMax returns MAX  */
        return (Ce) ;
}

#endif


/* ======================================================================== */
/*  End of file: exp10dp_i.h                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
