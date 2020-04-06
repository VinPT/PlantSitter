#include "Moist.h"


Moist::Moist(int pin){
    inputPin = pin;
    pinMode(pin, INPUT);
}

int Moist::state(){
    int data = analogRead(inputPin);
    return data;
}

Moist::~Moist(){
    
}
    
    
    
    
