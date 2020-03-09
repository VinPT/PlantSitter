#include <bitset>
#include <Arduino.h>

typedef std::bitset<8> BYTE;

int lKDataIO = 0;
int lKClock = 1;
int lKStrobe = 2;

BYTE instruction = 0b10001111; //

void setup() {
  // put your setup code here, to run once:
  pinMode(lKDataIO, OUTPUT);
  pinMode(lKClock, OUTPUT);
  pinMode(lKStrobe, OUTPUT);

  digitalWrite(lKDataIO, HIGH);
  digitalWrite(lKClock, HIGH);
  digitalWrite(lKStrobe, HIGH);


}

void loop() {
  // put your main code here, to run repeatedly:

}