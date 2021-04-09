/* ======================================================================= */
/* powsp_c.h - double precision floating point raise to a power            */
/*             optimized  C implementation (w/ intrinsics) single sample   */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


#include "powdp_c.h"

static inline double divdpMod_powc(double a, double b)
{


/*                                  */
double  X, TWO=2.0;



        X = _rcpdp(b) ;
        
        X = X*( TWO - b*X ) ;
        X = X*( TWO - b*X ) ;
		X = X*( TWO - b*X );
        
        
		// a*X = a*(1/b)
		X = a*X;



        return (X) ;           /* returns DP FP value = 1.0 / A */

}

static inline double logdp_powc(double a)
{

double Zero = 0.0, Half = 0.5 ;
double srHalf= 0.70710678118654752440 ;         /*  sqrt(0.5)   */
double MIN   =    2.2250738585072014e-308 ;
double LnMin = -708.3964185322641 ;
double MAX   =    1.7976931348623157e+308 ;
double LnMax =  709.7827138470578 ;
double  a0 =-0.64124943423745581147e+2 ;
double  a1 = 0.16383943563021534222e+2 ;
double  a2 =-0.78956112887491257267e+0 ;
double  b0 =-0.76949932108494879777e+3 ;
double  b1 = 0.31203222091924532844e+3 ;
double  b2 =-0.35667977739034646171e+2 ; /*  Note b3 = 1.0        */
double  c1 = 0.693359375  ;       		 /*  355/512      */
double  c2 =-2.121944400546905827679e-4 ;

double  Y,Z,zn,zd,X,W,Rz,Sa,Bd,Cn,Da ;
int     N, exp, upper; 

        Y = a ;
        //N = gtexp(Y) ;     /* get unbiased exponent  */
        exp = _extu(_hi(Y),1,21);
       	N = exp - 1022;

		//Z = fxexp(Y) ;     /* force SP exp = 1022 if not zero     */
 		upper = _clr(_hi(Y),20,31);
		upper = 0x3fe00000 | upper;
		Z = _itod(upper, _lo(Y));
		if (exp == 0) Z = 0;


        
        
        if (Z > srHalf)
                { zn=(Z-Half)-Half ; zd=Z*Half+Half  ; }
        else
                { zn=Z-Half; zd=zn*Half+Half ; N=N-1 ; }
        
        
        //X = zn/zd;
        X = divdpMod_powc(zn,zd);
        
        W = X*X ;
        Bd= ( (W+b2) * W + b1) * W + b0 ;
        Cn= (W*a2 + a1) * W + a0 ;
        Rz= W * divdpMod_powc(Cn,Bd);//Cn / Bd ;
        Sa = X + X*Rz ;
        Cn= N ;
        Da = (Cn*c2 + Sa) + Cn*c1 ;




		if (Y <= Zero) Da = -1;//{Z = setnmx(Y) ; Da = (Z) ; }
        if (Y < MIN)  Da = (LnMin)  ;
        if (Y > MAX)  Da = (LnMax)  ;




        return (Da) ;

}



static inline double expdp_powc(double a)
{

double Halfe = 0.5; //Zeroe = 0.0, Onee = 1.0,  ;
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


double  Ye,Xe,We,Re,Se,Be,Ce,De;
int     Ne, upper; 


        Ye = a;      
        Ce = Ye*L2e ;                     /* base e --> base 2 argument */           
        Ne = _dpint(Ce) ;                 /* get unbiased exponent as an int */
        Se = Ne ;                         /* double(int N) */ 
        Xe = (Ye - Se*c1e) - Se*C2e ;         /*  range reduction  */ 
        We = Xe*Xe ;
        Be = (b2e*We + b1e)*We + b0e ;                  /* denominator  */
        De = ((a2e*We + a1e)*We + a0e)*Xe ;             /* numerator  */
        Re = Halfe + divdpMod_powc( De, (Be-De) ) ;
        upper = 1024 + Ne;
        upper = _extu(upper,20,0); 
        Se = _itod(upper,0x00000000);
        Ce = Re*Se ;                       /* scale by power of 2  */ 



		
        
        if (a > LnMaxe)  Ce = (Maxe)  ;  /* > LnMax returns MAX  */
        return (Ce) ;
}



double powdp_c(double a, double b)
{

/*                                   (2 ^ +127)          (2 ^ -126)   */
double   arg,W,X2;//,Zero=0.0,TWO=2.0,Big=1.7014118e+38,Small=1.17549435e-38 ;
int y, Sign=1,exp;
        
		
		y = _dpint(b);

		if (a<0 & b==y){
			if (y&1){
				Sign = -1;	
			}
		}	
		
		arg = fabs(a);
		W = b*logdp_powc(arg);
     	X2 = Sign*expdp_powc(W);
	
		if (a<0 & b!=y) X2 = _itod(0x7fffffff, 0xffffffff); // NaN	
		exp = _extu(_ftoi(_hi(arg)),1,21);
		if (exp<1) X2 = 0;
		

		return (X2); 
}



/* ======================================================================== */
/*  End of file: powdp_c.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
