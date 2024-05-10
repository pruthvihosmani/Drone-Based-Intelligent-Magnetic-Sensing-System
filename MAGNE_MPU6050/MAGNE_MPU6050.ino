#include <Wire.h>
#include <MPU6050.h>

MPU6050 sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  sensor.initialize();

  if (!sensor.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1); // Loop forever if connection failed
  } else {
    Serial.println("MPU6050 connection successful");
  }
}

void loop() {
  // Read raw data from the MPU-6050
  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  
  sensor.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Print the raw data values to the serial monitor
  Serial.print("Accel X: "); Serial.print(ax); Serial.print(" ");
  Serial.print("Accel Y: "); Serial.print(ay); Serial.print(" ");
  Serial.print("Accel Z: "); Serial.print(az); Serial.print(" ");
  Serial.print("Gyro X: "); Serial.print(gx); Serial.print(" ");
  Serial.print("Gyro Y: "); Serial.print(gy); Serial.print(" ");
  Serial.print("Gyro Z: "); Serial.println(gz);
  
  delay(1000); // Delay for readability
}
