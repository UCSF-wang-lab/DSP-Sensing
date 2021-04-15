#include <TimeLib.h>
#include <Bounce2.h>
#include <Keyboard.h>

// general timers
elapsedMicros SinceStart;
elapsedMicros LastScan;

// clock variables
String elmicros;
String tix;
String rtc;

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

// might be able to change this variable type for the caps
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
  
//  starttime = micros();
//  endtime = starttime + RunTime;

}

void loop() {
  
//  if (micros() < endtime) {
//time1 = micros();

  // i am too fucking tired to figure out why, but having the first part with lastscan>=scanspace ensures that it is always a 250us diff between samples even tho it always evaluates to true no matter what
  if(LastScan>=ScanSpace && ((LastScan%ScanSpace>=0 && LastScan%ScanSpace<6) || (LastScan%ScanSpace>=(ScanSpace-5) && LastScan%ScanSpace<=(ScanSpace-1)))){
//  if((LastScan%ScanSpace>=0 && LastScan%ScanSpace<6) || (LastScan%ScanSpace>=(ScanSpace-5) && LastScan%ScanSpace<=(ScanSpace-1))){
//  if (sample <= n_samples) {
//    sample = sample+1;
    LastScan = LastScan-ScanSpace;
//    elapsedMicros looptime;

//    Serial.println(String(LastScan));

    elmicros = String(SinceStart);
    tix = String(ARM_DWT_CYCCNT);
    rtc = String(now());

//    EEG_val = analogRead(EEG);
    EEG_val = analogRead(EEG);
    EEG_val = analogRead(EEG);
    EEG_val = analogRead(EEG);

    PhotoD_val = analogRead(PhotoD);
    PhotoD_val = analogRead(PhotoD);
    PhotoD_val = analogRead(PhotoD);

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

    FSR1_val = analogRead(FSR1);
    FSR2_val = analogRead(FSR2);
    FSR3_val = analogRead(FSR3);
    FSR4_val = analogRead(FSR4);
    FSR5_val = analogRead(FSR5);

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

    // if there is space in the serial buffer, print timestamps: EEG_val, PhotoD_val, Cap1_val, ..., FSR1_val, FSR2_val, ...,  Key1_val, ..., elapsedmicros(), ARM_DWT_CYCCNT, RTC
    int sz = sizeof(String(EEG_val)+","+String(PhotoD_val)+","+String(Cap1_val)+","+String(Cap2_val)+","+String(Cap3_val)+","+String(Cap4_val)+","+String(Cap5_val)+","+String(FSR1_val)+","+String(FSR2_val)+","+String(FSR3_val)+","+String(FSR4_val)+","+String(FSR5_val)+","+String(Key1_val)+","+String(Key2_val)+","+String(Key3_val)+","+String(Key4_val)+","+String(Key5_val)+","+elmicros+","+tix+","+rtc);
//    while looptime < (ScanSpace-35){    // for scan spaces that are much larger than actual loop time, can try to send the data for a waiting period to minimize skipped packets, but will need to double check how long it takes to print the string when certain values are all at maximum levels since longer strings take longer to print
    if(sz <= Serial.availableForWrite()){
      Report = String(EEG_val)+","+String(PhotoD_val)+","+String(Cap1_val)+","+String(Cap2_val)+","+String(Cap3_val)+","+String(Cap4_val)+","+String(Cap5_val)+","+String(FSR1_val)+","+String(FSR2_val)+","+String(FSR3_val)+","+String(FSR4_val)+","+String(FSR5_val)+","+String(Key1_val)+","+String(Key2_val)+","+String(Key3_val)+","+String(Key4_val)+","+String(Key5_val)+","+elmicros+","+tix+","+rtc;
      Serial.println(Report);
//      break
    }
  //    }
// change it so that it always runs sampling if SinceStart%ScanSpace instead? or LastScan%ScanSpace == 0? Otherwise could there be a cumulative drift if it always scans at 251us for example. opted for doing lastscan-scanspace
   // need to think more about this tho when less tired
    


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
