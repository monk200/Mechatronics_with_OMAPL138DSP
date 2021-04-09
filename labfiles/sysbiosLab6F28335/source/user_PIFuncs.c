#include <coecsl.h>

extern float Enc1_rad;
extern float Enc2_rad;

// globals only used by PIVelCopntrol
float encoder1 = 0.0F;
float encoder2 = 0.0F;
float p1_old   = 0.0F;
float p2_old   = 0.0F;
float v1       = 0.0F;
float v2       = 0.0F;
float v1_old   = 0.0F;
float v2_old   = 0.0F;
float u1       = 0.0F;
float u2       = 0.0F;
float e1       = 0.0F;
float e2       = 0.0F;
float e1s      = 0.0F;
float e2s      = 0.0F;
float esteer   = 0.0F;
float esteeri  = 0.0F;
// Tunable gains
// Closed-loop coupled velocity control
float Kp       = 3.0F;
float Ki       = 15.0F;
float Kp_turn  = 3.0F;
// Friction Compensation
float Vpos =  2.17*0.6;
float Vneg =  2.15*0.6;
float Cpos =  2.8*0.6;
float Cneg = -2.6*0.6;

void PIVelControl(float vref, float turn) {

    float x1,x2;

    //read_encoders(1, &encoder1, &encoder2, g_standard_GearMotor);
    encoder1 = Enc1_rad;
    encoder2 = Enc2_rad;
    // Calculate position (tiles) from encoder readings
    x1 = encoder1/193.0;  // was 193
    x2 = encoder2/193.0;
	
    // Calculate velocity (tiles/sec) from position
    v1 = (x1 - p1_old)/0.001;
    v2 = (x2 - p2_old)/0.001;
    
    // Fix the flip-over problem with the encoders...
    if ((-100.0F>v1)||(100.0F<v1))  v1 = v1_old;
    if ((-100.0F>v2)||(100.0F<v2))  v2 = v2_old;

    // Calculate PI Coupled Control Effort
    esteer   = v2 - v1 + turn;
    e1  =  vref - v1 + Kp_turn*esteer;
    e2  =  vref - v2 - Kp_turn*esteer;
    e1s =  e1s + e1;
    e2s =  e2s + e2;
    u1  = Kp*e1 + Ki*0.001*e1s;
    u2  = Kp*e2 + Ki*0.001*e2s;
    
    // Check for integral windup
    if (fabs(u1)>10.0) e1s = e1s * 0.99;
    if (fabs(u2)>10.0) e2s = e2s * 0.99;

    // Friction compensation
    if (v1> 0.0) {
        u1 = u1 + Vpos*v1 + Cpos;
    }
    else {
        u1 = u1 + Vneg*v1 + Cneg;
    }

    if (v2> 0.0) {
        u2 = u2 + Vpos*v2 + Cpos;
    }
    else {
        u2 = u2 + Vneg*v2 + Cneg;
    }
    
    // Final check to make sure within range
    if (u1> 10)  u1 = 10.0;
    if (u1<-10)  u1 = -10.0;
    if (u2> 10)  u2 = 10.0;
    if (u2<-10)  u2 = -10.0;

    // Send PWM command to motors
    PWM_out(EPWM1,u1);
	PWM_out(EPWM2,-u2);
        

    // Save old positions and velocities
    p1_old = x1;
    p2_old = x2;
        
    v1_old = v1;
    v2_old = v2;

}

void PIVelControl_Zero(void) {
	float x1,x2;

	    //read_encoders(1, &encoder1, &encoder2, g_standard_GearMotor);
		encoder1 = Enc1_rad;
	    encoder2 = Enc2_rad;
	    // Calculate position (tiles) from encoder readings
	    x1 = encoder1/193.0;  // was 193
	    x2 = encoder2/193.0;
	    p1_old = x1;
	    p2_old = x2;

	    v1 = 0;
	    v2 = 0;
	    v1_old = v1;
	    v2_old = v2;

	    e1s = 0;
	    e2s = 0;

	    PWM_out(EPWM1,0.0);
	    PWM_out(EPWM2,0.0);
}
