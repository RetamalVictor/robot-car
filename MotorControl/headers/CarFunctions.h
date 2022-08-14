#pragma once
#include <stdint.h>

class carFunctions
{
public:
    enum MotionControl{

        Forward,       //(1)
        Backward,      //(2)
        Left,          //(3)
        Right,         //(4)
        LeftForward,   //(5)
        LeftBackward,  //(6)
        RightForward,  //(7)
        RightBackward, //(8)
        stop_it        //(9)
    };
    void initCar();
    void initControl(float& desired_yaw);
    void computePIDControl(uint8_t speed, uint8_t Kp, uint8_t UpperLimit, float desired_yaw, float& R, float& L);
    void movementFunction(MotionControl direction, uint8_t speed, uint8_t Kp, uint8_t UpperLimit, float desired_yaw);
};
