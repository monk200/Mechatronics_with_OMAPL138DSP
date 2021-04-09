/* ======================================================================= */
/* log10sp_d.h - log10 driver file                                         */
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

#include "log10sp.h"
#include "log10sp_i.h"
#include "log10sp_c.h"

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


// Floating Point Tolerances
#define RET_VAL_TOL (0.000005)



//  Initialized arrays with fixed test data.
float a [NUM_INPUTS] = 
{
/* Input Number: 0 */
 920184.5063765,

/* Input Number: 1 */
 182379.1119679,

/* Input Number: 2 */
 382181.6699036,

/* Input Number: 3 */
 291296.1817645,

/* Input Number: 4 */
 736276.2133991,

/* Input Number: 5 */
 413037.4952929,

/* Input Number: 6 */
 616996.8623519,

/* Input Number: 7 */
 826318.5844631,

/* Input Number: 8 */
 173241.6031542,

/* Input Number: 9 */
 784028.6320466,

/* Input Number: 10 */
 976065.8912868,

/* Input Number: 11 */
 374039.7151784,

/* Input Number: 12 */
 856094.0404753,

/* Input Number: 13 */
 403451.7501951,

/* Input Number: 14 */
 815068.5125761,

/* Input Number: 15 */
 282926.6915757,

/* Input Number: 16 */
 871180.9700556,

/* Input Number: 17 */
 867967.7436367,

/* Input Number: 18 */
 962742.4410124,

/* Input Number: 19 */
 374455.8143055,

/* Input Number: 20 */
 785690.4862970,

/* Input Number: 21 */
 219946.6280076,

/* Input Number: 22 */
 713006.5090306,

/* Input Number: 23 */
 931410.7057498,

/* Input Number: 24 */
 628132.6224710,

/* Input Number: 25 */
 986507.5030108,

/* Input Number: 26 */
 828885.5375070,

/* Input Number: 27 */
 713505.6837507,

/* Input Number: 28 */
 888248.4402638,

/* Input Number: 29 */
 156040.1537284,

/* Input Number: 30 */
 542552.6351054,

/* Input Number: 31 */
 941764.4477205,

/* Input Number: 32 */
 540598.4376451,

/* Input Number: 33 */
 182214.5118521,

/* Input Number: 34 */
 551365.2665486,

/* Input Number: 35 */
 310234.1381602,

/* Input Number: 36 */
 20990.5797884,

/* Input Number: 37 */
 999444.5491402,

/* Input Number: 38 */
 33532.9256771,

/* Input Number: 39 */
 985975.7809896,

/* Input Number: 40 */
 222664.5949517,

/* Input Number: 41 */
 999604.6377293,

/* Input Number: 42 */
 624653.0953392,

/* Input Number: 43 */
 593431.3289670,

/* Input Number: 44 */
 531415.8631044,

/* Input Number: 45 */
 47581.0340092,

/* Input Number: 46 */
 425533.1306504,

/* Input Number: 47 */
 234008.9490799,

/* Input Number: 48 */
 786488.7425884,

/* Input Number: 49 */
 481257.8594062,

/* Input Number: 50 */
 17836.1785927,

/* Input Number: 51 */
 474314.2441315,

/* Input Number: 52 */
 292416.8195025,

/* Input Number: 53 */
 99852.1936695,

/* Input Number: 54 */
 444487.2895656,

/* Input Number: 55 */
 353946.5615868,

/* Input Number: 56 */
 830561.4431689,

/* Input Number: 57 */
 179501.3145454,

/* Input Number: 58 */
 217543.7802081,

/* Input Number: 59 */
 373859.4669676,

/* Input Number: 60 */
 651460.8889073,

/* Input Number: 61 */
 449805.3325427,

/* Input Number: 62 */
 322137.0668377,

/* Input Number: 63 */
 511892.3845398,

/* Input Number: 64 */
 463087.1955951,

/* Input Number: 65 */
 129059.8762657,

/* Input Number: 66 */
 208518.7071077,

/* Input Number: 67 */
 211112.7527549,

/* Input Number: 68 */
 461971.2473192,

/* Input Number: 69 */
 892933.9005685,

/* Input Number: 70 */
 796137.4430053,

/* Input Number: 71 */
 387599.9532337,

/* Input Number: 72 */
 298183.6372464,

/* Input Number: 73 */
 886211.7719198,

/* Input Number: 74 */
 469576.8341217,

/* Input Number: 75 */
 414847.9934179,

/* Input Number: 76 */
 90899.8280118,

/* Input Number: 77 */
 718863.6901555,

/* Input Number: 78 */
 90430.8337065,

/* Input Number: 79 */
 147174.2721193,

/* Input Number: 80 */
 436273.3962606,

/* Input Number: 81 */
 485664.4973139,

/* Input Number: 82 */
 985431.1527733,

/* Input Number: 83 */
 896298.3761208,

/* Input Number: 84 */
 391656.7269982,

/* Input Number: 85 */
 730916.9180941,

/* Input Number: 86 */
 950486.5477805,

/* Input Number: 87 */
 454759.8211826,

/* Input Number: 88 */
 491442.5328053,

/* Input Number: 89 */
 479790.9653551,

/* Input Number: 90 */
 242738.7421288,

/* Input Number: 91 */
 76423.3452796,

/* Input Number: 92 */
 723441.2855155,

/* Input Number: 93 */
 222625.6302332,

/* Input Number: 94 */
 600246.0010973,

/* Input Number: 95 */
 488179.3670543,

/* Input Number: 96 */
 560222.5607080,

/* Input Number: 97 */
 907222.1852593,

/* Input Number: 98 */
 218402.2053418,

/* Input Number: 99 */
 874286.8549054,

/* Input Number: 100 */
 939586.2457130,

/* Input Number: 101 */
 977781.7142256,

/* Input Number: 102 */
 765631.0344657,

/* Input Number: 103 */
 907671.3744685,

/* Input Number: 104 */
 264527.4853309,

/* Input Number: 105 */
 324203.9848170,

/* Input Number: 106 */
 391221.2175773,

/* Input Number: 107 */
 714753.4834155,

/* Input Number: 108 */
 403243.0990585,

/* Input Number: 109 */
 301618.7784431,

/* Input Number: 110 */
 694053.2826855,

/* Input Number: 111 */
 891058.4903808,

/* Input Number: 112 */
 700874.5023269,

/* Input Number: 113 */
 757665.7508823,

/* Input Number: 114 */
 753767.1146532,

/* Input Number: 115 */
 512963.7917861,

/* Input Number: 116 */
 967746.4677917,

/* Input Number: 117 */
 989633.2732874,

/* Input Number: 118 */
 111401.8903728,

/* Input Number: 119 */
 110296.9414768,

/* Input Number: 120 */
 479442.4773275,

/* Input Number: 121 */
 767774.8842591,

/* Input Number: 122 */
 780933.3774339,

/* Input Number: 123 */
 689879.1040609,

/* Input Number: 124 */
 988403.9374025,

/* Input Number: 125 */
 331479.4487083,

/* Input Number: 126 */
 245543.8452481,

/* Input Number: 127 */
 727572.1596549,

/* Input Number: 128 */
 708467.4871450,

/* Input Number: 129 */
 393146.8957747,

/* Input Number: 130 */
 453541.9434361,

/* Input Number: 131 */
 164528.9171790,

/* Input Number: 132 */
 330327.9277667,

/* Input Number: 133 */
 122622.1774292,

/* Input Number: 134 */
 834133.0680143,

/* Input Number: 135 */
 418759.7653344,

/* Input Number: 136 */
 998175.1731253,

/* Input Number: 137 */
 178356.7480524,

/* Input Number: 138 */
 262158.2643734,

/* Input Number: 139 */
 365718.6399763,

/* Input Number: 140 */
 340970.6200044,

/* Input Number: 141 */
 660546.6555312,

/* Input Number: 142 */
 108939.7409252,

/* Input Number: 143 */
 349950.3849473,

/* Input Number: 144 */
 452862.8412661,

/* Input Number: 145 */
 169817.3210691,

/* Input Number: 146 */
 183652.2469776,

/* Input Number: 147 */
 200774.2662454,

/* Input Number: 148 */
 889320.2298957,

/* Input Number: 149 */
 744621.0091774,

/* Input Number: 150 */
 795856.1869482,

/* Input Number: 151 */
 193115.5631234,

/* Input Number: 152 */
 678821.3611628,

/* Input Number: 153 */
 912088.0790592,

/* Input Number: 154 */
 704682.9698467,

/* Input Number: 155 */
 94548.0559947,

/* Input Number: 156 */
 322886.9744765,

/* Input Number: 157 */
 660596.2351088,

/* Input Number: 158 */
 138385.5490218,

/* Input Number: 159 */
 118251.2998765,

/* Input Number: 160 */
 784315.1488906,

/* Input Number: 161 */
 451610.5988871,

/* Input Number: 162 */
 798258.9816634,

/* Input Number: 163 */
 966086.8834751,

/* Input Number: 164 */
 502833.3618170,

/* Input Number: 165 */
 207856.8379728,

/* Input Number: 166 */
 862466.0455021,

/* Input Number: 167 */
 797314.5830052,

/* Input Number: 168 */
 375587.5961221,

/* Input Number: 169 */
 329023.8323139,

/* Input Number: 170 */
 958805.9736787,

/* Input Number: 171 */
 240285.7255048,

/* Input Number: 172 */
 788358.7343177,

/* Input Number: 173 */
 679952.1817945,

/* Input Number: 174 */
 199836.2821280,

/* Input Number: 175 */
 396408.4770296,

/* Input Number: 176 */
 568702.2482647,

/* Input Number: 177 */
 594677.5502692,

/* Input Number: 178 */
 163254.0065901,

/* Input Number: 179 */
 828365.8089292,

/* Input Number: 180 */
 32840.7290545,

/* Input Number: 181 */
 872374.4194199,

/* Input Number: 182 */
 884231.6659614,

/* Input Number: 183 */
 583600.0940896,

/* Input Number: 184 */
 958259.8504797,

/* Input Number: 185 */
 789193.4457097,

/* Input Number: 186 */
 890451.5925058,

/* Input Number: 187 */
 163019.2405963,

/* Input Number: 188 */
 595481.6285919,

/* Input Number: 189 */
 82562.2077714,

/* Input Number: 190 */
 151358.0916312,

/* Input Number: 191 */
 536681.6229039,

/* Input Number: 192 */
 656370.2163453,

/* Input Number: 193 */
 962951.8067097,

/* Input Number: 194 */
 125063.0652845,

/* Input Number: 195 */
 151544.7341742,

/* Input Number: 196 */
 333549.0651071,

/* Input Number: 197 */
 102119.7639609,

/* Input Number: 198 */
 727092.7425107,

/* Input Number: 199 */
 919813.0411491,

/* Input Number: 200 */
 281026.5996295,
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
        a0[i] = log10f(a[i]);
    }
    for (i = 0; i < NUM_INPUTS ; i++) {
        a1[i] = log10sp(a[i]);
    }
    for (i = 0; i < NUM_INPUTS; i++) {
        a2[i] = log10sp_c(a[i]);
    }
	for (i = 0; i < NUM_INPUTS ; i++) {
        a3[i] = log10sp_i(a[i]);
    }
    log10sp_v(a, a4, NUM_INPUTS);
    

    
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
        output0[i] = log10f(arg[i]);
    }
    t_stop = clock();

    clockdata[0] = t_stop - t_start - t_offset;
    clockdata[0] = clockdata[0] / BUF_SIZE;

    // Time the fastRTS ASM function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output1[i] = log10sp(arg[i]);
    }
    t_stop = clock();

    clockdata[1] = t_stop - t_start - t_offset;
    clockdata[1] = clockdata[1] / BUF_SIZE;

    // Time the fastRTS C intrinsic function
    t_start = clock();
    for (i = 0; i < BUF_SIZE; i++) {
        output2[i] = log10sp_c(arg[i]);
    }
    t_stop = clock();

    clockdata[2] = t_stop - t_start - t_offset;
    clockdata[2] = clockdata[2] / BUF_SIZE;

    // Time the fastRTS inlined function    
    t_start = clock();  
    for (i = 0; i < BUF_SIZE; i++) {
        output3[i] = log10sp_i(arg[i]);
    }
    t_stop = clock();
    
    clockdata[3] = t_stop - t_start - t_offset;
    clockdata[3] = clockdata[3] / BUF_SIZE;
    
    // Time the fastRTS vector function
    t_start = clock();  
    log10sp_v(arg, output4, BUF_SIZE);
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
    printf ("Number of Clocks for log10:\n");
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
/*  End of file: log10sp_d.c                                                 */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
