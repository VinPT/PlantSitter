#include "TM1638.h"

TM1638::TM1638(int data, int clock, int strobe){
    lKDataIO = data;
    lKClock = clock;
    lKStrobe = strobe;
    
    instruction = 0b10001111;
    
    initArduino();
}

int TM1638::initArduino(){
    
    pinMode(lKDataIO, OUTPUT);
    pinMode(lKClock, OUTPUT);
    pinMode(lKStrobe, OUTPUT);

    digitalWrite(lKDataIO, HIGH);
    digitalWrite(lKClock, HIGH);
    digitalWrite(lKStrobe, HIGH);

    Serial.write("Starting Instruction write:");
    
    digitalWrite(lKStrobe, LOW);
    
    for(int i = 0; 8 > i; i++){
        Serial.write(lKDataIO);
        digitalWrite(lKClock, LOW);
        digitalWrite(lKDataIO, instruction[i]);
        digitalWrite(lKClock, HIGH);
    }
    
    digitalWrite(lKStrobe, HIGH);

    return 0;
}

//destructor empty as there is nothing to destroy
TM1638::~TM1638(){

}