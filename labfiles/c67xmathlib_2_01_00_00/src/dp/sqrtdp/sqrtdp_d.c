/* ======================================================================= */
/* sqrtdp_d.h - sqrtrocal driver file                                    */
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

#include "sqrtdp.h"
#include "sqrtdp_i.h"
#include "sqrtdp_c.h"

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


/* ======================================================================== */
/*  Number of input arguments:                                              */
/* ======================================================================== */
#define NUM_INPUTS  (10)

/* ======================================================================== */
/*  floating Point Tolerances                                               */
/* ======================================================================== */
#define RET_VAL_TOL (0.0000000005)


/* ======================================================================== */
/*  Initialized arrays with fixed test data.                                */
/* ======================================================================== */
//double a [NUM_INPUTS];



double a [NUM_INPUTS] = 
{
/* Input Number: 0 */
 987.6072190,

/* Input Number: 1 */
 362.0357379,

/* Input Number: 2 */
 296.0055346,

/* Input Number: 3 */
 158.4783886,

/* Input Number: 4 */
 905.8672893,

/* Input Number: 5 */
 718.7834984,

/* Input Number: 6 */
 560.2071005,

/* Input Number: 7 */
 530.6445342,

/* Input Number: 8 */
 189.7256508,

/* Input Number: 9 */
 685.5739133,


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
        a0[i] = sqrt(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = sqrtdp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = sqrtdp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = sqrtdp_i(a[i]);
    }
    sqrtdp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = sqrt(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = sqrtdp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = sqrtdp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = sqrtdp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    sqrtdp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for sqrt:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of -1 to 1000
double gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*1001-1;
}

// compare two arrays (in this case tolerance is treated as percent error)
int isequal(double *arg1, double *arg2, int size, double tol){
	int x;
	int flag = 1;	
		for (x = 0; x < size; x++) {
			if(fabs(arg1[x] - arg2[x])/arg1[x] > tol*100){
				flag = 0;
				break;
			}
		}
	return flag;
}
/* ======================================================================== */
/*  End of file: sqrtdp_d.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
