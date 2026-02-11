#include "Sensors.h"

extern bool SimMode;
extern const int sl, sc, sr, TriggerFront, ReceiveFront, TriggerRear, ReceiveRear;
extern const int LineActiveLevel;

void SensorSetup() {
  pinMode(sl, INPUT);
  pinMode(sc, INPUT);
  pinMode(sr, INPUT);
  pinMode(TriggerFront, OUTPUT);
  pinMode(ReceiveFront, INPUT);
  pinMode(TriggerRear, OUTPUT);
  pinMode(ReceiveRear, INPUT);
}

void GetLineSensors(int &L, int &C, int &R) {
  if (SimMode)  {
    static int step = 0; 
     if (step == 0) {
      L = 0; C = 1; R = 0; 
    } else if (step == 1) {
      L = 1; C = 0; R = 0; 
    } else if (step == 2) {
      L = 0; C = 0; R = 1; 
    } else if (step == 3) {
      L = 0; C = 0; R = 0; 
    } else if (step == 4) {
      L = 1; C = 1; R = 0; 
    } else if (step == 5) {
      L = 0; C = 1; R = 0; 
    }
    step = step + 1;
    
    if (step > 5) {
      step = 0;
    }
    
    return;
  }

  int rawL = digitalRead(sl);
  int rawC = digitalRead(sc); 
  int rawR = digitalRead(sr);

  L = (rawL == LineActiveLevel) ? 1 : 0;
  C = (rawC == LineActiveLevel) ? 1 : 0;
  R = (rawR == LineActiveLevel) ? 1 : 0;

}

float DistanceToPlate(int TriggerPin, int ReceivePin) {
digitalWrite(TriggerPin, LOW);
delayMicroseconds(2);
digitalWrite(TriggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(TriggerPin, LOW);

long duration = pulseIn(ReceivePin, HIGH, 30000);
if (duration == 0) {
  return 1000; 
}
float distance_cm = duration * 0.0343 / 2;
return distance_cm;
}