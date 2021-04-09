/* ======================================================================= */
/* log2dp_v.c - double precision floating point log base 2                 */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "log2dp_i.h"

void log2dp_v(double * restrict arg, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = log2dp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: log2dp_v.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */




