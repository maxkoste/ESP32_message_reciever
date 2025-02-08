# **ESP32 WebSocket Display Project**  

## **Overview**  
This project connects an **ESP32 microcontroller** to a **WebSocket server**, enabling real-time communication between a client (e.g., a web app) and the ESP32. Received messages are displayed on an **SSD1306 OLED screen**.  

## **Features**  
✅ Connects to a WebSocket server to receive messages  

✅ Displays received messages on an **SSD1306 OLED screen**  

✅ Uses **PlatformIO** for easy development, package managment and deployment  

## **Project Structure**  

```
ESP32_WebSocket_Display/
│── src/
│   ├── main.cpp          # ESP32 firmware (main source code)
│── platformio.ini        # PlatformIO configuration file
│── README.md             # Documentation
```

## **Hardware Requirements**  
- **ESP32** development board
- **SSD1306 OLED display** (I2C)  
- **WiFi network**  

## **Software Requirements**  
📦 **Install the following:**  
- [**PlatformIO**](https://platformio.org/install) (for ESP32 development)  
- **Arduino framework** (included in PlatformIO)  
- **WebSocketsClient library** (for ESP32 communication)  
- **Adafruit SSD1306 library** (for OLED display)  

## **Setup & Installation**  

1. **Clone the repository:**  
   ```sh
   git clone https://github.com/maxkoste/ESP32_display_project.git
   cd ESP32_display_project

2. **Install dependencies using PlatformIO:**

```sh
  pio pkg install
