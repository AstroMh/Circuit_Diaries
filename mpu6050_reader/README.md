# MPU6050 Real-Time Data Logger

Arduino + Python project that reads acceleration data from an MPU6050 sensor and visualizes it in real-time.

## Hardware
- Arduino Uno
- MPU6050 (GY-521 module)
- Jumper wires

### Wiring
| MPU6050 | Arduino Uno |
|---------|-------------|
| VCC     | 5V          |
| GND     | GND         |
| SCL     | A5          |
| SDA     | A4          |

## Arduino Setup
1. Install `MPU6050_light` library via Arduino Library Manager
2. Upload `arduino/mpu6050_reader.ino`
3. Open Serial Monitor at 9600 baud to verify data

## Features
- Real-time 3-axis acceleration plotting
- CSV data logging
- Console output with formatted values
- Auto-scaling graph

---

## Note:

This project does include any circuit schematics or ".brd" file. You just need to connect a simple mpu6050 to the arduino and that's it!
