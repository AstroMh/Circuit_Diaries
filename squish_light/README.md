# SquishLight

Control an LED's brightness by squishing your fingers together. This project demonstrates real-time serial communication between Python and Arduino.

## How It Works

Your webcam captures your hand. Python (using MediaPipe) tracks the distance between your thumb and index finger. This distance is mapped to a brightness value (0-255) and sent over USB to an Arduino, which adjusts the LED's brightness using PWM.

## Hardware

- Arduino Nano (or Uno)
- LED (any color)
- 220Ω resistor
- Jumper wires

### Wiring

| Component | Arduino Pin |
|-----------|-------------|
| LED (Anode, long leg) | Pin 9 (PWM) |
| LED (Cathode, short leg) | GND (via 220Ω resistor) |

> Pin 9 is a PWM pin, which allows analog dimming.

## Software

### Arduino

1. Upload the `SquishLight.ino` sketch to your Arduino.
2. Open the Serial Monitor to confirm the connection.

## What I Learned
- Reading and sending data over serial.
- Mapping sensor values to PWM output.
- Connecting computer vision to physical hardware.

## Next Steps
- Add more LEDs and map each to a different finger.
- Control multiple LEDs based on finger count.
- Use gestures to cycle through colors.
