#include <TimeLib.h>
#include <Bounce2.h>
#include <Keyboard.h>
#include <CapacitiveSensor.h>


CapacitiveSensor Cap1 = CapacitiveSensor(19,20);
long Cap1_val;

const int out_pin = 0;


//const int Cap1 = 0;
//long Cap1_val;
//long Cap1_report;

//const int lower_in = 2200;
//const int upper_in = 3223;
//
//const int lower_out = 0;
//const int upper_out = 1023;

//unsigned long RunTime = 100000;
unsigned long time1;
unsigned long time2;
unsigned long tottime;

void setup() {  
  // put your setup code here, to run once:

  pinMode(19, OUTPUT);
  pinMode(20, INPUT_DISABLE);

  pinMode(out_pin, OUTPUT);

//  Serial.begin(1000000);

}

void loop() {
//  if (millis() < RunTime) {

    time1 = micros();
    Cap1_val = Cap1.capacitiveSensor(25);
    time2 = micros();
    tottime = time2 - time1;
    
//    Serial.println(Cap1_val);
//    Serial.println(Cap1_val);
//    Serial.println(tottime);

//  Cap1_report = map(Cap1_val,lower_in,upper_in,lower_out,upper_out);
//  Cap1_report = constrain(Cap1_report,lower_out,upper_out);
//  Serial.print(',');
//  Serial.println(Cap1_report);

//  analogWrite(A14,Cap1_report);

  digitalWrite(out_pin, 1);

//  }
}
