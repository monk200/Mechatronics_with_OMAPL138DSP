/* ======================================================================= */
/* exp10dp_d.h - exp base 2 driver file                                     */
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

#include "exp10dp.h"
#include "exp10dp_i.h"
#include "exp10dp_c.h"

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

//  Number of input arguments:                                              
#define NUM_INPUTS  (201)

//  Floating Point Tolerances                                               
#define RET_VAL_TOL (0.0000000005)


//  Initialized arrays with fixed test data.                                
double a [NUM_INPUTS] = 
{
/* Input Number: 0 */
  7.2555330,

/* Input Number: 1 */
  8.1863761,

/* Input Number: 2 */
  7.7506020,

/* Input Number: 3 */
  4.8799741,

/* Input Number: 4 */
- 9.4049913,

/* Input Number: 5 */
- 1.9325319,

/* Input Number: 6 */
  0.7166932,

/* Input Number: 7 */
- 2.7496546,

/* Input Number: 8 */
  4.2748349,

/* Input Number: 9 */
- 3.2138848,

/* Input Number: 10 */
- 4.2416360,

/* Input Number: 11 */
  3.3820191,

/* Input Number: 12 */
  5.8675362,

/* Input Number: 13 */
  3.6622841,

/* Input Number: 14 */
  8.9243333,

/* Input Number: 15 */
- 8.7333771,

/* Input Number: 16 */
- 9.8688202,

/* Input Number: 17 */
- 5.0328877,

/* Input Number: 18 */
- 6.7867291,

/* Input Number: 19 */
  5.5326228,

/* Input Number: 20 */
  8.2269113,

/* Input Number: 21 */
  3.7660479,

/* Input Number: 22 */
- 1.4249858,

/* Input Number: 23 */
  7.7599622,

/* Input Number: 24 */
  8.6579726,

/* Input Number: 25 */
  0.3091667,

/* Input Number: 26 */
- 8.4037573,

/* Input Number: 27 */
- 3.5208564,

/* Input Number: 28 */
- 3.5127629,

/* Input Number: 29 */
- 8.7488544,

/* Input Number: 30 */
- 4.0274223,

/* Input Number: 31 */
  6.9362425,

/* Input Number: 32 */
- 6.1931270,

/* Input Number: 33 */
  0.5085038,

/* Input Number: 34 */
- 7.8078777,

/* Input Number: 35 */
- 8.7487045,

/* Input Number: 36 */
- 0.4191279,

/* Input Number: 37 */
  8.5598237,

/* Input Number: 38 */
- 2.3827548,

/* Input Number: 39 */
- 1.1938234,

/* Input Number: 40 */
  9.4900223,

/* Input Number: 41 */
- 6.9335072,

/* Input Number: 42 */
  6.4818313,

/* Input Number: 43 */
- 4.7682750,

/* Input Number: 44 */
- 3.7562043,

/* Input Number: 45 */
  8.4076066,

/* Input Number: 46 */
  9.8143845,

/* Input Number: 47 */
  3.4203095,

/* Input Number: 48 */
  9.4244026,

/* Input Number: 49 */
  5.7568750,

/* Input Number: 50 */
- 4.2494801,

/* Input Number: 51 */
  3.1379537,

/* Input Number: 52 */
- 4.5922453,

/* Input Number: 53 */
- 6.6839170,

/* Input Number: 54 */
  8.9073566,

/* Input Number: 55 */
- 8.9768792,

/* Input Number: 56 */
- 2.4000274,

/* Input Number: 57 */
- 3.9183689,

/* Input Number: 58 */
- 8.6777567,

/* Input Number: 59 */
  0.4301454,

/* Input Number: 60 */
- 3.9562872,

/* Input Number: 61 */
- 3.9992191,

/* Input Number: 62 */
  1.3571700,

/* Input Number: 63 */
  1.7426653,

/* Input Number: 64 */
  7.8902695,

/* Input Number: 65 */
- 8.3411409,

/* Input Number: 66 */
- 5.3612892,

/* Input Number: 67 */
  2.0608031,

/* Input Number: 68 */
  6.9274730,

/* Input Number: 69 */
- 1.0179319,

/* Input Number: 70 */
  3.4299765,

/* Input Number: 71 */
  5.5902710,

/* Input Number: 72 */
  4.0511835,

/* Input Number: 73 */
- 9.6987901,

/* Input Number: 74 */
- 2.9760216,

/* Input Number: 75 */
- 6.7452011,

/* Input Number: 76 */
  6.8728349,

/* Input Number: 77 */
- 5.1023506,

/* Input Number: 78 */
  1.5083506,

/* Input Number: 79 */
  2.7718159,

/* Input Number: 80 */
- 0.0446651,

/* Input Number: 81 */
- 0.7626204,

/* Input Number: 82 */
- 0.0799416,

/* Input Number: 83 */
  9.0430710,

/* Input Number: 84 */
  4.8118501,

/* Input Number: 85 */
  6.4247566,

/* Input Number: 86 */
- 7.9859137,

/* Input Number: 87 */
  3.3761378,

/* Input Number: 88 */
- 0.3279694,

/* Input Number: 89 */
- 3.5634269,

/* Input Number: 90 */
- 5.4271156,

/* Input Number: 91 */
- 5.5045403,

/* Input Number: 92 */
- 0.4404623,

/* Input Number: 93 */
  6.2010968,

/* Input Number: 94 */
  1.1741231,

/* Input Number: 95 */
  7.5309898,

/* Input Number: 96 */
- 3.2386088,

/* Input Number: 97 */
  9.4393750,

/* Input Number: 98 */
  2.3457293,

/* Input Number: 99 */
  4.7979289,

/* Input Number: 100 */
  0.1248551,

/* Input Number: 101 */
- 3.3313973,

/* Input Number: 102 */
  5.4886780,

/* Input Number: 103 */
  5.3261313,

/* Input Number: 104 */
- 4.6300683,

/* Input Number: 105 */
- 4.3318838,

/* Input Number: 106 */
- 5.2023603,

/* Input Number: 107 */
  5.0978407,

/* Input Number: 108 */
  5.1668774,

/* Input Number: 109 */
- 9.2997218,

/* Input Number: 110 */
- 8.6596684,

/* Input Number: 111 */
- 3.1106918,

/* Input Number: 112 */
  9.2930631,

/* Input Number: 113 */
  2.9761855,

/* Input Number: 114 */
- 6.8649719,

/* Input Number: 115 */
- 9.5738751,

/* Input Number: 116 */
  3.7729911,

/* Input Number: 117 */
- 9.3403731,

/* Input Number: 118 */
- 4.8491260,

/* Input Number: 119 */
- 7.6131199,

/* Input Number: 120 */
  2.2082465,

/* Input Number: 121 */
  8.8643438,

/* Input Number: 122 */
  8.7606911,

/* Input Number: 123 */
  6.0866976,

/* Input Number: 124 */
- 5.3196049,

/* Input Number: 125 */
  9.4196491,

/* Input Number: 126 */
  2.9912979,

/* Input Number: 127 */
- 8.1303067,

/* Input Number: 128 */
  8.1446565,

/* Input Number: 129 */
  0.9503867,

/* Input Number: 130 */
  3.1947633,

/* Input Number: 131 */
  6.9530240,

/* Input Number: 132 */
  6.7417982,

/* Input Number: 133 */
  9.3441549,

/* Input Number: 134 */
- 8.4825344,

/* Input Number: 135 */
  5.3481580,

/* Input Number: 136 */
- 8.9068292,

/* Input Number: 137 */
- 3.1077617,

/* Input Number: 138 */
  7.4481928,

/* Input Number: 139 */
- 1.7488046,

/* Input Number: 140 */
- 1.1496570,

/* Input Number: 141 */
  3.1489800,

/* Input Number: 142 */
  6.9566196,

/* Input Number: 143 */
- 6.7371676,

/* Input Number: 144 */
  4.6145191,

/* Input Number: 145 */
  4.3076952,

/* Input Number: 146 */
  3.1973633,

/* Input Number: 147 */
- 4.9881574,

/* Input Number: 148 */
- 0.1403476,

/* Input Number: 149 */
- 6.4102220,

/* Input Number: 150 */
  5.8080650,

/* Input Number: 151 */
  5.3900567,

/* Input Number: 152 */
- 7.1450875,

/* Input Number: 153 */
  0.8543764,

/* Input Number: 154 */
  1.6885158,

/* Input Number: 155 */
  2.6160875,

/* Input Number: 156 */
  8.7403849,

/* Input Number: 157 */
- 6.9310297,

/* Input Number: 158 */
- 5.7012586,

/* Input Number: 159 */
  2.0925669,

/* Input Number: 160 */
  9.6088466,

/* Input Number: 161 */
- 6.0055634,

/* Input Number: 162 */
  4.2849247,

/* Input Number: 163 */
- 4.1395103,

/* Input Number: 164 */
- 5.7316564,

/* Input Number: 165 */
  4.3425168,

/* Input Number: 166 */
  8.8510481,

/* Input Number: 167 */
- 6.6973507,

/* Input Number: 168 */
- 1.4449982,

/* Input Number: 169 */
  1.5411367,

/* Input Number: 170 */
  2.3884696,

/* Input Number: 171 */
  0.1270904,

/* Input Number: 172 */
- 4.7426721,

/* Input Number: 173 */
- 0.0306071,

/* Input Number: 174 */
- 4.1524353,

/* Input Number: 175 */
- 0.7732077,

/* Input Number: 176 */
- 6.1993210,

/* Input Number: 177 */
- 9.1217965,

/* Input Number: 178 */
- 2.7147859,

/* Input Number: 179 */
- 9.6322201,

/* Input Number: 180 */
  0.6400001,

/* Input Number: 181 */
  2.5483941,

/* Input Number: 182 */
- 8.3680449,

/* Input Number: 183 */
- 9.9680401,

/* Input Number: 184 */
- 0.8979266,

/* Input Number: 185 */
- 0.1020661,

/* Input Number: 186 */
  0.5335943,

/* Input Number: 187 */
- 8.3479005,

/* Input Number: 188 */
  9.3082845,

/* Input Number: 189 */
  4.7956578,

/* Input Number: 190 */
  2.5871062,

/* Input Number: 191 */
  5.7680854,

/* Input Number: 192 */
  8.4096276,

/* Input Number: 193 */
- 4.0162494,

/* Input Number: 194 */
- 6.6593667,

/* Input Number: 195 */
- 0.6771267,

/* Input Number: 196 */
- 9.8835867,

/* Input Number: 197 */
  9.1537332,

/* Input Number: 198 */
  5.0575942,

/* Input Number: 199 */
- 3.4759923,

/* Input Number: 200 */
  5.4020199,


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
        a0[i] = exp10(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = exp10dp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = exp10dp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = exp10dp_i(a[i]);
    }
    exp10dp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = exp10(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = exp10dp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = exp10dp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = exp10dp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    exp10dp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for exp2:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of -10 to 10
double gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*20-10;
}

// compare two arrays (in this case tolerance is treated as percent error)
int isequal(double *arg1, double *arg2, int size, double tol){
	int x;
	int flag = 1;	
		for (x = 0; x < size; x++) {
			if(fabs(arg1[x] - arg2[x])/arg1[x] > tol*100){
				flag = 0;
				
				//printf("Error for %d and %d", arg1[x], arg2[x]);
				break;
			}
		}
	return flag;
}

/* ======================================================================== */
/*  End of file: exp10dp_d.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
