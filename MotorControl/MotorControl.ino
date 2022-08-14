#include <Arduino.h>
#include <avr/wdt.h>
#include "src/CarFunctions.h"

carFunctions functionSet;
float desiredYaw;
uint8_t Kp, UpperLimit, speed;
// the setup function runs once when you press reset or power the board
void setup() 
{
    speed = 100;
    Kp = 10;
    UpperLimit = 255;

    Serial.begin(9600);
    while(!Serial);
    
    functionSet.initCar();
    delay(6000);
    Serial.println("Initializing controller");
    functionSet.initControl(desiredYaw);

}

// the loop function runs over and over again until power down or reset
void loop() 
{
    functionSet.movementFunction(functionSet.Forward,speed, Kp, UpperLimit, desiredYaw);
    delay(2000);
}
