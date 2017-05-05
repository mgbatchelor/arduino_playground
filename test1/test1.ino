const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

const int SENSOR_1 = 0;
const int SENSOR_2 = 1;

void setup() {
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);  
}

void loop() {
  int sensor1Value = map(analogRead(SENSOR_1), 0, 200, 10, 0);
  int sensor2Value = map(analogRead(SENSOR_2), 0, 200, 100, 0);
  int displayValue = sensor1Value * sensor2Value;
  Serial.println(displayValue);
  display(displayValue);
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
