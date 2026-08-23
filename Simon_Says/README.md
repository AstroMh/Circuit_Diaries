# 🎮 Arduino Memory Game (Simon Says)

A classic Simon Says memory game built with Arduino, LEDs, buttons, and a buzzer. Test your memory by repeating randomly generated sequences that grow longer each round!

---

## 📝 Description

This project is an Arduino-based memory game where:
- **3 LEDs** (Red, Green, Yellow) flash in a random sequence
- **3 Buttons** allow the player to repeat the sequence
- Each correct round adds **2 more steps** to the sequence
- Wrong input resets the player's progress and replays the same sequence
- A **buzzer** provides sound feedback for each action
- A **new random pattern** is generated every time the Arduino resets

---

## ✨ Features

- ✅ **Random Sequences** - Different pattern every reset using `randomSeed()`
- ✅ **Progressive Difficulty** - Sequence grows by +2 after each correct round
- ✅ **Sound Feedback** - Unique tones for each color and action
- ✅ **Visual Feedback** - LED flashes for correct, all blink for wrong
- ✅ **Error Handling** - Wrong input resets progress and replays sequence
- ✅ **Victory Celebration** - Special melody and LED show when round is complete
- ✅ **Debounced Buttons** - Reliable input reading with proper debouncing

---

## 🔧 Hardware Requirements

| Component | Quantity | Pins Used |
|-----------|----------|-----------|
| Arduino Uno/Nano | 1 | - |
| Red LED | 1 | Pin 10 |
| Green LED | 1 | Pin 9 |
| Yellow LED | 1 | Pin 8 |
| Push Buttons | 3 | Pins 2, 3, 4 |
| Buzzer (Passive) | 1 | Pin 7 |
| Resistors (220Ω) | 3 | For LEDs |
| Breadboard | 1 | - |
| Jumper Wires | Several | - |

---

## 🎵 Sound Guide

| Action | Sound | Frequency | Duration |
|--------|-------|-----------|----------|
| Red Button | Low Tone | 262 Hz (C4) | 150ms |
| Green Button | Middle Tone | 330 Hz (E4) | 150ms |
| Yellow Button | High Tone | 392 Hz (G4) | 150ms |
| Wrong Input | Descending Buzz | 300→200 Hz | 200ms each |
| Round Complete | Victory Melody | 523→659→784 Hz | 150-200ms |
| Game Start | Startup Jingle | 392→523→659 Hz | 100-150ms |

---

## 🚀 How to Play

1. **Upload the code** to your Arduino
2. **Watch the sequence** - LEDs will flash in random order with sounds
3. **Repeat the pattern** - Press the buttons in the same order
4. **Correct** - LED flashes, and you continue to the next step
5. **Complete round** - Victory sound plays, and the sequence grows by 2
6. **Wrong** - Error sound plays, pattern resets, and replays
7. **Reset** - Press the reset button on Arduino for a completely new pattern
