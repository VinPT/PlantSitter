#include <Arduino.h>

#include <bitset>

typedef std::bitset<8> BYTE;

class TM1638
{
public:
    TM1638(int data, int clock, int strobe);
    void update();
    void setdigit(int data, int digit);
    void setled(bool on, int number);
    void sSegTurnOn();
    void sSegTurnOn(int brightness); //brightness not implemented yet

    void sSegTurnOff();
    void sendInstruction(BYTE instruction);
    void sendData(BYTE instruction);
    BYTE getButtonData();
    BYTE sSNumber(unsigned int number);
    ~TM1638();

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
