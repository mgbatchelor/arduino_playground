#include "scanner.h"

Scanner::Scanner() {
  followDirection = 2;
  moveTo = 0;
}

int Scanner::track(int pointer, int newValue) {
  if (newValue > brain.average()) {
    moveTo = pointer;
    brain.record(newValue);
  } else if (pointer == moveTo) {
    brain.record(newValue);
  }
  
  pointer += followDirection;
  if (pointer <= 10 || pointer >= 170) {
    followDirection = -1 * followDirection;
  }
  return pointer;
}

int Scanner::average() {
  return brain.average();
}

