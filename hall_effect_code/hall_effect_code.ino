int hallPin = 2; // DO pin of the HW484 connected to digital pin 2 of the Arduino
int hallState = 0; // Variable to store the hall sensor status

void setup() {
  pinMode(hallPin, INPUT); // Initialize the hall effect sensor pin as an input
  Serial.begin(9600); // Start serial communication at 9600 bps
}

void loop() {
  hallState = digitalRead(hallPin); // Read the state of the hall effect sensor
  if (hallState == HIGH) {
    Serial.println("Magnetic field detected!"); // Print message if a magnetic field is detected
  } else {
    Serial.println("No magnetic field detected."); // Print message if no magnetic field is detected
  }
  delay(500); // Delay for half a second before the next read
}
