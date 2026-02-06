#include "Config.h"
#include "motors.h"

extern bool SimMode;
extern int sl, sc, sr;
extern const int LineActiveLevel;

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

void GetDropoffIR(int &IR_F, int &IR_R) {
  if (SimMode) {
    static int t=0;
    IR_F = (t == 180 || t == 181 || t == 182 || t == 183) ? 1 : 0;  
    IR_R = (t == 184 || t == 185 || t == 186 || t == 187) ? 1 : 0;
    
    t++;
    if (t>11) t = 0;
    return;
    
  }
  IR_F = 0;
  IR_R = 0;

}