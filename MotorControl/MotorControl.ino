#include "IMPU.h"
#include "src/MyConfig.h"
#include <avr/wdt.h>
// #include "src/DeviceDriverSet.h"
// #include "src/AppFunctionSet.cpp"

MyConfig config;
IMPU& mpu = config.getMPU();
// DeviceDriverSet_Motor AppMotor;
// Application_xxx  FunctionSetMotor;

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    while(!Serial);
    // if (mpu.isCalibrated() == false){
    //     Serial.println("Calibration starting, set the robot in flat surface");
    // mpu.Calibrate();
    // delay(2000);
    // Serial.println(mpu.isCalibrated());
    mpu.Init();
    //     mpu.Init();
    // } 
    // else{
    //     mpu.Init();
    // }
}

// the loop function runs over and over again until power down or reset
void loop() {

    float y, p, r;

	mpu.getYawPitchRoll(y, p, r);
	Serial.print(y);
	Serial.print("\t");
	Serial.print(p);
	Serial.print("\t");
	Serial.println(r);  
    delay(2000);
}
