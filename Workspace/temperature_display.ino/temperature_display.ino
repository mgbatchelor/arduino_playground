// Binary Temperature Display

const int temperaturePin = 0;
const int alertSensorPin = 1;

const int datapin = 2; 
const int clockpin = 3;
const int latchpin = 4;

const int buzzerPin = 9;

const int measureDuration = 10000;
const int measureReadings = 20;

void setup() {
  pinMode(datapin, OUTPUT);
  pinMode(clockpin, OUTPUT);  
  pinMode(latchpin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  int temperature = normalizedTemperature(measureDuration, measureReadings);
  displayTemperature(temperature);
  alertTemperature(temperature);
}

float normalizedTemperature(int period, int readings) {
  float total = 0;
  for(int i = 0; i < readings; i++) {
    total += readTemperature();
    delay(period / readings);
  }
  return total / readings;
}

float readTemperature() {
  return ((getVoltage(temperaturePin) - 0.5) * 100.0) * (9.0/5.0) + 32.0;
}

float getVoltage(int pin) {
  return (analogRead(pin) * 0.004882814);
}

void displayTemperature(float temperature) {
  Serial.print("temperature: ");
  Serial.println(temperature);
  
  shiftOut(datapin, clockpin, MSBFIRST, (int) temperature);
  
  digitalWrite(latchpin, HIGH);
  digitalWrite(latchpin, LOW);
}

void alertTemperature(float temperature) {
  float alertLevel = getAlertLevel();
  Serial.print("Alert level: ");
  Serial.println(alertLevel);
  if (temperature >= alertLevel) {
    tone(buzzerPin, 500, 100);
  }
}


float getAlertLevel() {
  return (analogRead(alertSensorPin) / 1023.0) * 100.0;
}

