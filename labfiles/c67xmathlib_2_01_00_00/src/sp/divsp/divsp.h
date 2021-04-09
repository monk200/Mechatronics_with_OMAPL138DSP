/* ======================================================================= */
/* divsp.h - single precision floating point divide                        */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef DIVSP_H_
#define DIVSP_H_ 1

float divsp(float a, float b);
void divsp_v(float *arg, float *arg2, float *output, int size);

#endif
/* ======================================================================== */
/*  End of file: divsp.h                                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
