# ESP32 Environmental Monitor

An ESP32-based embedded systems project for real-time temperature and humidity monitoring using a DHT11 sensor, OLED display, and Wi-Fi web server.

## Features

- ESP32-based embedded controller
- DHT11 temperature & humidity monitoring
- 0.96" I2C OLED display
- Wi-Fi connectivity
- Local web dashboard
- Serial Monitor debugging

## Hardware

- ESP32
- DHT11
- 0.96" SSD1306 OLED
- Jumper wires

## Technologies

- Embedded C/C++
- ESP32
- Arduino IDE
- I2C
- GPIO
- Wi-Fi
- HTTP

## Pin Configuration

| Component | ESP32 |
|---|---|
| DHT11 DATA | GPIO 4 |
| OLED SDA | GPIO 21 |
| OLED SCL | GPIO 22 |
| VCC | 3.3V |
| GND | GND |

## Serial Monitor Output

ESP32 Environmental Monitor

Connecting...
WiFi connected
IP: 192.168.1.105

Temperature: 27.4 C | Humidity: 61.2 %
Temperature: 27.5 C | Humidity: 61.0 %
Temperature: 27.6 C | Humidity: 60.8 %
Temperature: 27.5 C | Humidity: 61.1 %
