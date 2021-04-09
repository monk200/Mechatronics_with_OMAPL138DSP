/* ======================================================================= */
/* atan2sp_d.h - arctangent two argument driver file                       */
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

#include "atan2sp.h"
#include "atan2sp_i.h"
#include "atan2sp_c.h"

#define BUF_SIZE 128

extern float gimme_random( void );
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
#define NUM_INPUTS  (201)

//  Floating Point Tolerances
#define RET_VAL_TOL (0.000001)

//  Initialized arrays with fixed test data
float a [NUM_INPUTS] = 
{
/* Input Number: 0 */
  2.3135381,

/* Input Number: 1 */
  1.8968619,

/* Input Number: 2 */
- 0.0756768,

/* Input Number: 3 */
  0.8868028,

/* Input Number: 4 */
- 0.9800547,

/* Input Number: 5 */
  0.1826697,

/* Input Number: 6 */
- 1.1155889,

/* Input Number: 7 */
- 1.0483080,

/* Input Number: 8 */
  1.6465753,

/* Input Number: 9 */
- 0.8641856,

/* Input Number: 10 */
- 0.8528155,

/* Input Number: 11 */
- 1.9450655,

/* Input Number: 12 */
- 2.6390254,

/* Input Number: 13 */
  0.5221994,

/* Input Number: 14 */
  2.8218998,

/* Input Number: 15 */
- 0.9806798,

/* Input Number: 16 */
- 3.1345328,

/* Input Number: 17 */
- 1.9067114,

/* Input Number: 18 */
- 2.3209479,

/* Input Number: 19 */
  1.0272207,

/* Input Number: 20 */
  2.8233285,

/* Input Number: 21 */
  2.6390254,

/* Input Number: 22 */
  1.1275215,

/* Input Number: 23 */
  1.3495004,

/* Input Number: 24 */
- 2.9128084,

/* Input Number: 25 */
- 1.9651832,

/* Input Number: 26 */
- 2.5642326,

/* Input Number: 27 */
  1.8925702,

/* Input Number: 28 */
- 2.3064093,

/* Input Number: 29 */
- 2.1316203,

/* Input Number: 30 */
  0.4856401,

/* Input Number: 31 */
  2.7499643,

/* Input Number: 32 */
  1.9174446,

/* Input Number: 33 */
  1.3146485,

/* Input Number: 34 */
- 2.7798670,

/* Input Number: 35 */
  2.2517497,

/* Input Number: 36 */
- 1.0791098,

/* Input Number: 37 */
- 0.4656905,

/* Input Number: 38 */
- 1.9318173,

/* Input Number: 39 */
- 3.0600822,

/* Input Number: 40 */
  1.4257409,

/* Input Number: 41 */
  0.8000701,

/* Input Number: 42 */
- 0.9783753,

/* Input Number: 43 */
  0.4934743,

/* Input Number: 44 */
  1.3673927,

/* Input Number: 45 */
- 1.0034392,

/* Input Number: 46 */
  0.6332442,

/* Input Number: 47 */
- 0.3479142,

/* Input Number: 48 */
  1.5669944,

/* Input Number: 49 */
- 1.1302520,

/* Input Number: 50 */
  1.6678470,

/* Input Number: 51 */
- 1.8060988,

/* Input Number: 52 */
  3.0330084,

/* Input Number: 53 */
- 2.9716971,

/* Input Number: 54 */
- 0.9224464,

/* Input Number: 55 */
- 1.7681531,

/* Input Number: 56 */
- 1.2403497,

/* Input Number: 57 */
  0.9910658,

/* Input Number: 58 */
  0.7251339,

/* Input Number: 59 */
  0.0664521,

/* Input Number: 60 */
- 1.1956786,

/* Input Number: 61 */
- 2.4353275,

/* Input Number: 62 */
  0.0850895,

/* Input Number: 63 */
  2.2100750,

/* Input Number: 64 */
- 1.0904034,

/* Input Number: 65 */
- 3.0326055,

/* Input Number: 66 */
  1.3948207,

/* Input Number: 67 */
  1.3624830,

/* Input Number: 68 */
- 0.6940544,

/* Input Number: 69 */
  1.3543253,

/* Input Number: 70 */
  0.8774785,

/* Input Number: 71 */
- 1.1167824,

/* Input Number: 72 */
- 1.5397275,

/* Input Number: 73 */
- 1.4583951,

/* Input Number: 74 */
- 0.7318605,

/* Input Number: 75 */
  0.4957987,

/* Input Number: 76 */
- 0.5997590,

/* Input Number: 77 */
- 0.2675051,

/* Input Number: 78 */
  1.8631171,

/* Input Number: 79 */
- 2.2671664,

/* Input Number: 80 */
- 2.9832040,

/* Input Number: 81 */
  1.7920738,

/* Input Number: 82 */
- 0.5029850,

/* Input Number: 83 */
- 0.9580196,

/* Input Number: 84 */
- 2.9132679,

/* Input Number: 85 */
- 0.2031369,

/* Input Number: 86 */
  0.2392143,

/* Input Number: 87 */
- 1.2708957,

/* Input Number: 88 */
- 2.7262275,

/* Input Number: 89 */
- 0.3890131,

/* Input Number: 90 */
- 2.3026158,

/* Input Number: 91 */
  1.7395388,

/* Input Number: 92 */
- 0.1722220,

/* Input Number: 93 */
- 0.8664596,

/* Input Number: 94 */
  2.6893643,

/* Input Number: 95 */
- 1.2955357,

/* Input Number: 96 */
- 1.1141723,

/* Input Number: 97 */
  0.6524964,

/* Input Number: 98 */
- 1.0036292,

/* Input Number: 99 */
- 2.5341911,

/* Input Number: 100 */
- 0.6030755,

/* Input Number: 101 */
- 1.4845922,

/* Input Number: 102 */
  0.1847009,

/* Input Number: 103 */
- 2.2969809,

/* Input Number: 104 */
- 1.7284012,

/* Input Number: 105 */
- 2.1670837,

/* Input Number: 106 */
- 0.9162604,

/* Input Number: 107 */
- 2.6918627,

/* Input Number: 108 */
- 3.0926890,

/* Input Number: 109 */
  1.9026916,

/* Input Number: 110 */
- 0.6157909,

/* Input Number: 111 */
- 1.2167198,

/* Input Number: 112 */
  1.3122679,

/* Input Number: 113 */
- 0.2426267,

/* Input Number: 114 */
  2.9885612,

/* Input Number: 115 */
  2.7933659,

/* Input Number: 116 */
  3.0079707,

/* Input Number: 117 */
- 2.5318231,

/* Input Number: 118 */
- 2.4902929,

/* Input Number: 119 */
  1.9892559,

/* Input Number: 120 */
- 1.8243082,

/* Input Number: 121 */
- 0.6330179,

/* Input Number: 122 */
  0.1249213,

/* Input Number: 123 */
- 0.2402831,

/* Input Number: 124 */
- 0.0144180,

/* Input Number: 125 */
  1.7226800,

/* Input Number: 126 */
  1.2449822,

/* Input Number: 127 */
- 2.1712261,

/* Input Number: 128 */
  1.0182503,

/* Input Number: 129 */
- 0.9841044,

/* Input Number: 130 */
  1.8955267,

/* Input Number: 131 */
  2.3830600,

/* Input Number: 132 */
- 1.5845531,

/* Input Number: 133 */
  2.8392730,

/* Input Number: 134 */
  1.5114688,

/* Input Number: 135 */
- 1.1034743,

/* Input Number: 136 */
  0.0325057,

/* Input Number: 137 */
- 2.1286954,

/* Input Number: 138 */
- 2.3589811,

/* Input Number: 139 */
  2.7031802,

/* Input Number: 140 */
- 0.5401727,

/* Input Number: 141 */
- 1.5467144,

/* Input Number: 142 */
- 1.2573473,

/* Input Number: 143 */
  2.0498470,

/* Input Number: 144 */
  1.0994474,

/* Input Number: 145 */
- 1.6878354,

/* Input Number: 146 */
- 1.2113809,

/* Input Number: 147 */
  2.3451656,

/* Input Number: 148 */
  1.1922679,

/* Input Number: 149 */
  1.9623993,

/* Input Number: 150 */
  2.6861392,

/* Input Number: 151 */
  0.9585329,

/* Input Number: 152 */
  0.6380016,

/* Input Number: 153 */
- 0.4698215,

/* Input Number: 154 */
  0.9541665,

/* Input Number: 155 */
- 0.2773711,

/* Input Number: 156 */
- 1.5496726,

/* Input Number: 157 */
- 1.6967815,

/* Input Number: 158 */
  1.1994481,

/* Input Number: 159 */
- 1.2693016,

/* Input Number: 160 */
- 1.7465209,

/* Input Number: 161 */
- 2.4450130,

/* Input Number: 162 */
  2.9895873,

/* Input Number: 163 */
  2.6623165,

/* Input Number: 164 */
  1.8586202,

/* Input Number: 165 */
  0.9722465,

/* Input Number: 166 */
- 2.2202118,

/* Input Number: 167 */
  1.7101600,

/* Input Number: 168 */
  3.0139285,

/* Input Number: 169 */
- 2.0721991,

/* Input Number: 170 */
  0.5109130,

/* Input Number: 171 */
- 2.9975483,

/* Input Number: 172 */
- 0.0452963,

/* Input Number: 173 */
  1.1814785,

/* Input Number: 174 */
- 0.8643483,

/* Input Number: 175 */
  0.4049361,

/* Input Number: 176 */
  1.8757297,

/* Input Number: 177 */
  2.9287528,

/* Input Number: 178 */
- 1.3302178,

/* Input Number: 179 */
- 3.1057060,

/* Input Number: 180 */
- 2.8633637,

/* Input Number: 181 */
- 0.1973840,

/* Input Number: 182 */
  2.4147408,

/* Input Number: 183 */
  1.1097204,

/* Input Number: 184 */
- 2.3930683,

/* Input Number: 185 */
- 0.7517271,

/* Input Number: 186 */
- 0.6176767,

/* Input Number: 187 */
  0.7760660,

/* Input Number: 188 */
  0.7684358,

/* Input Number: 189 */
  0.6968723,

/* Input Number: 190 */
  1.7993756,

/* Input Number: 191 */
  0.6814629,

/* Input Number: 192 */
  2.3639156,

/* Input Number: 193 */
  1.7913911,

/* Input Number: 194 */
  1.4757554,

/* Input Number: 195 */
- 2.4254864,

/* Input Number: 196 */
  2.6482566,

/* Input Number: 197 */
- 1.6377824,

/* Input Number: 198 */
  0.8112791,

/* Input Number: 199 */
- 0.9589719,

/* Input Number: 200 */
  0.0636593,


};

float b [NUM_INPUTS] = 
{
/* Input Number: 0 */
-91.2572958,

/* Input Number: 1 */
 18.7408531,

/* Input Number: 2 */
-53.8650442,

/* Input Number: 3 */
-75.7569229,

/* Input Number: 4 */
 96.3077229,

/* Input Number: 5 */
- 7.6091001,

/* Input Number: 6 */
-19.2073345,

/* Input Number: 7 */
 90.0992421,

/* Input Number: 8 */
  8.8307813,

/* Input Number: 9 */
 58.0715861,

/* Input Number: 10 */
-55.1536422,

/* Input Number: 11 */
 82.1953898,

/* Input Number: 12 */
 90.7922245,

/* Input Number: 13 */
 70.3973330,

/* Input Number: 14 */
 54.3926883,

/* Input Number: 15 */
 27.9326546,

/* Input Number: 16 */
-70.8640362,

/* Input Number: 17 */
 28.7746900,

/* Input Number: 18 */
 67.9949544,

/* Input Number: 19 */
- 4.3990179,

/* Input Number: 20 */
 56.3853689,

/* Input Number: 21 */
 72.7330394,

/* Input Number: 22 */
 89.7958760,

/* Input Number: 23 */
  0.6506345,

/* Input Number: 24 */
-53.2568907,

/* Input Number: 25 */
 90.5001414,

/* Input Number: 26 */
-34.3886068,

/* Input Number: 27 */
  0.1867002,

/* Input Number: 28 */
 18.4165466,

/* Input Number: 29 */
-89.5764153,

/* Input Number: 30 */
 86.0586351,

/* Input Number: 31 */
 96.1277471,

/* Input Number: 32 */
 33.6452472,

/* Input Number: 33 */
-93.5818388,

/* Input Number: 34 */
-13.4470613,

/* Input Number: 35 */
-65.5907704,

/* Input Number: 36 */
-99.7548511,

/* Input Number: 37 */
- 4.3503695,

/* Input Number: 38 */
-56.5984360,

/* Input Number: 39 */
-97.3693208,

/* Input Number: 40 */
 66.9302629,

/* Input Number: 41 */
 39.2945708,

/* Input Number: 42 */
-19.9401670,

/* Input Number: 43 */
-65.2324650,

/* Input Number: 44 */
-72.0181957,

/* Input Number: 45 */
 40.9931386,

/* Input Number: 46 */
 62.4405059,

/* Input Number: 47 */
-93.5376590,

/* Input Number: 48 */
 20.1598249,

/* Input Number: 49 */
-49.2629567,

/* Input Number: 50 */
 97.3422339,

/* Input Number: 51 */
 38.1619053,

/* Input Number: 52 */
 24.9950952,

/* Input Number: 53 */
 57.8565606,

/* Input Number: 54 */
-59.7228016,

/* Input Number: 55 */
 94.3208155,

/* Input Number: 56 */
-33.4966502,

/* Input Number: 57 */
  1.9489241,

/* Input Number: 58 */
-13.1378145,

/* Input Number: 59 */
-17.3492702,

/* Input Number: 60 */
 15.8208954,

/* Input Number: 61 */
-40.3999316,

/* Input Number: 62 */
-21.6943411,

/* Input Number: 63 */
-46.7005935,

/* Input Number: 64 */
 83.4348239,

/* Input Number: 65 */
 56.1003863,

/* Input Number: 66 */
- 0.9574840,

/* Input Number: 67 */
  3.5718092,

/* Input Number: 68 */
 26.1776647,

/* Input Number: 69 */
-42.3677828,

/* Input Number: 70 */
 75.9682995,

/* Input Number: 71 */
 71.6556690,

/* Input Number: 72 */
 43.3485769,

/* Input Number: 73 */
 74.3978270,

/* Input Number: 74 */
-17.6547310,

/* Input Number: 75 */
 40.5521602,

/* Input Number: 76 */
 79.0387887,

/* Input Number: 77 */
-37.0366985,

/* Input Number: 78 */
 32.3184751,

/* Input Number: 79 */
-64.2953153,

/* Input Number: 80 */
 21.3656540,

/* Input Number: 81 */
-79.2134105,

/* Input Number: 82 */
 87.1901856,

/* Input Number: 83 */
-72.6390439,

/* Input Number: 84 */
-99.0990864,

/* Input Number: 85 */
-10.6543498,

/* Input Number: 86 */
-51.6327866,

/* Input Number: 87 */
-68.6458331,

/* Input Number: 88 */
 93.0084248,

/* Input Number: 89 */
-45.0833611,

/* Input Number: 90 */
-37.1702853,

/* Input Number: 91 */
  5.1907654,

/* Input Number: 92 */
-83.6970233,

/* Input Number: 93 */
-52.2043266,

/* Input Number: 94 */
 21.5931263,

/* Input Number: 95 */
-51.1775924,

/* Input Number: 96 */
 32.6228238,

/* Input Number: 97 */
 40.7333065,

/* Input Number: 98 */
-41.1037088,

/* Input Number: 99 */
-92.1953541,

/* Input Number: 100 */
 47.8323105,

/* Input Number: 101 */
 51.2813626,

/* Input Number: 102 */
-46.9896947,

/* Input Number: 103 */
-27.5270931,

/* Input Number: 104 */
-87.4029587,

/* Input Number: 105 */
-59.7726969,

/* Input Number: 106 */
-74.5733577,

/* Input Number: 107 */
-25.9424445,

/* Input Number: 108 */
-78.4035322,

/* Input Number: 109 */
 12.3785878,

/* Input Number: 110 */
-58.3340343,

/* Input Number: 111 */
 89.3806460,

/* Input Number: 112 */
-89.5980000,

/* Input Number: 113 */
-85.7810516,

/* Input Number: 114 */
 12.0531909,

/* Input Number: 115 */
 40.0593417,

/* Input Number: 116 */
 61.7391895,

/* Input Number: 117 */
 40.9334400,

/* Input Number: 118 */
 87.7929490,

/* Input Number: 119 */
 88.5997007,

/* Input Number: 120 */
-99.2242204,

/* Input Number: 121 */
-73.7385827,

/* Input Number: 122 */
 67.2410088,

/* Input Number: 123 */
 43.0963350,

/* Input Number: 124 */
 93.5867665,

/* Input Number: 125 */
 51.0842296,

/* Input Number: 126 */
- 8.7863589,

/* Input Number: 127 */
 55.6547355,

/* Input Number: 128 */
 54.9392907,

/* Input Number: 129 */
 37.9593670,

/* Input Number: 130 */
 41.4129360,

/* Input Number: 131 */
 21.6191053,

/* Input Number: 132 */
-58.7140204,

/* Input Number: 133 */
 53.4582739,

/* Input Number: 134 */
-50.1859543,

/* Input Number: 135 */
-21.1997344,

/* Input Number: 136 */
 51.5337994,

/* Input Number: 137 */
 10.5222224,

/* Input Number: 138 */
-14.6191417,

/* Input Number: 139 */
-89.4206358,

/* Input Number: 140 */
 28.6006195,

/* Input Number: 141 */
-37.8060334,

/* Input Number: 142 */
-35.7869307,

/* Input Number: 143 */
-55.6486036,

/* Input Number: 144 */
 61.7771647,

/* Input Number: 145 */
-92.8920502,

/* Input Number: 146 */
 47.2177382,

/* Input Number: 147 */
-50.7940962,

/* Input Number: 148 */
 82.0212409,

/* Input Number: 149 */
-12.0875024,

/* Input Number: 150 */
-64.5874273,

/* Input Number: 151 */
-60.2094873,

/* Input Number: 152 */
-38.0300459,

/* Input Number: 153 */
 89.7133750,

/* Input Number: 154 */
 76.1698976,

/* Input Number: 155 */
 73.2225305,

/* Input Number: 156 */
-76.2539171,

/* Input Number: 157 */
 42.4176305,

/* Input Number: 158 */
 60.8972830,

/* Input Number: 159 */
 51.4205129,

/* Input Number: 160 */
-71.9763577,

/* Input Number: 161 */
 19.9461477,

/* Input Number: 162 */
 22.6601886,

/* Input Number: 163 */
-80.4704549,

/* Input Number: 164 */
 80.2687399,

/* Input Number: 165 */
-60.5444334,

/* Input Number: 166 */
 40.8969899,

/* Input Number: 167 */
 66.7207540,

/* Input Number: 168 */
 31.5421414,

/* Input Number: 169 */
 60.5660213,

/* Input Number: 170 */
-63.2807533,

/* Input Number: 171 */
 26.1853248,

/* Input Number: 172 */
-24.6500728,

/* Input Number: 173 */
-10.7415857,

/* Input Number: 174 */
 76.0305761,

/* Input Number: 175 */
 73.5657775,

/* Input Number: 176 */
 49.2212160,

/* Input Number: 177 */
 73.1837210,

/* Input Number: 178 */
-32.8017910,

/* Input Number: 179 */
 30.0932223,

/* Input Number: 180 */
-65.3040785,

/* Input Number: 181 */
  4.7972407,

/* Input Number: 182 */
 64.1718504,

/* Input Number: 183 */
 57.8754685,

/* Input Number: 184 */
 55.7897783,

/* Input Number: 185 */
 20.5711835,

/* Input Number: 186 */
-35.8692133,

/* Input Number: 187 */
 67.7430589,

/* Input Number: 188 */
-18.7016050,

/* Input Number: 189 */
 98.6509677,

/* Input Number: 190 */
  6.7179056,

/* Input Number: 191 */
-90.9222510,

/* Input Number: 192 */
 24.8186046,

/* Input Number: 193 */
-36.4573513,

/* Input Number: 194 */
 77.1555061,

/* Input Number: 195 */
-23.1775585,

/* Input Number: 196 */
 40.8544334,

/* Input Number: 197 */
 82.2189711,

/* Input Number: 198 */
  2.3360194,

/* Input Number: 199 */
 11.5269520,

/* Input Number: 200 */
 31.0396471,


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
        a0[i] = atan2f(a[i], b[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = atan2sp(a[i], b[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = atan2sp_c(a[i], b[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = atan2sp_i(a[i], b[i]);
    }
    atan2sp_v(a, b, a4, NUM_INPUTS);
    

    
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
        arg1[i] = gimme_random();
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
        output0[i] = atan2f(arg[i], arg1[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = atan2sp(arg[i], arg1[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = atan2sp_c(arg[i], arg1[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = atan2sp_i(arg[i], arg1[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    atan2sp_v(arg, arg1, output4, BUF_SIZE);
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
    printf ("Number of Clocks for atan2:\n");
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
/*  End of file: atan2sp_d.c                                                */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */


