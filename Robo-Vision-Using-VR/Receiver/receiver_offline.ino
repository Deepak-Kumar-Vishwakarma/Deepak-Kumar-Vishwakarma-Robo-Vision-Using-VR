#include <ESP8266WiFi.h>
#include <espnow.h>
#include <Servo.h>

// Servo objects
Servo servoX, servoY, servoZ;

// Structure to receive data
typedef struct {
  int posX;
  int posY;
  int posZ;
} SensorData;
SensorData receivedData;

// Callback function when data is received
void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&receivedData, incomingData, sizeof(receivedData));

  // Constrain values to prevent servo issues
  receivedData.posX = constrain(receivedData.posX, 10, 170);
  receivedData.posY = constrain(receivedData.posY, 0, 180);
  receivedData.posZ = constrain(receivedData.posZ, 60, 120);

  // Move servos
  servoX.write(receivedData.posX);
  servoY.write(receivedData.posY);
  servoZ.write(receivedData.posZ);

  // Print received values
  Serial.print("📡 Received -> X: "); 
  Serial.print(receivedData.posX);
  Serial.print(" | Y: ");
  Serial.print(receivedData.posY);
  Serial.print(" | Z: "); 
  Serial.println(receivedData.posZ);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Set to station mode
  Serial.println("\n🚀 ESP8266 MAC Address:");
  Serial.println(WiFi.macAddress()); // Print MAC address
  Serial.println("\n🔄 ESP8266 Receiver Starting...");

  // Attach servos to correct pins
  servoX.attach(D7);  // GPIO13
  servoY.attach(D6);  // GPIO12
  servoZ.attach(D5);  // GPIO14

  // Set initial servo positions
  servoX.write(90);
  servoY.write(60);
  servoZ.write(90);

  WiFi.mode(WIFI_STA); // Set device to Station mode

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("❌ ESP-NOW Initialization Failed!");
    return;
  }

  // Register receiver callback function
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("✅ ESP8266 Receiver Ready! Waiting for data...");
}

void loop() {
  // ESP-NOW handles data reception automatically
}



