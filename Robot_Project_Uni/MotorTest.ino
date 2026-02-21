const int ForwardL = 8;
const int ReverseL = 7;
const int ForwardR = 12;
const int ReverseR = 11;
const int mr = 10;
const int ml = 9;

void setup() {
  pinMode(mr, OUTPUT);
  pinMode(ml, OUTPUT);
  pinMode(ForwardL, OUTPUT);
  pinMode(ForwardR, OUTPUT);
  pinMode(ReverseL, OUTPUT);
  pinMode(ReverseR, OUTPUT);
}

void loop() {

  digitalWrite(ForwardL, HIGH);
  digitalWrite(ReverseL, LOW);
  digitalWrite(ForwardR, HIGH);
  digitalWrite(ReverseR, LOW);
  analogWrite(ml, 150);
  analogWrite(mr, 150);
  delay(2000);

  analogWrite(ml, 0);
  analogWrite(mr, 0);
  delay(2000);

  digitalWrite(ForwardL, LOW);
  digitalWrite(ReverseL, HIGH);
  digitalWrite(ForwardR, LOW);
  digitalWrite(ReverseR, HIGH);
  analogWrite(ml, 150);
  analogWrite(mr, 150);
  delay(2000);
  
  analogWrite(ml, 0);
  analogWrite(mr, 0);
  delay(2000);

}