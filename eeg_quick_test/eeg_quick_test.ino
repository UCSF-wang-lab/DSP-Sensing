elapsedMicros LastScan;

unsigned long RunTime = 1000000;  // in micros
unsigned long ScanSpace = 20;   // in micros
unsigned long starttime;
unsigned long iter = 1;
unsigned long endtime;
unsigned long t1;
unsigned long t2;
unsigned long tottime;

const int EEG = 40;
unsigned long EEG_val;


void setup() {

Serial.begin(9600);

//  pinMode(EEG,INPUT_DISABLE);

  delay(5000);

}

void loop() {    // only takes 17-18us to loop this

  
  if (iter == 1) {
    starttime = micros();
    endtime = starttime + RunTime;
    iter = iter + 1;
//    Serial.println("here");
  }

  if (micros() < endtime) {

      if (LastScan >= ScanSpace){
        LastScan = 0;
      
    //    delay(1);
//        t1 = micros();
        EEG_val = analogRead(EEG);

//      t2 = micros();
//      tottime = t2-t1;
//      Serial.print("TIMEEEEE:  ");
//      Serial.println(tottime);
//        Serial.println(EEG_val);
        Serial.println(micros());

    
      }

  }


}
