/* ======================================================================= */
/* expdp_v.c - double precision floating point exp                         */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "expdp_i.h"

void expdp_v(double * restrict arg, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = expdp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: expdp_v.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */



