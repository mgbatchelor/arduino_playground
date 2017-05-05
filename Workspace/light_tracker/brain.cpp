#include "brain.h"
#include "math.h"

Brain::Brain() {
  bufferSize = 50;
}

int Brain::average() {
  return sum() / (pointer + 1);
}

void Brain::record(int sensorValue) {
  if (pointer == bufferSize) pop();
  push(sensorValue);
}

int Brain::pop() {
  int value = history[0];
  for (int i = 0; i < bufferSize; i++) {
    history[i] = history[i + 1];
  }
  pointer -= 1;
  return value;
}

void Brain::push(int value) {
  if(value < 0) { value = 0; }
  history[pointer] = value;
  pointer += 1;
}

int Brain::sum() {
  int sum = 0;
  for (int i = 0; i < pointer; i++) {
    sum += history[i];
  }
  return sum;
}

