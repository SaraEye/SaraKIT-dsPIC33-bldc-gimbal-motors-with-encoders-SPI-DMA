#include "LSM6DS3TR.h"

#include <string.h>
#include <stdio.h>
#include <stdint.h>

#define _2PI 6.28318530718f

struct Encoder encoder[2];

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
}  

