/* ======================================================================= */
/* atan2dp.h - double precision floating point arctangent two arguments    */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef ATAN2DP_H_
#define ATAN2DP_H_ 1

double atan2dp(double a, double b);
void atan2dp_v(double *  arg, double *  arg2, double *  output, int size);

#endif
/* ======================================================================== */
/*  End of file: atan2dp.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
