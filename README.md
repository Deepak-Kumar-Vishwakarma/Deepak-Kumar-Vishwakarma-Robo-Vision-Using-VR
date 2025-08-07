![ESP32-CAM-Pinout](https://github.com/user-attachments/assets/88faf127-0043-4b80-860b-3f3f25ac220f)# Robo Vision Using VR

> **Stereo Camera Streaming + Real-Time RC Car Control using ESP32 & WebVR**
![WhatsApp Image 2025-04-16 at 18 20 54_e92ca4d4](https://github.com/user-attachments/assets/e84c398d-6426-4607-a6a6-ea2a9f8537f9)

![WhatsApp Image 2025-04-16 at 18 24 26_75749c7a](https://github.com/user-attachments/assets/044c3526-5e52-4688-b8ce-499985c37415)

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
|----------------------------------|-----------------------------------------------------------|
| ESP32-CAM Module (x2)            | ![ESP32-CAM-Pinout](https://github.com/user-attachments/assets/0d6efa9d-159f-4172-b57a-e33f567da4f6)                                       |
| ESP32 Dev Board                  | ![ESP32-Pinout](https://github.com/user-attachments/assets/38f957c2-c6dd-4365-911c-f0a8f9cffda1)                                       |
| NodeMCU / ESP8266 (Optional)     | ![ESP8266-Pinout-NodeMCU](https://github.com/user-attachments/assets/65f9d79a-0cea-4532-9dd0-6462e22f2423)                                       |
| BO Motors with Wheels            | ![BO motor](https://github.com/user-attachments/assets/d507746c-9254-4f72-b7ed-d205bc06a631)                                       |
| L298N Motor Driver               | ![L298N-Module-Pinout](https://github.com/user-attachments/assets/4e2ee618-8595-4109-bbbd-bf6a8d1b39a9)                                       |
| Breadboard Power Supply          | ![Breadboard power supply module](https://github.com/user-attachments/assets/4e8fb44e-d0af-4feb-90be-e0b8ac264794)                                       |
| Acrylic Chassis / Zero PCB       | ![Arylic_zero_pcb_board](https://github.com/user-attachments/assets/8b4e5d7f-dcf8-4546-8a22-e533c729badb)                                       |
| MPU6050 (Optional IMU)           | ![mpu6050](https://github.com/user-attachments/assets/a7eb9b46-e155-4b18-a962-728e567822e0)                                       |
| 2200mAh / 400mAh Batteries       | ![400mah](https://github.com/user-attachments/assets/8b78dca5-318f-48b6-8828-6c3abc4dd083)
                                     ![2200mah](https://github.com/user-attachments/assets/560e1c3d-ecaa-44b4-b4dc-0c3b091f98ee)                                       |
| Full Robot Assembly              | <img width="1536" height="1024" alt="process" src="https://github.com/user-attachments/assets/0a0313fe-e93c-4b4a-8877-e4af83976d6a" />  
                                     <img width="1447" height="1570" alt="Bot" src="https://github.com/user-attachments/assets/8e7ccd6b-905c-4580-b649-7f6fefb7f5f7" />       |

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

![Process Diagram]

<img width="1536" height="1024" alt="process" src="https://github.com/user-attachments/assets/c8e36051-d46b-4ded-820f-01e560f5c933" />

![Mac address](https://github.com/user-attachments/assets/7014fb23-9748-44d9-aa95-608dc8b34db1)


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
