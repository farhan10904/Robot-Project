#include "Types.h"
#include "Sensors.h"
#include "Motors.h"
#include "Line_Following.h"

extern State CurrentState;
extern Action LastTurn;
extern const int base;
extern const int turnL, turnR;
extern const int reversebase; 
extern bool SimMode, CoolDown;
// Keep all of the above

extern bool FrontSeenForPlate;
extern bool PrevFront, PrevRear;
extern const unsigned long FrontTimeoutMS;
extern unsigned long FrontSeenTime;
extern const int mr, ml, sl, sc, sr, led, TriggerFront, ReceiveFront, TriggerRear, ReceiveRear, StepPin, DirPin, ForwardL, ReverseL, ForwardR, ReverseR; 
extern int DeliveriesDone, PlateHits;
extern const float PlateDistanceThreshold;
extern unsigned long LastDeliveryTime; 
extern const unsigned long DeliveryCooldown;
// Remove if you want

void setup() {
  void MotorSetup();
  void SensorSetup();
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

  if (CoolDown) {
    if (millis() - LastDeliveryTime > DeliveryCooldown) {
      CoolDown = false;
      PrevFront = FrontPlate;
      PrevRear = RearPlate;
    }
  }

  if (!CoolDown) {

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
    }

    PrevFront = FrontPlate;
    PrevRear = RearPlate;

  }

  // Package delivery logic
  if (CurrentState == DeliverPackage) {
    PackageDelivery();
    LastDeliveryTime = millis();
    CoolDown = true;
    DeliveriesDone += 1;
    FrontSeenForPlate = false;
    CurrentState = FollowLine;
    FrontSeenTime = 0;
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
        LeftSpeed = -(reversebase + turnL);
        RightSpeed = -(reversebase - turnL);
    } 
      else {
        LeftSpeed = -(reversebase - turnR);
        RightSpeed = -(reversebase + turnR);
      }
    }
  }

  SetMotorSpeed(LeftSpeed, RightSpeed);  
  delay(50);

}
