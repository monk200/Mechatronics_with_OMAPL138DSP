/* ======================================================================= */
/* sindp_v.c - single precision floating point sine                      */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "sindp_i.h"


void sindp_v(double* restrict arg, double* restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = sindp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: sinsp_v.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */



