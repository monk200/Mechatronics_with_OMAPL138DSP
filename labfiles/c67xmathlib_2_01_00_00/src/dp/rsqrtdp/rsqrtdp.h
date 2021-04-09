/* ======================================================================= */
/* rsqrtdp.h - double precision doubleing point recip sqrt                 */
/*              optimized hand ASM single sample                           */ 
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#ifndef RSQRTDP_H_
#define RSQRTDP_H_ 1

double rsqrtdp(double a);
void rsqrtdp_v(double *arg, double *output, int size);

#endif
/* ======================================================================== */
/*  End of file: rsqrtdp.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
