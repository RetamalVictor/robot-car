#include "IMPU.h"
#include "SampleConfig.h"

SampleConfig config;
IMPU& mpu = config.getMPU();

void setup() {
  Serial.begin(9600);
  while (!Serial);
  mpu.Calibrate();
  }

void loop() {
  // put your main code here, to run repeatedly:

}
