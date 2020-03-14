//arduino library includes
#include <Arduino.h>
#include <hardwareSerial.h>
//C++ includes
#include <bitset>
//costom includes
#include "TM1638.h"



typedef std::bitset<8> BYTE;

int lKDataIO = 0;
int lKClock = 1;
int lKStrobe = 2;
int x = 0;


BYTE emptyData = 0b00000000;
BYTE fullData = 0b11111111;

TM1638 ledKey(0,1,2);

void setup() {
    
    Serial.begin(9600);
    Serial.write("comInit");

}

void loop() {
    /*ledKey.sendInstruction(instruction1);
    Serial.println("Update1...");
    delay(500);
    ledKey.sendInstruction(instruction2);
    Serial.println("Update2...");
    delay(10);

    ledKey.sendInstruction(setWriteMode);
    Serial.println("set Data...");
    delay(10);*/

    ledKey.update();
    ledKey.setdigit(rand()%10,x%8);
    x++;

    delay(100);


  // put your main code here, to run repeatedly:

}