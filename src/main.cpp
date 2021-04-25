//arduino library includes
#include <Arduino.h>
#include <hardwareSerial.h>
//#include <Wire.h>
#include <i2c_t3.h>

//C++ includes
#include <bitset>
#include <ctime>

//costom includes
#include "TM1638.h"
#include "Clock.h"
#include "Relay.h"
#include "Moist.h"
#include "Dusk2Dawn/Dusk2Dawn.h"
int x = 0;

Clock worldtime;

//init GPIO DEVICES
TM1638 ledKey(2, 3, 4);
Relay light(27);
Relay pump(26);
//Relay fan;
Moist plant1(14);
Moist plant2(16);
Moist plant3(17);
Moist plant4(22);

//INIT I2C DEVICES
void print_scan_status(uint8_t target, uint8_t all);
int pdxSunrise, pdxSunset;
Dusk2Dawn pdx(34.0522, -118.2437, -8);
uint8_t found, target, all;

void setup()
{

    pdxSunrise = pdx.sunrise(2021, 3, 30, false);
    pdxSunset = pdx.sunset(2021, 3, 30, false);

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
//   -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -
//  |   |     | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//   -   -       -  |  -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -
//    | |     | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
//   -   -       -  |  -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -   -   -  |  -   -
void loop()
{

    //Serial.print("Sunrise: ");
    //Serial.println(pdxSunrise);
    //Serial.print("Sunset: ");
    //Serial.println(pdxSunset);

    ledKey.update();
    worldtime.update();

    //BYTE keys = ledKey.getButtonData();
    BYTE keys = 0b00000000;
    for (int i = 0; i < 8; i++)
    {
        int change = (i % 2) ? 1 : -1;

        if (keys[i] && i < 2)
            worldtime.relitiveSetHours(change);
        else if (keys[i] && i < 4)
            worldtime.relitiveSetMinutes(change);
        else if (keys[i] && i < 6)
            worldtime.relitiveSetSeconds(change);
    }

    Clock::Time currentTime = worldtime.getTime();
    //Serial.println(currentTime.hours + currentTime.minutes + currentTime.seconds + currentTime.miliSeconds);
    ledKey.setdigit((int)currentTime.days / 10, 0);
    ledKey.setdigit((int)currentTime.days % 10, 1);
    ledKey.setdigit((int)currentTime.hours / 10, 2);
    ledKey.setdigit((int)currentTime.hours % 10, 3);
    ledKey.setdigit((int)currentTime.minutes / 10, 4);
    ledKey.setdigit((int)currentTime.minutes % 10, 5);
    ledKey.setdigit((int)currentTime.seconds / 10, 6);
    ledKey.setdigit((int)currentTime.seconds % 10, 7);

    //ledKey.setdigit(0, 6);
    //ledKey.setdigit(0, 7);

    //ledKey.setdigit(0, 0);
    //ledKey.setdigit(1, 1);
    //ledKey.setdigit(2, 2);
    //ledKey.setdigit(3, 3);
    //ledKey.setdigit(6, 4);
    //ledKey.setdigit(7, 5);
    //ledKey.setdigit(8, 6);
    //ledKey.setdigit(9, 7);

    all = true;
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

    if (0 == x % 20)
    {
        light.on();
    }
    else
    {

        light.off();
    }

    if (800 < plant2.state())
    {
        pump.on();
    }
    else
    {
        pump.off();
    }
    /*
    Serial.print("Plant1: ");
    Serial.print(plant1.state());
    Serial.print("Plant2: ");
    Serial.print(plant2.state());
    Serial.print("plant3: ");
    Serial.print(plant3.state());
    Serial.print("plant4: ");
    Serial.println(plant4.state());
*/
    delay(1000);
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