/* =========================================================================== */
/* powsp_i.h - single precision floating point raise to a power                */
/*              optimized inlined C implementation (w/ intrinsics)             */
/*                                                                             */
/* Rev 0.0.1                                                                   */
/*                                                                             */
/* --------------------------------------------------------------------------- */
/*            Copyright (c) 2010 Texas Instruments, Incorporated.              */
/*                           All Rights Reserved.                              */
/* =========================================================================== */


#ifndef POWSP_I_
#define POWSP_I_ 1



static double logtablei3[8] = {0, -.1177830356,
						-.2231435513,
						-.3184537311,
						-.4054651081,
						-.4855078157,
						-.5596157879,
						-.6286086594};



static inline float logsp_i1(float a)
{


	double	ln2  =  0.693147180559945;
	float	c1 = -0.2302894f;
	float	c2 =  0.1908169f;
	float	c3 = -0.2505905f;
	float	c4 =  0.3333164f;
	float	c5 = -0.5000002f;

	unsigned int	T_index;
	
	double dr;
	double frcpax;
	int N;
	float pol;
	float r;
	float r2;
	float r3;
	float r4;
	double rcp;
	double res;
	double T;
	
 /* r = x * frcpa(x) -1 */
    rcp = _rcpdp((double) a);
	frcpax = _itod(_clr(_hi(rcp),0,16), 0);
	dr = frcpax * (double) a  - 1.0; 

 /* Polynomial p(r) that approximates ln(1+r) - r  */
    r = (float) dr;
	r2 = r*r;
	r3 = r*r2;
	r4 = r2*r2; 
	
	pol = c5 * r2 + ((c4 * r3) + ((c2 * r + c3) + c1 * r2) * r4);
 
 /* Reconstruction: result = T + r + p(r) */

	N = _extu(_hi(frcpax), 1, 21) - 1023;
	T_index = _extu(_hi(frcpax), 12, 29);
	T = logtablei3[T_index] - ln2 * (double) N;
	res = (dr  + T) + (double) (pol);
	
	if (a<0) res = -3.40282347e+38;
	
	return (res);
}

/* kTable:  2^(0/4), 2^(1/4), 2^(2/4), 2^(3/4) */
static double kTablei1[4] = {1.0, 1.189207115, 1.414213562, 1.681792831}; 

	/* jTable:  2^(0/16), 2^(1/16), 2^(2/16), 2^(3/16) */
static double jTablei1[4] = {1.0, 1.044273782, 1.090507733, 1.138788635}; 

static inline float expsp_i1(float a)
{

	

	float	c0 = 0.1667361910f;
	float	c1 = 0.4999999651f;
	float	c2 = 0.9999998881f;
	double	dT;
	int		J;
	int		K;
	float	lnbase = 1.0f;
	float	log2_base_x16 = 1.442695041 * 16.0;
	int		N;
	float	P1 = 0.04331970214844;
	float	P2 = 1.99663646e-6;
	float	pol;
	float	r;
	float	r2;
	float	r3;
	double	resdp;
	unsigned int	Ttemp;

	/* Get N such that |N - x*16/ln(2)| is minimized */
	N = (int) (a * log2_base_x16 +.5f);
	
	if(( a * log2_base_x16)<-0.5f){
		N--;
	}

	/* Argument reduction, r, and polynomial approximation pol(r) */
	r = (a - P1 * (float) N) - P2 * (float) N;
	r2 = r * r;
	r3 = r * r2;
 
	pol = (r * c2) + ((r3 * c0) + (r2 * c1));
 
	/* Get index for ktable and jtable */
	K = _extu(N, 28, 30);
	J = N & 0x3;
	dT = kTablei1[K] * jTablei1[J];

	/* scale exponent to adjust for 2^M */
	Ttemp = _hi(dT) + (unsigned int) ((N >> 4) << 20);
	dT = _itod( Ttemp, _lo(dT));

	resdp = (dT * (1.0 + pol));
	
	if(_extu(_ftoi(a * lnbase), 1, 24) < 114){
		resdp = (1.0f + a * lnbase);               /* early exit for small a*/
	}

	/* Check if result would be +Inf. In that case,  */
	/* return 0x7f7fffff instead                     */
	if((a * lnbase)>88.722831726f){
		resdp = (_itof(0x7f7fffff));
	} 

	return((float) resdp);
}

static inline float powsp_i(float a, float b)
{

//#define NaN _itof(0x7fc00000)

/*                                   (2 ^ +127)          (2 ^ -126)   */
float   arg,W,X2;//,Zero=0.0,TWO=2.0,Big=1.7014118e+38,Small=1.17549435e-38 ;
int y, Sign=1,exp;
        
		
		y = _spint(b);

		if (a<0 & b==y){
			if (y&1){
				Sign = -1;	
			}
		}	
		
		arg = _fabsf(a);
		W = b*logsp_i1(arg);
     	X2 = Sign*expsp_i1(W);
	
		if (a<0 & b!=y) X2 = _itof(0x7fffffff); // NaN	
		
		exp = _extu(_ftoi(arg),1,24);
		if (exp<1) X2 = 0;
		

		return (X2); 
}


#endif

/* ======================================================================== */
/*  End of file: powsp_i.h                                                  */
/* ------------------------------------------------------------------------ */
/*          Copyright (C) 2010 Texas Instruments, Incorporated.             */
/*                          All Rights Reserved.                            */
/* ======================================================================== */
