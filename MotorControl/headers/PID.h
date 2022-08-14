#pragma once

typedef struct {

    // Gains    
    float Kp, Ki, Kd;

    // Derivate pass filter
    float tau;

    // Output limits
    float limMin, limMax;

    // Sample time in seconds
    float T;

    // Controller memory
    float integrator, differentiator;
    float prevError, prevMeasurement;

    // Controller output
    float out;

} PIDController;

void PIDControllerInit(PIDController *pid);
float PIDControllerUpdate(PIDController *pid, float reference, float measurement);
