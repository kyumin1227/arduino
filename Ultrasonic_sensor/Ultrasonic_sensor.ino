#define echoPin 2
#define trigPin 3

#define crosswalkBluePin 5
#define crosswalkRedPin 6

#define vehiclesBluePin 8
#define vehiclesYelloPin 9
#define vehiclesRedPin 10

long duration;
int distance;
bool startLed = false;

// 거리를 확인하여 10 이하면 true를 반환
bool checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  if (distance <= 10 && distance != 0) {
    return true;
  }
  return false;
}

void startVehicleLight() {
  digitalWrite(vehiclesBluePin, LOW);
  digitalWrite(vehiclesYelloPin, HIGH);
  delay(3000);
  digitalWrite(vehiclesYelloPin, LOW);
  digitalWrite(vehiclesRedPin, HIGH);
}

void startCrosswalkLight() {
  digitalWrite(crosswalkRedPin, LOW);
  digitalWrite(crosswalkBluePin, HIGH);
  delay(10000);

  for (int i = 0; i < 6; i++) {
    digitalWrite(crosswalkBluePin, HIGH);
    delay(250);
    digitalWrite(crosswalkBluePin, LOW);
    delay(250);
  }

  digitalWrite(crosswalkRedPin, HIGH);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(crosswalkBluePin, OUTPUT);
  pinMode(crosswalkRedPin, OUTPUT);
  pinMode(vehiclesBluePin, OUTPUT);
  pinMode(vehiclesYelloPin, OUTPUT);
  pinMode(vehiclesRedPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(vehiclesBluePin, HIGH);
  digitalWrite(crosswalkRedPin, HIGH);
}

void loop() {
  startLed = checkDistance();

  if (startLed) {
    startVehicleLight();
    startCrosswalkLight();
    digitalWrite(vehiclesBluePin, HIGH);
    digitalWrite(vehiclesRedPin, LOW);
  }

  delay(1000);
}
