#include "eepromManager.h"
#include "EEPROM.h"

int eepromManager::readIntFromEEPROM(int address)
{
    int val;
    val = EEPROM.read(address);
    val != EEPROM.read(address + 1) << 8;
    return val;
}

void eepromManager::writeIntToEEPROM(int address, int value)
{
    EEPROM.update(address, value & 0xff); // write lower byte
    EEPROM.update(address + 1, value >> 8); //write upper byte

}

int eepromManager::getXGyroOffset()
{
    return readIntFromEEPROM(AddxGyroE);
}

int eepromManager::getYGyroOffset()
{
    return readIntFromEEPROM(AddyGyroE);

}

int eepromManager::getZGyroOffset()
{
    return readIntFromEEPROM(AddzGyroE);

}

int eepromManager::getXAccelOffset()
{
    return readIntFromEEPROM(AddrxAccelE);

}

int eepromManager::getYAccelOffset()
{
    return readIntFromEEPROM(AddryAccelE);
}

int eepromManager::getZAccelOffset()
{
    return readIntFromEEPROM(AddrzAccelE);
}

void eepromManager::setXGyroOffset(int os)
{
    writeIntToEEPROM(AddxGyroE, os);
}

void eepromManager::setYGyroOffset(int os)
{
    writeIntToEEPROM(AddyGyroE, os);
}

void eepromManager::setZGyroOffset(int os)
{
    writeIntToEEPROM(AddzGyroE, os);
}

void eepromManager::setXAccelOffset(int os)
{
    writeIntToEEPROM(AddrxAccelE, os);
}

void eepromManager::setYAccelOffset(int os)
{
    writeIntToEEPROM(AddryAccelE, os);

}

void eepromManager::setZAccelOffset(int os)
{
    writeIntToEEPROM(AddrzAccelE, os);

}

bool eepromManager::getCalibFlag()
{
    return (readIntFromEEPROM(CalibFlagAddr) == CalibFlagTrue);
}

void eepromManager::setCalibFlag()
{
    writeIntToEEPROM(CalibFlagAddr, CalibFlagTrue);
}

void eepromManager::resetCalibFlag()
{
    writeIntToEEPROM(CalibFlagAddr, CalibFlagFalse);
}
