#pragma once
#include <Servo.h>
#include <arduino.h>

class DeviceDriverSet_Motor
{
    public:
    void DeviceDriverSet_Motor_Init(void);
    void DeviceDriverSet_Motor_control(boolean direction_A, uint8_t speed_A,
                                        boolean direction_B, uint8_t speed_B,
                                        boolean controlED
    );

private:
#define PIN_Motor_PWMA 5
#define PIN_Motor_PWMB 6
#define PIN_Motor_BIN_1 8
#define PIN_Motor_AIN_1 7
#define PIN_Motor_STBY 3

public:
#define speed_Max 255
#define direction_just true
#define direction_back false
#define direction_void 3

#define Duration_enable true
#define Duration_disable false
#define control_enable true
#define control_disable false
};

class DeviceDriverSet_Servo
{
public:
    void DeviceDriverSet_Servo_Init(unsigned int positionAngle);
    void DeviceDriverSet_Servo_Control(uint8_t servo, unsigned int positionAngle);
    void DeviceDriverSet_Servo_SControl(Servo servo, unsigned int positionAngle);
private:
#define PIN_Servo_z 10
#define PIN_Servo_y 11
};
