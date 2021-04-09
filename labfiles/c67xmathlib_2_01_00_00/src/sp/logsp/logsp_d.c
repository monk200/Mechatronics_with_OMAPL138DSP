/* ======================================================================= */
/* logsp_d.h - log driver file                                             */
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

#include "logsp.h"
#include "logsp_i.h"
#include "logsp_c.h"

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
 882801.6794445,

/* Input Number: 1 */
 560317.0630053,

/* Input Number: 2 */
 122262.5250991,

/* Input Number: 3 */
 488666.1829456,

/* Input Number: 4 */
 59841.4251888,

/* Input Number: 5 */
 584370.8070949,

/* Input Number: 6 */
 374632.8022302,

/* Input Number: 7 */
 912026.4368577,

/* Input Number: 8 */
 842783.8098368,

/* Input Number: 9 */
 312756.9875380,

/* Input Number: 10 */
 723821.9348381,

/* Input Number: 11 */
 806095.6331373,

/* Input Number: 12 */
 127254.1847402,

/* Input Number: 13 */
 933245.6419599,

/* Input Number: 14 */
 379333.5453191,

/* Input Number: 15 */
 151118.0176415,

/* Input Number: 16 */
 417104.0555357,

/* Input Number: 17 */
 206774.3096981,

/* Input Number: 18 */
 135532.0028255,

/* Input Number: 19 */
 504309.8405133,

/* Input Number: 20 */
 793258.8017512,

/* Input Number: 21 */
 502566.9568444,

/* Input Number: 22 */
 375486.0566168,

/* Input Number: 23 */
 46851.7703576,

/* Input Number: 24 */
 960520.6096414,

/* Input Number: 25 */
 778533.3748699,

/* Input Number: 26 */
 94466.0389568,

/* Input Number: 27 */
 517367.4473240,

/* Input Number: 28 */
 185082.6081897,

/* Input Number: 29 */
 597005.1261599,

/* Input Number: 30 */
 856933.5341473,

/* Input Number: 31 */
 274538.3196528,

/* Input Number: 32 */
 345328.3101796,

/* Input Number: 33 */
 97330.6720787,

/* Input Number: 34 */
 843501.7982517,

/* Input Number: 35 */
 261801.0670960,

/* Input Number: 36 */
 904483.0122721,

/* Input Number: 37 */
 23203.8910473,

/* Input Number: 38 */
 811726.8713380,

/* Input Number: 39 */
 23121.1452181,

/* Input Number: 40 */
 930146.9469522,

/* Input Number: 41 */
 703193.0835740,

/* Input Number: 42 */
 123614.9634868,

/* Input Number: 43 */
 679481.8491929,

/* Input Number: 44 */
 74764.9524670,

/* Input Number: 45 */
 78021.1774775,

/* Input Number: 46 */
 725942.6554218,

/* Input Number: 47 */
 960100.1254672,

/* Input Number: 48 */
 591223.2092584,

/* Input Number: 49 */
 661556.6206542,

/* Input Number: 50 */
 169918.5582823,

/* Input Number: 51 */
 186895.5718195,

/* Input Number: 52 */
 313341.3101541,

/* Input Number: 53 */
 568101.7263595,

/* Input Number: 54 */
 591523.7737617,

/* Input Number: 55 */
 262682.7787054,

/* Input Number: 56 */
 683254.4938615,

/* Input Number: 57 */
 512461.3051655,

/* Input Number: 58 */
 727250.6830705,

/* Input Number: 59 */
 710304.6866620,

/* Input Number: 60 */
 727878.7498375,

/* Input Number: 61 */
 794207.5389890,

/* Input Number: 62 */
 906234.8791187,

/* Input Number: 63 */
 617886.1733557,

/* Input Number: 64 */
 74645.4646405,

/* Input Number: 65 */
 313486.9240174,

/* Input Number: 66 */
 38548.1287870,

/* Input Number: 67 */
 685756.8188983,

/* Input Number: 68 */
 939723.8052013,

/* Input Number: 69 */
 562998.6751490,

/* Input Number: 70 */
 646423.4216111,

/* Input Number: 71 */
 199043.0318191,

/* Input Number: 72 */
 131873.1958555,

/* Input Number: 73 */
 624235.4650102,

/* Input Number: 74 */
 836948.5525543,

/* Input Number: 75 */
 35575.4701211,

/* Input Number: 76 */
 60403.7970599,

/* Input Number: 77 */
 175207.7966430,

/* Input Number: 78 */
 313775.8034993,

/* Input Number: 79 */
 677529.0288811,

/* Input Number: 80 */
 719391.3802034,

/* Input Number: 81 */
 486645.2022061,

/* Input Number: 82 */
 369263.5398134,

/* Input Number: 83 */
 191905.0707410,

/* Input Number: 84 */
 703455.6914472,

/* Input Number: 85 */
 429683.2768611,

/* Input Number: 86 */
 892407.9681125,

/* Input Number: 87 */
 238395.7080342,

/* Input Number: 88 */
 199783.1569117,

/* Input Number: 89 */
 460318.2428449,

/* Input Number: 90 */
 372581.5412187,

/* Input Number: 91 */
 81020.2721105,

/* Input Number: 92 */
 992170.2879347,

/* Input Number: 93 */
 631093.6094214,

/* Input Number: 94 */
 876207.0696352,

/* Input Number: 95 */
 560831.2518734,

/* Input Number: 96 */
 445316.7274230,

/* Input Number: 97 */
 595036.8261095,

/* Input Number: 98 */
 85858.0363305,

/* Input Number: 99 */
 127190.9020074,

/* Input Number: 100 */
 532238.6463448,

/* Input Number: 101 */
 586083.4749314,

/* Input Number: 102 */
 257131.1955642,

/* Input Number: 103 */
 814263.2478729,

/* Input Number: 104 */
 814639.3386080,

/* Input Number: 105 */
 442559.0342842,

/* Input Number: 106 */
 250071.5894191,

/* Input Number: 107 */
 260614.1244948,

/* Input Number: 108 */
 446954.4465755,

/* Input Number: 109 */
 595415.8756193,

/* Input Number: 110 */
 517321.1611491,

/* Input Number: 111 */
 685705.6454784,

/* Input Number: 112 */
 176171.0931318,

/* Input Number: 113 */
 60479.6141308,

/* Input Number: 114 */
 108129.4135054,

/* Input Number: 115 */
 909496.3602833,

/* Input Number: 116 */
 349836.5751374,

/* Input Number: 117 */
 457908.0234948,

/* Input Number: 118 */
 656546.5614665,

/* Input Number: 119 */
 344586.8533488,

/* Input Number: 120 */
 896344.1686953,

/* Input Number: 121 */
 996652.4538629,

/* Input Number: 122 */
 397103.9970643,

/* Input Number: 123 */
 96.2401071,

/* Input Number: 124 */
 348522.1789260,

/* Input Number: 125 */
 482150.6273325,

/* Input Number: 126 */
 156976.7293764,

/* Input Number: 127 */
 473969.9093535,

/* Input Number: 128 */
 835734.6420742,

/* Input Number: 129 */
 304778.3051430,

/* Input Number: 130 */
 359902.5528877,

/* Input Number: 131 */
 964559.8958883,

/* Input Number: 132 */
 68279.3041031,

/* Input Number: 133 */
 466975.9796017,

/* Input Number: 134 */
 14446.5485080,

/* Input Number: 135 */
 251140.5666811,

/* Input Number: 136 */
 360803.2688866,

/* Input Number: 137 */
 540509.1859847,

/* Input Number: 138 */
 733551.7334338,

/* Input Number: 139 */
 721301.9341041,

/* Input Number: 140 */
 620637.3310868,

/* Input Number: 141 */
 713147.0818281,

/* Input Number: 142 */
 715017.1680112,

/* Input Number: 143 */
 355255.6088280,

/* Input Number: 144 */
 336035.3195075,

/* Input Number: 145 */
 757548.0866992,

/* Input Number: 146 */
 760989.3296372,

/* Input Number: 147 */
 710279.0540959,

/* Input Number: 148 */
 615238.1118337,

/* Input Number: 149 */
 31198.8486069,

/* Input Number: 150 */
 254551.1672393,

/* Input Number: 151 */
 955758.7633309,

/* Input Number: 152 */
 135718.3164065,

/* Input Number: 153 */
 499840.2234308,

/* Input Number: 154 */
 183177.7645389,

/* Input Number: 155 */
 846002.3094769,

/* Input Number: 156 */
 179265.5599926,

/* Input Number: 157 */
 717990.0871624,

/* Input Number: 158 */
 119125.9546122,

/* Input Number: 159 */
 735741.4073163,

/* Input Number: 160 */
 612588.3100005,

/* Input Number: 161 */
 824996.9605397,

/* Input Number: 162 */
 235198.5453145,

/* Input Number: 163 */
 568457.2748272,

/* Input Number: 164 */
 910600.1081331,

/* Input Number: 165 */
 576287.7427351,

/* Input Number: 166 */
 300684.4179585,

/* Input Number: 167 */
 876351.8299096,

/* Input Number: 168 */
 137025.4501108,

/* Input Number: 169 */
 292572.3901982,

/* Input Number: 170 */
 661935.4286696,

/* Input Number: 171 */
 799953.1940939,

/* Input Number: 172 */
 944266.5768153,

/* Input Number: 173 */
 906825.4771285,

/* Input Number: 174 */
 281365.4328340,

/* Input Number: 175 */
 52884.3978818,

/* Input Number: 176 */
 581343.9523098,

/* Input Number: 177 */
 948475.2534796,

/* Input Number: 178 */
 706280.6677766,

/* Input Number: 179 */
 964819.8101342,

/* Input Number: 180 */
 885941.7665924,

/* Input Number: 181 */
 520153.2858538,

/* Input Number: 182 */
 64860.9873477,

/* Input Number: 183 */
 442536.1919205,

/* Input Number: 184 */
 296316.4028624,

/* Input Number: 185 */
 340524.6830367,

/* Input Number: 186 */
 101383.9403789,

/* Input Number: 187 */
 993239.2675543,

/* Input Number: 188 */
 847214.7953092,

/* Input Number: 189 */
 713144.2347114,

/* Input Number: 190 */
 133310.9561250,

/* Input Number: 191 */
 724553.4887445,

/* Input Number: 192 */
 158223.2461638,

/* Input Number: 193 */
 534160.6298664,

/* Input Number: 194 */
 86278.9611551,

/* Input Number: 195 */
 317292.6625962,

/* Input Number: 196 */
 445480.4045156,

/* Input Number: 197 */
 292426.8053394,

/* Input Number: 198 */
 478658.2879981,

/* Input Number: 199 */
 72224.3540203,

/* Input Number: 200 */
 529557.8900335,

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
        a0[i] = logf(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = logsp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = logsp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = logsp_i(a[i]);
    }
    logsp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = logf(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = logsp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = logsp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = logsp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    logsp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for log:\n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    printf ("RTS\t\tASM\t\tC\t\tInlined\t\tVector \n");
    printf ("-------------------------------------------------------------------------------------------------------\n");
    
    printf ("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            (int)clockdata[0], (int)clockdata[1], (int)clockdata[2], (int)clockdata[3], (int)clockdata[4]);
}

// return random value of -1 to 1000000
float gimme_random( void ){
	return ((double)rand()/(double)RAND_MAX)*1000001-1;
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
/*  End of file: logsp_d.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */

