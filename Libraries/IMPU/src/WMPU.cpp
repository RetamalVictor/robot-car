#include <math.h>
#include "WMPU.h"
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

namespace nsMPU {
    MPU6050 mpu;
}
 
WMPU::WMPU(IeepromMPU& ieepromMPU)
    :eepromMngr(ieepromMPU)
{
}

int WMPU::begin()
{
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin();
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    nsMPU::mpu.initialize();
    nsMPU::mpu.testConnection();
    uint8_t  devStatus;  // return status after each device operation (0 = success, !0 = error)
    devStatus = nsMPU::mpu.dmpInitialize();
    guessOffsets();
    return devStatus;
}


void WMPU::Init()
{
    uint8_t devStatus = begin();

    if (devStatus == 0) {
        if (isCalibrated()) {
            loadCalibration();
            nsMPU::mpu.setDMPEnabled(true);
        }
        else {
            Serial.println("MPU not calibrated. Halting execution.");
            while (true) {
                //failure: no calibration
            }
        }
    }
    else {
        Serial.println("Bad devStatus. Halting execution.");
        while (true) {
            //failure
        }
    }
}

void WMPU::getYawPitchRoll(float& y, float& p, float& r)
{
    uint8_t fifoBuffer[64]; // FIFO storage buffer
    Quaternion q;           // [w, x, y, z]         quaternion container
    if (nsMPU::mpu.dmpGetCurrentFIFOPacket(fifoBuffer)) { // Get the Latest packet 
        nsMPU::mpu.dmpGetQuaternion(&q, fifoBuffer);

        // Info extraction from quaternion
        float q0 = q.w;
        float q1 = q.x;
        float q2 = q.y;
        float q3 = q.z;

        // Yaw, pitch, roll calculation
        float yr = -atan2(-2 * q1 * q2 + 2 * q0 * q3, q2 * q2 - q3 * q3 - q1 * q1 + q0 * q0);
        float pr = asin(2 * q2 * q3 + 2 * q0 * q1);
        float rr = atan2(-2 * q1 * q3 + 2 * q0 * q2, q3 * q3 - q2 * q2 - q1 * q1 + q0 * q0);

        // Conversion to Degrees
        y = yr * 180 / M_PI;
        p = pr * 180 / M_PI;
        r = rr * 180 / M_PI;

    }

}

void WMPU::guessOffsets() 
{
    // supply your own gyro offsets here, scaled for min sensitivity
    nsMPU::mpu.setXGyroOffset(220);
    nsMPU::mpu.setYGyroOffset(76);
    nsMPU::mpu.setZGyroOffset(-85);
    nsMPU::mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
}

void WMPU::loadCalibration()
{
    nsMPU::mpu.setXGyroOffset(eepromMngr.getXGyroOffset());
    nsMPU::mpu.setYGyroOffset(eepromMngr.getYGyroOffset());
    nsMPU::mpu.setZGyroOffset(eepromMngr.getZGyroOffset());


    nsMPU::mpu.setXAccelOffset(eepromMngr.getXAccelOffset());
    nsMPU::mpu.setYAccelOffset(eepromMngr.getYAccelOffset());
    nsMPU::mpu.setZAccelOffset(eepromMngr.getZAccelOffset());

}


void WMPU::Calibrate()
{
    Serial.println("Tank should be still and flat!");

    uint8_t devStatus = begin();

    if (devStatus == 0) {
        // Performing calibration and setting obtained offsets
        // as active offsets (The ones DMP will use to generate quaternion)
        nsMPU::mpu.CalibrateAccel(6);
        nsMPU::mpu.CalibrateGyro(6); 

        // Getting the offsets and saving them in EEPROM
        eepromMngr.setXGyroOffset(nsMPU::mpu.getXGyroOffset());
        eepromMngr.setYGyroOffset(nsMPU::mpu.getYGyroOffset());
        eepromMngr.setZGyroOffset(nsMPU::mpu.getZGyroOffset());

        eepromMngr.setXAccelOffset(nsMPU::mpu.getXAccelOffset());
        eepromMngr.setYAccelOffset(nsMPU::mpu.getYAccelOffset());
        eepromMngr.setZAccelOffset(nsMPU::mpu.getZAccelOffset());

        // Set the flag to calibrated
        eepromMngr.setCalibFlag();
        Serial.print("Calibration flag is set to: ");
        Serial.println(eepromMngr.getCalibFlag());
        Serial.println("Calibration Completed");

    }
    else {
        Serial.println("Bad devStatus. Halting execution.");
        while (true) {
            //failure
        }
    }
}

bool WMPU::isCalibrated()
{
    return eepromMngr.getCalibFlag();
}

void WMPU::resetCalibFlag()
{
    eepromMngr.resetCalibFlag();
    Serial.println("Reset completed");
}
