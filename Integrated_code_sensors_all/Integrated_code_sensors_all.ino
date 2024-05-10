#include <Wire.h>
#include <MPU6050.h>
#include <HMC5883L.h>

// MPU6050 and HMC5883L objects
MPU6050 mpu;
HMC5883L magnetometer;

// Ultrasonic Sensor Pins
#define TRIG_PIN 9
#define ECHO_PIN 10
#define MAX_DISTANCE 200

// Inductive Sensor Pin
#define IND_SENSOR_PIN 2

// Initialize the sensors
void setup() {
  Serial.begin(9600);
  Wire.begin();

  // MPU6050 Setup
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
  }

  // HMC5883L Setup
  magnetometer.initialize();
  if (!magnetometer.testConnection()) {
    Serial.println("HMC5883L connection failed");
  }

  // Ultrasonic Sensor Setup
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inductive Proximity Sensor Setup
  pinMode(IND_SENSOR_PIN, INPUT);
}

void loop() {
  // Read MPU6050
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  Serial.print("MPU6050 Accel/Gyro: ");
  Serial.print("A(");
  Serial.print(ax); Serial.print(",");
  Serial.print(ay); Serial.print(",");
  Serial.print(az); Serial.print(") ");
  Serial.print("G(");
  Serial.print(gx); Serial.print(",");
  Serial.print(gy); Serial.print(",");
  Serial.print(gz); Serial.println(")");

  // Read HMC5883L
  int16_t mx, my, mz;
  magnetometer.getHeading(&mx, &my, &mz);
  Serial.print("HMC5883L Magnetometer: ");
  Serial.print("M(");
  Serial.print(mx); Serial.print(",");
  Serial.print(my); Serial.print(",");
  Serial.print(mz); Serial.println(")");

  // Read Ultrasonic Sensor
  long duration, distance;
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("Ultrasonic Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Read Inductive Proximity Sensor
  int metalDetected = digitalRead(IND_SENSOR_PIN);
  Serial.print("Inductive Sensor: ");
  Serial.println(metalDetected ? "Metal detected!" : "No metal detected.");

  delay(1000); // Delay between readings
}