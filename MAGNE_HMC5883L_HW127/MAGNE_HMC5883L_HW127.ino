#include <Wire.h>

// I2C address of the HMC5883L
#define HMC5883L_Address 0x1E

// Offsets applied to raw x, y, z values
int xOffset = 0, yOffset = 0, zOffset = 0;

// Function to read data from HMC5883L
void readMagnetometer(int &x, int &y, int &z) {
  Wire.beginTransmission(HMC5883L_Address);
  Wire.write(0x03); // Start reading from register 3
  Wire.endTransmission();

  Wire.requestFrom(HMC5883L_Address, 6);
  if (6 <= Wire.available()) {
    x = Wire.read() << 8; // X msb
    x |= Wire.read();     // X lsb
    z = Wire.read() << 8; // Z msb
    z |= Wire.read();     // Z lsb
    y = Wire.read() << 8; // Y msb
    y |= Wire.read();     // Y lsb
    x -= xOffset;
    y -= yOffset;
    z -= zOffset;
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();

  // Setup configuration register A
  // Average 8 samples, 15 Hz data output rate, normal measurement
  Wire.beginTransmission(HMC5883L_Address);
  Wire.write(0x00); // Select register
  Wire.write(0x70); // Write register value
  Wire.endTransmission();

  // Setup configuration register B (gain)
  Wire.beginTransmission(HMC5883L_Address);
  Wire.write(0x01); // Select register
  Wire.write(0xA0); // Gain = 5
  Wire.endTransmission();

  // Set mode register to continuous measurement mode
  Wire.beginTransmission(HMC5883L_Address);
  Wire.write(0x02); // Select register
  Wire.write(0x00); // Continuous measurement mode
  Wire.endTransmission();
}

void loop() {
  int x, y, z;
  readMagnetometer(x, y, z);
  
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(", Y: ");
  Serial.print(y);
  Serial.print(", Z: ");
  Serial.print(z);
  Serial.println();

  delay(500); // Update every half-second
}
