#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

// Structure to send data
typedef struct {
  int posX;
  int posY;
  int posZ;
} SensorData;
SensorData sensorData;

// Receiver MAC Address
uint8_t receiverMAC[] = {0x8C, 0x4F, 0x00, 0xE0, 0x53, 0x98};

// For smoothing Z rotation
float smoothedZ = 60;  // Start from mid-point

// ESP-NOW send callback
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.println(sendStatus == 0 ? "✅ Data Sent!" : "❌ Send Failed");
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // Initialize MPU6050
  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("❌ MPU6050 Connection Failed!");
    while (1);
  }
  Serial.println("✅ MPU6050 Ready!");

  // Set ESP8266 to Station mode
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("❌ ESP-NOW Initialization Failed!");
    return;
  }

  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(receiverMAC, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

  Serial.println("🚀 Transmitter Ready!");
}

void loop() {
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read accelerometer and gyroscope data
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Map X/Y tilt using accelerometer
  int mappedX = map(ax, -17000, 17000, 10, 170);
  int mappedY = map(ay, -17000, 17000, 0, 180);

  // Map Z rotation using gyroscope (slower motion)
  int rawZ = map(gz, -12000, 12000, 0, 180);  // Wider input range = slower response

  // Smooth Z with exponential filter
  float alpha = 0.1;  // Smoothing factor (0.05–0.2)
  smoothedZ = (alpha * rawZ) + ((1 - alpha) * smoothedZ);

  // Constrain values
  sensorData.posX = constrain(mappedX, 10, 170);
  sensorData.posY = constrain(mappedY, 0, 180);
  sensorData.posZ = constrain((int)smoothedZ, 0, 180);

  // Send via ESP-NOW
  esp_now_send(receiverMAC, (uint8_t *)&sensorData, sizeof(sensorData));

  // Debug output
  Serial.printf("📡 Sent -> X: %d | Y: %d | Z (smooth): %d\n",
                sensorData.posX, sensorData.posY, sensorData.posZ);

  delay(50);  // Lower delay for smoother updates
}
