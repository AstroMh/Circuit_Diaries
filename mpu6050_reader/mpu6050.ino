#include <Wire.h>
#include <MPU6050_light.h>

MPU6050 mpu(Wire);

void setup() {
  Serial.begin(9600);
  
  // Initialize I2C
  Wire.begin();
  
  Serial.println("Searching for MPU6050...");
  
  // Try to connect to the sensor
  byte status = mpu.begin();
  
  if (status != 0) {
    Serial.print("MPU6050 connection failed. Error code: ");
    Serial.println(status);
    Serial.println("Troubleshooting tips:");
    Serial.println("1. Check if the sensor is powered (LED should be on)");
    Serial.println("2. Try swapping SDA and SCL pins");
    Serial.println("3. Try connecting VCC to 3.3V instead of 5V");
    while (1) {
      delay(10); // Stop here forever
    }
  }
  
  Serial.println("MPU6050 connected successfully!");
  Serial.println("Calibrating... Please keep the sensor still.");
  
  // Calibrate gyroscope and accelerometer
  mpu.calcOffsets();
  
  Serial.println("Calibration complete!");
  Serial.println("Reading sensor data...");
}

void loop() {
  // Update sensor readings
  mpu.update();
  
  // Get accelerometer data (in m/s²)
  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();

  Serial.print(ax);
  Serial.print(",");
  Serial.print(ay);
  Serial.print(",");
  Serial.println(az);
  
  delay(100); // 10 Hz update rate
}