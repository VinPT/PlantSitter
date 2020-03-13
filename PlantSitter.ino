//arduino library includes
#include <Arduino.h>

//C++ includes
#include <bitset>
//costom includes
#include "TM1638.h"



typedef std::bitset<8> BYTE;

int lKDataIO = 0;
int lKClock = 1;
int lKStrobe = 2;
int x = 0;

BYTE instruction1 = 0b10001111; //
BYTE instruction2 = 0b10000111;
BYTE setWriteMode = 0b01000000;
BYTE emptyData = 0b00000000;
BYTE fullData = 0b11111111;

TM1638 ledKey(0,1,2);

void setup() {
    
    Serial.begin(9600);
    Serial.write("comInit");
    //ledKey = (0,1,2);

    // put your setup code here, to run once:
    


}

void loop() {
    ledKey.sendInstruction(instruction1);
    Serial.println("Update1...");
    delay(500);
    ledKey.sendInstruction(instruction2);
    Serial.println("Update2...");
    delay(10);

    ledKey.sendInstruction(setWriteMode);
    Serial.println("set Data...");
    delay(10);


    //for(int i = 0;10>i;i++){
        for(int j = 0;16>j;j++){
            
            if(j%2 == 1){
                ledKey.sendData(fullData);
                //Serial.println("Full Data...");
                delay(10);
            }
            else{
                //emptyData[(int)(i/2)].flip();
                ledKey.sendData(ledKey.sSNumber(x%10));
                //Serial.println("set Data...");
                delay(10);
            }
            
        }
    //}

    x++;


  // put your main code here, to run repeatedly:

}