elapsedMicros LastScan;

unsigned long RunTime = 1000;
unsigned long ScanSpace = 20000;
unsigned long starttime;
unsigned long iter = 1;
unsigned long endtime;

const int EEG = 40;


void setup() {

//  pinMode(EEG,INPUT_DISABLE);
  
}

void loop() {
  if (iter == 1) {
    starttime = millis;
    endtime = starttime + RunTime;
    iter = iter + 1;
  }

  if (millis() < endtime) {

      if (LastScan >= ScanSpace){
        LastScan = 0;
      
    //    delay(1);
      
        unsigned long EEG_val = analogRead(EEG);
        Serial.println(EEG_val);
//        Serial.println(millis());
    
      }
  }

}
