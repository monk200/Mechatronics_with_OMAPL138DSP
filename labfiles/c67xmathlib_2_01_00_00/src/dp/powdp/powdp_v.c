/* ======================================================================= */
/* powdp_v.c - double precision floating point raise to a power            */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


#include "powdp_i.h"


void powdp_v(double * restrict arg, double * restrict arg2, double * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = powdp_i(arg[x], arg2[x]);
		}
}

/* ======================================================================== */
/*  End of file: powdp_v.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
