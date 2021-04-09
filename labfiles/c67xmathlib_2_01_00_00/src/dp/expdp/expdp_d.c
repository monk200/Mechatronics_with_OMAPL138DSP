/* ======================================================================= */
/* expdp_d.h - exp base 2 driver file                                     */
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

#include "expdp.h"
#include "expdp_i.h"
#include "expdp_c.h"

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
- 6.5536564,

/* Input Number: 1 */
 97.8278644,

/* Input Number: 2 */
-22.1616453,

/* Input Number: 3 */
-57.3984788,

/* Input Number: 4 */
 58.7622427,

/* Input Number: 5 */
 65.5014001,

/* Input Number: 6 */
-50.4600560,

/* Input Number: 7 */
 13.8791552,

/* Input Number: 8 */
  1.0522846,

/* Input Number: 9 */
-89.1277857,

/* Input Number: 10 */
 77.4207240,

/* Input Number: 11 */
-67.3367065,

/* Input Number: 12 */
 33.2636883,

/* Input Number: 13 */
-21.3189942,

/* Input Number: 14 */
-14.5432661,

/* Input Number: 15 */
-47.2373295,

/* Input Number: 16 */
- 9.6017980,

/* Input Number: 17 */
 32.5858308,

/* Input Number: 18 */
-83.4525378,

/* Input Number: 19 */
-53.0965975,

/* Input Number: 20 */
-75.9657075,

/* Input Number: 21 */
 53.5934757,

/* Input Number: 22 */
-67.4871935,

/* Input Number: 23 */
  7.5132645,

/* Input Number: 24 */
-95.3322157,

/* Input Number: 25 */
 41.6495183,

/* Input Number: 26 */
-87.4754940,

/* Input Number: 27 */
 42.0311633,

/* Input Number: 28 */
 21.7240902,

/* Input Number: 29 */
 17.9453374,

/* Input Number: 30 */
-43.7444800,

/* Input Number: 31 */
-19.2681798,

/* Input Number: 32 */
-15.6819484,

/* Input Number: 33 */
 18.7018018,

/* Input Number: 34 */
-18.5033478,

/* Input Number: 35 */
-29.5364242,

/* Input Number: 36 */
-81.8496401,

/* Input Number: 37 */
-97.8240139,

/* Input Number: 38 */
-75.0317886,

/* Input Number: 39 */
-22.2265739,

/* Input Number: 40 */
-29.0298081,

/* Input Number: 41 */
-58.3516487,

/* Input Number: 42 */
-59.2423575,

/* Input Number: 43 */
-12.6525332,

/* Input Number: 44 */
-93.6900737,

/* Input Number: 45 */
 34.0011166,

/* Input Number: 46 */
  3.4261324,

/* Input Number: 47 */
  2.8045053,

/* Input Number: 48 */
-92.5811399,

/* Input Number: 49 */
 91.1307437,

/* Input Number: 50 */
-93.5446987,

/* Input Number: 51 */
 46.6623362,

/* Input Number: 52 */
-22.7611701,

/* Input Number: 53 */
 44.6352942,

/* Input Number: 54 */
 60.6907821,

/* Input Number: 55 */
-39.6133108,

/* Input Number: 56 */
-64.7086164,

/* Input Number: 57 */
 45.0455055,

/* Input Number: 58 */
 95.8925376,

/* Input Number: 59 */
  2.7798407,

/* Input Number: 60 */
 23.1495817,

/* Input Number: 61 */
 61.7972419,

/* Input Number: 62 */
 62.3156584,

/* Input Number: 63 */
 53.1391836,

/* Input Number: 64 */
 97.3854092,

/* Input Number: 65 */
 84.0341898,

/* Input Number: 66 */
 25.9923224,

/* Input Number: 67 */
 10.4576783,

/* Input Number: 68 */
 35.0751705,

/* Input Number: 69 */
-83.2984871,

/* Input Number: 70 */
 74.2341968,

/* Input Number: 71 */
-12.0387576,

/* Input Number: 72 */
-67.0184894,

/* Input Number: 73 */
-13.9975097,

/* Input Number: 74 */
-86.7236497,

/* Input Number: 75 */
-76.7228759,

/* Input Number: 76 */
-94.7688410,

/* Input Number: 77 */
-62.9392375,

/* Input Number: 78 */
 65.1309865,

/* Input Number: 79 */
-32.5309804,

/* Input Number: 80 */
 85.6524927,

/* Input Number: 81 */
 31.5828166,

/* Input Number: 82 */
 73.8771277,

/* Input Number: 83 */
 95.2237934,

/* Input Number: 84 */
 26.2160996,

/* Input Number: 85 */
-48.2450626,

/* Input Number: 86 */
-99.8356715,

/* Input Number: 87 */
 96.2302503,

/* Input Number: 88 */
 96.2444094,

/* Input Number: 89 */
- 1.3100059,

/* Input Number: 90 */
-74.8871422,

/* Input Number: 91 */
-18.5555225,

/* Input Number: 92 */
 87.8987535,

/* Input Number: 93 */
 91.6216807,

/* Input Number: 94 */
-51.9964465,

/* Input Number: 95 */
-20.8104326,

/* Input Number: 96 */
  8.3392926,

/* Input Number: 97 */
-31.2684094,

/* Input Number: 98 */
-14.5431953,

/* Input Number: 99 */
-63.3000501,

/* Input Number: 100 */
 83.6558354,

/* Input Number: 101 */
-14.4651761,

/* Input Number: 102 */
 73.8069504,

/* Input Number: 103 */
-80.6477939,

/* Input Number: 104 */
-38.7884830,

/* Input Number: 105 */
-81.9461720,

/* Input Number: 106 */
 69.0899291,

/* Input Number: 107 */
 13.7932519,

/* Input Number: 108 */
-94.2939924,

/* Input Number: 109 */
-38.0117162,

/* Input Number: 110 */
 44.6966085,

/* Input Number: 111 */
-77.5437672,

/* Input Number: 112 */
- 1.5599372,

/* Input Number: 113 */
-71.1453086,

/* Input Number: 114 */
 94.4977019,

/* Input Number: 115 */
-32.5148549,

/* Input Number: 116 */
-55.6990030,

/* Input Number: 117 */
 50.6432573,

/* Input Number: 118 */
-72.6127627,

/* Input Number: 119 */
 90.7226045,

/* Input Number: 120 */
 62.4273444,

/* Input Number: 121 */
-21.7383831,

/* Input Number: 122 */
 76.6423220,

/* Input Number: 123 */
 52.9285721,

/* Input Number: 124 */
 91.6532786,

/* Input Number: 125 */
-19.2342676,

/* Input Number: 126 */
 90.5603504,

/* Input Number: 127 */
 30.6614942,

/* Input Number: 128 */
- 7.1447407,

/* Input Number: 129 */
-53.0929264,

/* Input Number: 130 */
-65.2155813,

/* Input Number: 131 */
 24.0938535,

/* Input Number: 132 */
-58.8573211,

/* Input Number: 133 */
-17.1988046,

/* Input Number: 134 */
- 2.1943547,

/* Input Number: 135 */
 46.8467404,

/* Input Number: 136 */
-67.8829216,

/* Input Number: 137 */
 13.4809976,

/* Input Number: 138 */
 83.8923063,

/* Input Number: 139 */
-66.2037268,

/* Input Number: 140 */
-17.3589774,

/* Input Number: 141 */
-16.3158846,

/* Input Number: 142 */
 18.5828816,

/* Input Number: 143 */
-58.8989838,

/* Input Number: 144 */
-76.9803483,

/* Input Number: 145 */
 57.0594377,

/* Input Number: 146 */
 41.6579868,

/* Input Number: 147 */
-61.6470343,

/* Input Number: 148 */
  7.9594846,

/* Input Number: 149 */
 15.4072200,

/* Input Number: 150 */
 17.2721382,

/* Input Number: 151 */
 18.7672149,

/* Input Number: 152 */
-93.6000748,

/* Input Number: 153 */
 57.8856865,

/* Input Number: 154 */
 24.6122983,

/* Input Number: 155 */
 92.1325597,

/* Input Number: 156 */
-89.8990307,

/* Input Number: 157 */
  4.9080298,

/* Input Number: 158 */
-37.4542143,

/* Input Number: 159 */
 85.5895302,

/* Input Number: 160 */
-74.9444543,

/* Input Number: 161 */
 95.0357810,

/* Input Number: 162 */
-50.3309675,

/* Input Number: 163 */
-52.4509969,

/* Input Number: 164 */
 80.0923860,

/* Input Number: 165 */
-16.5928340,

/* Input Number: 166 */
-78.8722997,

/* Input Number: 167 */
 43.7797403,

/* Input Number: 168 */
-80.1704490,

/* Input Number: 169 */
-53.5845970,

/* Input Number: 170 */
 33.3559760,

/* Input Number: 171 */
-40.2478252,

/* Input Number: 172 */
 10.1523369,

/* Input Number: 173 */
 79.3894023,

/* Input Number: 174 */
 60.1338322,

/* Input Number: 175 */
 99.8602130,

/* Input Number: 176 */
-66.4803645,

/* Input Number: 177 */
 93.4443040,

/* Input Number: 178 */
- 7.4008607,

/* Input Number: 179 */
 84.2871024,

/* Input Number: 180 */
 91.3168748,

/* Input Number: 181 */
-78.2592469,

/* Input Number: 182 */
 43.9351647,

/* Input Number: 183 */
-44.7323962,

/* Input Number: 184 */
-93.8124370,

/* Input Number: 185 */
-85.9748743,

/* Input Number: 186 */
 43.9140781,

/* Input Number: 187 */
-26.8243750,

/* Input Number: 188 */
 15.7954468,

/* Input Number: 189 */
 39.7333337,

/* Input Number: 190 */
 41.9944615,

/* Input Number: 191 */
 16.5212291,

/* Input Number: 192 */
 80.6249126,

/* Input Number: 193 */
 87.2338695,

/* Input Number: 194 */
-94.9980385,

/* Input Number: 195 */
-17.2620597,

/* Input Number: 196 */
-23.8103188,

/* Input Number: 197 */
 63.0252772,

/* Input Number: 198 */
-79.7517783,

/* Input Number: 199 */
-12.5985059,

/* Input Number: 200 */
- 0.7566982,


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
        a0[i] = exp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = expdp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = expdp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = expdp_i(a[i]);
    }
    expdp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = exp(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = expdp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = expdp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = expdp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    expdp_v(arg, output4, BUF_SIZE);
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
/*  End of file: expdp_d.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
