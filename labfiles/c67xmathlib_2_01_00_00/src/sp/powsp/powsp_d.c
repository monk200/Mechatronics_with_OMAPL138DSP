/* ======================================================================= */
/* powsp_d.c - single precision floating point raise to power driver file  */
/*                                                                         */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#include "powsp.h"
#include "powsp_i.h"
#include "powsp_c.h"

#define BUF_SIZE 128

extern float gimme_random( void );
extern float gimme_random2( void );
extern int isequal(float *arg1, float *arg2, int size, double tol);

/* Global declarations */
float array0[BUF_SIZE];
float array00[BUF_SIZE];
float array1[BUF_SIZE];
float array2[BUF_SIZE];
float array3[BUF_SIZE];
float array4[BUF_SIZE];
float array5[BUF_SIZE];


float * restrict arg;
float * restrict arg1;
float * restrict output0;
float * restrict output1;
float * restrict output2;
float * restrict output3;
float * restrict output4;

float t_start, t_stop, t_offset;
float clockdata[5];

int pass_flag1 = 0;
int pass_flag2 = 0;

//  Number of input arguments:
#define NUM_INPUTS  (100)

//  Floating Point Tolerances
#define RET_VAL_TOL (0.000005)

//  Initialized arrays with fixed test data
float a [NUM_INPUTS] = 
{
/* Input Number: 0 */
- 6.2674615,

/* Input Number: 1 */
- 8.9541214,

/* Input Number: 2 */
  9.0147413,

/* Input Number: 3 */
  8.3288975,

/* Input Number: 4 */
  1.7458942,

/* Input Number: 5 */
  7.2526186,

/* Input Number: 6 */
- 0.5334484,

/* Input Number: 7 */
- 1.2066532,

/* Input Number: 8 */
- 3.3643183,

/* Input Number: 9 */
- 0.3106860,

/* Input Number: 10 */
- 8.6991514,

/* Input Number: 11 */
  9.2646808,

/* Input Number: 12 */
  3.1734357,

/* Input Number: 13 */
  7.0393559,

/* Input Number: 14 */
- 8.8414850,

/* Input Number: 15 */
- 9.6651444,

/* Input Number: 16 */
- 9.5849543,

/* Input Number: 17 */
- 8.1961269,

/* Input Number: 18 */
- 9.4892508,

/* Input Number: 19 */
- 3.1185971,

/* Input Number: 20 */
- 7.9086205,

/* Input Number: 21 */
  1.2358813,

/* Input Number: 22 */
  5.0358955,

/* Input Number: 23 */
  8.1428017,

/* Input Number: 24 */
  5.7495188,

/* Input Number: 25 */
  6.6389807,

/* Input Number: 26 */
- 5.2255332,

/* Input Number: 27 */
  7.9568324,

/* Input Number: 28 */
- 6.0753700,

/* Input Number: 29 */
  3.9139295,

/* Input Number: 30 */
  4.2869274,

/* Input Number: 31 */
  4.2094146,

/* Input Number: 32 */
  3.2018657,

/* Input Number: 33 */
- 6.5182520,

/* Input Number: 34 */
  2.2615400,

/* Input Number: 35 */
  9.3076435,

/* Input Number: 36 */
  4.4501136,

/* Input Number: 37 */
- 0.2665339,

/* Input Number: 38 */
  1.9059056,

/* Input Number: 39 */
  0.1761222,

/* Input Number: 40 */
- 6.8624408,

/* Input Number: 41 */
- 8.2630656,

/* Input Number: 42 */
  0.7897965,

/* Input Number: 43 */
- 2.0531010,

/* Input Number: 44 */
  9.0933412,

/* Input Number: 45 */
  2.7662245,

/* Input Number: 46 */
  1.0813660,

/* Input Number: 47 */
  8.1138917,

/* Input Number: 48 */
- 3.6459533,

/* Input Number: 49 */
- 9.3077361,

/* Input Number: 50 */
  8.7631509,

/* Input Number: 51 */
  0.5344139,

/* Input Number: 52 */
  3.5528103,

/* Input Number: 53 */
- 2.4849990,

/* Input Number: 54 */
- 5.1148819,

/* Input Number: 55 */
  9.5848076,

/* Input Number: 56 */
  3.4514799,

/* Input Number: 57 */
  9.7528021,

/* Input Number: 58 */
- 5.8443213,

/* Input Number: 59 */
- 6.1514362,

/* Input Number: 60 */
- 6.5903261,

/* Input Number: 61 */
- 1.7913028,

/* Input Number: 62 */
  6.2719355,

/* Input Number: 63 */
- 3.4173759,

/* Input Number: 64 */
- 5.0073741,

/* Input Number: 65 */
- 1.8727676,

/* Input Number: 66 */
- 4.9415105,

/* Input Number: 67 */
  4.9397934,

/* Input Number: 68 */
- 5.8713388,

/* Input Number: 69 */
  9.2716791,

/* Input Number: 70 */
  8.5473888,

/* Input Number: 71 */
- 9.0961979,

/* Input Number: 72 */
  1.3435668,

/* Input Number: 73 */
- 4.6225238,

/* Input Number: 74 */
- 0.4762142,

/* Input Number: 75 */
- 9.4132132,

/* Input Number: 76 */
- 8.5528224,

/* Input Number: 77 */
  4.8550296,

/* Input Number: 78 */
  4.7446843,

/* Input Number: 79 */
  4.3852377,

/* Input Number: 80 */
  3.3786530,

/* Input Number: 81 */
- 9.4440308,

/* Input Number: 82 */
  5.5648588,

/* Input Number: 83 */
- 2.5506419,

/* Input Number: 84 */
  0.8302576,

/* Input Number: 85 */
  9.4603231,

/* Input Number: 86 */
  7.7793777,

/* Input Number: 87 */
- 1.0197528,

/* Input Number: 88 */
- 8.3782565,

/* Input Number: 89 */
  3.2237184,

/* Input Number: 90 */
  1.4679760,

/* Input Number: 91 */
  2.5405675,

/* Input Number: 92 */
  7.9368739,

/* Input Number: 93 */
- 2.5263722,

/* Input Number: 94 */
  0.9181350,

/* Input Number: 95 */
  6.2907450,

/* Input Number: 96 */
  6.5559545,

/* Input Number: 97 */
  2.5909355,

/* Input Number: 98 */
  5.0907913,

/* Input Number: 99 */
- 7.3235199,


};

float b [NUM_INPUTS] = 
{
/* Input Number: 0 */
 25.0000000,

/* Input Number: 1 */
 25.0000000,

/* Input Number: 2 */
 25.0000000,

/* Input Number: 3 */
 25.0000000,

/* Input Number: 4 */
 25.0000000,

/* Input Number: 5 */
 25.0000000,

/* Input Number: 6 */
 25.0000000,

/* Input Number: 7 */
 25.0000000,

/* Input Number: 8 */
 25.0000000,

/* Input Number: 9 */
 25.0000000,

/* Input Number: 10 */
 25.0000000,

/* Input Number: 11 */
 25.0000000,

/* Input Number: 12 */
 25.0000000,

/* Input Number: 13 */
 25.0000000,

/* Input Number: 14 */
 25.0000000,

/* Input Number: 15 */
 25.0000000,

/* Input Number: 16 */
 25.0000000,

/* Input Number: 17 */
 25.0000000,

/* Input Number: 18 */
 25.0000000,

/* Input Number: 19 */
 25.0000000,

/* Input Number: 20 */
 25.0000000,

/* Input Number: 21 */
 25.0000000,

/* Input Number: 22 */
 25.0000000,

/* Input Number: 23 */
 25.0000000,

/* Input Number: 24 */
 25.0000000,

/* Input Number: 25 */
 25.0000000,

/* Input Number: 26 */
 25.0000000,

/* Input Number: 27 */
 25.0000000,

/* Input Number: 28 */
 25.0000000,

/* Input Number: 29 */
 25.0000000,

/* Input Number: 30 */
 25.0000000,

/* Input Number: 31 */
 25.0000000,

/* Input Number: 32 */
 25.0000000,

/* Input Number: 33 */
 25.0000000,

/* Input Number: 34 */
 25.0000000,

/* Input Number: 35 */
 25.0000000,

/* Input Number: 36 */
 25.0000000,

/* Input Number: 37 */
 25.0000000,

/* Input Number: 38 */
 25.0000000,

/* Input Number: 39 */
 25.0000000,

/* Input Number: 40 */
 25.0000000,

/* Input Number: 41 */
 25.0000000,

/* Input Number: 42 */
 25.0000000,

/* Input Number: 43 */
 25.0000000,

/* Input Number: 44 */
 25.0000000,

/* Input Number: 45 */
 25.0000000,

/* Input Number: 46 */
 25.0000000,

/* Input Number: 47 */
 25.0000000,

/* Input Number: 48 */
 25.0000000,

/* Input Number: 49 */
 25.0000000,

/* Input Number: 50 */
 25.0000000,

/* Input Number: 51 */
 25.0000000,

/* Input Number: 52 */
 25.0000000,

/* Input Number: 53 */
 25.0000000,

/* Input Number: 54 */
 25.0000000,

/* Input Number: 55 */
 25.0000000,

/* Input Number: 56 */
 25.0000000,

/* Input Number: 57 */
 25.0000000,

/* Input Number: 58 */
 25.0000000,

/* Input Number: 59 */
 25.0000000,

/* Input Number: 60 */
 25.0000000,

/* Input Number: 61 */
 25.0000000,

/* Input Number: 62 */
 25.0000000,

/* Input Number: 63 */
 25.0000000,

/* Input Number: 64 */
 25.0000000,

/* Input Number: 65 */
 25.0000000,

/* Input Number: 66 */
 25.0000000,

/* Input Number: 67 */
 25.0000000,

/* Input Number: 68 */
 25.0000000,

/* Input Number: 69 */
 25.0000000,

/* Input Number: 70 */
 25.0000000,

/* Input Number: 71 */
 25.0000000,

/* Input Number: 72 */
 25.0000000,

/* Input Number: 73 */
 25.0000000,

/* Input Number: 74 */
 25.0000000,

/* Input Number: 75 */
 25.0000000,

/* Input Number: 76 */
 25.0000000,

/* Input Number: 77 */
 25.0000000,

/* Input Number: 78 */
 25.0000000,

/* Input Number: 79 */
 25.0000000,

/* Input Number: 80 */
 25.0000000,

/* Input Number: 81 */
 25.0000000,

/* Input Number: 82 */
 25.0000000,

/* Input Number: 83 */
 25.0000000,

/* Input Number: 84 */
 25.0000000,

/* Input Number: 85 */
 25.0000000,

/* Input Number: 86 */
 25.0000000,

/* Input Number: 87 */
 25.0000000,

/* Input Number: 88 */
 25.0000000,

/* Input Number: 89 */
 25.0000000,

/* Input Number: 90 */
 25.0000000,

/* Input Number: 91 */
 25.0000000,

/* Input Number: 92 */
 25.0000000,

/* Input Number: 93 */
 25.0000000,

/* Input Number: 94 */
 25.0000000,

/* Input Number: 95 */
 25.0000000,

/* Input Number: 96 */
 25.0000000,

/* Input Number: 97 */
 25.0000000,

/* Input Number: 98 */
 25.0000000,

/* Input Number: 99 */
 25.0000000,


};

float a0[NUM_INPUTS];
float a1[NUM_INPUTS];
float a2[NUM_INPUTS];
float a3[NUM_INPUTS];
float a4[NUM_INPUTS];

//  These variables are needed only when working with random test vectors.
char *seed_fname = "seedfile.txt";
int   seed;

//  main
void main(){
    int i;  
    FILE *fp;

    
    // Obtain output of ASM and inline using test vectors for verification 
    for (i = 0; i < NUM_INPUTS ; i++) {
        a0[i] = powf(a[i], b[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = powsp(a[i], b[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = powsp_c(a[i], b[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = powsp_i(a[i], b[i]);
    }
    powsp_v(a, b, a4, NUM_INPUTS);
    

    
    //  Random Data
    //  Load in a new random number seed from seedfile, or if seedfile
    //  does not exist, pick an initial fixed seed.  Then seed rand().
    
    //  intialize seed if the file does not exist
    seed = 0x2A3A4A5A;
    
    // if the seed file exist read and seed the value to seed
    if ((fp = fopen(seed_fname,"r")) != NULL)   /* open seed file   */
    {
        fscanf(fp,"%d",&seed);                  /* get current seed */
        fclose(fp);
    }
    srand(seed);

    // Generate random test vectors.
    arg = array0;
    arg1 = array00;
    
    for (i = 0 ; i < BUF_SIZE; i++) {
        arg[i] = gimme_random();
        arg1[i] = gimme_random2();
    }   

    // Compute the overhead of calling clock twice to get timing info
    t_start = clock();
    t_stop = clock();
    t_offset = t_stop - t_start;
    
    output0 = array1;
    output1 = array2;
    output2 = array3;
    output3 = array4;
    output4 = array5;
    
    // Time the RTS function 
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output0[i] = powf(arg[i], arg1[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = powsp(arg[i], arg1[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = powsp_c(arg[i], arg1[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = powsp_i(arg[i], arg1[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    powsp_v(arg, arg1, output4, BUF_SIZE);
    t_stop = clock();
    
    clockdata[4] = t_stop - t_start - t_offset;
    clockdata[4] = clockdata[4] / BUF_SIZE;
    

    // Display Test Vector Verificaition Results 
    printf ("Verification Results:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("Predefined Test Vector: ");

    pass_flag1 =    (isequal(a0, a1, NUM_INPUTS, RET_VAL_TOL)) && 
                    (isequal(a0, a2, NUM_INPUTS, RET_VAL_TOL)) &&
                    (isequal(a0, a3, NUM_INPUTS, RET_VAL_TOL)) &&
                    (isequal(a0, a4, NUM_INPUTS, RET_VAL_TOL));
    
    
    if (pass_flag1){
        printf ("Passed\n");
    }
    else{
        printf ("Failed\n");
    }


    // Display Random Test Vector Results   
    printf ("Random Test Vector (seed = %d): ", seed);


    pass_flag2 =    (isequal(output0, output1, BUF_SIZE, RET_VAL_TOL)) && 
                    (isequal(output0, output2, BUF_SIZE, RET_VAL_TOL)) &&
                    (isequal(output0, output3, BUF_SIZE, RET_VAL_TOL)) &&
                    (isequal(output0, output4, BUF_SIZE, RET_VAL_TOL));


    if (pass_flag2)
    {
        printf ("Passed\n");
    }
    else{
        printf ("Failed\n");
    }


    if (pass_flag2)
    {
        seed = rand();                      /* get next seed  */
        if (!(fp = fopen(seed_fname,"w")))  /* open seed file */
        {   
            printf("failure writing seed file \"%s\"\n", seed_fname);
            exit(1);
        }
        fprintf(fp,"%d\n",seed);            /* set next seed  */
        fclose(fp);
    }   
    printf ("-------------------------------------------------------------------------------------------------------\n");
    

    // Display average clock for RTS, ASM, Inlined and Vector methods
    printf ("\n");
    printf ("Number of Clocks for pow:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of 0 to 20 and 25
float gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*(2*10)-10;
}
float gimme_random2( void ){
	return 25;
}

// compare two arrays
int isequal(float *arg1, float *arg2, int size, double tol){
	int x;
	int flag = 1;	
		for (x = 0; x < size; x++) {
			if(fabs(arg1[x] - arg2[x])/arg1[x] > tol*100){
				if (!isnan(arg1[x]) && !isnan(arg2[x])){
					flag = 0;
					//printf("at %d %d and %d,",(int)x,arg1[x], arg2[x]); 
					break;
				}
			}
		}
	return flag;
}


/* ======================================================================== */
/*  End of file: powsp_d.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


