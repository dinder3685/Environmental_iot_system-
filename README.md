# IoT Healthcare Environmental Monitoring System

![Project Banner](https://img.shields.io/badge/Platform-ESP32-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![IoT](https://img.shields.io/badge/IoT-Healthcare-blue?style=for-the-badge)
![BLE](https://img.shields.io/badge/Protocol-BLE_5.0-0082FC?style=for-the-badge)

A real-time environmental monitoring system using ESP32-WROOM-32 with I2C sensors, implementing data filtering and BLE 5.0 transmission for healthcare applications.

## Key Features

- **Multi-sensor Interface**: 
  - BME280 (Humidity)
  - BMP280 (Pressure)
  - HTU21D (Temperature)
- **Real-time Processing**:
  - 1Hz sampling with moving median filter
  - Circular buffer storage (30 samples)
- **Wireless Transmission**:
  - BLE 5.0 GATT Server
  - JSON-encoded statistical summaries every 30s
- **Comprehensive Metrics**:
  - Min/Max/Median/StdDev for all parameters

## Hardware Architecture

![Hardware Block Diagram](docs/hardware_diagram.png) *(Replace with your actual diagram)*

### Components
| Component | Specification |
|-----------|--------------|
| MCU | ESP32-WROOM-32 (Dual-core 240MHz) |
| Sensors | BME280 (0x76), BMP280 (0x77), HTU21D (0x40) |
| Communication | BLE 5.0 (Integrated) |

### Connections
```plaintext
ESP32 Pin   → Sensor Connection
-------------------------------
GPIO21 (SDA) → SDA (All Sensors)
GPIO22 (SCL) → SCL (All Sensors)
3.3V        → VCC (All Sensors)
GND         → GND (All Sensors)
Software Implementation
System Flow
mermaid
Copy
graph TD
    A[Initialize MCU] --> B[Read Sensors]
    B --> C[Apply Median Filter]
    C --> D[Store in Circular Buffer]
    D --> E{30s Interval?}
    E -->|Yes| F[Calculate Statistics]
    E -->|No| B
    F --> G[Send BLE Packet]
    G --> B
Code Structure
Copy
src/
├── main.ino              # Main program loop
├── sensor_interface.h    # I2C sensor communication
├── filtering.h           # Moving median filter
├── circular_buffer.h     # FIFO data storage
├── statistics.h          # Statistical calculations
└── ble_handler.h         # BLE configuration & transmission
Getting Started
Prerequisites
Arduino IDE with ESP32 Board Package

Physical Components:

ESP32-WROOM-32

BME280, BMP280, HTU21D sensors

Breadboard & jumper wires

Installation
Clone the repository:

bash
Copy
git clone https://github.com/yourusername/iot-healthcare-monitoring.git
Open main.ino in Arduino IDE

Install required libraries:

Wire.h (I2C)

ESP32 BLE libraries

Flash to ESP32

Example Output
json
Copy
{
  "temperature": {
    "min": 22.5,
    "max": 23.1,
    "median": 22.8,
    "stddev": 0.2
  },
  "pressure": {
    "min": 1013.25,
    "max": 1015.01,
    "median": 1014.0
  },
  "humidity": {
    "min": 30.2,
    "max": 35.8,
    "median": 32.5
  }
}
Testing & Validation
Sensor Simulation: Returns -1.0 if sensors fail

BLE Verification: Use nRF Connect app (UUIDs in system_config.h)

Debugging:

Serial monitor for I2C errors

Buffer state monitoring

Performance Metrics
Metric	Value
Sampling Rate	1Hz (strict)
BLE Latency	<50ms
Processing Time	<10ms per sample
Future Improvements
Add WiFi fallback communication

Implement OTA updates

Power optimization for battery operation

Mobile app dashboard

References
BME280 Datasheet

ESP32 BLE Documentation
