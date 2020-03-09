#include<Arduino.h>

class TM1638{
    public:
        TM1638(int data, int clock, int strobe);

        ~TM1638();
    
    private:
        int lKDataIO;
        int lKClock;
        int lKStrobe;

        int initArduino();

};




