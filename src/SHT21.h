#include <Arduino.h>
#include "Byte.h"
#include "TM1638.h"
#include <i2c_t3.h>

class SHT21
{
public:
    SHT21(i2c_t3 i2cbus);

    void update();

    ~SHT21();

private:
    //Pin settings
    int lKDataIO;
    int lKClock;
    int lKStrobe;
    bool sSegOn;

    //Commands
    BYTE sSOn = 0b10001111; //
    BYTE sSOff = 0b10000111;
    BYTE setWriteMode = 0b01000000;
    BYTE setGetButtonData = 0b01000010;

    //Data Presets and stores
    BYTE fullData;
    BYTE emptyData;
    BYTE digit[8];
    BYTE led;

    int initArduino();
};