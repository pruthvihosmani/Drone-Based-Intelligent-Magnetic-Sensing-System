#include <SoftwareSerial.h>
SoftwareSerial gsm(10, 11); // RX, TX

#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200

void setup() {
  gsm.begin(9600);
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  delay(10000); // Allow time for GSM modem to initialize
  gsm.println("AT"); // Check if GSM modem is working
  delay(1000);
  gsm.println("AT+CMGF=1"); // Set GSM to SMS mode
  delay(1000);
}

void loop() {
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration/2) / 29.1;

  if (distance > MAX_DISTANCE) {
    sendSMS(distance);
  }

  delay(1000);
}

void sendSMS(float distance) {
  gsm.println("AT+CMGS=\"+1234567890\""); // Replace with your phone number
  delay(1000);
  gsm.print("Alert: Distance exceeding 2 meters: ");
  gsm.print(distance);
  gsm.println(" cm");
  delay(1000);
  gsm.write(26); // ASCII code for CTRL+Z
}
