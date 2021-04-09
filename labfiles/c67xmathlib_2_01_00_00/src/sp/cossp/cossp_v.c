/* ======================================================================= */
/* cossp_v.c - single precision floating point cosine                    */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "cossp_i.h"


void cossp_v(float * restrict arg, float * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = cossp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: cossp_v.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

