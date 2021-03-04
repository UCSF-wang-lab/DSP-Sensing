#include <TimeLib.h>
#include <Bounce2.h>
#include <Keyboard.h>
#include <CapacitiveSensor.h>

// pin labels
const int FSR1 = 14;
int FSR1_val;
const int FSR2 = 15;
int FSR2_val;
const int FSR3 = 16;
int FSR3_val;
const int FSR4 = 17;
int FSR4_val;
const int FSR5 = 18;
int FSR5_val;

CapacitiveSensor Cap1 = CapacitiveSensor(19,20);
long Cap1_val;

//CapacitiveSensor Cap2 = CapacitiveSensor(21,22);
long Cap2_val;

CapacitiveSensor Cap3 = CapacitiveSensor(21,22);
long Cap3_val;

CapacitiveSensor Cap4 = CapacitiveSensor(23,24);
long Cap4_val;

CapacitiveSensor Cap5 = CapacitiveSensor(25,26);
long Cap5_val;


const int PhotoD = 41;
int PhotoD_val;

const int EEG = 40;
int EEG_val;

const int Key1 = 2;
int Key1_val;
int lastKey1 = LOW;
const int Key2 = 3;
int Key2_val;
int lastKey2 = LOW;
const int Key3 = 4;
int Key3_val;
int lastKey3 = LOW;
const int Key4 = 5;
int Key4_val;
int lastKey4 = LOW;
const int Key5 = 6;
int Key5_val;
int lastKey5 = LOW;

String Report;

Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncer4 = Bounce(); 
Bounce debouncer5 = Bounce(); 

// timers
elapsedMicros LastScan;
elapsedMicros SinceStart;

unsigned long ScanSpace = 2000;

unsigned long time1;
unsigned long time2;
unsigned long tottime;

//unsigned long RunTime = 2000;

void setup() {
  setSyncProvider(getTeensy3Time);
  
  pinMode(FSR1,INPUT_DISABLE);
  pinMode(FSR2,INPUT_DISABLE);
  pinMode(FSR3,INPUT_DISABLE);
  pinMode(FSR4,INPUT_DISABLE);
  pinMode(FSR5,INPUT_DISABLE);

  pinMode(19, OUTPUT);
  pinMode(20, INPUT_DISABLE);
//  pinMode(21, OUTPUT);
//  pinMode(22, INPUT_DISABLE);
  pinMode(21, OUTPUT);
  pinMode(22, INPUT_DISABLE);
  pinMode(23, OUTPUT);
  pinMode(24, INPUT_DISABLE);
  pinMode(25, OUTPUT);
  pinMode(26, INPUT_DISABLE);

  pinMode(PhotoD,INPUT_DISABLE);
  
  pinMode(EEG, INPUT_DISABLE);
  
  pinMode(Key1,INPUT);
  debouncer1.attach(Key1);
  debouncer1.interval(5); // interval in ms
  pinMode(Key2,INPUT);
  debouncer2.attach(Key2);
  debouncer2.interval(5); // interval in ms
  pinMode(Key3,INPUT);
  debouncer3.attach(Key3);
  debouncer3.interval(5); // interval in ms
  pinMode(Key4,INPUT);
  debouncer4.attach(Key4);
  debouncer4.interval(5); // interval in ms
  pinMode(Key5,INPUT);
  debouncer5.attach(Key5);
  debouncer5.interval(5); // interval in ms

  Cap1.set_CS_Timeout_Millis(1);
//  Cap2.set_CS_Timeout_Millis(1);
  Cap3.set_CS_Timeout_Millis(1);
  Cap4.set_CS_Timeout_Millis(1);
  Cap5.set_CS_Timeout_Millis(1);
  
  Serial.begin(9600);   // baud rate irrelevant for teensy but have to initialize
  Keyboard.begin();

  delay(10000);
  Serial.println("FSR1,FSR2,FSR3,FSR4,FSR5,Cap1,Cap2,Cap3,Cap4,Cap5,PhotoD,EEG,Key1,Key2,Key3,Key4,Key5,ElapsedMicros,Ticks,RTC");
  
}

void loop() {
//  if (millis() < RunTime) {
//time1 = micros();

  if (LastScan >= ScanSpace){
    LastScan = 0;
    
    FSR1_val = analogRead(FSR1);
    FSR2_val = analogRead(FSR2);
    FSR3_val = analogRead(FSR3);
    FSR4_val = analogRead(FSR4);
    FSR5_val = analogRead(FSR5);

    Cap1_val = Cap1.capacitiveSensor(25);
//    Cap2_Val = Cap2.capacitiveSensor(30);
    Cap2_val = 0;
    Cap3_val = Cap3.capacitiveSensor(25);
    Cap4_val = Cap4.capacitiveSensor(25);
    Cap5_val = Cap5.capacitiveSensor(25);

    PhotoD_val = analogRead(PhotoD);

    EEG_val = analogRead(EEG);

    debouncer1.update();
    debouncer2.update();
    debouncer3.update();
    debouncer4.update();
    debouncer5.update();

    Key1_val = debouncer1.read();
//    Key2_val = debouncer2.read();
    Key3_val = debouncer3.read();
    Key4_val = debouncer4.read();
    Key5_val = debouncer5.read();


    // print timestamps: FSR1_val, FSR2_val, ..., Cap1_val, ..., PhotoD_val, EEG_val, Key1_val, ..., micros(), ARM_DWT_CYCCNT, RTC
    Report = String(FSR1_val)+","+String(FSR2_val)+","+String(FSR3_val)+","+String(FSR4_val)+","+String(FSR5_val)+","+String(Cap1_val)+","+String(Cap2_val)+","+String(Cap3_val)+","+String(Cap4_val)+","+String(Cap5_val)+","+String(PhotoD_val)+","+String(EEG_val)+","+String(Key1_val)+","+String(Key2_val)+","+String(Key3_val)+","+String(Key4_val)+","+String(Key5_val)+","+String(SinceStart)+","+String(ARM_DWT_CYCCNT)+","+String(now());
//    Report = String(FSR1_val)+","+String(FSR2_val)+","+String(FSR3_val)+","+String(FSR4_val)+","+String(FSR5_val)+","+String(Cap1_val)+","+String(Cap2_val)+","+String(Cap3_val)+","+String(Cap4_val)+","+String(Cap5_val)+","+String(PhotoD_val)+","+String(EEG_val)+","+String(Key1_val)+","+String(Key2_val)+","+String(Key3_val)+","+String(Key4_val)+","+String(Key5_val)+","+String(micros())+","+String(ARM_DWT_CYCCNT)+","+String(now());
    Serial.println(Report);
    
    // keyboard interaction with computer
    if (Key1_val == HIGH && lastKey1 == LOW) {
      Keyboard.write('m');
    }
  //  if (Key2_val == HIGH && lastKey2 == LOW) {
  //    Keyboard.write('2');
  //  }
    if (Key3_val == HIGH && lastKey3 == LOW) {
      Keyboard.write(',');
    }
    if (Key4_val == HIGH && lastKey4 == LOW) {
      Keyboard.write('.');
    }
    if (Key5_val == HIGH && lastKey5 == LOW) {
      Keyboard.write('/');
    }

    lastKey1 = Key1_val;
    lastKey2 = Key2_val;
    lastKey3 = Key3_val;
    lastKey4 = Key4_val;
    lastKey5 = Key5_val;

    
    //label,value,micros(),ARM_DWT_CYCCNT,RTC
//    FSR1_Report = "FSR1,"+String(FSR1_val)+","+String(micros())+","+String(ARM_DWT_CYCCNT)+","+String(now());
//    Serial.println(FSR1_Report);

//
//    time2 = micros();
//    tottime = time2-time1;
//    Serial.print("TIMEEEEEEEEEEEEEEEEEEEE = ");
//    Serial.println(tottime);


//  }
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}