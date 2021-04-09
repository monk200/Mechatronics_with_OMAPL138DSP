/* ======================================================================= */
/* atansp_d.h - arctangent driver file                                     */
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

#include "atansp.h"
#include "atansp_i.h"
#include "atansp_c.h"

#define BUF_SIZE 128

extern float gimme_random( void );
extern int isequal(float *arg1, float *arg2, int size, double tol);

/* Global declarations */
float array0[BUF_SIZE];
float array1[BUF_SIZE];
float array2[BUF_SIZE];
float array3[BUF_SIZE];
float array4[BUF_SIZE];
float array5[BUF_SIZE];


float * restrict arg;
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
#define NUM_INPUTS  (201)

//  Floating Point Tolerances
#define RET_VAL_TOL (0.000001)

//  Initialized arrays with fixed test data
float a [NUM_INPUTS] = 
{
/* Input Number: 0 */
  4.6857751,

/* Input Number: 1 */
- 4.3888050,

/* Input Number: 2 */
- 6.2219309,

/* Input Number: 3 */
  2.9734052,

/* Input Number: 4 */
- 3.3967064,

/* Input Number: 5 */
  3.6387301,

/* Input Number: 6 */
- 1.7971204,

/* Input Number: 7 */
- 5.4644940,

/* Input Number: 8 */
- 3.9856986,

/* Input Number: 9 */
- 0.5585872,

/* Input Number: 10 */
  3.8899913,

/* Input Number: 11 */
- 1.3168933,

/* Input Number: 12 */
- 5.4385924,

/* Input Number: 13 */
- 3.7650699,

/* Input Number: 14 */
  4.6782969,

/* Input Number: 15 */
- 0.4647531,

/* Input Number: 16 */
  1.0419428,

/* Input Number: 17 */
- 1.0364327,

/* Input Number: 18 */
- 1.2014995,

/* Input Number: 19 */
- 2.1744585,

/* Input Number: 20 */
  3.1192100,

/* Input Number: 21 */
  4.3466117,

/* Input Number: 22 */
  1.2910699,

/* Input Number: 23 */
- 1.2718891,

/* Input Number: 24 */
  5.4156570,

/* Input Number: 25 */
  0.8315685,

/* Input Number: 26 */
- 6.0598363,

/* Input Number: 27 */
- 0.7572985,

/* Input Number: 28 */
  4.4759914,

/* Input Number: 29 */
- 6.1766455,

/* Input Number: 30 */
  0.3737053,

/* Input Number: 31 */
  0.5156207,

/* Input Number: 32 */
  0.9926337,

/* Input Number: 33 */
  5.5872771,

/* Input Number: 34 */
- 1.6042174,

/* Input Number: 35 */
- 4.4321149,

/* Input Number: 36 */
  0.0484700,

/* Input Number: 37 */
- 0.1984939,

/* Input Number: 38 */
- 4.7144343,

/* Input Number: 39 */
- 5.7204383,

/* Input Number: 40 */
- 1.6439593,

/* Input Number: 41 */
- 5.2481460,

/* Input Number: 42 */
  2.4693651,

/* Input Number: 43 */
- 1.7414520,

/* Input Number: 44 */
- 2.7835699,

/* Input Number: 45 */
  0.5988448,

/* Input Number: 46 */
- 1.7384408,

/* Input Number: 47 */
  0.9387471,

/* Input Number: 48 */
  1.9785296,

/* Input Number: 49 */
- 6.0000916,

/* Input Number: 50 */
  2.7242336,

/* Input Number: 51 */
- 0.0025418,

/* Input Number: 52 */
- 2.6517277,

/* Input Number: 53 */
  6.2686322,

/* Input Number: 54 */
  2.6614318,

/* Input Number: 55 */
- 2.6427103,

/* Input Number: 56 */
- 2.6400110,

/* Input Number: 57 */
- 2.4830394,

/* Input Number: 58 */
  1.8838924,

/* Input Number: 59 */
- 0.4713757,

/* Input Number: 60 */
- 4.6442288,

/* Input Number: 61 */
- 4.8222659,

/* Input Number: 62 */
- 4.3154439,

/* Input Number: 63 */
  4.5527520,

/* Input Number: 64 */
  1.4895902,

/* Input Number: 65 */
  5.6976069,

/* Input Number: 66 */
- 3.4396315,

/* Input Number: 67 */
  2.1984083,

/* Input Number: 68 */
  5.1242322,

/* Input Number: 69 */
  2.3639411,

/* Input Number: 70 */
- 4.1265235,

/* Input Number: 71 */
- 0.7093108,

/* Input Number: 72 */
- 0.1325848,

/* Input Number: 73 */
  0.2595502,

/* Input Number: 74 */
  2.0924353,

/* Input Number: 75 */
- 5.7657023,

/* Input Number: 76 */
- 3.6162158,

/* Input Number: 77 */
- 6.1753312,

/* Input Number: 78 */
  2.8462950,

/* Input Number: 79 */
  2.4904875,

/* Input Number: 80 */
- 3.0831660,

/* Input Number: 81 */
- 5.7871494,

/* Input Number: 82 */
  2.5259382,

/* Input Number: 83 */
  6.0172287,

/* Input Number: 84 */
- 4.4142767,

/* Input Number: 85 */
  4.5001068,

/* Input Number: 86 */
- 2.6030415,

/* Input Number: 87 */
  3.6806216,

/* Input Number: 88 */
  3.3684705,

/* Input Number: 89 */
- 5.7893480,

/* Input Number: 90 */
  0.6336588,

/* Input Number: 91 */
- 1.3586379,

/* Input Number: 92 */
- 2.2594250,

/* Input Number: 93 */
  0.2887305,

/* Input Number: 94 */
  4.3750683,

/* Input Number: 95 */
- 1.4995354,

/* Input Number: 96 */
- 1.6341247,

/* Input Number: 97 */
  0.8448597,

/* Input Number: 98 */
  5.4956329,

/* Input Number: 99 */
  2.5371082,

/* Input Number: 100 */
  4.0196222,

/* Input Number: 101 */
  3.7116159,

/* Input Number: 102 */
  4.6723642,

/* Input Number: 103 */
  1.7090287,

/* Input Number: 104 */
  5.2056630,

/* Input Number: 105 */
- 4.3639392,

/* Input Number: 106 */
- 5.1992106,

/* Input Number: 107 */
  3.8826736,

/* Input Number: 108 */
- 3.1818808,

/* Input Number: 109 */
  5.7020068,

/* Input Number: 110 */
- 2.0431976,

/* Input Number: 111 */
- 3.6693872,

/* Input Number: 112 */
  3.1784537,

/* Input Number: 113 */
  4.3081429,

/* Input Number: 114 */
  2.8606615,

/* Input Number: 115 */
- 4.5421471,

/* Input Number: 116 */
  2.6360666,

/* Input Number: 117 */
  3.7467859,

/* Input Number: 118 */
  2.6723677,

/* Input Number: 119 */
- 2.9248591,

/* Input Number: 120 */
  2.9170800,

/* Input Number: 121 */
- 4.2826643,

/* Input Number: 122 */
- 5.2518562,

/* Input Number: 123 */
  1.1890674,

/* Input Number: 124 */
  3.7210742,

/* Input Number: 125 */
  1.2962931,

/* Input Number: 126 */
  6.0178581,

/* Input Number: 127 */
- 0.3196450,

/* Input Number: 128 */
- 3.7216546,

/* Input Number: 129 */
- 4.4120904,

/* Input Number: 130 */
  4.7258738,

/* Input Number: 131 */
  1.1919446,

/* Input Number: 132 */
  1.4413478,

/* Input Number: 133 */
- 4.2122495,

/* Input Number: 134 */
  1.3541709,

/* Input Number: 135 */
  6.1918232,

/* Input Number: 136 */
- 6.0560219,

/* Input Number: 137 */
- 1.8461036,

/* Input Number: 138 */
- 2.0835953,

/* Input Number: 139 */
- 5.7400353,

/* Input Number: 140 */
  3.2752317,

/* Input Number: 141 */
  3.3855143,

/* Input Number: 142 */
  0.9150622,

/* Input Number: 143 */
- 0.2683679,

/* Input Number: 144 */
  0.2876863,

/* Input Number: 145 */
  3.7615734,

/* Input Number: 146 */
- 3.9849563,

/* Input Number: 147 */
- 1.7430330,

/* Input Number: 148 */
- 2.0745753,

/* Input Number: 149 */
- 3.8509931,

/* Input Number: 150 */
- 1.8411623,

/* Input Number: 151 */
- 5.0391879,

/* Input Number: 152 */
  0.8101256,

/* Input Number: 153 */
- 5.8721242,

/* Input Number: 154 */
  1.7456782,

/* Input Number: 155 */
- 0.5412394,

/* Input Number: 156 */
  5.4864989,

/* Input Number: 157 */
  2.9558379,

/* Input Number: 158 */
  5.2709332,

/* Input Number: 159 */
  0.2325686,

/* Input Number: 160 */
  0.0316935,

/* Input Number: 161 */
- 5.2198479,

/* Input Number: 162 */
- 0.8460418,

/* Input Number: 163 */
  2.9672278,

/* Input Number: 164 */
  2.0953534,

/* Input Number: 165 */
- 3.9875018,

/* Input Number: 166 */
  3.0934242,

/* Input Number: 167 */
  4.9277258,

/* Input Number: 168 */
- 4.0785624,

/* Input Number: 169 */
- 0.1447828,

/* Input Number: 170 */
  3.6277482,

/* Input Number: 171 */
- 4.7947532,

/* Input Number: 172 */
- 4.7209644,

/* Input Number: 173 */
  3.9513529,

/* Input Number: 174 */
  3.9101131,

/* Input Number: 175 */
  4.8825841,

/* Input Number: 176 */
  5.5174241,

/* Input Number: 177 */
- 2.5734623,

/* Input Number: 178 */
- 0.8850934,

/* Input Number: 179 */
- 6.0615151,

/* Input Number: 180 */
- 1.2242225,

/* Input Number: 181 */
- 0.9716348,

/* Input Number: 182 */
  1.0316600,

/* Input Number: 183 */
  2.0928574,

/* Input Number: 184 */
  1.8022556,

/* Input Number: 185 */
- 5.9010623,

/* Input Number: 186 */
  1.0032966,

/* Input Number: 187 */
- 2.0393881,

/* Input Number: 188 */
- 4.8233904,

/* Input Number: 189 */
- 2.5928760,

/* Input Number: 190 */
- 5.7267153,

/* Input Number: 191 */
  4.8141505,

/* Input Number: 192 */
  1.6676956,

/* Input Number: 193 */
  2.9808447,

/* Input Number: 194 */
  5.8558562,

/* Input Number: 195 */
- 0.0463704,

/* Input Number: 196 */
- 1.8786020,

/* Input Number: 197 */
- 3.5725546,

/* Input Number: 198 */
  2.0789706,

/* Input Number: 199 */
  2.6725338,

/* Input Number: 200 */
  3.2779916,


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
        a0[i] = atanf(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = atansp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = atansp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = atansp_i(a[i]);
    }
    atansp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = atanf(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = atansp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = atansp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = atansp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    atansp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for atan:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of -6.283185 to 6.283185
float gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*(2*6.283185)-6.28319;
}

// compare two arrays
int isequal(float *arg1, float *arg2, int size, double tol){
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
/*  End of file: atansp_d.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

