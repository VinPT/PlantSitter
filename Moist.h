#include<Arduino.h>


class Moist{
    public:
        Moist(int pin);
        //Relay(int pin, bool offState); init with calibration would be nice one day

        int state();

        ~Moist();

    private:
        int inputPin;
        
};