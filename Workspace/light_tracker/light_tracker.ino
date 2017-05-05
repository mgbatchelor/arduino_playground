#include <Servo.h>
#include "scanner.h"

Servo servo;

int tunePin = 0;
int lightSensorPin = 1;
int counter = 0;

int val;

Scanner scanner = Scanner();

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  
  servo.write(90);
  delay(1000);
}

void loop() {
  int next = scanner.track(servo.read(), analogRead(lightSensorPin));
  servo.write(next);
//  Serial.println(scanner.moveTo);
//  Serial.println(scanner.average());
  delay(10);
}


