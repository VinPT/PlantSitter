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

BYTE instruction = 0b10001111; //

void setup() {
    
    Serial.begin(9600);
    Serial.write("comInit");
    TM1638 ledKey(0,1,2);

    // put your setup code here, to run once:
    


}

void loop() {
    //TM1638 ledKey(0,1,2);
    Serial.println("Update...");
    delay(1000);
  // put your main code here, to run repeatedly:

}