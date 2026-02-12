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
extern bool PrevFront, PrevRear;
extern const unsigned long FrontTimeoutMS;
extern unsigned long FrontSeenTime;
extern const int mr, ml, sl, sc, sr, led, TriggerFront, ReceiveFront, TriggerRear, ReceiveRear, PlateDistanceThreshold; 
extern int DeliveriesDone;
extern const float PlateDistanceThreshold;
// Remove if you want

void setup() {
  pinMode(mr, OUTPUT);
  pinMode(ml, OUTPUT);
  pinMode(sl, INPUT);
  pinMode(sc, INPUT);
  pinMode(sr, INPUT);
  pinMode(led, OUTPUT);
  pinMode(TriggerFront, OUTPUT);
  pinMode(ReceiveFront, INPUT);
  pinMode(TriggerRear, OUTPUT);
  pinMode(ReceiveRear, INPUT);

  delay(1000);
  Serial.begin(9600);
}

void loop() {
  int L, C, R;
  int LeftSpeed = 0;
  int RightSpeed = 0;
  int FrontPlate = 0;
  int RearPlate = 0;


  // Plate delivery logic
  GetLineSensors(L, C, R);
  float FrontDistance = DistanceToPlate(TriggerFront, ReceiveFront);
  float RearDistance = DistanceToPlate(TriggerRear, ReceiveRear);

  if (FrontDistance <= PlateDistanceThreshold) {
    FrontPlate = 1;
  }
  if (RearDistance <= PlateDistanceThreshold) {
    RearPlate = 1;
  }
  bool FrontRise = (FrontPlate == 1) && (PrevFront == 0);
  bool RearRise = (RearPlate == 1) && (PrevRear == 0);

  if (FrontRise) {
    PlateHits += 1; 
    FrontSeenForPlate = true;
    FrontSeenTime = millis();
    CurrentState = ApproachDropoff;
  }
  if (FrontSeenForPlate) {
    if (millis() - FrontSeenTime > FrontTimeoutMS) {
      FrontSeenForPlate = false;
      CurrentState = FollowLine;
    }
  }

  if ((RearRise) && (CurrentState == ApproachDropoff) ){
    PlateHits += 1;
    FrontSeenForPlate = false;
    CurrentState = DeliverPackage;
  }
  else if (RearRise) {
    PlateHits += 2;
    FrontSeenForPlate = false;
    DeliveriesDone += 1;
  }

  PrevFront = FrontPlate;
  PrevRear = RearPlate;

  // Package delivery logic
  if (CurrentState == DeliverPackage) {
    PackageDelivery();
    DeliveriesDone += 1;
    CurrentState = FollowLine;
    delay(1000);  
  }  

   // Line following logic 
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
