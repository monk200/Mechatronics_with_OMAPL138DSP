/* ======================================================================= */
/* powdp.h - double precision floating point raise to power                */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef POWDP_H_
#define POWDP_H_ 1

double powdp(double a, double b);
void powdp_v(double *arg, double *arg2, double *output, int size);

#endif

/* ======================================================================== */
/*  End of file: powsp.h                                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
