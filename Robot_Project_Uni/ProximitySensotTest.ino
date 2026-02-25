const int TriggerFront = A0;
const int ReceiveFront = A1;
const int TriggerRear = A2;
const int ReceiveRear = A3;

void setup() {
    pinMode(TriggerFront, OUTPUT);
    pinMode(ReceiveFront, INPUT);
    pinMode(TriggerRear, OUTPUT);
    pinMode(ReceiveRear, INPUT);
    Serial.begin(9600);
}

float DistanceToPlate(int TriggerPin, int ReceivePin) {
digitalWrite(TriggerPin, LOW);
delayMicroseconds(2);
digitalWrite(TriggerPin, HIGH);
delayMicroseconds(10);
digitalWrite(TriggerPin, LOW);

long duration = pulseIn(ReceivePin, HIGH, 30000);
if (duration == 0) {
return 1000; 
}
float distance_cm = duration * 0.0343 / 2;
return distance_cm;
}

void loop() {

    float distanceFront = DistanceToPlate(TriggerFront, ReceiveFront);
    if (distanceFront <= 15) {
        Serial.println("Plate detected in front");
    } else {
        Serial.println("No plate detected in front");
    }

    delay(1000);

    float distanceRear = DistanceToPlate(TriggerRear, ReceiveRear);
    if (distanceRear <= 15) {
        Serial.println("Plate detected in rear");
    } else {
        Serial.println("No plate detected in rear");
    }

    delay(1000);
    
}