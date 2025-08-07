# Deepak-Kumar-Vishwakarma-Robo-Vision-Using-VR


# Robo Vision Using VR

> **Stereo Camera Streaming + Real-Time RC Car Control using ESP32 & WebVR**

![Header](images/header.jpeg)

**Robo Vision Using VR** is a modular robotics and IoT project designed to bring immersive, remote navigation to life using affordable hardware. It combines stereo video streaming using two ESP32-CAM modules with real-time control of a web-operated RC car, all integrated into a mobile VR-compatible interface.

---

## 🧠 Project Highlights

- 📷 Dual ESP32-CAM modules for left/right-eye stereo video
- 🚗 Web-controlled robotic car using ESP32 and L298N motor driver
- 🌐 Real-time communication via WebSockets and HTTP server
- 🥽 VR-compatible side-by-side video for immersive vision
- 🧩 DIY and scalable using low-cost components

---

## 📁 Repository Structure

```
ROBO_VISION_USING_VR/
├── camera(Left)/                      # Left-eye ESP32-CAM firmware
├── camera(Right)/                     # Right-eye ESP32-CAM firmware
├── Esp32_RC_CAR__WEBSERVER_FIX_CODE/  # Web-based RC car controller
├── images/                            # Hardware reference images
```

---

## 🔧 Hardware Components

| Component                        | Image |
|----------------------------------|-------|
| ESP32-CAM Module (x2)            | ![](images/ESP32-CAM-Pinout.webp) |
| ESP32 Dev Board                  | ![](images/ESP32-Pinout.webp) |
| NodeMCU / ESP8266 (Optional)     | ![](images/ESP8266-Pinout-NodeMCU.webp) |
| BO Motors with Wheels            | ![](images/BO%20motor.jpeg) |
| L298N Motor Driver               | ![](images/L298N-Module-Pinout.jpg) |
| Breadboard Power Supply          | ![](images/Breadboard%20power%20supply%20module.jpg) |
| Acrylic Chassis / Zero PCB       | ![](images/Arylic_zero_pcb_board.jpeg) |
| MPU6050 (Optional IMU)           | ![](images/mpu6050.jpeg) |
| 2200mAh / 400mAh Batteries       | ![](images/2200mah.jpeg) ![](images/400mah.jpeg) |
| Full Robot Assembly              | ![](images/Bot.png) |

---

## 🛠️ Setup & Installation

### 1. Flashing the ESP32-CAMs

- Open `CameraWebServer-Left.ino` and `CameraWebServer-Right.ino` using Arduino IDE.
- Replace Wi-Fi SSID and password.
- Flash each to a separate ESP32-CAM (for left and right views).

### 2. Flashing the RC Car Controller

- Navigate to `webserver-RC-Car.ino`.
- Configure motor pins and Wi-Fi credentials.
- Upload to the ESP32 controlling the car via L298N.

### 3. Wiring Overview

- Motor driver to BO motors
- ESP32 to motor driver (L298N)
- Camera boards with onboard camera modules
- Optional: integrate MPU6050 for future expansion

---

## 🖥️ Usage

1. Power on all devices and connect to the same Wi-Fi network.
2. Identify the IP addresses of the ESP32-CAMs and the ESP32 car controller.
3. Access the camera IPs in browser (side-by-side) for VR.
4. Open the RC car controller IP for real-time movement commands.
5. Slot your mobile device into a VR headset (e.g., Google Cardboard) for immersive remote control.

---

## 🧩 System Architecture

![Process Diagram](images/process.png)

---

## 📌 Future Enhancements

- [ ] Merge dual-camera view into a single stereoscopic stream
- [ ] Add depth detection using triangulation
- [ ] Optimize video compression for low-latency transmission
- [ ] Autonomous navigation with obstacle avoidance
- [ ] Central dashboard to monitor all modules

---

## 👤 Author

**[Your Full Name]**  
Embedded Systems & Robotics Developer  
[GitHub](https://github.com/your-username) · [LinkedIn](https://linkedin.com/in/your-profile)

---

## 📜 License

This project is released under the [MIT License](LICENSE).  
Use, modify, and distribute freely with proper attribution.
