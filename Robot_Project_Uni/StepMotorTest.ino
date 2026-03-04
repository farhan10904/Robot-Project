const int StepPin = 2;
const int DirPin  = 3;

void setup() {
  pinMode(StepPin, OUTPUT);
  pinMode(DirPin, OUTPUT);
}

void loop() {

  digitalWrite(DirPin, HIGH);

  for (int i = 0; i < 200; i++) {   
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(1000);
  }

  delay(1500);

  digitalWrite(DirPin, LOW);

  for (int i = 0; i < 200; i++) {
    digitalWrite(StepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(StepPin, LOW);
    delayMicroseconds(1000);
  }

  delay(2000);
}