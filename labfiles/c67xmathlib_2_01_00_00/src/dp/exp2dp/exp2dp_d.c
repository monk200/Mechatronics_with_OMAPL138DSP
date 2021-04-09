/* ======================================================================= */
/* exp2dp_d.h - exp base 2 driver file                                     */
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

#include "exp2dp.h"
#include "exp2dp_i.h"
#include "exp2dp_c.h"

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

//  doubleing Point Tolerances                                               
#define RET_VAL_TOL (0.0000000005)


//  Initialized arrays with fixed test data.                                
double a [NUM_INPUTS] = 
{
/* Input Number: 0 */
-10.2244097,

/* Input Number: 1 */
-42.1539375,

/* Input Number: 2 */
 71.0171908,

/* Input Number: 3 */
  9.2099160,

/* Input Number: 4 */
 55.8582317,

/* Input Number: 5 */
-83.1524307,

/* Input Number: 6 */
-80.6279024,

/* Input Number: 7 */
-12.3099474,

/* Input Number: 8 */
- 7.4002587,

/* Input Number: 9 */
 73.0712053,

/* Input Number: 10 */
-59.7986326,

/* Input Number: 11 */
-52.8700513,

/* Input Number: 12 */
-61.1413063,

/* Input Number: 13 */
 78.2272169,

/* Input Number: 14 */
 45.5485121,

/* Input Number: 15 */
  9.6858536,

/* Input Number: 16 */
-20.9269145,

/* Input Number: 17 */
-71.1637219,

/* Input Number: 18 */
 91.4647876,

/* Input Number: 19 */
 43.1056347,

/* Input Number: 20 */
-56.7365998,

/* Input Number: 21 */
-38.4672131,

/* Input Number: 22 */
 78.8118408,

/* Input Number: 23 */
 59.1540819,

/* Input Number: 24 */
  0.7826549,

/* Input Number: 25 */
 60.8681988,

/* Input Number: 26 */
-50.6536589,

/* Input Number: 27 */
 10.4940589,

/* Input Number: 28 */
 68.9039044,

/* Input Number: 29 */
 52.2950828,

/* Input Number: 30 */
- 8.0453385,

/* Input Number: 31 */
- 3.0788152,

/* Input Number: 32 */
  6.5826384,

/* Input Number: 33 */
-93.1606848,

/* Input Number: 34 */
 37.2116301,

/* Input Number: 35 */
 61.4820101,

/* Input Number: 36 */
 16.7851184,

/* Input Number: 37 */
-61.2253124,

/* Input Number: 38 */
 60.4871485,

/* Input Number: 39 */
-11.8971631,

/* Input Number: 40 */
 45.7224573,

/* Input Number: 41 */
  4.8172075,

/* Input Number: 42 */
-18.8318639,

/* Input Number: 43 */
-93.6953754,

/* Input Number: 44 */
-15.5990870,

/* Input Number: 45 */
-92.7224484,

/* Input Number: 46 */
 59.5395027,

/* Input Number: 47 */
 91.1756199,

/* Input Number: 48 */
 67.8406022,

/* Input Number: 49 */
- 9.0852247,

/* Input Number: 50 */
-96.1998127,

/* Input Number: 51 */
-41.2888087,

/* Input Number: 52 */
 72.7531726,

/* Input Number: 53 */
-53.9326549,

/* Input Number: 54 */
 63.0593861,

/* Input Number: 55 */
 70.4770225,

/* Input Number: 56 */
-77.8104537,

/* Input Number: 57 */
  2.4122812,

/* Input Number: 58 */
 31.9965508,

/* Input Number: 59 */
-69.5037050,

/* Input Number: 60 */
 80.8952281,

/* Input Number: 61 */
-60.1094655,

/* Input Number: 62 */
 45.4018651,

/* Input Number: 63 */
-12.3974653,

/* Input Number: 64 */
-40.8170616,

/* Input Number: 65 */
 77.7724544,

/* Input Number: 66 */
 87.5603050,

/* Input Number: 67 */
 33.8527922,

/* Input Number: 68 */
-90.9492344,

/* Input Number: 69 */
 78.5702265,

/* Input Number: 70 */
 82.0771257,

/* Input Number: 71 */
  5.3301967,

/* Input Number: 72 */
 28.0701643,

/* Input Number: 73 */
-48.0651408,

/* Input Number: 74 */
 98.1553515,

/* Input Number: 75 */
-19.4277246,

/* Input Number: 76 */
-44.5081459,

/* Input Number: 77 */
 48.4154231,

/* Input Number: 78 */
-52.5628414,

/* Input Number: 79 */
-16.3039735,

/* Input Number: 80 */
 77.7085004,

/* Input Number: 81 */
 63.3530815,

/* Input Number: 82 */
-12.8466515,

/* Input Number: 83 */
-17.9397760,

/* Input Number: 84 */
-77.9922686,

/* Input Number: 85 */
 35.3399174,

/* Input Number: 86 */
-83.7860366,

/* Input Number: 87 */
 87.0405764,

/* Input Number: 88 */
-40.3089061,

/* Input Number: 89 */
-51.4647347,

/* Input Number: 90 */
-21.6849650,

/* Input Number: 91 */
-47.5389002,

/* Input Number: 92 */
  6.8643750,

/* Input Number: 93 */
-71.2161850,

/* Input Number: 94 */
-38.0339381,

/* Input Number: 95 */
-23.0437509,

/* Input Number: 96 */
 21.3096339,

/* Input Number: 97 */
 45.1568339,

/* Input Number: 98 */
- 2.6502964,

/* Input Number: 99 */
-98.3851218,

/* Input Number: 100 */
-91.2740010,

/* Input Number: 101 */
-86.9076945,

/* Input Number: 102 */
-40.5592874,

/* Input Number: 103 */
 14.6647238,

/* Input Number: 104 */
-85.8457600,

/* Input Number: 105 */
 90.4949385,

/* Input Number: 106 */
 68.0181054,

/* Input Number: 107 */
-55.5557928,

/* Input Number: 108 */
 28.2115097,

/* Input Number: 109 */
 76.9272960,

/* Input Number: 110 */
 84.5402109,

/* Input Number: 111 */
 62.5396533,

/* Input Number: 112 */
-13.6929938,

/* Input Number: 113 */
-80.1095801,

/* Input Number: 114 */
-83.9643752,

/* Input Number: 115 */
 89.2326541,

/* Input Number: 116 */
 66.3196922,

/* Input Number: 117 */
  7.7650678,

/* Input Number: 118 */
 11.9965090,

/* Input Number: 119 */
 84.1372881,

/* Input Number: 120 */
 88.5768021,

/* Input Number: 121 */
 72.9672546,

/* Input Number: 122 */
-34.8400629,

/* Input Number: 123 */
 50.8967871,

/* Input Number: 124 */
 19.7632149,

/* Input Number: 125 */
- 8.0853652,

/* Input Number: 126 */
-85.3947393,

/* Input Number: 127 */
-60.5002387,

/* Input Number: 128 */
-30.1852351,

/* Input Number: 129 */
-14.9459595,

/* Input Number: 130 */
-59.6808913,

/* Input Number: 131 */
 40.8420738,

/* Input Number: 132 */
- 9.6717480,

/* Input Number: 133 */
 16.8522901,

/* Input Number: 134 */
 68.6486990,

/* Input Number: 135 */
- 7.8197519,

/* Input Number: 136 */
 79.2733437,

/* Input Number: 137 */
- 5.7724628,

/* Input Number: 138 */
 66.0551051,

/* Input Number: 139 */
-28.3464245,

/* Input Number: 140 */
-22.9318895,

/* Input Number: 141 */
-31.1068845,

/* Input Number: 142 */
 46.9194140,

/* Input Number: 143 */
-97.0039597,

/* Input Number: 144 */
-32.6276850,

/* Input Number: 145 */
-63.4115631,

/* Input Number: 146 */
 66.5208222,

/* Input Number: 147 */
 53.9494300,

/* Input Number: 148 */
 79.4221866,

/* Input Number: 149 */
 36.2916260,

/* Input Number: 150 */
-73.5038405,

/* Input Number: 151 */
 35.5033762,

/* Input Number: 152 */
 84.1392745,

/* Input Number: 153 */
-49.7865245,

/* Input Number: 154 */
-32.1822665,

/* Input Number: 155 */
  1.0928492,

/* Input Number: 156 */
 97.2281014,

/* Input Number: 157 */
-94.6370729,

/* Input Number: 158 */
 79.3810963,

/* Input Number: 159 */
 50.5225996,

/* Input Number: 160 */
-22.3528389,

/* Input Number: 161 */
 71.2094727,

/* Input Number: 162 */
 92.5331472,

/* Input Number: 163 */
 25.2675346,

/* Input Number: 164 */
-70.0717094,

/* Input Number: 165 */
-36.4167117,

/* Input Number: 166 */
-18.1313113,

/* Input Number: 167 */
-88.3931385,

/* Input Number: 168 */
 98.7139877,

/* Input Number: 169 */
 38.4221832,

/* Input Number: 170 */
 65.9903148,

/* Input Number: 171 */
 38.2742100,

/* Input Number: 172 */
-23.4269782,

/* Input Number: 173 */
 98.0399215,

/* Input Number: 174 */
  8.3079111,

/* Input Number: 175 */
 79.5795809,

/* Input Number: 176 */
- 3.0278349,

/* Input Number: 177 */
 87.9706697,

/* Input Number: 178 */
 13.9015564,

/* Input Number: 179 */
 52.2935369,

/* Input Number: 180 */
-61.8297174,

/* Input Number: 181 */
 95.4370373,

/* Input Number: 182 */
 33.4337914,

/* Input Number: 183 */
-84.3559087,

/* Input Number: 184 */
-78.3319608,

/* Input Number: 185 */
-44.4273886,

/* Input Number: 186 */
-39.9753926,

/* Input Number: 187 */
-21.6550464,

/* Input Number: 188 */
 12.9891142,

/* Input Number: 189 */
 44.4243117,

/* Input Number: 190 */
 30.8109783,

/* Input Number: 191 */
 85.3173556,

/* Input Number: 192 */
 21.6649542,

/* Input Number: 193 */
 80.4690190,

/* Input Number: 194 */
 27.7310781,

/* Input Number: 195 */
 30.1838404,

/* Input Number: 196 */
-98.7437931,

/* Input Number: 197 */
-70.6469499,

/* Input Number: 198 */
 75.9557378,

/* Input Number: 199 */
-51.7597809,

/* Input Number: 200 */
-52.2282086,
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
        a0[i] = exp2(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = exp2dp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = exp2dp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = exp2dp_i(a[i]);
    }
    exp2dp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = exp2(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = exp2dp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = exp2dp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = exp2dp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    exp2dp_v(arg, output4, BUF_SIZE);
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

// return random value of -100 to 100
double gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*200-100;
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
/*  End of file: exp2dp_d.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
