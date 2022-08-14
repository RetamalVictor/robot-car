#include "PID.h"


void PIDControllerInit(PIDController *pid)
{
    // Cleaning Variables
    pid->integrator = 0.0f;
    pid->prevError = 0.0f;
    
    pid->differentiator = 0.0f;
    pid->prevMeasurement = 0.0f;

    pid->out = 0.0f;
}

float PIDControllerUpdate(PIDController *pid, float reference, float measurement)
{
    // Error signal
    float error = reference -  measurement;

    // Proportional
    float proportional = pid->Kp * error;

    // Integral
    pid->integrator = pid->integrator + 0.5f * pid->Ki * pid->T * (error + pid->prevError);

    // Anti-wind-up via Dynamic integrator clamping
    float limMinInt, limMaxInt;

    // Computing integrator limits
    if (pid->limMax > proportional) {
        limMaxInt = pid->limMax - proportional;
    } else{
        limMaxInt=0.0f;
    }

    if (pid->limMin < proportional) {
        limMinInt = pid->limMin - proportional;
    } else {
        limMinInt=0.0f;
    }

    // Clamp integrator
    if(pid->integrator > limMaxInt) {
        pid->integrator = limMaxInt;
    } else if (pid->integrator < limMinInt) {
        pid->integrator = limMinInt;
    }

    // Derivative (band-limited differentiator)
    pid->differentiator = (0.2f * pid->Kd * (measurement - pid->prevMeasurement)
                        + (0.2f * pid->tau - pid->T) * pid->differentiator)
                        / (0.2f * pid->tau + pid->T);

    // Compute output
    pid->out = proportional + pid->integrator + pid->differentiator;

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
