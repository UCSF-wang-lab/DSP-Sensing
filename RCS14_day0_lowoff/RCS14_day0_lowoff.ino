#include <TimeLib.h>
#include <Bounce2.h>
#include <Keyboard.h>

// general timers
elapsedMicros SinceStart;
elapsedMicros LastScan;

// for sampling rate
unsigned long ScanSpace = 250;

// for timing how long things take
unsigned long time1;
unsigned long time2;
unsigned long tottime;

// for predetermining how many samples there should be, for testing purposes
unsigned long RunTime = 5000000;  // in micros
unsigned long starttime;
unsigned long sample = 1;
unsigned long n_samples = RunTime/ScanSpace;
unsigned long endtime;

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


const int Cap1 = 19;
long Cap1_val;

const int Cap2 = 20;
long Cap2_val;

const int Cap3 = 21;
long Cap3_val;

const int Cap4 = 22;
long Cap4_val;

const int Cap5 = 23;
long Cap5_val;


const int EEG = 40;
int EEG_val;


const int PhotoD = 41;
int PhotoD_val;


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

Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncer4 = Bounce(); 
Bounce debouncer5 = Bounce(); 

const int debounce_time = 5;


String Report;


void setup() {
  setSyncProvider(getTeensy3Time);
  
  pinMode(FSR1,INPUT_DISABLE);
  pinMode(FSR2,INPUT_DISABLE);
  pinMode(FSR3,INPUT_DISABLE);
  pinMode(FSR4,INPUT_DISABLE);
  pinMode(FSR5,INPUT_DISABLE);

  pinMode(Cap1, INPUT_DISABLE);
  pinMode(Cap2, INPUT_DISABLE);
  pinMode(Cap3, INPUT_DISABLE);
  pinMode(Cap4, INPUT_DISABLE);
  pinMode(Cap5, INPUT_DISABLE);

  pinMode(PhotoD,INPUT_DISABLE);
  
  pinMode(EEG, INPUT_DISABLE);
  
  pinMode(Key1,INPUT);
  debouncer1.attach(Key1);
  debouncer1.interval(debounce_time); // interval in ms
  pinMode(Key2,INPUT);
  debouncer2.attach(Key2);
  debouncer2.interval(debounce_time); // interval in ms
  pinMode(Key3,INPUT);
  debouncer3.attach(Key3);
  debouncer3.interval(debounce_time); // interval in ms
  pinMode(Key4,INPUT);
  debouncer4.attach(Key4);
  debouncer4.interval(debounce_time); // interval in ms
  pinMode(Key5,INPUT);
  debouncer5.attach(Key5);
  debouncer5.interval(debounce_time); // interval in ms
  
  Serial.begin(9600);   // baud rate irrelevant for teensy but have to initialize
  Keyboard.begin();

  delay(10000);
  Serial.println("EEG,PhotoD,Cap1,Cap2,Cap3,Cap4,Cap5,FSR1,FSR2,FSR3,FSR4,FSR5,Key1,Key2,Key3,Key4,Key5,ElapsedMicros,Ticks,RTC");
  
  starttime = micros();
  endtime = starttime + RunTime;
  
}

void loop() {
  
//  if (micros() < endtime) {
//time1 = micros();

  if (LastScan >= ScanSpace){
//  if (sample <= n_samples) {
//    sample = sample+1;
    LastScan = 0;
    
    FSR1_val = analogRead(FSR1);
    FSR2_val = analogRead(FSR2);
    FSR3_val = analogRead(FSR3);
    FSR4_val = analogRead(FSR4);
    FSR5_val = analogRead(FSR5);

//    Cap1_val = analogRead(Cap1);
//    Cap2_val = analogRead(Cap2);
//    Cap3_val = analogRead(Cap3);
//    Cap4_val = analogRead(Cap4);
//    Cap5_val = analogRead(Cap5);

    Cap1_val = 0;
    Cap2_val = 0;
    Cap3_val = 0;
    Cap4_val = 0;
    Cap5_val = 0;

    PhotoD_val = analogRead(PhotoD);
    PhotoD_val = analogRead(PhotoD);
    PhotoD_val = analogRead(PhotoD);

    EEG_val = analogRead(EEG);
    EEG_val = analogRead(EEG);
    EEG_val = analogRead(EEG);
    EEG_val = analogRead(EEG);

    debouncer1.update();
    debouncer2.update();
    debouncer3.update();
    debouncer4.update();
    debouncer5.update();

    Key1_val = debouncer1.read();
    Key2_val = debouncer2.read();
    Key3_val = debouncer3.read();
    Key4_val = debouncer4.read();
    Key5_val = debouncer5.read();


    // print timestamps: EEG_val, PhotoD_val, Cap1_val, ..., FSR1_val, FSR2_val, ...,  Key1_val, ..., micros(), ARM_DWT_CYCCNT, RTC
    Report = String(EEG_val)+","+String(PhotoD_val)+","+String(Cap1_val)+","+String(Cap2_val)+","+String(Cap3_val)+","+String(Cap4_val)+","+String(Cap5_val)+","+String(FSR1_val)+","+String(FSR2_val)+","+String(FSR3_val)+","+String(FSR4_val)+","+String(FSR5_val)+","+String(Key1_val)+","+String(Key2_val)+","+String(Key3_val)+","+String(Key4_val)+","+String(Key5_val)+","+String(SinceStart)+","+String(ARM_DWT_CYCCNT)+","+String(now());
    Serial.println(Report);
//Serial.println(FSR1_val);

    

    
    // keyboard interaction with computer
    if (Key1_val == HIGH && lastKey1 == LOW) {
      Keyboard.write('1');
    }
    if (Key2_val == HIGH && lastKey2 == LOW) {
      Keyboard.write('2');
    }
    if (Key3_val == HIGH && lastKey3 == LOW) {
      Keyboard.write('3');
    }
    if (Key4_val == HIGH && lastKey4 == LOW) {
      Keyboard.write('4');
    }
    if (Key5_val == HIGH && lastKey5 == LOW) {
      Keyboard.write('5');
    }

    lastKey1 = Key1_val;
    lastKey2 = Key2_val;
    lastKey3 = Key3_val;
    lastKey4 = Key4_val;
    lastKey5 = Key5_val;

    
    //label,value,micros(),ARM_DWT_CYCCNT,RTC
//    FSR1_Report = "FSR1,"+String(FSR1_val)+","+String(micros())+","+String(ARM_DWT_CYCCNT)+","+String(now());
//    Serial.println(FSR1_Report);

////
//    time2 = micros();
//    tottime = time2-time1;
//    Serial.print("TIMEEEEEEEEEEEEEEEEEEEE = ");
//    Serial.println(tottime);


//  }
//  }
  }
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}
