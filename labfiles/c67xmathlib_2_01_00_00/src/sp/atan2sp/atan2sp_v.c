/* ======================================================================= */
/* atan2sp_v.c - single precision floating point arctangent two argument   */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "atan2sp_i.h"

void atan2sp_v(float * restrict arg, float * restrict arg2, float * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = atan2sp_i(arg[x], arg2[x]);
		}
}

/* ======================================================================== */
/*  End of file: atan2sp_v.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
