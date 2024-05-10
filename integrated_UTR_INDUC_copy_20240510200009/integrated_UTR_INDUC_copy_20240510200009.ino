#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200
#define IND_SENSOR_PIN 2 // Inductive sensor connected to digital pin 2

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IND_SENSOR_PIN, INPUT);
}

void loop() {
  // Ultrasonic sensor measurement
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;

  // Display the distance
  Serial.print("Current Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the distance exceeds the maximum threshold
  if (distance > MAX_DISTANCE) {
    Serial.println("Alert: Distance exceeding 2 meters!");
  }

  // Inductive sensor check
  int metalDetected = digitalRead(IND_SENSOR_PIN);
  if (metalDetected == HIGH) {
    Serial.println("Metal detected!");
  } else {
    Serial.println("No metal detected.");
  }

  delay(1000); // Delay between reads for stability
}
