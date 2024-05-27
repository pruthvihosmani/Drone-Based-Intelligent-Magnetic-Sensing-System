#include <Wire.h>
#include <MPU6050.h>
#include <Adafruit_HMC5883_U.h>
#include <ArduinoJson.h>

// MPU6050 and HMC5883L objects
MPU6050 mpu;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200

// Inductive Sensor Pin
#define IND_SENSOR_PIN 2

void setup() {
  Serial.begin(9600);
  Serial1.begin(115200); // Communication with the ESP32
  Wire.begin();

  // MPU6050 Setup
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
  } else {
    Serial.println("MPU6050 connection successful");
  }

  // HMC5883L Setup
  if (!mag.begin()) {
    Serial.println("HMC5883L connection failed");
  } else {
    Serial.println("HMC5883L connection successful");
  }

  // Ultrasonic Sensor Setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inductive Proximity Sensor Setup
  pinMode(IND_SENSOR_PIN, INPUT);
}

void loop() {
  // Create a JSON document
  StaticJsonDocument<256> jsonDoc;

  // Read MPU6050
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  JsonObject accelerometer = jsonDoc.createNestedObject("accelerometer");
  accelerometer["ax"] = ax;
  accelerometer["ay"] = ay;
  accelerometer["az"] = az;

  JsonObject gyroscope = jsonDoc.createNestedObject("gyroscope");
  gyroscope["gx"] = gx;
  gyroscope["gy"] = gy;
  gyroscope["gz"] = gz;

  // Read HMC5883L
  sensors_event_t event;
  mag.getEvent(&event);
  JsonObject magnetometer = jsonDoc.createNestedObject("magnetometer");
  magnetometer["mx"] = event.magnetic.x;
  magnetometer["my"] = event.magnetic.y;
  magnetometer["mz"] = event.magnetic.z;

  // Read Ultrasonic Sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
  JsonObject ultrasonic = jsonDoc.createNestedObject("ultrasonic");
  ultrasonic["distance"] = distance;

  // Read Inductive Proximity Sensor
  int metalDetected = digitalRead(IND_SENSOR_PIN);
  jsonDoc["metallicPresence"] = metalDetected;

  // Serialize JSON to string
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Send JSON string to ESP32 via Serial1
  Serial1.println(jsonString);

  // Also print to Serial Monitor for debuggingh
  Serial.println(jsonString);

  delay(1000); // Delay between readings
}
