/* ======================================================================= */
/* log10dp_v.c - double precision floating point log base 10               */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "log10dp_i.h"

void log10dp_v(double * restrict arg, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = log10dp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: log10dp_v.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */




