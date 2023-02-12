#pragma once
class IMPU
{
public:
	virtual void Init() = 0;
	virtual void getYawPitchRoll(float& y, float& p, float& r) = 0;
	virtual void getYaw(float& y) = 0;
	
	// Calibration
	virtual void Calibrate() = 0;
	virtual bool isCalibrated() = 0;
	virtual void resetCalibFlag() = 0;
};

