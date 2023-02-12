#include "IMPU.h"
#include "CarFunctions.h"
#include "DeviceDriverSet.h"
#include "MyConfig.h"
#include "ControllerParams.h"
#include "PID.h"

PIDController RightControl = { PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN, PID_LIM_MAX,
            PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S };

PIDController LeftControl = { PID_KP, PID_KI, PID_KD,
                        PID_TAU,
                        PID_LIM_MIN, PID_LIM_MAX,
            PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                        SAMPLE_TIME_S };


MyConfig config;
IMPU& mpu = config.getMPU();

DeviceDriverSet_Motor AppMotor;
DeviceDriverSet_Servo AppServo;

void carFunctions::initSerial()
{
    Serial.begin(9600);
}

void carFunctions::initServo(unsigned int positionAngle)
{
    AppServo.DeviceDriverSet_Servo_Init(positionAngle);
}

void carFunctions::moveServo(uint8_t setServo, unsigned int positionAngle)

{
    /* 
    Servo -- y == 2
    Servo -- Z == 1
    */
    AppServo.DeviceDriverSet_Servo_Control(/*uint8_t Servo--y*/ setServo, /*unsigned int Position_angle*/ positionAngle);

}
void carFunctions::servoTestFunction(uint8_t setServo)
{
    static int z_angle = 9;
    static int y_angle = 9;
    uint8_t temp_setServo = setServo;
    switch (temp_setServo)
    {
    case 1 ... 2:
    {
        if (1 == temp_setServo) {
        y_angle -= 1;
        }else if (2 == temp_setServo){
        y_angle += 1;
        }

        if (y_angle <= 5){
        y_angle = 5;
        }

        if (y_angle >= 11){
        y_angle = 11;
        }
        AppServo.DeviceDriverSet_Servo_Control(/*uint8_t Servo--y*/ 2, /*unsigned int Position_angle*/ y_angle);
    }
    break;

    case 3 ... 4:
    {
        if (3 == temp_setServo){
        z_angle += 1;
        } else if (4 == temp_setServo) {
        z_angle -= 1;
        }

        if (z_angle <= 1){
        z_angle = 1;
        }

        if (z_angle >= 17){
        z_angle = 17;
        }
        
        AppServo.DeviceDriverSet_Servo_Control(/*uint8_t Servo--z*/ 1, /*unsigned int Position_angle*/ z_angle);
    }
    break;
    case 5:
        AppServo.DeviceDriverSet_Servo_Control(/*uint8_t Servo--y*/ 2, /*unsigned int Position_angle*/ 9);
        AppServo.DeviceDriverSet_Servo_Control(/*uint8_t Servo--z*/ 1, /*unsigned int Position_angle*/ 9);
        break;
    default:
        break;
    }
}

void carFunctions::initCarMPU()
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
    PIDControllerInit(&RightControl);
    PIDControllerInit(&LeftControl);
    mpu.getYaw(desired_yaw);
}


void carFunctions::computePropControl(uint8_t speed, uint8_t Kp, uint8_t UpperLimit,
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


void carFunctions::computePIDControl(uint8_t speed, float desired_yaw, uint8_t UpperLimit, float& R, float& L)
{
    float yaw;
    mpu.getYaw(yaw);
    // Serial.print("Yaw: ");
    // Serial.println(yaw);

    PIDControllerUpdate(&RightControl,desired_yaw, yaw, speed);
    PIDControllerUpdate(&LeftControl, yaw, desired_yaw, speed);

    R = RightControl.out;
    L = LeftControl.out;
 
}


void carFunctions::movementFunction(MotionControl direction, uint8_t speed, uint8_t Kp,
                                     uint8_t UpperLimit, float desired_yaw)
{
    float R, L;
    if ((direction == Forward) || (direction == Backward)){
    carFunctions::computePropControl(speed, Kp, UpperLimit, desired_yaw, R, L);
    // carFunctions::computePIDControl(speed, desired_yaw, UpperLimit, R, L);
    }
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

