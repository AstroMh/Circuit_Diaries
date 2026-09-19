#include <Wire.h>

#define OV7670_ADDR 0x21

#define WIDTH  32
#define HEIGHT 24

uint8_t frame[WIDTH * HEIGHT];

void setupXCLK() {
  pinMode(9, OUTPUT);

  TCCR1A = _BV(COM1A0);
  TCCR1B = _BV(WGM12) | _BV(CS10);

  // 2 MHz XCLK
  OCR1A = 3;
}

bool writeReg(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(OV7670_ADDR);
  Wire.write(reg);
  Wire.write(value);
  return Wire.endTransmission() == 0;
}

void configureCamera() {
  writeReg(0x12, 0x80);
  delay(200);

  // YUV
  writeReg(0x12, 0x08);

  // Scaling
  writeReg(0x0C, 0x04);
  writeReg(0x3E, 0x1A);

  writeReg(0x70, 0x3A);
  writeReg(0x71, 0x35);
  writeReg(0x72, 0x22);
  writeReg(0x73, 0xF2);
  writeReg(0xA2, 0x02);

  delay(300);
}

inline uint8_t readCameraBus() {
  return (PINC & 0x0F) | (PIND & 0xF0);
}

inline bool href() {
  return PIND & _BV(PD3);
}

inline bool vsync() {
  return PIND & _BV(PD2);
}

bool readCameraByte(uint8_t &value) {

  // Wait PCLK LOW
  while (PINB & _BV(PB4)) {
    if (!href())
      return false;
  }

  // Wait PCLK HIGH
  while (!(PINB & _BV(PB4))) {
    if (!href())
      return false;
  }

  value = readCameraBus();

  // Wait for PCLK LOW
  while (PINB & _BV(PB4)) {
    if (!href())
      break;
  }

  return true;
}

bool captureFrame() {

  uint16_t bufferIndex = 0;

  // Synchronize to new frame
  while (vsync());
  while (!vsync());
  while (vsync());

  uint8_t sourceLine = 0;
  uint8_t savedLine = 0;

  while (savedLine < HEIGHT) {

    while (!href()) {
      if (vsync())
        return false;
    }

    // 120 source rows / 24 = every 5th row
    bool saveThisLine = (sourceLine % 5 == 0);

    uint16_t byteNumber = 0;
    uint8_t savedPixel = 0;

    while (href()) {

      uint8_t value;

      if (!readCameraByte(value))
        break;

      // Raw test showed odd bytes are Y
      if (saveThisLine && (byteNumber & 1)) {

        uint16_t sourcePixel = byteNumber >> 1;

        // Approximately 160 -> 32 pixels
        if ((sourcePixel % 5) == 0) {

          if (savedPixel < WIDTH) {
            frame[bufferIndex++] = value;
            savedPixel++;
          }
        }
      }

      byteNumber++;
    }

    if (saveThisLine) {

      while (savedPixel < WIDTH) {
        frame[bufferIndex++] = 0;
        savedPixel++;
      }

      savedLine++;
    }

    sourceLine++;
  }

  return bufferIndex == WIDTH * HEIGHT;
}

void sendFrame() {

  Serial.write(0xAA);
  Serial.write(0x55);

  Serial.write((uint8_t)WIDTH);
  Serial.write((uint8_t)HEIGHT);

  Serial.write(frame, sizeof(frame));

  Serial.write(0x55);
  Serial.write(0xAA);
}

void setup() {

  Serial.begin(115200);

  setupXCLK();

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(12, INPUT);

  delay(200);

  Wire.begin();
  Wire.setClock(50000);

  configureCamera();

  Serial.println(F("READY"));
}

void loop() {

  if (Serial.available() && Serial.read() == 'C') {

    if (captureFrame()) {
      sendFrame();
    } else {
      Serial.println(F("CAPTURE_FAILED"));
    }
  }
}