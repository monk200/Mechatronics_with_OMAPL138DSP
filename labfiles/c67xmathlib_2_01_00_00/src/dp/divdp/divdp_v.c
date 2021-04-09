/* ======================================================================= */
/* divdp_v.c - single precision floating point divide                      */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "divdp_i.h"


void divdp_v(double * restrict arg, double * restrict arg2, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = divdp_i(arg[x], arg2[x]);
		}
}

/* ======================================================================== */
/*  End of file: divsp_v.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


