//arduino library includes
#include <Arduino.h>
#include <hardwareSerial.h>
//#include <Wire.h>
#include <i2c_t3.h>

//C++ includes
#include <bitset>

//costom includes
#include "TM1638.h"
#include "Clock.h"
#include "Relay.h"
#include "Moist.h"

int x = 0;

Clock time;

//init GPIO DEVICES
TM1638 ledKey(0, 1, 2);
Relay light(27);
Relay pump(26);
//Relay fan;
Moist plant1(14);
Moist plant2(16);
Moist plant3(17);
Moist plant4(22);

//INIT I2C DEVICES
void print_scan_status(uint8_t target, uint8_t all);

uint8_t found, target, all;

void setup()
{
    Serial.begin(9600);
    delay(50);
    pinMode(A9, INPUT);

    ////////// EXAMPLE CODE
    pinMode(LED_BUILTIN, OUTPUT); // LED
    pinMode(12, INPUT_PULLUP);    // pull pin 12 low to show ACK only results
    pinMode(11, INPUT_PULLUP);    // pull pin 11 low for a more verbose result (shows both ACK and NACK)

    // Setup for Master mode, pins 18/19, external pullups, 400kHz, 10ms default timeout
    Wire.begin(I2C_MASTER, 0x00, I2C_PINS_18_19, I2C_PULLUP_EXT, 400000);
    Wire.setDefaultTimeout(10000);
    //////////

    Serial.write("comInit");
}

void loop()
{

    ledKey.update();
    time.update();

    BYTE keys = ledKey.getButtonData();

    for (int i = 0; i < 8; i++)
    {
        int change = (i % 2) ? 1 : -1;

        if (keys[i] && i < 2)
            time.relitiveSetHours(change);
        else if (keys[i] && i < 4)
            time.relitiveSetMinutes(change);
        else if (keys[i] && i < 6)
            time.relitiveSetSeconds(change);
    }

    Clock::Time currentTime = time.getTime();

    ledKey.setdigit((int)currentTime.hours / 10, 0);
    ledKey.setdigit((int)currentTime.hours % 10, 1);
    ledKey.setdigit((int)currentTime.minutes / 10, 2);
    ledKey.setdigit((int)currentTime.minutes % 10, 3);
    ledKey.setdigit((int)currentTime.seconds / 10, 4);
    ledKey.setdigit((int)currentTime.seconds % 10, 5);
    ledKey.setdigit((int)currentTime.miliSeconds / 100, 6);
    ledKey.setdigit(((int)currentTime.miliSeconds / 10) % 10, 7);

    /*    if(0 == x%20){
        light.on();
    }
    else
    {
        
        light.off();
    }

    if(800 < plant2.state()){
        pump.on();
    }
    else{  
        pump.off();
    }

    Serial.print("Plant1: ");
    Serial.print(plant1.state());
    Serial.print("Plant2: ");
    Serial.print(plant2.state());
    Serial.print("plant3: ");
    Serial.print(plant3.state());
    Serial.print("plant4: ");
    Serial.println(plant4.state());

  */

    ///////////////////////////////////

    if (digitalRead(12) == LOW || digitalRead(11) == LOW)
    {
        all = (digitalRead(11) == LOW);
        found = 0;

        Serial.print("---------------------------------------------------\n");
        Serial.print("Starting scan...\n");
        digitalWrite(LED_BUILTIN, HIGH);           // LED on
        for (target = 1; target <= 0x7F; target++) // sweep addr, skip general call
        {
            Wire.beginTransmission(target); // slave addr
            Wire.endTransmission();         // no data, just addr
            print_scan_status(target, all);
        }
        digitalWrite(LED_BUILTIN, LOW); // LED off

        if (!found)
            Serial.print("No devices found.\n");
        ///////////////////////////////////////

        delay(500);
    }
    delay(500);
    x++;

    // put your main code here, to run repeatedly:
}

void print_scan_status(uint8_t target, uint8_t all)
{
    switch (Wire.status())
    {
    case I2C_WAITING:
        Serial.printf("Addr: 0x%02X ACK\n", target);
        found = 1;
        break;
    case I2C_ADDR_NAK:
        if (all)
            Serial.printf("Addr: 0x%02X\n", target);
        break;
    default:
        break;
    }
}