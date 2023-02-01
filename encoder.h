#ifndef ENCODER_C_H
#define ENCODER_C_H

#ifdef __cplusplus
extern "C" {
#endif
/* Private variables ---------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdint.h> 

typedef struct LowPassFilter
{
    float Tf; //!< Low pass filter time constant
    uint64_t timestamp_prev;  //!< Last execution timestamp
    float y_prev; //!< filtered value in previous execution step 
} lowPassFilter;  

// velocity calculation variables
struct Encoder {
    bool enabled;
    volatile float angle;
    volatile float velocity;
    struct LowPassFilter LPF_velocity;
    struct LowPassFilter LPF_angle;
    int8_t encoderDirection;//!< if encoderDirection == Direction::CCW then direction will be flipped to CW 0 (auto) or 1 or -1    
    float angle_prev; // result of last call to getSensorAngle(), used for full rotations and velocity
    uint64_t angle_prev_ts; // timestamp of last call to getAngle, used for velocity
    float vel_angle_prev; // angle at last call to getVelocity, used for velocity
    uint64_t vel_angle_prev_ts; // last velocity calculation timestamp
    int32_t full_rotations; // full rotation tracking
    int32_t vel_full_rotations; // previous full rotation value for velocity calculation
    uint16_t encoderMinRawAngle;//
    uint16_t encoderMaxRawAngle;//    
    float encoderRawAngle;
    float min_elapsed_time;;
    volatile float zeroAngle;
};
  
float encoder_getAngle(uint16_t n);
float encoder_getVelocity(uint16_t n);
float encoder_getLastAngle(uint16_t n);
void encoderUpdate(uint16_t n);

#ifdef __cplusplus
}
#endif

#endif /* ENCODER_C_H */

