/* ======================================================================= */
/* powsp_c.h - single precision floating point raise to a power            */
/*             optimized  C implementation (w/ intrinsics) single sample   */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


#include "powsp_i.h"


float powsp_c(float a, float b)
{


/*                                   (2 ^ +127)          (2 ^ -126)   */
float   arg,W,X2;//,Zero=0.0,TWO=2.0,Big=1.7014118e+38,Small=1.17549435e-38 ;
int y, Sign=1,exp;
        
		
		y = _spint(b);

		if (a<0 & b==y){
			if (y&1){
				Sign = -1;	
			}
		}	
		
		arg = fabsf(a);
		W = b*logsp_i1(arg);
     	X2 = Sign*expsp_i1(W);
	
		if (a<0 & b!=y) X2 = _itof(0x7fffffff); // NaN	
		
		exp = _extu(_ftoi(arg),1,24);
		if (exp<1) X2 = 0;
		
		//if (exp>254) X2 = _itof(0x7F800000);
		//if (arg>Big) X2 = _itof(0x7F800000); //Infinity
		//if (arg<Small) X2 = 0;
		//if (a == 0) X2 =  0;

		// Old Range Checks
		//if (W>88.029692) X2 = _itof(0x7F800000);	//Infinity
		//if (W<-87.336545) X2 = 0;	
		//if (a!=arg && b!=a) X2 = _itof(0x7fffffff); // NaN
		//if (arg>Big) X2 = _itof(0x7F800000); //Infinity
		//if (arg<Small) X2 = 0;
		//if (b == 0) X2 =  1;
		//if (a == 0) X2 = 0;

		return (X2); 
}


/* ======================================================================== */
/*  End of file: powsp_c.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2002 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
