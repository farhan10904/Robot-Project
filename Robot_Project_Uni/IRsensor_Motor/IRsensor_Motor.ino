#include "Types.h"
Action LastTurn = Act_Left;
extern State CurrentState;
const int sl = A0;
const int sc = A1;
const int sr = A2;
const int ForwardL = 8;
const int ReverseL = 7;
const int ForwardR = 12;
const int ReverseR = 11;
const int mr = 10;
const int ml = 9;
const int base = 150;
const int turnL = 80;
const int turnR = 160;
const int reversebase = base / 2;
const int LineActiveLevel = LOW;
int LeftSpeed = 0;
int RightSpeed = 0;

void setup() {
  pinMode(mr, OUTPUT);
  pinMode(ml, OUTPUT);
  pinMode(ForwardL, OUTPUT);
  pinMode(ForwardR, OUTPUT);
  pinMode(ReverseL, OUTPUT);
  pinMode(ReverseR, OUTPUT);
  pinMode(sl, INPUT);
  pinMode(sc, INPUT);
  pinMode(sr, INPUT);
  Serial.begin(9600);
  
}

void loop() {

    int rawL = digitalRead(sl);
    int rawC = digitalRead(sc); 
    int rawR = digitalRead(sr);
    int L = (rawL == LineActiveLevel) ? 1 : 0;
    int C = (rawC == LineActiveLevel) ? 1 : 0;
    int R = (rawR == LineActiveLevel) ? 1 : 0;

    Serial.print("Left: ");
    Serial.print(L);
    Serial.print(" | Center: ");
    Serial.print(C);
    Serial.print(" | Right: ");
    Serial.println(R);
    delay(500); 

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
