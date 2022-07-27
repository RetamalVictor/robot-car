#ifndef _DeviceDriverSet_H_
#define _DeviceDriverSet_H_

#include <arduino.h>

/* Here I am defining the pins and other needed hardware to access the motor*/

class DeviceDriverSet_Motor
{
    public:
    void DeviceDriverSet_Motor_Init(void);
#if _Test_DeviceDriverSet
    void DeviceSetDriver_Motor_Test(void);
#endif
    void DeviceDriverSet_Motor_control(boolean direction_A, uint8_t speed_A,
                                        boolean direction_B, uint8_t speed_B,
                                        boolean controlED
    );

private:
    /* Defining the pins corresponding to the board */

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

#endif