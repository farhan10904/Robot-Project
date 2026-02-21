#include "Types.h"
#include "Motors.h"

extern State CurrentState;
extern Action LastTurn;
extern const int base,turnR, turnL;
extern const int reversebase;

void ComputeMotorSpeed(int L, int C, int R, int &LeftSpeed, int &RightSpeed) { 
     if (L == 0 && C == 1 && R == 0) {
         LeftSpeed = base;
         RightSpeed = base;
     }
     else if (L == 1 && C == 0 && R == 0) {
         LeftSpeed = base - turnL;
         RightSpeed = base + turnL;
         LastTurn = Act_Left;
     }
     else if (L == 0 && C == 0 && R == 1) {
         LeftSpeed = base + turnR;
         RightSpeed = base - turnR;
         LastTurn = Act_Right;
     }
     else if (L == 1 && C == 1 && R == 0) {
         LeftSpeed = base - (turnL / 2);
         RightSpeed = base + (turnL / 2);
         LastTurn = Act_Left;
     }
     else if (L == 0 && C == 1 && R == 1) {
         LeftSpeed = base + (turnR / 2);
         RightSpeed = base - (turnR / 2);
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
}

