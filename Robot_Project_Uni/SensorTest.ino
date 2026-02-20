const int sl = 6;
const int sc = 5;
const int sr = 4;

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