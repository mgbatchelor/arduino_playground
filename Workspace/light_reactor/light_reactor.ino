#include <Servo.h>

Servo servo;

int tunePin = 0;
int lightSensorPin = 1;

int val;

void setup() {
  servo.attach(9);
}

void loop() {
  servo.write(normalize(analogRead(lightSensorPin)));
}

int offset() {
  return map(analogRead(tunePin), 0, 1023, 0, 800);
}

int normalize(int lightLevel) {
  lightLevel = map(lightLevel, 0, offset(), 0, 255);
//  lightLevel = constrain(lightLevel, 0, 255);
  return lightLevel;
}

