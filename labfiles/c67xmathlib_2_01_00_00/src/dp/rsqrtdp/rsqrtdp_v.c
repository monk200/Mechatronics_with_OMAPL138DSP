/* ======================================================================= */
/* rsqrtdp_v.c - double precision floating point recip sqrt                */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include "rsqrtdp_i.h"


void rsqrtdp_v(double * restrict arg, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = rsqrtdp_i(arg[x]);
		}
}

/* ======================================================================== */
/*  End of file: rsqrtdp_v.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
