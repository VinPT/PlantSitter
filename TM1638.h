#include<Arduino.h>

#include <bitset>

typedef std::bitset<8> BYTE;

class TM1638{
    public:
        TM1638(int data, int clock, int strobe);

        ~TM1638();
    
    private:
        int lKDataIO;
        int lKClock;
        int lKStrobe;
        BYTE instruction;

        int initArduino();

};




