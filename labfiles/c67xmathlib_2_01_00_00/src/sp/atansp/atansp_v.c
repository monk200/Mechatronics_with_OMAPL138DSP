/* ======================================================================= */
/* atansp_vec.c - single precision floating point cosine                   */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "atansp_i.h"


void atansp_v(float * restrict arg, float * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = atansp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: atandp_vec.c                                               */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
