/* ======================================================================= */
/* logsp_v.c - single precision floating point log                         */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "logsp_i.h"


void logsp_v(float * restrict arg, float * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = logsp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: logsp_v.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
