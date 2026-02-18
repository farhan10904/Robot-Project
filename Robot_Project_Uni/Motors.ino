#include "Motors.h"
extern bool SimMode;
extern const int mr,ml,ForwardL, ReverseL, ForwardR, ReverseR, StepPin, DirPin, StepsPerRevolution, StepDelay;

void MotorSetup() {
  pinMode(mr, OUTPUT);
  pinMode(ml, OUTPUT);
  pinMode(ForwardL, OUTPUT);
  pinMode(ReverseL, OUTPUT);
  pinMode(ForwardR, OUTPUT);
  pinMode(ReverseR, OUTPUT);
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
}

void DriverMotor(int Speed, int ForwardPin, int ReversePin, int PWMPin) {
Speed = constrain(Speed, -255, 255);

if (Speed > 0) {
  digitalWrite(ForwardPin, HIGH);
  digitalWrite(ReversePin, LOW);
  analogWrite(PWMPin, Speed);
} else if (Speed < 0) {
  digitalWrite(ForwardPin, LOW);
  digitalWrite(ReversePin, HIGH);
  analogWrite(PWMPin, abs(Speed));
} else {
  digitalWrite(ForwardPin, HIGH);
  digitalWrite(ReversePin, HIGH); // Brake mode, both pins HIGH, or LOW for coasting
  analogWrite(PWMPin, 0);
}
}

void SetMotorSpeed(int LeftSpeed, int RightSpeed) {
   if (SimMode) {
     Serial.print("Left Motor Speed: ");
     Serial.print(LeftSpeed);
     Serial.print(" Right Motor Speed: ");
     Serial.println(RightSpeed);
     return;
   }

    DriverMotor(LeftSpeed, ForwardL, ReverseL, ml);
    DriverMotor(RightSpeed, ForwardR, ReverseR, mr);
}

void PackageDelivery() {
  SetMotorSpeed(0, 0);
  digitalWrite(DirPin, HIGH);

  for (int i = 0; i < StepsPerRevolution; i++) {
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(StepDelay);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(StepDelay);
  }
}
