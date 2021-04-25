#include "TM1638.h"

TM1638::TM1638(int data, int clock, int strobe)
{
    lKDataIO = data;
    lKClock = clock;
    lKStrobe = strobe;

    sSegOn = false;
    //set instructions
    sSOn = 0b10001111; //
    sSOff = 0b10000111;
    setWriteMode = 0b01000000;

    //set data presets
    fullData = 0b11111111;
    emptyData = 0b00000000;

    led = fullData;

    initArduino();
}

int TM1638::initArduino()
{

    pinMode(lKDataIO, OUTPUT);
    pinMode(lKClock, OUTPUT);
    pinMode(lKStrobe, OUTPUT);

    digitalWrite(lKDataIO, HIGH);
    digitalWrite(lKClock, HIGH);
    digitalWrite(lKStrobe, HIGH);

    return 0;
}

//update seven seg and led data <-- might split too two update functions
void TM1638::update()
{
    //if (!sSegOn)
    sSegTurnOn();

    sendInstruction(setWriteMode);
    //16 needed as one byte is led next is seven seg for total of eight each
    for (int i = 0; 16 > i; i++)
    {
        int select = (int)i / 2;

        if (i % 2 == 1)
        { //led update on odd
            sendData(led[select] ? emptyData : fullData);
        }
        else
        { //seven seg update on even
            sendData(digit[select]);
        }
    }
}

void TM1638::setdigit(int data, int djit)
{                                 //miss spelled digit to avoid same variable name
    digit[djit] = sSNumber(data); // need to add checks and return success or fail
}

void TM1638::setled(bool on, int number)
{
    led[number] = on;
}

void TM1638::sSegTurnOn()
{
    if (!sSegOn)
    {
        sendInstruction(sSOn);
        sSegOn = true;
    }
}
void TM1638::sSegTurnOff()
{
    if (sSegOn)
    {
        sendInstruction(sSOff);
        sSegOn = false;
    }
}

void TM1638::sendInstruction(BYTE instruction)
{

    digitalWrite(lKStrobe, HIGH);
    digitalWrite(lKStrobe, LOW);

    sendData(instruction);
}

void TM1638::sendData(BYTE instruction)
{

    for (int i = 0; 8 > i; i++)
    {
        digitalWrite(lKClock, LOW);
        digitalWrite(lKDataIO, instruction[i]);
        digitalWrite(lKClock, HIGH);
    }
}

BYTE TM1638::getButtonData()
{
    BYTE buttonData;
    //setup
    sendInstruction(setGetButtonData);
    pinMode(lKDataIO, INPUT);

    //Read
    for (int i = 0; 4 > i; i++)
    {
        for (int j = 0; 8 > j; j++)
        {
            digitalWrite(lKClock, LOW);
            digitalWrite(lKClock, HIGH);
            if (0 == j % 4)
            {
                buttonData[(i + ((j == 4) ? 4 : 0))] = digitalRead(lKDataIO);
            }
        }
    }

    //cleanup
    pinMode(lKDataIO, OUTPUT);

    return buttonData;
}

BYTE TM1638::sSNumber(unsigned int number)
{
    //check value less than 10

    BYTE result;
    switch (number)
    {
    case 0:
        result = 0b00111111;
        break;
    case 1:
        result = 0b00000110;
        break;
    case 2:
        result = 0b01011011;
        break;
    case 3:
        result = 0b01001111;
        break;
    case 4:
        result = 0b01100110;
        break;
    case 5:
        result = 0b01101101;
        break;
    case 6:
        result = 0b01111101;
        break;
    case 7:
        result = 0b00000111;
        break;
    case 8:
        result = 0b01111111;
        break;
    case 9:
        result = 0b01100111;
        break;

    default:
        result = 0b00000000;
    }
    return result;
}

//destructor empty as there is nothing to destroy
TM1638::~TM1638()
{
}