/* ======================================================================= */
/* divsp_i.h - single precision floating point cosine                      */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef DIVSP_I_
#define DIVSP_I_ 1

static inline float divsp_i(float a, float b)
{


/*                                   (2 ^ +126)*4          (2 ^ -126)   */
float   X,Y,Zero=0.0,TWO=2.0,Big=8.5070592e37*TWO*TWO,Small=1.17549435e-38 ;

      Y = _fabsf(b) ;
      X = _rcpsp(b) ;
        
      X = X*( TWO - b*X ) ;
      X = X*( TWO - b*X ) ;

	  X = a*X;

	  if (Y < Small){     
           X = Big ;                /* Div by Small, return MAX    */ 
              if (b < Zero){
                 	X = -Big ;
              }  
        }
  		
		
		
		if (Y > Big) X = 0 ;            /* Div by MAX, return 0 */
        return (X) ;           /* returns SP FP value = 1.0 / A  */

}

#endif


/* ======================================================================== */
/*  End of file: divsp_i.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
