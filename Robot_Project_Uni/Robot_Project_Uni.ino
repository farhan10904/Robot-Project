#include "Types.h"
#include "Sensors.h"
#include "motors.h"
#include "Line_Following.h"

extern State CurrentState;
extern Action LastTurn;
extern const int base;
extern const int turn;
extern const int reversebase; 
// Keep all of the above

extern bool FrontSeenForPlate;
extern bool PrevIR_F, PrevIR_R;
extern const unsigned long FrontTimeoutMS;
extern unsigned long FrontSeenTime;
extern const int mr, ml, sl, sc, sr, led, TriggerFront, ReceiveFront, TriggerRear, ReceiveRear, PlateDistanceThreshold; 
extern int PlateHits, DeliveriesDone;
// Remove if you want

void setup() {
  pinMode(mr, OUTPUT);
  pinMode(ml, OUTPUT);
  pinMode(sl, INPUT);
  pinMode(sc, INPUT);
  pinMode(sr, INPUT);

  pinMode(led, OUTPUT);

  delay(1000);
  Serial.begin(9600);
}

void loop() {
  int L, C, R;
  int LeftSpeed = 0;
  int RightSpeed = 0;

  GetLineSensors(L, C, R);

  float FrontDistance = DistanceToPlate(TriggerFront, ReceiveFront);
  float RearDistance = DistanceToPlate(TriggerRear, ReceiveRear);

   if (FrontDistance <= PlateDistanceThreshold) {
    FrontSeenForPlate = true;
    FrontSeenTime = millis();
    PlateHits += 1;
    int FrontPlate = 1;
   }


  //int IR_F = 0, IR_R = 0;
  // GetDropoffIR(IR_F, IR_R);
  // if (CurrentState == FollowLine || CurrentState == ApproachDropoff) {
  //   bool FrontRise = (IR_F == 1) && (PrevIR_F == 0);
  //   bool RearRise = (IR_R == 1) && (PrevIR_R == 0);
  //   if (FrontRise) {
  //     PlateHits += 1; 
  //     FrontSeenForPlate = true;
  //     FrontSeenTime = millis();
  //   }
  //   if (FrontSeenForPlate) {
  //     if (millis() - FrontSeenTime > FrontTimeoutMS) {
  //       FrontSeenForPlate = false;
  //     }
  //   }
  //   if (RearRise) {
  //     if (FrontSeenForPlate) {
  //       PlateHits += 1;
  //     }
  //     else {
  //       PlateHits += 2;
  //     }
  //     FrontSeenForPlate = false;
  //   }
  //   PrevIR_F = (IR_F == 1);
  //   PrevIR_R = (IR_R == 1);
  // }

  if (CurrentState == FollowLine) {
    ComputeMotorSpeed(L, C, R, LeftSpeed, RightSpeed);
  } 

  else if (CurrentState == LostLine) {
    if (L == 1 || C == 1 || R == 1) {
      CurrentState = FollowLine;
      ComputeMotorSpeed(L, C, R, LeftSpeed, RightSpeed);
    } 
    else {
      if (LastTurn == Act_Left) {
        LeftSpeed = -(reversebase + turn);
        RightSpeed = -(reversebase - turn);
    } 
      else {
        LeftSpeed = -(reversebase - turn);
        RightSpeed = -(reversebase + turn);
      }
    }
  }

  SetMotorSpeed(LeftSpeed, RightSpeed);  
  delay(50);

}
