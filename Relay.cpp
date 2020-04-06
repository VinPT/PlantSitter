#include "Relay.h"


Relay::Relay(int mypin):Relay(mypin, 0) {}
Relay::Relay(int mypin, bool onState){
    mydigitalPinOutput = mypin;
    activeMode= onState;
    
    pinMode(mydigitalPinOutput, OUTPUT);

    off();
}

void Relay::on(){
    relayState = 1;
    digitalWrite(mydigitalPinOutput, activeMode);
}
void Relay::off(){
    relayState = 0;
    digitalWrite(mydigitalPinOutput, !activeMode);
}

bool Relay::state(){
    return relayState;
}

Relay::~Relay(){
    
}
