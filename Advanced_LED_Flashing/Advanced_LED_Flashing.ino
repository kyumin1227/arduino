const int ledPin = 2;
const int redPin = 3;
const int bluePin = 4;
const int yellowPin = 5;

void startLedFlashing() {
  digitalWrite(redPin, HIGH);
      delay(5000);
      digitalWrite(yellowPin, HIGH);
      delay(2000);
      digitalWrite(redPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(bluePin, HIGH);
      delay(5000);
      digitalWrite(bluePin, LOW);
      digitalWrite(yellowPin, HIGH);
      delay(2000);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, HIGH);
}

void endLedFlashing() {
digitalWrite(redPin, LOW);
      digitalWrite(bluePin, LOW);
      digitalWrite(yellowPin, LOW);
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    int command = Serial.read();

    if (command == '1') {
      digitalWrite(ledPin, HIGH);
      Serial.println("LED on");
      startLedFlashing();
    } else if (command == '2') {
      digitalWrite(ledPin, LOW);
      endLedFlashing();
      Serial.println("LED off");
    } else {
      Serial.println("Unknown command");
    }
  }
}
