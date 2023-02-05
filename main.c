/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CK32MP503
    The generated drivers are tested against the following:
        Compiler          :  XC16 v2.0
        MPLAB 	          :  MPLAB X v6.05
*/

//raspi-gpio set 17 ip pn //(before PIC programming)

#include "mcc_generated_files/system.h"
#include "mcc_generated_files/i2c1.h"
#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pwm.h"
#include "mcc_generated_files/spi1.h"
#include "mcc_generated_files/sccp1_tmr.h"
#include "mcc_generated_files/interrupt_manager.h"
#include "mcc_generated_files/delay.h"
#include "mcc_generated_files/dma.h"
#include <stdio.h>
#include <math.h>
//#include <p33CK32MP503.h>
#ifdef SaraKIT
#include "LSM6DS3TR.h"
#endif

#define ACC_I2C_ADDRESS ((uint8_t)0b1101010)
#define NOT_SET -12345.0
#define _PI 3.14159265359f
#define _2PI 6.28318530718f
#define _PI_2 1.57079632679f
#define _PI_3 1.0471975512f
#define _3PI_2 4.71238898038f
#define _SQRT3 1.73205080757f
#define _sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )
#define _constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))
#define _sqrt(a) (_sqrtApprox(a))
#define _isset(a) ( (a) != (NOT_SET) )
#define _round(x) ((x)>=0?(long)((x)+0.5f):(long)((x)-0.5f))
#define _fabs(x) ((x)>=0?(float)(x):(float)(-x))

//MotionControlType
#define MCT_torque              0x00 //Torque control as Gimbal Motors (only torque, without velocity, without angle control)
#define MCT_velocity            0x01 //Velocity motion control (velocity, torque)
#define MCT_angle               0x02 //Position/angle motion control (angle, velocity, torque)
#define MCT_velocity_openloop   0x03 //mode without encoder (only velocity)
#define MCT_angle_openloop      0x04 //mode without encoder

typedef struct PIDController
{
    /*
     * @param P - Proportional gain
     * @param I - Integral gain
     * @param D - Derivative gain
     * @param ramp - Maximum speed of change of the output value
     * @param limit - Maximum output value
     */
    float P; //Proportional gain
    float I; //Integral gain
    float D; //Derivative gain
    float output_ramp; //Maximum speed of change of the output value
    float limit; //Maximum output value

    float error_prev; //last tracking error value
    float output_prev;  //last pid output value
    float integral_prev; //last integral component value
    uint64_t timestamp_prev; //Last execution timestamp
} pidController;

typedef struct LowPassFilter
{
    float Tf; //Low pass filter time constant
    uint64_t timestamp_prev;  //Last execution timestamp
    float y_prev; //filtered value in previous execution step
} lowPassFilter;

struct DQVoltage_s
{
    float d;
    float q;
};

// velocity calculation variables
volatile struct Encoder {
    bool enabled;
    volatile float angle;
    volatile float velocity;
    struct LowPassFilter LPF_velocity;
    struct LowPassFilter LPF_angle;
    int8_t encoderDirection;//if encoderDirection == Direction::CCW then direction will be flipped to CW 0 (auto) or 1 or -1
    float angle_prev; //result of last call to getSensorAngle(), used for full rotations and velocity
    uint64_t angle_prev_ts; //timestamp of last call to getAngle, used for velocity
    float vel_angle_prev; //angle at last call to getVelocity, used for velocity
    uint64_t vel_angle_prev_ts; //last velocity calculation timestamp
    int32_t full_rotations; //full rotation tracking
    int32_t vel_full_rotations; //previous full rotation value for velocity calculation
    uint16_t encoderMinRawAngle;//PWM min Range
    uint16_t encoderMaxRawAngle;//PWM max Range
    float encoderRawAngle;
    float min_elapsed_time;
    volatile float zeroAngle;
    volatile int16_t motorNr;
};
//todo - dokonczyc opisy
volatile struct motor{
    volatile bool enabled;
    volatile int16_t mode;
    volatile int16_t PolePairs;//11 //5 for 12N14P or 11 for 24N22P
    volatile bool isEncoder;//0 //pod??czony encoder =1
    volatile float currentPosition;//0 //obecna pozycja silnikow (7x360)/2 => -1260-0-1260
    volatile float currentVelocity;//0 //current velocity
    volatile float target; //!< current target value - depends of the controller
    //!< current target velocity //przy velocity sprawdzic poni?ej 0.3 i - przy zero da przekr?ci? i trzyma z oporem pozycj? ale jest zero wi?c nie wraca
    volatile float maxVelocity;//1 = 2PI = jeden obrót ale gdy 11 polepair to 1=1/11 
    volatile float maxTorque; //!< Voltage limitting variable - global limit
    volatile float electricalPosition;//0 //obecna pozycja w tablicy generujacej kolowe pole magnetyczne 0.0-360.0
    volatile uint32_t lastMotion;//0 //jak dawno ostatni ruch, zero gdy nadal trwa
    volatile float idleTorque;//1.0f
    volatile float keepTorqueTime;//2000
    volatile float dir;//1 //kierunek ruchu
    volatile uint64_t openLoopTimeStamp;
    // sensor related variabels
    float sensorOffset; //!< user defined sensor zero offset
    uint8_t controller;
    volatile int16_t encoderNr;
    struct DQVoltage_s voltage;
    struct PIDController PID_velocity;//={0.2f,20.0f,0.0f,1000.0f,10.0f};//!< parameter determining the velocity PID configuration
    struct PIDController P_angle;//={20.0f,0,0,0,10.0f};	//!< parameter determining the position PID configuration            
    
    int gennum1;
    int gennum2;
    int gennum3;
    float Ua,Ub,Uc;
};

volatile struct Encoder encoder[2];

//uint16_t __attribute__((coherent)) DMA_XRxBuffer[32];
extern volatile uint16_t DMA_TxBuffer[16];
extern volatile uint16_t DMA_RxBuffer[16];

volatile uint8_t I2C_Buffer[16];
volatile bool I2CRead = false;
volatile bool I2CWrite = false;
volatile uint8_t I2Caddress;
volatile uint8_t I2Cdata;
volatile uint8_t I2Clength;

extern int16_t data_raw_acceleration[3];
extern int16_t data_raw_angular_rate[3];
extern int16_t data_raw_temperature;
extern float temperature_degC;


const int sine_array[200] = {0,79,158,237,316,395,473,552,631,710,789,867,946,1024,1103,1181,1260,1338,1416,1494,1572,1650,1728,1806,1883,1961,2038,2115,2192,2269,2346,2423,2499,2575,2652,2728,2804,2879,2955,3030,3105,3180,3255,3329,3404,3478,3552,3625,3699,3772,3845,3918,3990,4063,4135,4206,4278,4349,4420,4491,4561,4631,4701,4770,4840,4909,4977,5046,5113,5181,5249,5316,5382,5449,5515,5580,5646,5711,5775,5839,5903,5967,6030,6093,6155,6217,6279,6340,6401,6461,6521,6581,6640,6699,6758,6815,6873,6930,6987,7043,7099,7154,7209,7264,7318,7371,7424,7477,7529,7581,7632,7683,7733,7783,7832,7881,7930,7977,8025,8072,8118,8164,8209,8254,8298,8342,8385,8428,8470,8512,8553,8594,8634,8673,8712,8751,8789,8826,8863,8899,8935,8970,9005,9039,9072,9105,9138,9169,9201,9231,9261,9291,9320,9348,9376,9403,9429,9455,9481,9506,9530,9554,9577,9599,9621,9642,9663,9683,9702,9721,9739,9757,9774,9790,9806,9821,9836,9850,9863,9876,9888,9899,9910,9920,9930,9939,9947,9955,9962,9969,9975,9980,9985,9989,9992,9995,9997,9999,10000,10000};

static struct motor mot[2];

//i2c LSM6DS3TR
volatile uint8_t i2cBufferTX[8] = {0};
volatile uint8_t i2cBufferRX[8] = {0};
extern bool LSM6DS3TREnable;

volatile uint64_t tmr2=0; //every 100us
volatile bool newTmr = false; //new timer event every 250us

uint64_t _micros(){  
    return tmr2*100;
}

void timer_interrupt(void){
    newTmr=true; //every 250us
}

void SCCP1_TMR_Timer32CallBack(){
    tmr2++;
}

static void Reset(void){
    asm ("reset");
}

void Delay(uint16_t ms){
    DELAY_milliseconds(ms);
}

float _sin(float a){
  if(a < _PI_2){
    //return sine_array[(int)(199.0f*( a / (_PI/2.0)))];
    //return sine_array[(int)(126.6873f* a)];           // float array optimized
    return 0.0001f*sine_array[_round((126.6873f* a))];      // int array optimized
  }else if(a < _PI){
    // return sine_array[(int)(199.0f*(1.0f - (a-_PI/2.0) / (_PI/2.0)))];
    //return sine_array[398 - (int)(126.6873f*a)];          // float array optimized
    return 0.0001f*sine_array[398 - _round((126.6873f*a))];     // int array optimized
  }else if(a < _3PI_2){
    // return -sine_array[(int)(199.0f*((a - _PI) / (_PI/2.0)))];
    //return -sine_array[-398 + (int)(126.6873f*a)];           // float array optimized
    return -0.0001f*sine_array[-398 + _round((126.6873f*a))];      // int array optimized
  } else {
    // return -sine_array[(int)(199.0f*(1.0f - (a - 3*_PI/2) / (_PI/2.0)))];
    //return -sine_array[796 - (int)(126.6873f*a)];           // float array optimized
    return -0.0001f*sine_array[796 - _round((126.6873f*a))];      // int array optimized
  }
}
/*
float _cos(float a){
  float a_sin = a + _PI_2;
  a_sin = a_sin > _2PI ? a_sin - _2PI : a_sin;
  return _sin(a_sin);
}
double MyFmod(double x, double y) {
  return x - trunc(x / y) * y;
}
*/

// square root approximation function using
// https://reprap.org/forum/read.php?147,219210
// https://en.wikipedia.org/wiki/Fast_inverse_square_root
float _sqrtApprox(float number) {//low in fat
  long i;
  float y;
  // float x;
  // const float f = 1.5F; // better precision

  // x = number * 0.5F;
  y = number;
  i = * ( long * ) &y;
  i = 0x5f375a86 - ( i >> 1 );
  y = * ( float * ) &i;
  // y = y * ( f - ( x * y * y ) ); // better precision
  return number * y;
}

float PIDControllerF(pidController *pid, float error){  
    // calculate the time from the last call
    uint64_t timestamp_now = _micros();
    float Ts = (timestamp_now - pid->timestamp_prev) * 1e-3f;
    Ts=Ts*1e-3f;
    // quick fix for strange cases (micros overflow)
    if(Ts <= 0 || Ts > 0.5f) Ts = 1e-3f;

    float proportional = pid->P * error;
    // Tustin transform of the integral part
    // u_ik = u_ik_1  + I*Ts/2*(ek + ek_1)
    float integral = pid->integral_prev + pid->I*Ts*0.5f*(error + pid->error_prev);
    // antiwindup - limit the output
    integral = _constrain(integral, -pid->limit, pid->limit);
    // Discrete derivation
    // u_dk = D(ek - ek_1)/Ts
    float derivative = pid->D*(error - pid->error_prev)/Ts;

    // sum all the components
    float output = proportional + integral + derivative;
    // antiwindup - limit the output variable
    output = _constrain(output, -pid->limit, pid->limit);

    // if output ramp defined
    if(pid->output_ramp > 0){
        // limit the acceleration by ramping the output
        float output_rate = (output - pid->output_prev)/Ts;
        if (output_rate > pid->output_ramp)
            output = pid->output_prev + pid->output_ramp*Ts;
        else if (output_rate < -pid->output_ramp)
            output = pid->output_prev - pid->output_ramp*Ts;
    }
    // saving for the next pass
    pid->integral_prev = integral;
    pid->output_prev = output;
    pid->error_prev = error;
    pid->timestamp_prev = timestamp_now;
    return output;
}

float LowPassFilterF(lowPassFilter *lpf, float x)
{
    uint64_t timestamp = _micros();
    float dt = (timestamp - lpf->timestamp_prev)*1e-3f;
    dt=dt*1e-3f;
  
    if (dt < 0.0f ) dt = 1e-3f;
    else if(dt > 0.3f) {
        lpf->y_prev = x;
        lpf->timestamp_prev = timestamp;
        return x;
    }

    float alpha = lpf->Tf/(lpf->Tf + dt);
    float y = alpha*lpf->y_prev + (1.0f - alpha)*x;
    lpf->y_prev = y;
    lpf->timestamp_prev = timestamp;
    return y;
}

// normalizing radian angle to [0,2PI]
float _normalizeAngle(float angle){
  float a = fmod(angle, _2PI);
  return a >= 0 ? a : (a + _2PI);
}
// Electrical angle calculation
float _electricalAngle(float currentPosition, int pole_pairs){
  return (currentPosition * pole_pairs);
}

/*--ENCODER-------------------------------*/
float encoder_getAngle(uint16_t n){
    uint16_t encVal=0;
    if (n==0)
        getEnc1Val(&encVal);
    else 
        getEnc2Val(&encVal);            

    return ( (float) (encVal) / encoder[n].encoderRawAngle) * _2PI;
}

float encoder_getVelocity(uint16_t n) {
    // calculate sample time
    float Ts = (encoder[n].angle_prev_ts - encoder[n].vel_angle_prev_ts)*1e-3f;
    Ts=Ts*1e-3f;
    if (Ts < encoder[n].min_elapsed_time) return encoder[n].velocity; // don't update velocity if Ts is too small

    encoder[n].velocity = ( (float)(encoder[n].full_rotations - encoder[n].vel_full_rotations)*_2PI + (encoder[n].angle_prev - encoder[n].vel_angle_prev) ) / Ts;
    encoder[n].vel_angle_prev = encoder[n].angle_prev;
    encoder[n].vel_full_rotations = encoder[n].full_rotations;
    encoder[n].vel_angle_prev_ts = encoder[n].angle_prev_ts;
    return encoder[n].velocity;
}

float encoder_getLastAngle(uint16_t n){
    return (float)encoder[n].full_rotations * _2PI + encoder[n].angle_prev;
}

void encoderUpdate(uint16_t n) {
    float val = encoder_getAngle(n);
    encoder[n].angle_prev_ts = _micros();
    float d_angle = val - encoder[n].angle_prev;
    // if overflow happened track it as full rotation
    if (abs(d_angle) > (0.8f*_2PI) ) encoder[n].full_rotations += ( d_angle > 0 ) ? -1 : 1;
    encoder[n].angle_prev = val;
    
    encoder[n].angle    =LowPassFilterF(&encoder[n].LPF_angle,encoder_getLastAngle(n));
    encoder[n].velocity =LowPassFilterF(&encoder[n].LPF_velocity,encoder_getVelocity(n));
}  
    
// shaft angle calculation
float shaftAngle(uint16_t m) {
    // if no sensor linked return previous value ( for open loop )
    if(mot[m].isEncoder==0) return mot[m].currentPosition;
    m=mot[m].encoderNr;
    return encoder[m].encoderDirection*encoder[m].angle-mot[m].sensorOffset;
}

void setPhaseVoltage(uint16_t m, float Uq, float Ud, float angle_el) {
    int sector;
      // case FOCModulationType::SpaceVectorPWM :
      // Nice video explaining the SpaceVectorModulation (SVPWM) algorithm
      // https://www.youtube.com/watch?v=QMSWUMEAejg

      // the algorithm goes
      // 1) Ualpha, Ubeta
      // 2) Uout = sqrt(Ualpha^2 + Ubeta^2)
      // 3) angle_el = atan2(Ubeta, Ualpha)
      //
      // equivalent to 2)  because the magnitude does not change is:
      // Uout = sqrt(Ud^2 + Uq^2)
      // equivalent to 3) is
      // angle_el = angle_el + atan2(Uq,Ud)

      float Uout;
      // a bit of optitmisation
      if(Ud){ // only if Ud and Uq set
        // _sqrt is an approx of sqrt (3-4% error)
        Uout = _sqrt((Ud*Ud + Uq*Uq)) / mot[m].maxTorque;
        // angle normalisation in between 0 and 2pi
        // only necessary if using _sin and _cos - approximation functions
        angle_el = _normalizeAngle(angle_el + atan2(Uq, Ud));
      }else{// only Uq available - no need for atan2 and sqrt
        Uout = Uq / mot[m].maxTorque;
        // angle normalisation in between 0 and 2pi
        // only necessary if using _sin and _cos - approximation functions
        angle_el = _normalizeAngle(angle_el + _PI_2);
      }
      // find the sector we are in currently
      sector = floor(angle_el / _PI_3) + 1;
      // calculate the duty cycles
      float T1 = _SQRT3*_sin(sector*_PI_3 - angle_el) * Uout;
      float T2 = _SQRT3*_sin(angle_el - (sector-1.0f)*_PI_3) * Uout;
      // two versions possible
      float T0 = 0; // pulled to 0 - better for low power supply voltage
      T0 = 1 - T1 - T2;

      // calculate the duty cycles(times)
      float Ta,Tb,Tc;
      switch(sector){
        case 1:
          Ta = T1 + T2 + T0/2;
          Tb = T2 + T0/2;
          Tc = T0/2;
          break;
        case 2:
          Ta = T1 +  T0/2;
          Tb = T1 + T2 + T0/2;
          Tc = T0/2;
          break;
        case 3:
          Ta = T0/2;
          Tb = T1 + T2 + T0/2;
          Tc = T2 + T0/2;
          break;
        case 4:
          Ta = T0/2;
          Tb = T1+ T0/2;
          Tc = T1 + T2 + T0/2;
          break;
        case 5:
          Ta = T2 + T0/2;
          Tb = T0/2;
          Tc = T1 + T2 + T0/2;
          break;
        case 6:
          Ta = T1 + T2 + T0/2;
          Tb = T0/2;
          Tc = T1 + T0/2;
          break;
        default:
         // possible error state
          Ta = 0;
          Tb = 0;
          Tc = 0;
      }

    float pwmmax=62492/2;//max -10 do 10v *3000+30.000

    mot[m].Ua = (Ta-0.5)*mot[m].maxTorque*pwmmax/10+pwmmax;
    mot[m].Ub = (Tb-0.5)*mot[m].maxTorque*pwmmax/10+pwmmax;
    mot[m].Uc = (Tc-0.5)*mot[m].maxTorque*pwmmax/10+pwmmax;    
    // set the voltages in driver
    PWM_DutyCycleSet(mot[m].gennum1, (uint16_t)mot[m].Ua);
    PWM_DutyCycleSet(mot[m].gennum2, (uint16_t)mot[m].Ub);
    PWM_DutyCycleSet(mot[m].gennum3, (uint16_t)mot[m].Uc); 
}

// Function (iterative) generating open loop movement towards the target angle
// - targetAngle - rad
// it uses mot[m].maxTorque and mot[m].maxVelocity variables
float angleOpenloop(uint16_t m, float targetAngle){
  // get current timestamp
  uint64_t now_us = _micros();
  // calculate the sample time from last call
  float Ts = ((float)now_us - mot[m].openLoopTimeStamp) * 1e-3f;
  Ts=Ts*1e-3f;
  // quick fix for strange cases (micros overflow + timestamp not defined)
  if(Ts <= 0 || Ts > 0.5f) Ts = 1e-3f;

  // calculate the necessary angle to move from current position towards target angle
  // with maximal velocity (mot[m].maxVelocity)
  // TODO sensor precision: this calculation is not numerically precise. The angle can grow to the point
  //                        where small position changes are no longer captured by the precision of floats
  //                        when the total position is large.
  if(_fabs( (targetAngle - mot[m].currentPosition) ) > (mot[m].maxVelocity*Ts)){
    mot[m].currentPosition +=_sign((targetAngle - mot[m].currentPosition)) * ( mot[m].maxVelocity *Ts);
    mot[m].currentVelocity = mot[m].maxVelocity;
  }else{
    mot[m].currentPosition = targetAngle;
    mot[m].currentVelocity = 0;
  }

  // use voltage limit or current limit
  float Uq = mot[m].maxTorque;
  // set the maximal allowed voltage (mot[m].maxTorque) with the necessary angle
  // sensor precision: this calculation is OK due to the normalisation
  setPhaseVoltage(m, Uq,  0, _electricalAngle(_normalizeAngle(mot[m].currentPosition), mot[m].PolePairs));

  // save timestamp for next call
  mot[m].openLoopTimeStamp = now_us;

  return Uq;
}

void encoder_init(uint16_t n){
    encoder_getAngle(n); // call once
    DELAY_microseconds(1);
    encoder[n].vel_angle_prev = encoder_getAngle(n); // call again
    encoder[n].vel_angle_prev_ts = _micros();
    DELAY_milliseconds(1);
    encoder_getAngle(n); // call once
    DELAY_microseconds(1);
    encoder[n].angle_prev = encoder_getAngle(n); // call again
    encoder[n].angle_prev_ts = _micros();
    mot[encoder[n].motorNr].currentPosition=encoder_getAngle(n);
}

float getMechanicalAngle(uint16_t m) {
    return encoder[mot[m].encoderNr].angle_prev;
}

float electricalAngle(uint16_t m){
  // if no sensor linked return previous value ( for open loop )
  if(mot[m].isEncoder==0) return mot[m].electricalPosition;
  return _normalizeAngle( (float)(encoder[mot[m].encoderNr].encoderDirection * mot[m].PolePairs) * getMechanicalAngle(m)  - encoder[mot[m].encoderNr].zeroAngle );
}

// Encoder alignment to electrical 0 angle
int alignSensor(uint16_t m) {
  int exit_flag = 1; //success
  
  encoder_init(mot[m].encoderNr);
  // if unknown natural direction
  if(encoder[mot[m].encoderNr].encoderDirection==0){
    // find natural direction
    for (int i = 0; i <=500; i++ ) {
      float angle = _3PI_2 + _2PI * i / 500.0f;
      setPhaseVoltage(m, mot[m].maxTorque, 0,  angle);
	  encoderUpdate(mot[m].encoderNr);
      Delay(1);
    }
    // take and angle in the middle
    encoderUpdate(mot[m].encoderNr);
    float mid_angle = encoder_getLastAngle(mot[m].encoderNr);
    // move one electrical revolution backwards
    for (int i = 500; i >=0; i-- ) {
      float angle = _3PI_2 + _2PI * i / 500.0f ;
      setPhaseVoltage(m, mot[m].maxTorque, 0,  angle);
	    encoderUpdate(mot[m].encoderNr);
      Delay(1);
    }
    encoderUpdate(mot[m].encoderNr);
    float end_angle = encoder_getLastAngle(mot[m].encoderNr);
    // determine the direction the sensor moved
    if (mid_angle == end_angle) {
      //SIMPLEFOC_DEBUG("MOT: Failed to notice movement");
      return 0; // failed calibration
    } else if (mid_angle < end_angle) {
      //SIMPLEFOC_DEBUG("MOT: mot[m].encoder.encoderDirection==CCW");
      encoder[mot[m].encoderNr].encoderDirection = -1;//Direction::CCW;
    } else{
      //SIMPLEFOC_DEBUG("MOT: mot[m].encoder.encoderDirection==CW");
      encoder[mot[m].encoderNr].encoderDirection = 1;//Direction::CW;
    }
    // check pole pair number
    float moved =  _fabs((mid_angle - end_angle));
    if( _fabs((moved*mot[m].PolePairs - _2PI)) > 0.5f ) { // 0.5f is arbitrary number it can be lower or higher!
      //SIMPLEFOC_DEBUG("MOT: PP check: fail - estimated pp: ", _2PI/moved);
    } else {
      //SIMPLEFOC_DEBUG("MOT: PP check: OK!");
    }

    // zero electric angle not known
    // align the electrical phases of the motor and sensor
    // set angle -90(270 = 3PI/2) degrees
    setPhaseVoltage(m, mot[m].maxTorque, 0,  _3PI_2);
    Delay(800);
    // read the sensor
    encoderUpdate(mot[m].encoderNr);
    // get the current zero electric angle
    encoder[mot[m].encoderNr].zeroAngle = 0;
    encoder[mot[m].encoderNr].zeroAngle = electricalAngle(m);
    Delay(20);
    // stop everything
    setPhaseVoltage(m, 0, 0, 0);
    Delay(100);
  }else {
      //SIMPLEFOC_DEBUG("MOT: Skip offset calib.");
  }
  return exit_flag;
}

// FOC initialization function
int initFOC(uint16_t m) { //CW      = 1,  // clockwise CCW     = -1, // counter clockwise UNKNOWN = 0   // not yet known or invalid state
    int exit_flag = 1;
    mot[m].maxTorque=10;
    if (encoder[mot[m].encoderNr].encoderDirection!=0)
        return 1;
    // align motor if necessary
    // alignment necessary for encoders!

    // sensor and motor alignment - can be skipped
    // by setting mot[m].encoder.encoderDirection and motor.zero_electric_angle

    exit_flag=alignSensor(m);
    // added the mot[m].currentPosition update
    encoderUpdate(mot[m].encoderNr);
    mot[m].currentPosition = shaftAngle(m);
    // aligning the current sensor - can be skipped
    // checks if driver phases are the same as current sense phases
    // and checks the direction of measuremnt.

    if(exit_flag){
        //SIMPLEFOC_DEBUG("MOT: Ready.");
    }else{
        //SIMPLEFOC_DEBUG("MOT: Init FOC failed.");
        //disable();
    }
    return exit_flag;
}

// shaft velocity calculation
float shaftVelocity(uint16_t m) {
  // if no sensor linked return previous value ( for open loop )
  if(mot[m].isEncoder==0) return mot[m].currentVelocity;
  m=mot[m].encoderNr;
  return encoder[m].encoderDirection*encoder[m].velocity;
}

// Function (iterative) generating open loop movement for target velocity
// - target_velocity - rad/s
// it uses mot[m].maxTorque variable
float velocityOpenloop(uint16_t m, float target_velocity){ //OK!
    // get current timestamp
    uint64_t now_us = _micros();
    // calculate the sample time from last call
    float Ts = (now_us - mot[m].openLoopTimeStamp) * 1e-3f;
    Ts=Ts*1e-3f;
    // quick fix for strange cases (micros overflow + timestamp not defined)
    if(Ts <= 0 || Ts > 0.5f) Ts = 1e-3f;
    // calculate the necessary angle to achieve target velocity
    mot[m].currentPosition = _normalizeAngle(mot[m].currentPosition + target_velocity*Ts);
    // for display purposes
    mot[m].currentVelocity = target_velocity;
    // use voltage limit or current limit
    float Uq = mot[m].maxTorque;
    // set the maximal allowed voltage (mot[m].maxTorque) with the necessary angle
    setPhaseVoltage(m, Uq,  0, _electricalAngle(mot[m].currentPosition, mot[m].PolePairs));
    // save timestamp for next call
    mot[m].openLoopTimeStamp = now_us;
    return Uq;
}

// Iterative function looping FOC algorithm, setting Uq on the Motor
// The faster it can be run the better
void loopFOC(uint16_t m) {
    // if open-loop do nothing
    if( mot[m].controller==MCT_angle_openloop || mot[m].controller==MCT_velocity_openloop ) return;
  
    // which is in range 0-2PI
    mot[m].electricalPosition = electricalAngle(m);
    setPhaseVoltage(m, mot[m].voltage.q, mot[m].voltage.d, mot[m].electricalPosition);
}

// - if target is not set it uses motor.target value
void move(uint16_t m, float new_target) {
    static float current_sp; //target current ( q current )
    static float targetVelocity;
    static float aoloop;
  // downsampling (optional)
  //  if(motion_cnt++ < motion_downsample) return;
  //  motion_cnt = 0;

  // shaft angle/velocity need the update() to be called first
  // get shaft angle
  // TODO sensor precision: the mot[m].currentPosition actually stores the complete position, including full rotations, as a float
  //                        For this reason it is NOT precise when the angles become large.
  //                        Additionally, the way LPF works on angle is a precision issue, and the angle-LPF is a problem
  //                        when switching to a 2-component representation.
    if( mot[m].controller!=MCT_angle_openloop && mot[m].controller!=MCT_velocity_openloop ) 
        mot[m].currentPosition = shaftAngle(m); // read value even if motor is disabled to keep the monitoring updated but not in openloop mode
    
    mot[m].currentVelocity = shaftVelocity(m); // read value even if motor is disabled to keep the monitoring updated

    // if disabled do nothing
    if (!mot[m].enabled) return;

    if(_isset(new_target)) mot[m].target = new_target;
  
  // upgrade the current based voltage limit
  switch (mot[m].controller) {      
    case MCT_torque:
        mot[m].voltage.q = mot[m].target;
        mot[m].voltage.q = _constrain(mot[m].voltage.q, -mot[m].maxTorque, mot[m].maxTorque);
        mot[m].voltage.d = 0;
      break;
    case MCT_angle:
      // TODO sensor precision: this calculation is not numerically precise. The target value cannot express precise positions when
      //                        the angles are large. This results in not being able to command small changes at high position values.
      //                        to solve this, the delta-angle has to be calculated in a numerically precise way.
      // angle set point
      // calculate velocity set point    
      targetVelocity = PIDControllerF(&mot[m].P_angle,mot[m].target - mot[m].currentPosition );
      // calculate the torque command - sensor precision: this calculation is ok, but based on bad value from previous calculation
      current_sp = PIDControllerF(&mot[m].PID_velocity,targetVelocity - mot[m].currentVelocity); // if voltage torque control
      // if torque controlled through voltage
        // use voltage if phase-resistance not provided
        mot[m].voltage.q = current_sp;
        mot[m].voltage.d = 0;
      break;
    case MCT_velocity:
      // velocity set point - sensor precision: this calculation is numerically precise.
      targetVelocity = mot[m].target;
      // calculate the torque command     
      current_sp = PIDControllerF(&mot[m].PID_velocity,targetVelocity - mot[m].currentVelocity); // if current/foc_current torque control
      // if torque controlled through voltage control
        // use voltage if phase-resistance not provided
        mot[m].voltage.q = current_sp;
        mot[m].voltage.d = 0;
      break;
    case MCT_velocity_openloop:
      // velocity control in open loop - sensor precision: this calculation is numerically precise.
      targetVelocity = mot[m].target;
      mot[m].voltage.q = velocityOpenloop(m, targetVelocity); // returns the voltage that is set to the motor
      mot[m].voltage.d = 0;
      break;
    case MCT_angle_openloop:
      // angle control in open loop - 
      // TODO sensor precision: this calculation NOT numerically precise, and subject
      //                        to the same problems in small set-point changes at high angles 
      //                        as the closed loop version.

      if (mot[m].PID_velocity.P!=-1)
        mot[m].maxVelocity = _fabs(PIDControllerF(&mot[m].PID_velocity,mot[m].target - mot[m].currentPosition));

      if (mot[m].maxVelocity>10)
          mot[m].maxVelocity=10;
      aoloop=angleOpenloop(m, mot[m].target); // returns the voltage that is set to the motor
     
      if (_fabs(mot[m].voltage.q-aoloop)<0.02) {
        mot[m].lastMotion++;
        if (mot[m].isEncoder==false && (float)mot[m].lastMotion/4.0>mot[m].keepTorqueTime) {
            mot[m].maxTorque=mot[m].idleTorque; 
        }          
      } else {
            mot[m].lastMotion=0;
      }

      mot[m].voltage.q = aoloop;
      mot[m].voltage.d = 0;
      break;
  }
}

void __attribute__ ( ( interrupt, no_auto_psv ) ) _SPI1RXInterrupt () {
    IFS0bits.SPI1RXIF = false;
    return;
}

void motorsInit(){
    for (int i=0;i<2;i++){
        mot[i].mode=0;
        mot[i].PolePairs=11;
        mot[i].keepTorqueTime=2000;
        mot[i].idleTorque=1;
        mot[i].maxVelocity=20;
        mot[i].maxTorque=0;
        mot[i].controller = MCT_angle_openloop;

        // velocity control loop controls the voltage
        mot[i].PID_velocity.P=0.2f;
        mot[i].PID_velocity.I=20.0f;
        mot[i].PID_velocity.D=0.0f;
        mot[i].PID_velocity.output_ramp=1000.0f;
        mot[i].PID_velocity.limit=10.0f;

        mot[i].P_angle.P=10.0f;
        mot[i].P_angle.I=0.0f;
        mot[i].P_angle.D=0.0f;
        mot[i].P_angle.output_ramp=0.0f;
        mot[i].P_angle.limit=10.0f;
    }
    mot[0].gennum1=PWM_GENERATOR_6;
    mot[0].gennum2=PWM_GENERATOR_5;
    mot[0].gennum3=PWM_GENERATOR_3;
    mot[1].gennum1=PWM_GENERATOR_2;
    mot[1].gennum2=PWM_GENERATOR_1;
    mot[1].gennum3=PWM_GENERATOR_4;      
}

typedef struct strfloatToInt16 {
    int16_t H;
    int16_t L;
} floatToInt16;

floatToInt16 FloatToInt16(float v) {
    floatToInt16 fti;
    uint32_t flo;
    memcpy(&flo, &v, 4);
    fti.L = (flo & 0x0000FFFF);
    fti.H = (uint32_t)(flo >> 16);
    return fti;
}

float getFloat(const void *bytes, uint8_t pos) {
    float f1=0;
    uint8_t *f_ptr = (uint8_t *) &f1;
    uint8_t *f_ptr2 = (uint8_t *) bytes;
    f_ptr2+=pos;
    f_ptr[0] = f_ptr2[1];
    f_ptr[1] = f_ptr2[0];
    f_ptr[2] = f_ptr2[3];
    f_ptr[3] = f_ptr2[2];
    return f1;
}

void __attribute__ ((weak)) DMA_Channel0_CallBack(void)
{
    //bcm2835_spi_transfer_one_dma
    //polowa doszla - mozna szykowac odpowiedz
    bool SPIOK = false;
    floatToInt16 ftoi16;
    uint8_t command=DMA_RxBuffer[0]>>8;
    if (DMAINT0bits.HALFIF && DMA_RxBuffer[3]==0xf1) {
        SPIOK=true;
        uint8_t nr=DMA_RxBuffer[0]&0x00FF;
        if (command==1) {//get acc + gyro +temp sensor enable
            LSM6DS3TREnable=DMA_RxBuffer[1];
        } else
        if (command==2) {//get acc + gyro info
            DMA_TxBuffer[1]=data_raw_acceleration[0];
            DMA_TxBuffer[2]=data_raw_acceleration[1];
            DMA_TxBuffer[3]=data_raw_acceleration[2];
            DMA_TxBuffer[4]=data_raw_angular_rate[0];
            DMA_TxBuffer[5]=data_raw_angular_rate[1];
            DMA_TxBuffer[6]=data_raw_angular_rate[2];            
        } else
        if (command==5) {//get temp info
            DMA_TxBuffer[1]=data_raw_temperature;
        } else
        if (command==6) {//read registers from LSM6DS3TR part 1
            I2Caddress=DMA_RxBuffer[1];
            I2Clength=DMA_RxBuffer[2];
            memset(I2C_Buffer, 0x00, 16);
            I2CRead=true;
        } else            
        if (command==7) {//read registers from LSM6DS3TR part 2
            memcpy(DMA_TxBuffer,I2C_Buffer,16);
        } else
        if (command==8) {//write registers to LSM6DS3TR
            I2Caddress=DMA_RxBuffer[1];
            I2Cdata=DMA_RxBuffer[2];
            I2CWrite=true;
        } else                        
        if (command==10) {//set encoders PWM params
            encoder[nr].encoderMinRawAngle=DMA_RxBuffer[1];
            encoder[nr].encoderMaxRawAngle=DMA_RxBuffer[2];
        } else
        if (command==11) {//set encoders enable
            encoder[nr].enabled=DMA_RxBuffer[1];
        } else
        if (command==12) {//get encoder angle
            ftoi16=FloatToInt16(encoder[nr].angle);
            DMA_TxBuffer[1]=ftoi16.L;
            DMA_TxBuffer[2]=ftoi16.H;

            ftoi16=FloatToInt16(encoder[nr].velocity);
            DMA_TxBuffer[3]=ftoi16.L;
            DMA_TxBuffer[4]=ftoi16.H;                
        } else
        if (command==20) { //SetPolePairs
            mot[nr].PolePairs=DMA_RxBuffer[1];
        } else
        if (command==21) { //set IdleTorque
            mot[nr].idleTorque=DMA_RxBuffer[1]/10.0;
            mot[nr].keepTorqueTime=DMA_RxBuffer[2];
        } else
        if (command==25) { //Enable Motor
            mot[nr].enabled=DMA_RxBuffer[1];
            mot[nr].mode=3;
        } else
        if (command==13) { //get ZeroAngle + encoder direction
            if (mot[nr].mode==3) {
                ftoi16=FloatToInt16(encoder[nr].zeroAngle);
            } else {
                ftoi16=FloatToInt16(-999.0f);
            }
            DMA_TxBuffer[1]=ftoi16.L;
            DMA_TxBuffer[2]=ftoi16.H;
            DMA_TxBuffer[3]=encoder[nr].encoderDirection;
        } else
        if (command==60) { //move stop
            if (mot[nr].controller==MCT_velocity) {
                mot[nr].target=0;
            }
            mot[nr].maxTorque=0;// zrobic lepiej dla kazdego trybu?
        } else
        if (command==100) { //info
            uint8_t info=DMA_RxBuffer[1];
            switch (info) {
                case 1:
                    ftoi16=FloatToInt16(mot[nr].electricalPosition);
                    DMA_TxBuffer[0]=ftoi16.L;
                    DMA_TxBuffer[1]=ftoi16.H;
                    ftoi16=FloatToInt16(mot[nr].currentPosition);
                    DMA_TxBuffer[2]=ftoi16.L;
                    DMA_TxBuffer[3]=ftoi16.H;
                break;
                case 2:
                    ftoi16=FloatToInt16(encoder[mot[nr].encoderNr].velocity);
                    DMA_TxBuffer[0]=ftoi16.L;
                    DMA_TxBuffer[1]=ftoi16.H;
                break;
                case 3:
                    ftoi16=FloatToInt16(mot[nr].maxTorque*10);
                    DMA_TxBuffer[0]=ftoi16.L;
                    DMA_TxBuffer[1]=ftoi16.H;
                break;
                
                default:{}
            }
        }

    }
    //set
    if (DMAINT0bits.DONEIF && DMA_RxBuffer[7]==0xf1) {
        SPIOK=true;
        uint8_t nr=DMA_RxBuffer[0]&0x00FF;
        if (command==50) { //Init Foc, set Encoder, zeroangle,
            mot[nr].encoderNr=DMA_RxBuffer[1];
            int16_t direction=DMA_RxBuffer[2];
            if (direction==0) { //initFoc, get anglezero+direction
                mot[nr].mode=1;
                return;
            } else {
                encoder[mot[nr].encoderNr].encoderDirection=direction;
                encoder[mot[nr].encoderNr].zeroAngle=getFloat(DMA_RxBuffer,6);
                encoder[mot[nr].encoderNr].enabled=true;
                mot[nr].maxTorque=0;//mot[nr].idleTorque;
                mot[nr].mode=3;
                mot[nr].isEncoder=true;
                mot[nr].controller=MCT_angle;
            }
        } else
        if (command==14) {//low pas filters
            encoder[nr].LPF_angle.Tf=getFloat(DMA_RxBuffer,4);
            encoder[nr].LPF_velocity.Tf=getFloat(DMA_RxBuffer,8);
        } else
        if (command==26) {//PID Angle1/2
            mot[nr].P_angle.P=getFloat(DMA_RxBuffer,4);
            mot[nr].P_angle.I=getFloat(DMA_RxBuffer,8);
        } else
        if (command==27) {//PID Angle2/2
            mot[nr].P_angle.D=getFloat(DMA_RxBuffer,4);
            mot[nr].P_angle.output_ramp=getFloat(DMA_RxBuffer,8);
        } else                    
        if (command==28) {//PID velocity 1/2
            mot[nr].PID_velocity.P=getFloat(DMA_RxBuffer,4);
            mot[nr].PID_velocity.I=getFloat(DMA_RxBuffer,8);
        } else
        if (command==29) {//PID velocity 2/2
            mot[nr].PID_velocity.D=getFloat(DMA_RxBuffer,4);
            mot[nr].PID_velocity.output_ramp=getFloat(DMA_RxBuffer,8);
        } else                                
        if (command==51 || command==52) { //Move To Angle / Move by Angle
            uint8_t torque=DMA_RxBuffer[1]&0x00FF;            
            float angle=getFloat(DMA_RxBuffer,4);
            float speed=getFloat(DMA_RxBuffer,8);
            
            if (mot[nr].isEncoder)
                mot[nr].controller=MCT_angle;
            else
                mot[nr].controller=MCT_angle_openloop;   

            mot[nr].lastMotion=0;
            mot[nr].maxTorque=(float)torque/10.0f;
            mot[nr].maxVelocity=speed;
            mot[nr].P_angle.limit=speed;
            mot[nr].PID_velocity.limit=10;
            if (mot[nr].maxVelocity<10) 
                mot[nr].PID_velocity.limit=mot[nr].maxVelocity;
            if (mot[nr].isEncoder)
                mot[nr].PID_velocity.limit=mot[nr].maxTorque;
            mot[nr].dir=angle<0?-1.0:1.0;            
            if (command==51)
                mot[nr].target=angle;
            else
                mot[nr].target=mot[nr].currentPosition+ angle;
        } else
        if (command==53) { //Move Continuous Torque
            int8_t direction=DMA_RxBuffer[1]>>8;
            float torque=(float)(DMA_RxBuffer[1]&0x00FF)/10.0f;

            if (mot[nr].isEncoder)
                mot[nr].controller=MCT_torque;
            else
                mot[nr].controller=MCT_velocity_openloop;
                       
            mot[nr].maxTorque=10.0;
            mot[nr].dir=direction;
            mot[nr].target=mot[nr].dir*torque;
        } else
        if (command==54) { //Move Continuous Velocity
            int8_t direction=DMA_RxBuffer[1]>>8;
            float torque=(float)(DMA_RxBuffer[1]&0x00FF)/10.0f;
            float speed=getFloat(DMA_RxBuffer,8);
            
            if (mot[nr].isEncoder)
                mot[nr].controller=MCT_velocity;
            else
                mot[nr].controller=MCT_velocity_openloop;
            
            mot[nr].PID_velocity.limit=torque;
            mot[nr].maxTorque=torque;
            mot[nr].dir=direction;
            mot[nr].target=mot[nr].dir*speed;
        }        
    }
    if (SPIOK==false && DMAINT0bits.DONEIF) {
        //SPI Synchronization if problem
        for (int o=0; o<8; o++){
            DMA_TxBuffer[o]=0;//command;//DMA_RxBuffer[o];
        }
        if (command==127) {
            DMA_TxBuffer[4]=127;
        }
    }
}

int main(void)
{
    //Inicjalizacja peryferiow
    SYSTEM_Initialize();
    
    //Wlaczenie kanalow wyjsiowych drivera A
    IO_RB7_SetHigh(); //EN1
    IO_RC5_SetHigh(); //EN2
    IO_RB5_SetHigh(); //EN3

    //Wlaczenie kanalow wyjsiowych drivera B
    IO_RB13_SetHigh(); //EN1
    IO_RB15_SetHigh(); //EN2
    IO_RB11_SetHigh(); //EN3

    //Uruchomienie driverow (wyjscie z resetu)
    IO_RA1_SetHigh(); //enable driver A
    IO_RA3_SetHigh(); //enable driver A
    
    //Inicjalizacja modulu PWM dopiero po skonfigurowaniu driverow                                                                     
    PWM_Initialize();

    #ifdef SaraKIT
    lsm6ds3tr_i2c_init();  
    #endif

    //Set 2 EncodersPWM range
    for (int i=0;i<2;i++){
        encoder[i].enabled=false;
        encoder[i].encoderMinRawAngle=1;
        encoder[i].encoderMaxRawAngle=45850;
        encoder[i].encoderRawAngle = (float)encoder[i].encoderMaxRawAngle - encoder[i].encoderMinRawAngle;
        encoder[i].min_elapsed_time = 0.000100;
        encoder[i].LPF_velocity.Tf=0.01f;//!<  parameter determining the velocity Low pass filter configuration
        encoder[i].LPF_angle.Tf=0.01f;//!< default velocity filter time constant
        encoder[i].zeroAngle=0;
    }

    //Inicjalizacja glownego przerwania programowego i uruchomienie sygnalow PWM
    //TMR1_Period16BitSet(defaultTimerPeriod);
    
    TMR1_SetInterruptHandler(&timer_interrupt);
    TMR1_Start(); //every 250us
    PWM_Enable();   
    
    SCCP1_TMR_Start(); //every 100us
    motorsInit();
    
    //glowna petla programu interpretujaca dane odczytane po SPI (od RPI)
    while (1) {

        if (I2CRead==true) {
            I2CRead=false;
            uint8_t res;
            res=I2C1_read_bytes(ACC_I2C_ADDRESS,I2Caddress,I2Clength,I2C_Buffer);
            I2C_Buffer[12]=(uint8_t)res;
            I2C_Buffer[13]=255;
        }
        if (I2CWrite==true) {
            I2CWrite=false;
            I2C1_write_bytes(ACC_I2C_ADDRESS,I2Caddress,1,&I2Cdata);
        }

        if (newTmr) {
            newTmr = false;
            #ifdef SaraKIT
            lsm6ds3tr_i2c_check();
            #endif
            for (int m=0;m<2;m++) {
                //init foc?
                if(mot[m].mode==1){ //  1 = start initFOC
                    mot[m].mode=2; //   2 = busy
                    encoder_init(m);
                    encoder[mot[m].encoderNr].encoderDirection=0;
                    encoder[mot[m].encoderNr].zeroAngle=0;

                    mot[m].controller = MCT_angle_openloop;
                    mot[m].maxVelocity=1000;
                    mot[m].isEncoder = true;

                    initFOC(m);
                    mot[m].maxTorque=0;                                                        
                    mot[m].mode=3;//    3 = ready
                }
                //encoder check angle/velocity
                if (encoder[m].enabled) {
                    encoderUpdate(m);
                }
                
                if (mot[m].enabled && (mot[m].mode==3 || encoder[mot[m].encoderNr].enabled==false)) {
                    loopFOC(m);
                    move(m, NOT_SET);
                }
            }
        }            
    }
    return -1;
}
/**
 End of File
*/
