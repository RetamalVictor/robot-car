#pragma once
class IeepromMPU
{
	// Offset getters
public:
	virtual int getXGyroOffset() = 0;
	virtual int getYGyroOffset() = 0;
	virtual int getZGyroOffset() = 0;
	virtual int getXAccelOffset() = 0;
	virtual int getYAccelOffset() = 0;
	virtual int getZAccelOffset() = 0;

	// Offset setter
	virtual void setXGyroOffset(int os) = 0;
	virtual void setYGyroOffset(int os) = 0;
	virtual void setZGyroOffset(int os) = 0;
	virtual void setXAccelOffset(int os) = 0;
	virtual void setYAccelOffset(int os) = 0;
	virtual void setZAccelOffset(int os) = 0;

	// Calibration flag
	virtual bool getCalibFlag() = 0;
	virtual void setCalibFlag() = 0;  //Set the flag to true
	virtual void resetCalibFlag() = 0; //Set the flag to false
};

