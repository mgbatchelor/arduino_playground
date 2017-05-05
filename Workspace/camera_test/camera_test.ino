#include <Adafruit_VC0706.h>

SoftwareSerial serial = SoftwareSerial(2, 3);

Adafruit_VC0706 cam = Adafruit_VC0706(&serial);

const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int RED = 0;
const int GREEN = 256;
const int BLUE = 512;
const int PURPLE = 700;

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  Serial.begin(38400);
  if (cam.begin()) {
    blink(PURPLE, 1);
  } else {
    blink(RED, 10);
    return;
  }

  cam.setImageSize(VC0706_640x480);
//  cam.setMotionDetect(true);
}

void display(int color) {
  int redIntensity;
  int greenIntensity;
  int blueIntensity;
  
  if (color <= 255)          // zone 1
  {
    redIntensity = 255 - color;    // red goes from on to off
    greenIntensity = color;        // green goes from off to on
    blueIntensity = 0;             // blue is always off
  }
  else if (color <= 511)     // zone 2
  {
    redIntensity = 0;                     // red is always off
    greenIntensity = 255 - (color - 256); // green on to off
    blueIntensity = (color - 256);        // blue off to on
  }
  else // color >= 512       // zone 3
  {
    redIntensity = (color - 512);         // red off to on
    greenIntensity = 0;                   // green is always off
    blueIntensity = 255 - (color - 512);  // blue on to off
  }
  
  analogWrite(RED_PIN, redIntensity/2);
  analogWrite(BLUE_PIN, blueIntensity/2);
  analogWrite(GREEN_PIN, greenIntensity/2);
}

void blink(int color, int duration) {
  for(int i = 0; i <= (duration * 4); i++) {
    display(color);
    delay(125);
    off();  
    delay(125);
  }
}

void off() {
  analogWrite(RED_PIN, 0);
  analogWrite(BLUE_PIN, 0);
  analogWrite(GREEN_PIN, 0);
}

void loop() {
//  if (cam.motionDetected()) {
//    cam.setMotionDetect(false);
    blink(GREEN, 2);  
    if (!cam.takePicture()) {
      blink(RED, 10);
      return;
    }
    
    Serial.print("!");
  
    // Get the size of the image (frame) taken
    uint16_t jpglen = cam.frameLength();
    Serial.print(jpglen, BIN);
    
    while (jpglen > 0) {
      uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
      Serial.write(cam.readPicture(bytesToRead), bytesToRead);
      jpglen -= bytesToRead;
      display(jpglen % 768);
    }
  
    blink(RED, 2);
    cam.resumeVideo();
    blink(PURPLE, 30);
//    cam.setMotionDetect(true);
//  }
}
