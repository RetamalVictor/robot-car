#include <Arduino.h>
#include <avr/wdt.h>
#include "CarFunctions.h"
// #include "PID.h"

/*--------------- Motor & Direction Functionality Test ---------------*/
carFunctions functionSet;
// float desiredYaw;
// uint8_t Kp, UpperLimit, speed;

void setup() 
{
    functionSet.initServo(0);
    functionSet.moveServo(1,0);
    delay(1000);
    functionSet.moveServo(1,90);
    delay(1000);
    functionSet.moveServo(1,180);
    delay(1000);

    functionSet.moveServo(2,0);
    delay(1000);
    functionSet.moveServo(2,90);
    delay(1000);
    functionSet.moveServo(2,180);
    delay(1000);
    functionSet.moveServo(1,0);
    functionSet.moveServo(2,0);

    // functionSet.moveServo(2,120);
    // delay(500);
    // functionSet.moveServo(2,50);
    // int pos= 0;
    // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    //     // in steps of 1 degree
    //     functionSet.moveServo(1, pos);              // tell servo to go to position in variable 'pos'
    //     delay(15);                       // waits 15ms for the servo to reach the position
    // }
    // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    //     functionSet.moveServo(1, pos);              // tell servo to go to position in variable 'pos'
    //     delay(15);                       // waits 15ms for the servo to reach the position
    // }
    /*--------------- Motor & Direction Functionality Test ---------------*/
    // speed = 150;
    // Kp = 10;
    // UpperLimit = 255;

    // Serial.begin(9600);
    // while(!Serial);

    // functionSet.initCar();
    // delay(6000);
    // Serial.println("Initializing controller");
    // functionSet.initControl(desiredYaw);
    // delay(1000);

}

void loop() 
{   
    // functionSet.moveServo(1,90);
    // delay(1000);
    // delay(1000);
    // functionSet.moveServo(1,0);

    /*--------------- Motor & Direction Functionality Test ---------------*/
    // float R,L;
    // Serial.print("Desired Yaw: ");
    // Serial.println(desiredYaw);
    // functionSet.computePIDControl(120, desiredYaw, UpperLimit, R, L);
    // Serial.print("Right speed: ");
    // Serial.println(R);
    // Serial.print("Left speed: ");
    // Serial.println(L);
    // delay(100);
    // functionSet.initControl(desiredYaw);   
    // for (int i = 0; i < 1000; i++)
    // {
    //     functionSet.movementFunction(functionSet.Forward,speed, Kp, UpperLimit, desiredYaw);
    //     delay(200);
    // }
}
