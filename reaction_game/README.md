# Two-Player Reaction Time Game 🎮

A fun, interactive Arduino-based reaction time game for two players! Test your reflexes by pressing your button at the right time - but be careful not to jump the gun!

## 🎯 How It Works

The game simulates a traffic light sequence:
1. **🔴 RED LIGHT** - 1 second wait (no pressing allowed!)
2. **🟡 YELLOW LIGHT** - Random delay (0-10 seconds) to keep players guessing
3. **🟢 GREEN LIGHT** - GO! Press your button as fast as you can!

## 🎮 Game Rules

- **Early Press**: If you press your button during RED or YELLOW phases, you get a penalty (RED LED flashes and buzzer sounds)
- **Perfect Press**: Press during the GREEN phase to win! 
- **Winner**: The first player to press their button during the GREEN phase wins with a victory jingle

## 🎵 Sound Effects

| Phase | Tone | Duration |
|-------|------|----------|
| RED Light | 500 Hz | 150 ms |
| YELLOW Light | 750 Hz | 150 ms |
| GREEN Light | 1000 Hz | 300 ms |
| Penalty (Early Press) | 300 Hz | 500 ms |
| Player 1 Victory | 988, 1319, 1568 Hz | Various |
| Player 2 Victory | 880, 1175, 1397 Hz | Various |

## 📦 Components Needed

| Component | Quantity | Pin Connections |
|-----------|----------|-----------------|
| Arduino Uno/Nano | 1 | - |
| LEDs (Green) | 3 | Pins 7, 12 |
| LEDs (Yellow) | 1 | Pin 11 |
| LEDs (Red) | 3 | Pins 2, 6, 10 |
| Push Buttons | 2 | Pins 4, 13 |
| Piezo Buzzer | 1 | Pin 8 |
| Resistors (220Ω) | 6 | For LEDs |
| Resistors (10kΩ) | 2 | For buttons (pull-down) |
| Breadboard | 1 | - |
| Jumper Wires | Several | - |

## 🔌 Pin Mapping

| Component | Pin |
|-----------|-----|
| Main Green LED | 12 |
| Main Yellow LED | 11 |
| Main Red LED | 10 |
| Buzzer | 8 |
| Player 1 Button | 4 |
| Player 1 Green LED | 7 |
| Player 1 Red LED | 6 |
| Player 2 Button | 13 |
| Player 2 Green LED | 3 |
| Player 2 Red LED | 2 |

## 🛠️ Circuit Setup

The complete breadboard layout and circuit schematics are available in this folder.

### What's Included:
- **Breadboard Layout** - Visual diagram showing component placement
- **Circuit Schematic** - Professional electronic schematic (available as `.brd` file)

### Quick Wiring Reference:
1. **LEDs**: Connect all LEDs through 220Ω resistors to their respective pins
2. **Buttons**: Connect one leg to ground, the other to the pin with a 10kΩ pull-down resistor
3. **Buzzer**: Connect positive leg to pin 8, negative to ground
4. **Power**: Ensure all components share a common ground
