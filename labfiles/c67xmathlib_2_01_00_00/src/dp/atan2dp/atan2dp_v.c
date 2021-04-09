/* ======================================================================= */
/* atan2dp_v.c - double precision floating point arctangent two argument   */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "atan2dp_i.h"


void atan2dp_v(double * restrict arg, double * restrict arg2, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = atan2dp_i(arg[x], arg2[x]);
		}
}

/* ======================================================================== */
/*  End of file: atan2sp_v.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
