#include <Arduino.h>
#include "DeviceDriverSet.h"

/*
Create two servo units and attach them individually
*/

Servo ServoUnit_z;
Servo ServoUnit_y;

void DeviceDriverSet_Servo::DeviceDriverSet_Servo_Init(unsigned int positionAngle)
{
    ServoUnit_z.attach(PIN_Servo_z);
    ServoUnit_y.attach(PIN_Servo_y);
    ServoUnit_z.write(positionAngle); //sets the servo position according to the 90（middle）
    delay(500);
    ServoUnit_y.write(positionAngle); //sets the servo position according to the 90（middle）
    delay(500);


    // ServoUnit_z.attach(PIN_Servo_z, 500, 2400); //500: 0 degree  2400: 180 degree
    // ServoUnit_z.attach(PIN_Servo_z);
    // ServoUnit_z.detach();

    // ServoUnit_y.attach(PIN_Servo_y, 500, 2400); //500: 0 degree  2400: 180 degree
    // ServoUnit_y.attach(PIN_Servo_y);
    // ServoUnit_y.detach();
}

void DeviceDriverSet_Servo::DeviceDriverSet_Servo_Control(uint8_t servo, unsigned int positionAngle)
{
    if (servo == 1) //Servo_z
    {
    ServoUnit_z.write(10 * positionAngle);
    // delay(500);
    }
    else if (servo == 2) //Servo_y
    {
    ServoUnit_y.write(positionAngle);
    // delay(500);
    }
    
}

void DeviceDriverSet_Servo::DeviceDriverSet_Servo_SControl(Servo servo, unsigned int positionAngle)
{
    servo.write(positionAngle);
}

