#include "PID.h"
#include <stdlib.h> 

void PIDControllerInit(PIDController *pid)
{
    // Cleaning Variables
    pid->integrator = 0.0f;
    pid->prevError = 0.0f;
    
    pid->differentiator = 0.0f;
    pid->prevMeasurement = 0.0f;

    pid->out = 0.0f;
}

float PIDControllerUpdate(PIDController *pid, float reference, float measurement, uint8_t speed)
{
    // Error signal
    float error = reference -  measurement;

    // Proportional
    float proportional = pid->Kp * error;

    // Integral
    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

    // Anti-wind-up via Dynamic integrator clamping
    if (pid->integrator > pid->limMaxInt) {
        pid->integrator = pid->limMaxInt;
    } else if (pid->integrator < pid->limMinInt) {
        pid->integrator = pid->limMinInt;
    }

    // Clamp integrator
    if(pid->integrator > pid->limMaxInt) {
        pid->integrator = pid->limMaxInt;
    } else if (pid->integrator < pid->limMinInt) {
        pid->integrator = pid->limMinInt;
    }

    // Derivative (band-limited differentiator)
    // pid->differentiator = -(0.2f * pid->Kd * (measurement - pid->prevMeasurement)
    //                     + (0.2f * pid->tau - pid->T) * pid->differentiator)
    //                     / (0.2f * pid->tau + pid->T);

    // Compute output
    pid->out = proportional + pid->integrator + speed;

    if(pid->out > pid->limMax) {
        pid->out = pid->limMax;
    } else if(pid->out < pid->limMin) {
        pid->out = pid->limMin;
    }

    // Store error and measurement
    pid->prevError          = error;
    pid->prevMeasurement    = measurement;

    return pid->out;
}
