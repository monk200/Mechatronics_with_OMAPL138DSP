/* ======================================================================= */
/* recipdp_v.c - double precision floating point reciprocal                */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "recipdp_i.h"


void recipdp_v(double * restrict arg, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = recipdp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: recipdp_v.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
