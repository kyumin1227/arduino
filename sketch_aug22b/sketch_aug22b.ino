// 落ちない、ぶつからない、格好いい
// ピカチュチム（チーム）
// 最終コード

#include <SoftwareSerial.h>
#include <AFMotor.h>
#include <stdlib.h>
#include <time.h>

#define echoPinRight A5
#define trigPinRight A4

AF_DCMotor motor_L(1);
AF_DCMotor motor_R(4);

AF_DCMotor motor_L2(2);
AF_DCMotor motor_R2(3);

// Sonic sensor
short echoPinLeft = 24;
short trigPinLeft = 25;
short echoPinRear = 26;
short trigPinRear = 27;
short echoPinFront = 30;
short trigPinFront = 31;
short echoPinUnder = 32;
short trigPinUnder = 33;

short front5v = 28;
short left5v = 51;
short rear5v = 53;

// 거리를 확인하여 3 이하면 true 초과할 경우에는 false 반환

long durationFront;
int distanceFront;
bool checkDistanceFront() {
  digitalWrite(trigPinFront, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinFront, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinFront, LOW);
  durationFront = pulseIn(echoPinFront, HIGH);
  distanceFront = durationFront * 0.034 / 2;
  // Serial.print("Front: ");
  // Serial.println(distanceFront);
  if (distanceFront > 15) {
    return true;
  }
  return false;
}

long durationUnder;
int distanceUnder;
bool checkDistanceUnder() {
  digitalWrite(trigPinUnder, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinUnder, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinUnder, LOW);
  durationUnder = pulseIn(echoPinUnder, HIGH);
  distanceUnder = durationUnder * 0.034 / 2;
  // Serial.print("Under: ");
  // Serial.println(distanceUnder);
  if (distanceUnder <= 3) {
    return true;
  }
  return false;
}

long durationRight;
int distanceRight;
bool checkDistanceRight() {
  digitalWrite(trigPinRight, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRight, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRight, LOW);
  durationRight = pulseIn(echoPinRight, HIGH);
  distanceRight = durationRight * 0.034 / 2;
  // Serial.print("Right: ");
  // Serial.println(distanceRight);
  if (distanceRight <= 3) {
    return true;
  }
  return false;
}

long durationLeft;
int distanceLeft;
bool checkDistanceLeft() {
  digitalWrite(trigPinLeft, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinLeft, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLeft, LOW);
  durationLeft = pulseIn(echoPinLeft, HIGH);
  distanceLeft = durationLeft * 0.034 / 2;
  // Serial.print("Left: ");
  // Serial.println(distanceLeft);
  if (distanceLeft <= 3) {
    return true;
  }
  return false;
}

long durationRear;
int distanceRear;
bool checkDistanceRear() {
  digitalWrite(trigPinRear, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRear, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRear, LOW);
  durationRear = pulseIn(echoPinRear, HIGH);
  distanceRear = durationRear * 0.034 / 2;
  // Serial.print("Rear: ");
  // Serial.println(distanceRear);
  if (distanceRear <= 3) {
    return true;
  }
  return false;
}

// LED
short rearLedYelloRight = 16;
short rearLedYelloLeft = 17;
short rearLedRedRight = 14;
short rearLedRedLeft = 15;

// 정지
void stop() {
  motor_L.run(RELEASE);
  motor_R.run(RELEASE);
  motor_L2.run(RELEASE);
  motor_R2.run(RELEASE);
  Serial.println("stop");

  digitalWrite(rearLedYelloRight, LOW);
  digitalWrite(rearLedYelloLeft, LOW);
  digitalWrite(rearLedRedRight, HIGH);
  digitalWrite(rearLedRedLeft, HIGH);

  delay(100);
}

// 전진
void forWard() {
  motor_L.run(FORWARD);
  motor_R.run(BACKWARD);
  motor_L2.run(FORWARD);
  motor_R2.run(FORWARD);

  motor_L.setSpeed(150);
  motor_R.setSpeed(150);
  motor_L2.setSpeed(150);
  motor_R2.setSpeed(150);

  digitalWrite(rearLedYelloRight, LOW);
  digitalWrite(rearLedYelloLeft, LOW);
  digitalWrite(rearLedRedRight, LOW);
  digitalWrite(rearLedRedLeft, LOW);
}

// 후진
void backWard() {
  motor_L.run(BACKWARD);
  motor_R.run(FORWARD);
  motor_L2.run(BACKWARD);
  motor_R2.run(BACKWARD);

  motor_L.setSpeed(200);
  motor_R.setSpeed(200);
  motor_L2.setSpeed(200);
  motor_R2.setSpeed(200);

  digitalWrite(rearLedYelloRight, HIGH);
  digitalWrite(rearLedYelloLeft, HIGH);
  digitalWrite(rearLedRedRight, LOW);
  digitalWrite(rearLedRedLeft, LOW);
}

// 좌회전
void turnLeft() {
  motor_L.run(FORWARD);
  motor_R.run(FORWARD);
  motor_L2.run(FORWARD);
  motor_R2.run(BACKWARD);

  motor_L.setSpeed(200);
  motor_R.setSpeed(200);
  motor_L2.setSpeed(200);
  motor_R2.setSpeed(200);

  digitalWrite(rearLedYelloRight, LOW);
  digitalWrite(rearLedYelloLeft, HIGH);
  digitalWrite(rearLedRedRight, LOW);
  digitalWrite(rearLedRedLeft, LOW);
}

// 우회전
void turnRight() {
  motor_L.run(BACKWARD);
  motor_R.run(BACKWARD);
  motor_L2.run(BACKWARD);
  motor_R2.run(FORWARD);

  motor_L.setSpeed(200);
  motor_R.setSpeed(200);
  motor_L2.setSpeed(200);
  motor_R2.setSpeed(200);

  digitalWrite(rearLedYelloRight, HIGH);
  digitalWrite(rearLedYelloLeft, LOW);
  digitalWrite(rearLedRedRight, LOW);
  digitalWrite(rearLedRedLeft, LOW);
}


unsigned long backwardTime = 700;
unsigned long backwardTimeMill = 0;

short forwardOrRearDef() {
  Serial.println(millis() - backwardTimeMill);
  // 반환값 0 = 전진, 1 = 후진
  if (millis() - backwardTimeMill < backwardTime) {
    return 1;
  } else if (millis() - backwardTimeMill < 1500) {
    Serial.println("turn");
    return 2;
  } else {
    return 0;
  }
}

short inputPinList[] = {echoPinLeft, echoPinRear, echoPinFront, echoPinUnder};
short outputPinList[] = {rearLedYelloRight, rearLedYelloLeft, rearLedRedRight, rearLedRedLeft, trigPinLeft, trigPinRear, trigPinFront, trigPinUnder, front5v, left5v, rear5v};

bool right = true;  // 처음 진행 방향
bool checkRight;
bool checkLeft;
bool checkUnder;
bool checkRear;
bool checkFront;

short forwardOrRear = 0;
short stopOrRightOrLeft;

void setup() {
  motor_L.setSpeed(150);
  motor_L.run(RELEASE);
  motor_R.setSpeed(150);
  motor_R.run(RELEASE);
  motor_L2.setSpeed(150);
  motor_L2.run(RELEASE);
  motor_R2.setSpeed(150);
  motor_R2.run(RELEASE);
  Serial.begin(9600);
  pinMode(echoPinRight, INPUT);
  pinMode(trigPinRight, OUTPUT);
  for (int i = 0; i < sizeof(inputPinList) / sizeof(inputPinList[0]); i++) {
    pinMode(inputPinList[i], INPUT);
  }
  for (int i = 0; i < sizeof(outputPinList) / sizeof(outputPinList[0]); i++) {
    pinMode(outputPinList[i], OUTPUT);
  }
  digitalWrite(front5v, HIGH);
}



bool sensorActive[5] = {true, true, true, true, true};
unsigned long sensorDeactivateTime[5] = {0, 0, 0, 0, 0};
unsigned long sensorCooldown = 1000;

// 특정 센서를 비활성화하는 함수
void deactivateSensor(int index) {
    sensorActive[index] = false;
    sensorDeactivateTime[index] = millis();
}

short random_num = 0;

void loop() {
  unsigned long currentMillis = millis();
  for (int i = 0; i < 5; i++) {
    if (!sensorActive[i] && (currentMillis - sensorDeactivateTime[i] >= sensorCooldown)) {
        sensorActive[i] = true;
    }
  }

  checkFront = sensorActive[0] ? checkDistanceFront() : true;
  checkUnder = sensorActive[1] ? checkDistanceUnder() : true;
  checkRear = sensorActive[2] ? checkDistanceRear() : true;
  checkRight = sensorActive[3] ? checkDistanceRight() : true;
  checkLeft = sensorActive[4] ? checkDistanceLeft() : true;
  
  if (!checkRight) {
    deactivateSensor(3);
    stop();
    backwardTimeMill = millis();
  } else if (!checkLeft) {
    deactivateSensor(4);
    stop();
    backwardTimeMill = millis();
  } else if (!checkUnder) {
    deactivateSensor(1);
    // 0
    stop();
    backwardTimeMill = millis();
    random_num = rand() % 2;
  } else if (!checkRear) {
    deactivateSensor(2);
    backwardTimeMill = 0;
    // 1
    stop();
  } else if (!checkFront) {
    deactivateSensor(0);
    // 0
    stop();
    backwardTimeMill = millis();
  } else {
    forwardOrRear = forwardOrRearDef();
    Serial.println(forwardOrRear);
    if (forwardOrRear == 0) {
      forWard();
      Serial.println("forward");
    } else if (forwardOrRear == 2) {
      if (random_num == 0) {
        turnRight();
      } else {
        turnLeft();
      }
    } else if (forwardOrRear == 1) {
      backWard();
      Serial.println("backward");
    }
  }
}
