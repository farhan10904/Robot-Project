const int sl = A0;
const int sc = A1;
const int sr = A2;

void setup() {

  pinMode(sl, INPUT);
  pinMode(sc, INPUT);
  pinMode(sr, INPUT);
  Serial.begin(9600);
  
}

void loop() {

  int leftValue = digitalRead(sl);
  int centerValue = digitalRead(sc);
  int rightValue = digitalRead(sr);

  Serial.print("Left: ");
  Serial.print(leftValue);
  Serial.print(" | Center: ");
  Serial.print(centerValue);
  Serial.print(" | Right: ");
  Serial.println(rightValue);
  delay(500); 

}