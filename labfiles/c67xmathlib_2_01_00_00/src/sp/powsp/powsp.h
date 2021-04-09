/* ======================================================================= */
/* powsp.h - single precision floating point raise to power			       */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef POWSP_H_
#define POWSP_H_ 1

float powsp(float a, float b);
void powsp_v(float *arg, float *arg2, float *output, int size);

#endif
/* ======================================================================== */
/*  End of file: powsp.h                                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
