import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation
import time
import numpy as np
from collections import deque

SERIAL_PORT = 'COM5'
BAUDRATE = 9600
MAX_POINTS = 50

try:
    ser = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
    print(f"Connected to {SERIAL_PORT}!")
    time.sleep(2)
except serial.SerialException as e:
    print(f"Error opening serial port: {e}")
    print("Make sure:")
    print("  1. The Arduino is plugged in")
    print("  2. The Serial Monitor is CLOSED")
    print("  3. You have the correct port name")
    exit()

x_data = deque(maxlen=MAX_POINTS)
y_data = deque(maxlen=MAX_POINTS)
z_data = deque(maxlen=MAX_POINTS)

plt.style.use('dark_background')
fig, ax = plt.subplots(figsize=(10, 6))
fig.canvas.manager.set_window_title('MPU6050 Live Data')

line_x, = ax.plot([], [], 'r-', label='X', linewidth=2)
line_y, = ax.plot([], [], 'g-', label="Y", linewidth=2)
line_z, = ax.plot([], [], 'b-', label='Z', linewidth=2)

ax.set_xlim(0, MAX_POINTS)
ax.set_ylim(-15, 15)
ax.set_xlabel('Time (samples)')
ax.set_ylabel("Acceleration (m/s²)")
ax.set_title('MPU6050 Real-time Data')
ax.legend()
ax.grid(True, alpha=0.3)


def update(frame):
    try:
        line = ser.readline().decode('utf-8').strip()

        if line:
            values = line.split(',')
            if len(values) == 3:
                try:
                    x = float(values[0])
                    y = float(values[1])
                    z = float(values[2])

                    x_data.append(x)
                    y_data.append(y)
                    z_data.append(z)

                    print(f"X: {x:6.2f}  Y: {y:6.2f}  Z: {z:6.2f}")

                    line_x.set_data(range(len(x_data)), x_data)
                    line_y.set_data(range(len(y_data)), y_data)
                    line_z.set_data(range(len(z_data)), z_data)

                    if len(x_data) > 5:
                        all_data = list(x_data) + list(y_data) + list(z_data)
                        max_val = max(all_data)
                        min_val = min(all_data)
                        margin = max(1.0, (max_val - min_val) * 0.2)
                        ax.set_ylim(min_val - margin, max_val + margin)

                except ValueError:
                    pass

    except serial.SerialException:
        print("Serial connection lost!")
        return line_x, line_y, line_z

    return line_x, line_y, line_z


ani = FuncAnimation(
    fig,
    update,
    interval=50,
    cache_frame_data=False,
    save_count=MAX_POINTS * 2,
    blit=True
)


def on_close(event):
    print("Closing...")
    if ser.is_open:
        ser.close()
        print("Serial port closed")


fig.canvas.mpl_connect('close_event', on_close)

print("\nStarting live plot... Press Ctrl+C to stop")
print("Or close the plot window to exit\n")

try:
    plt.show()
except KeyboardInterrupt:
    print("\nStopped by user")
finally:
    if ser.is_open:
        ser.close()
        print("Serial port closed")
