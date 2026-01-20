extern bool SimMode;

void SetMotorSpeed(int LeftSpeed, int RightSpeed) {
   if (SimMode) {
     Serial.print("Left Motor Speed: ");
     Serial.print(LeftSpeed);
     Serial.print(" Right Motor Speed: ");
     Serial.println(RightSpeed);
   }
  
}
