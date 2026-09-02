import cv2
import mediapipe as mp
import numpy as np
import math
import time
import serial

SERIAL_PORT = 'COM9'
BAUDRATE = 9600
LED_PIN = 11

try:
    print(f"[!] Trying to connect to {SERIAL_PORT}...")
    arduino = serial.Serial(SERIAL_PORT, BAUDRATE, timeout=1)
    print(f"[+] Connected to {SERIAL_PORT}")
    time.sleep(2)
except serial.SerialException as e:
    print(f"[-] Could not connect to {SERIAL_PORT}!")
    exit()

mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    static_image_mode=False,
    model_complexity=1,
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7
)
mp_draw = mp.solutions.drawing_utils

cap = cv2.VideoCapture(1)
print("Starting hand tracking. Close the camera window to exit.")

while True:
    success, frame = cap.read()
    if not success:
        break

    frame = cv2.flip(frame, 1)
    rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    results = hands.process(rgb_frame)

    brightness_value = 0

    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

            h, w, _ = frame.shape
            thumb_tip = hand_landmarks.landmark[mp_hands.HandLandmark.THUMB_TIP]
            index_tip = hand_landmarks.landmark[mp_hands.HandLandmark.INDEX_FINGER_TIP]

            x1, y1 = int(thumb_tip.x * w), int(thumb_tip.y * h)
            x2, y2 = int(index_tip.x * w), int(index_tip.y * h)

            distance_px = math.hypot(x2-x1, y2-y1)

            cv2.circle(frame, (x1, y1), 7, (0, 255, 0), cv2.FILLED)
            cv2.circle(frame, (x2, y2), 7, (0, 255, 0), cv2.FILLED)
            cv2.line(frame, (x1, y1), (x2, y2), (0, 255, 0), 3)

            min_distance = 20
            max_disnatce = 200
            brightness_value = int(np.interp(distance_px, [min_distance, max_disnatce], [0, 255]))
            brightness_value = max(0, min(255, brightness_value))

            cv2.putText(frame, f'Brightness: {brightness_value}', (10, 30),
                       cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

            cv2.putText(frame, f'Distance: {distance_px:.1f} px', (10, 70),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.7, (255, 255, 0), 2)

            arduino.write(f"{brightness_value}\n".encode())

    else:
        pass

    cv2.imshow("Squish Light (Hand gesture brightness control)", frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break


cap.release()
cv2.destroyAllWindows()
arduino.close()
print("Program finished and serial port closed.")