/*
  author: kara presbrey
  date: 20210122
*/

#include <CapacitiveSensor.h>
//#include </Users/karapresbrey/Downloads/Teensyduino.app/Contents/Java/hardware/teensy/avr/libraries/CapacitiveSensorT/CapacitiveSensorT.h>
//#include </Users/karapresbrey/Downloads/Teensyduino.app/Contents/Java/hardware/teensy/avr/libraries/CapacitiveSensorT/CapacitiveSensor.cpp>

const int    FSRpin = 14;
int FSRval;

CapacitiveSensor Cap1 = CapacitiveSensor(19, 20);
long Cap1_Val;

unsigned long RunTime = 100000;
unsigned long time1;
unsigned long time2;
unsigned long tottime;

void setup() {
  Serial.begin(1000000);
  pinMode(19, OUTPUT);
  pinMode(20, INPUT_DISABLE);
  pinMode(FSRpin, INPUT_DISABLE);
}

void loop() {
  if (millis() < RunTime) {
//    FSRval = analogRead(FSRpin);
//        Serial.println(FSRval);
//        delay(5);

    time1 = micros();
    Cap1_Val = Cap1.capacitiveSensor(15);
    time2 = micros();
    tottime = time2 - time1;
//        Serial.print(FSRval);
//        Serial.print(" ");
    Serial.println(Cap1_Val);
//        Serial.println(tottime);
  }
}
