int sensorPin = 2; // Connect the sensor output to digital pin 2
int sensorState = 0; // Variable for reading the sensor status

void setup() {
  pinMode(sensorPin, INPUT);
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
  sensorState = digitalRead(sensorPin); // Read the state of the sensor value

  if (sensorState == HIGH) {
    Serial.println("Metal detected!");
  } else {
    Serial.println("No metal detected.");
  }

  delay(500); // Delay a half-second before the next read
}
