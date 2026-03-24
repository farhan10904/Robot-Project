#include "Types.h"
#include "Motors.h"

extern State CurrentState;
extern Action LastTurn;
extern const int base, slightslow, slightfast, hardslow, hardfast;
extern const int reversebase;

void ComputeMotorSpeed(int L, int C, int R, int &LeftSpeed, int &RightSpeed) { 
     if (L == 0 && C == 1 && R == 0) {
         LeftSpeed = base;
         RightSpeed = base;
     }
     else if (L == 1 && C == 0 && R == 0) {
         LeftSpeed = hardslow;
         RightSpeed = hardfast;
         LastTurn = Act_Left;
     }
     else if (L == 0 && C == 0 && R == 1) {
         LeftSpeed = hardfast;
         RightSpeed = hardslow;
         LastTurn = Act_Right;
     }
     else if (L == 1 && C == 1 && R == 0) {
         LeftSpeed = slightslow;
         RightSpeed = slightfast;
         LastTurn = Act_Left;
     }
     else if (L == 0 && C == 1 && R == 1) {
         LeftSpeed = slightfast;
         RightSpeed = slightslow;
         LastTurn = Act_Right;
     }
     else if (L == 0 && C == 0 && R == 0) {
         CurrentState = LostLine;
         LeftSpeed = 0;
         RightSpeed = 0;
        }
    else if (L == 1 && C == 1 && R == 1) {
         LeftSpeed = base;
         RightSpeed = base;
     }

    Serial.print("L: ");
    Serial.print(L);
    Serial.print("  C: ");
    Serial.print(C);
    Serial.print("  R: ");
    Serial.println(R);
    Serial.print(" | LS: ");
    Serial.print(LeftSpeed);
    Serial.print(" RS: ");
    Serial.println(RightSpeed);
}

