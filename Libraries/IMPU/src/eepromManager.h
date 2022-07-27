#pragma once
#include "IeepromMPU.h"

class eepromManager : public IeepromMPU
{
	enum OffsetAddr{
		/* Each location in the EEPROM is 1 byte.
			We dont want the addres to overlap*/
		AddxGyroE = 2,
		AddyGyroE = 4,
		AddzGyroE = 6,
		AddrxAccelE = 8,
		AddryAccelE = 10,
		AddrzAccelE = 12
	};

	const int CalibFlagAddr = 0;
	const int CalibFlagTrue = 77;
	const int CalibFlagFalse = 0;

	int readIntFromEEPROM(int address);
	void writeIntToEEPROM(int address, int value);

	// Inherited via IeepromMPU
	virtual int getXGyroOffset() override;
	virtual int getYGyroOffset() override;
	virtual int getZGyroOffset() override;
	virtual int getXAccelOffset() override;
	virtual int getYAccelOffset() override;
	virtual int getZAccelOffset() override;

	virtual void setXGyroOffset(int os) override;
	virtual void setYGyroOffset(int os) override;
	virtual void setZGyroOffset(int os) override;
	virtual void setXAccelOffset(int os) override;
	virtual void setYAccelOffset(int os) override;
	virtual void setZAccelOffset(int os) override;

	virtual bool getCalibFlag() override;
	virtual void setCalibFlag() override;
	virtual void resetCalibFlag() override;

};

