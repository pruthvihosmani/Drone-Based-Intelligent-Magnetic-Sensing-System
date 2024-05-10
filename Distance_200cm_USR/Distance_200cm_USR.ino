#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters)

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);  
  delayMicroseconds(2); 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1; // Convert the time into a distance

  // Display the current distance
  Serial.print("Current Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Check if the distance exceeds the maximum threshold
  if (distance > MAX_DISTANCE) {
    Serial.println("Alert: Distance exceeding 2 meters!");
  }

  delay(1000); // Check every second
}
