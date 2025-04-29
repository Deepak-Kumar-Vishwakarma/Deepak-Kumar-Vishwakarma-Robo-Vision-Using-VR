#include <WiFi.h>
#include "BluetoothSerial.h"

// Wi-Fi Credentials
const char* ssid = "OPPO K10 5G";
const char* password = "hellosir1@34567890";

// Static IP Configuration for ESP32-Eye
IPAddress local_IP(192,168,204,24);
IPAddress gateway(192,168,204,1);
IPAddress subnet(255,255,255,0);

// ESP32-CAM IP Addresses
const char* esp32Cam1 = "192.168.204.100";
const char* esp32Cam2 = "192.168.204.101";

WiFiServer server(80);
BluetoothSerial SerialBT;

#define ENA 32
#define ENB 33
#define IN1 25
#define IN2 26
#define IN3 27
#define IN4 14

const char htmlHeader[] PROGMEM = 
  "<!DOCTYPE html><html><head><meta charset='utf-8'><title>ESP32 VR Eyes</title><style>"
  "body { background-color: #0A122A; color: #DF7401; text-align: center; font-family: Arial; }</style></head>"
  "<body><h1>ESP32 VR Eyes</h1>";

const char htmlFooter[] PROGMEM = 
  "</body></html>";

void setup() {
  Serial.begin(115200);
  delay(100);
  SerialBT.begin("ESP32_RC_Car");

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.println("\n🔵 Starting ESP32-Eye Web Server...");

  if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("⚠ Failed to configure Static IP!");
  }

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ Connected to Wi-Fi!");
  Serial.print("📌 Web Server running at: http://");
  Serial.println(WiFi.localIP());

  server.begin();
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 150);
  analogWrite(ENB, 150);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.println(command);

    if (command == 'F') {
      moveForward();
    } else if (command == 'B') {
      moveBackward();
    } else if (command == 'L') {
      turnLeft();
    } else if (command == 'R') {
      turnRight();
    } else if (command == 'S') {
      stopCar();
    }
  }

  WiFiClient client = server.available();

  if (client) {
    Serial.println("🔵 New Client Connected!");
    String header = "";
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        header += c;

        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type: text/html");
            client.println("Connection: close");
            client.println();

            client.println(htmlHeader);

            // ✅ Centered Left Eye and Right Eye view using inline HTML
            client.println("<div style='display: flex; justify-content: center; gap: 50px; flex-wrap: wrap; align-items: center;'>");

            client.println("  <div style='text-align: center;'>");
            client.println("    <h2>Left Eye</h2>");
            client.println("    <img src='http://" + String(esp32Cam1) + "/mjpeg/1' alt='ESP32-CAM Stream' width='430'>");
            client.println("  </div>");

            client.println("  <div style='text-align: center;'>");
            client.println("    <h2>Right Eye</h2>");
            client.println("    <img src='http://" + String(esp32Cam2) + "/mjpeg/1' alt='ESP32-CAM Stream' width='430'>");
            client.println("  </div>");

            client.println("</div>");

            client.println(htmlFooter);
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    client.flush();
    client.stop();
    Serial.println("🔴 Client Disconnected.");
  }
}
