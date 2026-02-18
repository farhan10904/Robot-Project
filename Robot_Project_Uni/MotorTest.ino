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

  digitalWrite(ForwardL, LOW);
  digitalWrite(ReverseL, HIGH);
  analogWrite(ml, 255);

  digitalWrite(ForwardR, LOW);
  digitalWrite(ReverseR, HIGH);
  analogWrite(mr, 255);

}