#include "TM1638.h"

TM1638::TM1638(int data, int clock, int strobe){
    lKDataIO = data;
    lKClock = clock;
    lKStrobe = strobe;
    
    ins = 0b10001111;
    
    initArduino();
}

int TM1638::initArduino(){
    
    pinMode(lKDataIO, OUTPUT);
    pinMode(lKClock, OUTPUT);
    pinMode(lKStrobe, OUTPUT);

    digitalWrite(lKDataIO, HIGH);
    digitalWrite(lKClock, HIGH);
    digitalWrite(lKStrobe, HIGH);

    

    return 0;
}

void TM1638::sendInstruction(BYTE instruction){
   
    digitalWrite(lKStrobe, HIGH);
    digitalWrite(lKStrobe, LOW);

    sendData(instruction);    
}

void TM1638::sendData(BYTE instruction){
   
    for(int i = 0; 8 > i; i++){
        digitalWrite(lKClock, LOW);
        digitalWrite(lKDataIO, instruction[i]);
        digitalWrite(lKClock, HIGH);
    }

}

BYTE TM1638::sSNumber(unsigned int number){
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
TM1638::~TM1638(){

}