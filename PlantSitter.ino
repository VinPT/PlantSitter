//arduino library includes
#include <Arduino.h>
#include <hardwareSerial.h>
//C++ includes
#include <bitset>

//costom includes
#include "TM1638.h"
#include "Clock.h"



//typedef std::bitset<8> BYTE;

int lKDataIO = 0;
int lKClock = 1;
int lKStrobe = 2;
int x = 0;


BYTE emptyData = 0b00000000;
BYTE fullData = 0b11111111;
BYTE keys = 0b00000000;

TM1638 ledKey(0,1,2);
Clock time;
void setup() {
    
    Serial.begin(9600);
    Serial.write("comInit");

}

void loop() {

    
    ledKey.update();
    keys = ledKey.getButtonData();

    for (int i = 0; i < 8; i++)
    {
        int change = (i%2)? 1:-1;
        
        if (keys[i]&&i<2)
            time.relitiveSetHours(change);
        else if (keys[i]&&i<4)
            time.relitiveSetMinutes(change);
        else if (keys[i]&&i<6)
            time.relitiveSetSeconds(change);

    }
    


    //ledKey.setdigit(rand()%10,x%8);
    time.update();
    Clock::Time currentTime = time.getTime();

    ledKey.setdigit((int)currentTime.hours / 10, 0);
    ledKey.setdigit((int)currentTime.hours % 10, 1);
    ledKey.setdigit((int)currentTime.minutes / 10, 2);
    ledKey.setdigit((int)currentTime.minutes % 10, 3);
    ledKey.setdigit((int)currentTime.seconds / 10, 4);
    ledKey.setdigit((int)currentTime.seconds % 10, 5);
    ledKey.setdigit((int)currentTime.miliSeconds / 100, 6);
    ledKey.setdigit(((int)currentTime.miliSeconds/10) % 10, 7);

    x++;

    delay(250);
    

    


  // put your main code here, to run repeatedly:

}