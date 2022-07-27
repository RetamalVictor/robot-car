#pragma once
#include "IMPU.h"
#include "IeepromMPU.h"

class WMPU: public IMPU
{
public:
	WMPU(IeepromMPU& ieepromMPU);
	// Inherited via IMPU
	virtual void Init() override;
	virtual void getYawPitchRoll(float& y, float& p, float& r) override;
	virtual void Calibrate() override;
	virtual bool isCalibrated() override;
	virtual void resetCalibFlag() override;

private:
	IeepromMPU& eepromMngr;
	void guessOffsets();
	void loadCalibration();
	int begin();

};

