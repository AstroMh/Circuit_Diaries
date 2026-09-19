import serial
import time
from PIL import Image

PORT = "COM5"  # CHANGE THIS
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=10)

time.sleep(2)
ser.reset_input_buffer()

print("Requesting frame...")
ser.write(b"C")

previous = None

while True:
    current = ser.read(1)

    if not current:
        raise RuntimeError("Timed out waiting for frame")

    value = current[0]

    if previous == 0xAA and value == 0x55:
        break

    previous = value

print("Frame header found")

width = ser.read(1)[0]
height = ser.read(1)[0]

print("Image size:", width, "x", height)

expected = width * height
pixels = ser.read(expected)

print("Received:", len(pixels), "/", expected)

if len(pixels) != expected:
    raise RuntimeError("Incomplete frame")

image = Image.frombytes("L", (width, height), pixels)

image = image.resize(
    (width * 15, height * 15),
    Image.Resampling.NEAREST
)

image.save("ov7670_test.png")
image.show()

print("Saved ov7670_test.png")

ser.close()