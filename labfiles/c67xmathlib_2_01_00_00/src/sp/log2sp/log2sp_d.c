/* ======================================================================= */
/* log2sp_d.h - log2 driver file                                             */
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

#include "log2sp.h"
#include "log2sp_i.h"
#include "log2sp_c.h"

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
#define RET_VAL_TOL (0.000005)



//  Initialized arrays with fixed test data.
float a [NUM_INPUTS] = 
{
/* Input Number: 0 */
 2489.2649736,

/* Input Number: 1 */
 9443.3078004,

/* Input Number: 2 */
 6955.4981987,

/* Input Number: 3 */
 1933.0101774,

/* Input Number: 4 */
 2633.7180318,

/* Input Number: 5 */
 4703.2060297,

/* Input Number: 6 */
 529.4456706,

/* Input Number: 7 */
 2422.6100483,

/* Input Number: 8 */
 9886.0317200,

/* Input Number: 9 */
 87.6337049,

/* Input Number: 10 */
 2318.2353777,

/* Input Number: 11 */
 6531.8372930,

/* Input Number: 12 */
 5017.7131332,

/* Input Number: 13 */
 8402.2680088,

/* Input Number: 14 */
 4920.2771308,

/* Input Number: 15 */
 3752.6587757,

/* Input Number: 16 */
 2181.0001355,

/* Input Number: 17 */
 5943.8693066,

/* Input Number: 18 */
 4154.9904529,

/* Input Number: 19 */
 7191.3249399,

/* Input Number: 20 */
 9022.2167468,

/* Input Number: 21 */
 2507.1321101,

/* Input Number: 22 */
 9416.6212649,

/* Input Number: 23 */
 3290.3627812,

/* Input Number: 24 */
 6524.1143518,

/* Input Number: 25 */
 1185.9568993,

/* Input Number: 26 */
 3513.8266409,

/* Input Number: 27 */
 1911.2502612,

/* Input Number: 28 */
 9284.5759143,

/* Input Number: 29 */
 8647.6187158,

/* Input Number: 30 */
 2557.2505907,

/* Input Number: 31 */
 6331.2642889,

/* Input Number: 32 */
 5198.3899385,

/* Input Number: 33 */
 4894.9019533,

/* Input Number: 34 */
 6268.7381252,

/* Input Number: 35 */
 3360.2915487,

/* Input Number: 36 */
 5657.5807001,

/* Input Number: 37 */
 3468.3539961,

/* Input Number: 38 */
 7746.8661930,

/* Input Number: 39 */
 3266.3863159,

/* Input Number: 40 */
 5430.2096353,

/* Input Number: 41 */
 1245.3403638,

/* Input Number: 42 */
 3546.3811289,

/* Input Number: 43 */
 9616.5095821,

/* Input Number: 44 */
 2818.7965474,

/* Input Number: 45 */
 8521.4839309,

/* Input Number: 46 */
 3600.7623956,

/* Input Number: 47 */
 9509.7737158,

/* Input Number: 48 */
 9504.4376055,

/* Input Number: 49 */
 9240.4505817,

/* Input Number: 50 */
 1298.2704447,

/* Input Number: 51 */
 3463.2414555,

/* Input Number: 52 */
 581.7933284,

/* Input Number: 53 */
 529.7657143,

/* Input Number: 54 */
 3522.9454851,

/* Input Number: 55 */
 5373.1646931,

/* Input Number: 56 */
 4645.6074082,

/* Input Number: 57 */
 3092.7829085,

/* Input Number: 58 */
 535.0156847,

/* Input Number: 59 */
 2706.3189041,

/* Input Number: 60 */
 3663.3572817,

/* Input Number: 61 */
 1045.3471102,

/* Input Number: 62 */
 6052.7295713,

/* Input Number: 63 */
 6270.1468907,

/* Input Number: 64 */
 3061.1457770,

/* Input Number: 65 */
 1883.6480139,

/* Input Number: 66 */
 7208.4380403,

/* Input Number: 67 */
 325.5636587,

/* Input Number: 68 */
 1759.0104646,

/* Input Number: 69 */
 6714.8519063,

/* Input Number: 70 */
 4630.8821523,

/* Input Number: 71 */
 2592.1999425,

/* Input Number: 72 */
 2055.0254820,

/* Input Number: 73 */
 9828.5967860,

/* Input Number: 74 */
 2365.9059342,

/* Input Number: 75 */
 4165.3328553,

/* Input Number: 76 */
 9664.6725360,

/* Input Number: 77 */
 9126.1884702,

/* Input Number: 78 */
 7837.0883521,

/* Input Number: 79 */
 9635.8666666,

/* Input Number: 80 */
 3833.8240742,

/* Input Number: 81 */
 5926.5006952,

/* Input Number: 82 */
 1921.3285478,

/* Input Number: 83 */
 7048.8762107,

/* Input Number: 84 */
 7152.5411431,

/* Input Number: 85 */
 4887.0679766,

/* Input Number: 86 */
 9072.8972462,

/* Input Number: 87 */
 7830.0826908,

/* Input Number: 88 */
 5701.0565140,

/* Input Number: 89 */
 4316.3888165,

/* Input Number: 90 */
 7001.9019077,

/* Input Number: 91 */
 6897.6830678,

/* Input Number: 92 */
 8940.4013439,

/* Input Number: 93 */
 5704.9026266,

/* Input Number: 94 */
 6916.6893553,

/* Input Number: 95 */
 2509.4560492,

/* Input Number: 96 */
 9824.3877415,

/* Input Number: 97 */
 4194.1612358,

/* Input Number: 98 */
 3479.7745892,

/* Input Number: 99 */
 6536.1575373,

/* Input Number: 100 */
 4762.9965873,

/* Input Number: 101 */
 8187.0977925,

/* Input Number: 102 */
 4849.9083909,

/* Input Number: 103 */
 4106.3813691,

/* Input Number: 104 */
 3506.4853206,

/* Input Number: 105 */
 9580.4922304,

/* Input Number: 106 */
 2483.2928422,

/* Input Number: 107 */
 3885.4837628,

/* Input Number: 108 */
 9337.9575375,

/* Input Number: 109 */
 3843.7330435,

/* Input Number: 110 */
 1333.1270309,

/* Input Number: 111 */
 7915.2470814,

/* Input Number: 112 */
 8955.7747925,

/* Input Number: 113 */
 9709.5020809,

/* Input Number: 114 */
 9847.3874224,

/* Input Number: 115 */
 1770.2154705,

/* Input Number: 116 */
 2476.7038363,

/* Input Number: 117 */
 9401.7199650,

/* Input Number: 118 */
 9887.8536022,

/* Input Number: 119 */
 4366.5998181,

/* Input Number: 120 */
 3474.3809415,

/* Input Number: 121 */
 8602.0194607,

/* Input Number: 122 */
 6696.9491524,

/* Input Number: 123 */
 8112.6929863,

/* Input Number: 124 */
 8898.1719480,

/* Input Number: 125 */
 6447.8131318,

/* Input Number: 126 */
 9012.1838109,

/* Input Number: 127 */
 8795.4371984,

/* Input Number: 128 */
 9231.3582832,

/* Input Number: 129 */
 5453.9426627,

/* Input Number: 130 */
 8946.4952464,

/* Input Number: 131 */
 5735.4688393,

/* Input Number: 132 */
 8335.8001175,

/* Input Number: 133 */
 1629.7907230,

/* Input Number: 134 */
 2148.0389340,

/* Input Number: 135 */
 1592.3932504,

/* Input Number: 136 */
 3528.6801932,

/* Input Number: 137 */
 4363.9297479,

/* Input Number: 138 */
 7644.2438993,

/* Input Number: 139 */
 2521.5105555,

/* Input Number: 140 */
 5584.3530115,

/* Input Number: 141 */
 6498.9507235,

/* Input Number: 142 */
 7875.6456993,

/* Input Number: 143 */
 8093.7696097,

/* Input Number: 144 */
 8613.9906239,

/* Input Number: 145 */
 4411.1376046,

/* Input Number: 146 */
 8780.7781030,

/* Input Number: 147 */
 1373.5052695,

/* Input Number: 148 */
 301.2880669,

/* Input Number: 149 */
 7739.6799047,

/* Input Number: 150 */
 9674.4490104,

/* Input Number: 151 */
 8768.3313238,

/* Input Number: 152 */
 1710.6723220,

/* Input Number: 153 */
 9733.2895055,

/* Input Number: 154 */
 3326.7900875,

/* Input Number: 155 */
 135.1159175,

/* Input Number: 156 */
 7282.2179435,

/* Input Number: 157 */
 6980.2576554,

/* Input Number: 158 */
 6005.1717640,

/* Input Number: 159 */
 8832.7259784,

/* Input Number: 160 */
 5066.5212490,

/* Input Number: 161 */
 9525.4375434,

/* Input Number: 162 */
 7274.1704357,

/* Input Number: 163 */
 1708.1140128,

/* Input Number: 164 */
 6299.9513064,

/* Input Number: 165 */
 789.3287416,

/* Input Number: 166 */
 349.1056621,

/* Input Number: 167 */
 8796.7838421,

/* Input Number: 168 */
 5906.3791511,

/* Input Number: 169 */
 7808.4103849,

/* Input Number: 170 */
 1669.9829555,

/* Input Number: 171 */
 3897.0960900,

/* Input Number: 172 */
 2070.9691925,

/* Input Number: 173 */
 834.9331511,

/* Input Number: 174 */
 1246.4134107,

/* Input Number: 175 */
 3954.8957187,

/* Input Number: 176 */
 6553.5637984,

/* Input Number: 177 */
 3738.7359072,

/* Input Number: 178 */
 2428.4396525,

/* Input Number: 179 */
 9643.6642791,

/* Input Number: 180 */
 4371.2316781,

/* Input Number: 181 */
 3724.9346687,

/* Input Number: 182 */
 2177.2329141,

/* Input Number: 183 */
 4739.4544539,

/* Input Number: 184 */
 4155.6309228,

/* Input Number: 185 */
 1454.9004011,

/* Input Number: 186 */
 636.6707407,

/* Input Number: 187 */
 6750.9567068,

/* Input Number: 188 */
 7876.6961828,

/* Input Number: 189 */
 1086.0034557,

/* Input Number: 190 */
 1602.4396744,

/* Input Number: 191 */
 6483.7640657,

/* Input Number: 192 */
 997.5972861,

/* Input Number: 193 */
 113.4317391,

/* Input Number: 194 */
 2246.9576103,

/* Input Number: 195 */
 8161.5743108,

/* Input Number: 196 */
 2400.8469961,

/* Input Number: 197 */
 9489.2403040,

/* Input Number: 198 */
 3120.5264006,

/* Input Number: 199 */
 9502.1701835,

/* Input Number: 200 */
 4344.7576497,


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
        a0[i] = log2f(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = log2sp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = log2sp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = log2sp_i(a[i]);
    }
    log2sp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = log2f(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = log2sp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = log2sp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = log2sp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    log2sp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for log2:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of -1 to 10000
float gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*10001-1;
}

// compare two arrays (in this case tolerance is treated as percent error)
int isequal(float *arg1, float *arg2, int size, double tol){
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
/*  End of file: log2sp_d.h                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
