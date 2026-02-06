#include "Config.h"
#include "Motors.h"

void motorSetup() {
  pinMode(mr, OUTPUT);
  pinMode(ml, OUTPUT);
}

void SetMotorSpeed(int LeftSpeed, int RightSpeed) {
   if (SimMode) {
     Serial.print("Left Motor Speed: ");
     Serial.print(LeftSpeed);
     Serial.print(" Right Motor Speed: ");
     Serial.println(RightSpeed);
     return;
   }
   
   LeftSpeed = constrain(LeftSpeed, -255, 255);
   RightSpeed = constrain(RightSpeed, -255, 255);

   analogWrite(ml, LeftSpeed);
   analogWrite(mr, RightSpeed);

   
}
