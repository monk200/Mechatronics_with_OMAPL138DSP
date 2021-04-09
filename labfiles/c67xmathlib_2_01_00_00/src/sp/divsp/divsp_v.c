/* ======================================================================= */
/* divsp_v.c - single precision floating point divide                    */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */


#include "divsp_i.h"


void divsp_v(float * restrict arg, float * restrict arg2, float * restrict output, int size){
		int x;	
		for (x = 0; x < size; x++) {
				output[x] = divsp_i(arg[x], arg2[x]);
		}
}

/* ======================================================================== */
/*  End of file: divsp_v.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
