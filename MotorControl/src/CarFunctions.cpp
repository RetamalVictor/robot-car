#include "CarFunctions.h"
#include "DeviceDriverSet.h"
#include "IMPU.h"
#include "MyConfig.h"


MyConfig config;
IMPU& mpu = config.getMPU();

extern DeviceDriverSet_Motor AppMotor;

void carFunctions::initCar()
{
    mpu.Init();
    if (mpu.isCalibrated() == false){
        Serial.println("Calibration starting, set the robot in flat surface");
    mpu.Calibrate();
    delay(2000);
    Serial.println(mpu.isCalibrated());
        mpu.Init();
    } 
    else{
        mpu.Init();
    }
}

void carFunctions::initControl(float& desired_yaw)
{
    mpu.getYaw(desired_yaw);
}

void carFunctions::computePIDControl(uint8_t speed, uint8_t Kp, uint8_t UpperLimit,
                                     float desired_yaw, float& R, float& L)
{
    float yaw;

    // Defining the Yaw to go only forward
    mpu.getYaw(yaw);
    Serial.print("Current Yaw:");
    Serial.println(yaw);

    // Proportional control
    // Right motor speed
    R = (yaw - desired_yaw) * Kp + speed;
    if (R > UpperLimit) {
        R = UpperLimit;
    }
    else if (R < 10)
    {
        R = 10;
    }

    // Left motor speed
    L = (desired_yaw - yaw) * Kp + speed;
    if (L > UpperLimit)
    {
        L = UpperLimit;
    }
    else if (L < 10)
    {
        L = 10;
    }  
}

void carFunctions::movementFunction(MotionControl direction, uint8_t speed, uint8_t Kp,
                                     uint8_t UpperLimit, float desired_yaw)
{
    float R, L;
    if ((direction == Forward) || (direction == Backward)){
    carFunctions::computePIDControl(speed, Kp, UpperLimit, desired_yaw, R, L);
    }
    Serial.print("Right speed: ");
    Serial.println(R);
    Serial.print("Right speed: ");
    Serial.println(L);
    // Serial.print("Desired Yaw:");
    // Serial.println(desired_yaw);
    // Serial.print("Motor R speed:");
    // Serial.println(R);
    // Serial.print("Motor L speed:");
    // Serial.println(L);
    switch (direction)
    {
        case Forward:
            AppMotor.DeviceDriverSet_Motor_control( direction_just, /*speed_A*/ R,
                                                    direction_just, /*speed_B*/ L,  control_enable);
            break;

        case  Backward:
            AppMotor.DeviceDriverSet_Motor_control( direction_back, /*speed_A*/ L,
                                                    direction_back, /*speed_B*/ R,  control_enable);
            break;

        case  Left:
            AppMotor.DeviceDriverSet_Motor_control( direction_just, /*speed_A*/ speed,
                                                    direction_back, /*speed_B*/ speed,  control_enable); 
            break;

        case  Right:
            AppMotor.DeviceDriverSet_Motor_control( direction_back, /*speed_A*/ speed,
                                                    direction_just, /*speed_B*/ speed,  control_enable); 
            break;

        case  LeftForward:
            AppMotor.DeviceDriverSet_Motor_control( direction_just, /*speed_A*/ speed,
                                                    direction_just, /*speed_B*/ speed / 2,  control_enable); 
            break;

        case  LeftBackward:
            AppMotor.DeviceDriverSet_Motor_control( direction_back, /*speed_A*/ speed,
                                                    direction_back, /*speed_B*/ speed / 2,  control_enable); 
            break;

        case  RightForward:
            AppMotor.DeviceDriverSet_Motor_control( direction_just, /*speed_A*/ speed / 2,
                                                    direction_just, /*speed_B*/ speed,  control_enable); 
            break;

        case  RightBackward:
            AppMotor.DeviceDriverSet_Motor_control( direction_back, /*speed_A*/ speed / 2,
                                                    direction_back, /*speed_B*/ speed,  control_enable); 
            break;

        case  stop_it:
            AppMotor.DeviceDriverSet_Motor_control( direction_void, /*speed_A*/ 0,
                                                    direction_void, /*speed_B*/ 0,  control_enable); 
            break;

        default:
            break;
    }
}

