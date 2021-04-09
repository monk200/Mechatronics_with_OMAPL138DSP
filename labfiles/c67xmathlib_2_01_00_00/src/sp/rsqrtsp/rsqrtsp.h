/* ======================================================================= */
/* rsqrtsp.h - single precision floating point reciprocal sqrt             */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef RSQRTSP_H_
#define RSQRTSP_H_ 1

float rsqrtsp(float a);
void rsqrtsp_v(float *arg, float *output, int size);

#endif
/* ======================================================================== */
/*  End of file: rsqrtsp.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
