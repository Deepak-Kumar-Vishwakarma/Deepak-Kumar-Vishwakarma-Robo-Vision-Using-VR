#include "esp_camera.h"
#include <WiFi.h>
#include <WebServer.h>
#include "Arduino.h"
#include "soc/rtc.h"

// ===================
// Select camera model
// ===================
#define CAMERA_MODEL_AI_THINKER // Has PSRAM
#include "camera_pins.h"

// ===========================
// Enter your WiFi credentials
// ===========================
const char *ssid = "OPPO K10 5G";
const char *password = "hellosir1@34567890";

// Define Static IP settings
IPAddress local_IP(192, 168, 204, 101); // Set your desired static IP
IPAddress gateway(192, 168, 204, 28);   // Set your router's gateway
IPAddress subnet(255, 255, 255, 0);     // Set subnet mask
IPAddress primaryDNS(192, 168, 204, 28);
IPAddress secondaryDNS(0, 0, 0, 0);

WebServer server(80);

void handleJPGSstream();
void handleJPG();
void handleNotFound();

void handleJPGSstream() {
  WiFiClient client = server.client();
  String response = "HTTP/1.1 200 OK\r\n";
  response += "Content-Type: multipart/x-mixed-replace; boundary=frame\r\n";
  response += "Connection: Keep-Alive\r\n";
  response += "\r\n";
  client.print(response);

  while (client.connected()) {
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Camera capture failed");
      break;
    }
    client.print("--frame\r\n");
    client.print("Content-Type: image/jpeg\r\n\r\n");
    client.write((const char *)fb->buf, fb->len);
    client.print("\r\n");
    esp_camera_fb_return(fb);
    delay(10); // Reduced delay for faster streaming
  }
}

void handleJPG() {
  camera_fb_t *fb = esp_camera_fb_get();
  if (!fb) {
    server.send(500, "text/plain", "Camera capture failed");
    return;
  }
  server.send_P(200, "image/jpeg", (const char *)fb->buf, fb->len);
  esp_camera_fb_return(fb);
}

void handleNotFound() {
  server.send(404, "text/plain", "Not Found");
}

void setup() {
  Serial.begin(115200);
  setCpuFrequencyMhz(240); // Increase CPU speed
  Serial.setDebugOutput(true);
  Serial.println();

  // Check if PSRAM is available
  if (!psramFound()) {
    Serial.println("PSRAM not found! Lowering resolution...");
  }

  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sccb_sda = SIOD_GPIO_NUM;
  config.pin_sccb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 8000000;
  
  config.frame_size = FRAMESIZE_HD; // Lower resolution for speed (320x240)
  config.pixel_format = PIXFORMAT_JPEG; // Use JPEG for streaming
  config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
  config.fb_location = psramFound() ? CAMERA_FB_IN_PSRAM : CAMERA_FB_IN_DRAM; // Use PSRAM if available
  config.jpeg_quality = 10; // Lower quality = faster processing
  config.fb_count = 3; // More buffers for better performance

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }

  
  // Flash LED always ON (non-PWM)
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  Serial.println("🚨 Flash LED turned ON (non-PWM mode)");



  sensor_t *s = esp_camera_sensor_get();

  

  if (s->id.PID == OV3660_PID) {
    s->set_gainceiling(s, (gainceiling_t)1); 
    s->set_awb_gain(s, 0);
    s->set_brightness(s, 1);
    s->set_saturation(s, 1);
    s->set_contrast(s, 2);
    s->set_sharpness(s, 2);
    s->set_hmirror(s, 0);
    s->set_vflip(s, 0);
    s->set_awb_gain(s, 0);  // Disable Auto White Balance
    s->set_whitebal(s, 0);  // Disable White Balance
    s->set_exposure_ctrl(s, 0);  // Disable Auto Exposure
    s->set_aec2(s, 0);  // Disable advanced exposure control
    s->set_aec_value(s, 300);  // Adjust exposure manually (try 200-500)
    s->set_agc_gain(s, 1);  // Reduce sensor gain
    s->set_lenc(s, 1);  // Enable lens correction
    s->set_denoise(s, 1);  // Enable denoising filter

  }

  // Configure static IP
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("⚠️ Failed to configure Static IP. Retrying...");
  }


  WiFi.begin(ssid, password);
  WiFi.setSleep(false);

  Serial.print("WiFi connecting");
  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 20) {
    delay(500);
    Serial.print(".");
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected");
  } else {
    Serial.println("\n❌ WiFi connection failed. Check credentials or signal strength.");
  }

  server.on("/mjpeg/1", HTTP_GET, handleJPGSstream);
  server.on("/jpg", HTTP_GET, handleJPG);
  server.onNotFound(handleNotFound);
  server.begin();

  Serial.print("📸 Camera Ready! View stream at: http://");
  Serial.print(WiFi.localIP());
  Serial.println("/mjpeg/1");
}

void loop() {
  server.handleClient();
  delay(10);
}