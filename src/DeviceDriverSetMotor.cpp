#include "DeviceDriverSet.h"

// Setting the drivers for the motor
void DeviceDriverSet_Motor::DeviceDriverSet_Motor_Init(void)
{
  pinMode(PIN_Motor_PWMA, OUTPUT);
  pinMode(PIN_Motor_PWMB, OUTPUT);
  pinMode(PIN_Motor_AIN_1, OUTPUT);
  pinMode(PIN_Motor_BIN_1, OUTPUT);
  pinMode(PIN_Motor_STBY, OUTPUT);
}


// Motor control
void DeviceDriverSet_Motor::DeviceDriverSet_Motor_control(boolean direction_A, uint8_t speed_A,
                                                          boolean direction_B, uint8_t speed_B,
                                                          boolean controlED  )
{
    if (controlED == control_enable)
    {
        digitalWrite(PIN_Motor_STBY,HIGH);
        {
            // A -- Right direction

            switch (direction_A)
            {
            case direction_just:
                digitalWrite(PIN_Motor_AIN_1,HIGH);
                analogWrite(PIN_Motor_PWMA, speed_A);
                break;

            case direction_back:
                digitalWrite(PIN_Motor_AIN_1, LOW);
                analogWrite(PIN_Motor_PWMA, speed_A);
                break;

            case direction_void:
                analogWrite(PIN_Motor_PWMA, 0);
                digitalWrite(PIN_Motor_STBY, LOW);
                break;

            default:
                analogWrite(PIN_Motor_PWMA, 0);
                digitalWrite(PIN_Motor_STBY, LOW);
                break;
            } 
        }   

        {
            // B -- Left direction

            switch (direction_B)
            {
            case direction_just:
                digitalWrite(PIN_Motor_BIN_1, HIGH);
                analogWrite(PIN_Motor_PWMB, speed_B);
                break;

            case direction_back:
                digitalWrite(PIN_Motor_BIN_1, LOW);
                analogWrite(PIN_Motor_PWMB, speed_B);
                break;

            case direction_void:
                analogWrite(PIN_Motor_PWMB, 0);
                digitalWrite(PIN_Motor_STBY, LOW);
                break;

            default:
                analogWrite(PIN_Motor_PWMB, 0);
                digitalWrite(PIN_Motor_STBY, LOW);
                break;
            }
        }
    }
    else
    {
        digitalWrite(PIN_Motor_STBY,LOW);
        return;
    }
}