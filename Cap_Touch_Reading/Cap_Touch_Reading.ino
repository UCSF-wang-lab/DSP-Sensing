
const int Cap1 = 0;
long Cap1_val;

unsigned long RunTime = 10000;
unsigned long time1;
unsigned long time2;
unsigned long tottime;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(1000000);
}

void loop() {
  if (millis() < RunTime) {

    time1 = micros();
    Cap1_val = touchRead(Cap1);
    time2 = micros();
    tottime = time2 - time1;
    
    Serial.println(Cap1_val);
//    Serial.println(tottime);
  }
}
