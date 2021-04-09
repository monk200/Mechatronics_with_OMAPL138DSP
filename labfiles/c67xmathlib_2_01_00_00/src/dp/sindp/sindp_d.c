/* ======================================================================= */
/* sindp_d.h - sine driver file                                            */
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

#include "sindp.h"
#include "sindp_i.h"
#include "sindp_c.h"

#define BUF_SIZE 128

extern double gimme_random( void );
extern int isequal(double *arg1, double *arg2, int size, double tol);

/* Global declarations */
double array0[BUF_SIZE];
double array1[BUF_SIZE];
double array2[BUF_SIZE];
double array3[BUF_SIZE];
double array4[BUF_SIZE];
double array5[BUF_SIZE];


double * restrict arg;
double * restrict output0;
double * restrict output1;
double * restrict output2;
double * restrict output3;
double * restrict output4;

double t_start, t_stop, t_offset;
double clockdata[5];

int pass_flag1 = 0;
int pass_flag2 = 0;

// Number of input arguments:
#define NUM_INPUTS  (10)


// doubleing Point Tolerances
#define RET_VAL_TOL (0.0005)

// Initialized arrays with fixed test data

double a [NUM_INPUTS] = 
{
/* Input Number: 0 */
 17.6184514,

/* Input Number: 1 */
 45.0716185,

/* Input Number: 2 */
-77.7551207,

/* Input Number: 3 */
 39.9507247,

/* Input Number: 4 */
-98.0882871,

/* Input Number: 5 */
-38.2869709,

/* Input Number: 6 */
-75.4914715,

/* Input Number: 7 */
-58.4133692,

/* Input Number: 8 */
 59.5762434,

/* Input Number: 9 */
-43.0416519,


};

double a0[NUM_INPUTS];
double a1[NUM_INPUTS];
double a2[NUM_INPUTS];
double a3[NUM_INPUTS];
double a4[NUM_INPUTS];

//  These variables are needed only when working with random test vectors.
char *seed_fname = "seedfile.txt";
int   seed;

//  main
void main(){
    int i;  
    FILE *fp;

    
    // Obtain output of ASM and inline using test vectors for verification 
    for (i = 0; i < NUM_INPUTS ; i++) {
        a0[i] = sin(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = sindp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = sindp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = sindp_i(a[i]);
    }
    sindp_v(a, a4, NUM_INPUTS);
    

    
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
    
    for (i = 0 ; i < BUF_SIZE; i++) {
        arg[i] = gimme_random();
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
        output0[i] = sin(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = sindp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = sindp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = sindp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    sindp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for sin:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of -100 to 100
double gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*200-100;
}

// compare two arrays
int isequal(double *arg1, double *arg2, int size, double tol){
	int x;
	int flag = 1;	
		for (x = 0; x < size; x++) {
			if(fabs(arg1[x] - arg2[x]) > tol){
				flag = 0;
				break;
			}
		}
	return flag;
}

/* ======================================================================== */
/*  End of file: sindp_d.c                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */ 

