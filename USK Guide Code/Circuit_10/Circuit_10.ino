
const int motorPin1 = 9;
const int motorPin2 = 10;

void setup()
{
  // Set up the motor pin to be an output:
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Set up the serial port:
  Serial.begin(9600);
}


void loop()
{
  digitalWrite(motorPin1, 1);
  digitalWrite(motorPin2, 1);
  delay(500);
  digitalWrite(motorPin1, 0);
  delay(500);
  digitalWrite(motorPin2, 0);
  digitalWrite(motorPin1, 1);
  delay(500);
}

