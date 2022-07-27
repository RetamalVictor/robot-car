#pragma once

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
    void computePIDControl(MotionControl direction, uint8_t is_speed,
                                uint8_t Kp, uint8_t UpperLimit);
    void movementFunction(MotionControl direction, uint8_t is_speed);
                       
};
