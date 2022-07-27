#include "CarFunctions.h"
#include "DeviceDriverSet.h"
#include "IMPU.h"
#include "MyConfig.h"

MyConfig config;
IMPU& mpu = config.getMPU();

extern DeviceDriverSet_Motor AppMotor;

void carFunctions::computePIDControl(MotionControl direction,uint8_t is_speed,
                                uint8_t Kp, uint8_t UpperLimit)
{
    static float yaw_0;
    float yaw;
    uint8_t en = 100;
    unsigned long is_time;
    
}
