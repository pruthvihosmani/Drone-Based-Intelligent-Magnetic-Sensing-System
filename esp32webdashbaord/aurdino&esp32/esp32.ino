#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi credentials
const char* ssid = "your_ssid";
const char* password = "your_password";

// Server URL
const char* serverName = "http://your_server_address/receive-data";

// Use hardware serial port 1
HardwareSerial Serial1(1);

void setup() {
  Serial.begin(115200);
  // Initialize Serial1 at the pins used for RX and TX (e.g., RX = 16, TX = 17)
  Serial1.begin(115200, SERIAL_8N1, 16, 17); // Change the pins if necessary

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Check if data is available on Serial1 (connected to Arduino Mega)
  if (Serial1.available()) {
    String dataFromMega = Serial1.readStringUntil('\n');
    sendToServer(dataFromMega);
  }
}

void sendToServer(String data) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    // Create JSON payload
    DynamicJsonDocument jsonDoc(1024);
    jsonDoc["sensorData"] = data;
    String jsonString;
    serializeJson(jsonDoc, jsonString);

    // Send POST request
    int httpResponseCode = http.POST(jsonString);
    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Server response: " + response);
    } else {
      Serial.println("Error in sending POST request");
    }
    http.end();
  }
}
