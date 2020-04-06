#include<Arduino.h>


class Relay{
    public:
        Relay(int pin);
        Relay(int pin, bool offState);

        void on();
        void off();

        bool state();

        ~Relay();

    private:
        int mydigitalPinOutput;

        bool relayState;
        bool activeMode; // 0 is active low // 1 is active high
        
};