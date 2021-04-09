/* ======================================================================= */
/* divdp.h - double precision floating point divide                        */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef DIVDP_H_
#define DIVDP_H_ 1

double divdp(double a, double b);
void divdp_v(double *arg, double *arg2, double *output, int size);

#endif
/* ======================================================================== */
/*  End of file: divdp.h                                                    */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
