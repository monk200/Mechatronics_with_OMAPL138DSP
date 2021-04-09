/* ======================================================================= */
/* atan2dp_vec.c - double precision floating point arctangent two argument */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "atan2dp_vec.h"
#include "atan2dp_inline.h"


void atan2dp_vec(double *arg, double *arg2, double *output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = atan2dp_inline(arg[x], arg2[x]);
		}
}

/* ======================================================================== */
/*  End of file: atan2sp_vec.c                                              */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
