/* ======================================================================= */
/* log2sp_v.c - single precision floating point log base 2               */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "log2sp_i.h"


void log2sp_v(float * restrict arg, float * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = log2sp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: log2sp_v.c                                               */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
