const int greenPin = 12;
const int yellowPin = 11;
const int redPin = 10;
const int buzzerPin = 8;

// Player 1
const int player1Green = 7;
const int player1Red = 6;
const int player1Button = 4;

// Player 2
const int player2Button = 13;
const int player2Green = 3;
const int player2Red = 2;

long randNumber;
bool player1Pressed = false;
bool player2Pressed = false;

void setup() {
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Player 1
  pinMode(player1Green, OUTPUT);
  pinMode(player1Red, OUTPUT);
  pinMode(player1Button, INPUT);

  // Player 2
  pinMode(player2Green, OUTPUT);
  pinMode(player2Red, OUTPUT);
  pinMode(player2Button, INPUT);

  randomSeed(analogRead(A0));
  
  // Reset player LEDs at start
  digitalWrite(player1Green, LOW);
  digitalWrite(player1Red, LOW);
  digitalWrite(player2Green, LOW);
  digitalWrite(player2Red, LOW);
}

void loop() {
  randNumber = random(15000);
  player1Pressed = false;
  player2Pressed = false;

  // Turn off all main LEDs
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  
  // --- RED LIGHT PHASE (1 second) ---
  digitalWrite(redPin, HIGH);
  tone(buzzerPin, 500, 150);
  
  // Non-blocking delay with button checking
  unsigned long startTime = millis();
  while(millis() - startTime < 1000) {
    checkBothButtons();
    if(player1Pressed) {
      handleEarlyPress(1);
      return;
    }
    if(player2Pressed) {
      handleEarlyPress(2);
      return;
    }
    delay(10);
  }
  
  // --- YELLOW LIGHT PHASE (random duration) ---
  digitalWrite(yellowPin, HIGH);
  tone(buzzerPin, 750, 150);
  
  // Non-blocking delay with button checking
  startTime = millis();
  while(millis() - startTime < randNumber) {
    checkBothButtons();
    if(player1Pressed) {
      handleEarlyPress(1);
      return;
    }
    if(player2Pressed) {
      handleEarlyPress(2);
      return;
    }
    delay(10);
  }
  
  // --- GREEN LIGHT PHASE (GO!) ---
  digitalWrite(greenPin, HIGH);
  tone(buzzerPin, 1000, 300);
  
  // Check for button press immediately after green turns on
  checkBothButtons();
  if(player1Pressed) {
    handleSuccess(1);
    return;
  }
  if(player2Pressed) {
    handleSuccess(2);
    return;
  }
  
  // Wait for button press during green phase (5 second timeout)
  startTime = millis();
  while(millis() - startTime < 5000) {
    checkBothButtons();
    if(player1Pressed) {
      handleSuccess(1);
      return;
    }
    if(player2Pressed) {
      handleSuccess(2);
      return;
    }
    delay(10);
  }
  
  // If no button pressed within timeout, restart cycle
  delay(3000);
}

// Function to check both buttons (with debouncing)
void checkBothButtons() {
  // Check Player 1 button
  if(digitalRead(player1Button) == HIGH) {
    delay(50); // Debounce delay
    if(digitalRead(player1Button) == HIGH) {
      player1Pressed = true;
    }
  }
  
  // Check Player 2 button
  if(digitalRead(player2Button) == HIGH) {
    delay(50); // Debounce delay
    if(digitalRead(player2Button) == HIGH) {
      player2Pressed = true;
    }
  }
}

// Function to handle early button press (penalty)
void handleEarlyPress(int player) {
  // Turn off all main LEDs
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  
  // Turn on the appropriate player's red LED as penalty
  if(player == 1) {
    digitalWrite(player1Red, HIGH);
    digitalWrite(player1Green, LOW);
    digitalWrite(player2Red, LOW);
    digitalWrite(player2Green, LOW);
  } else {
    digitalWrite(player2Red, HIGH);
    digitalWrite(player2Green, LOW);
    digitalWrite(player1Red, LOW);
    digitalWrite(player1Green, LOW);
  }
  
  // Sound penalty buzzer (longer, lower tone)
  tone(buzzerPin, 300, 500);
  delay(500);
  
  // Flash the appropriate red LED to indicate penalty
  for(int i = 0; i < 3; i++) {
    if(player == 1) {
      digitalWrite(player1Red, LOW);
      delay(200);
      digitalWrite(player1Red, HIGH);
      delay(200);
    } else {
      digitalWrite(player2Red, LOW);
      delay(200);
      digitalWrite(player2Red, HIGH);
      delay(200);
    }
  }
  
  delay(1000);
  
  // Reset and start new round
  setup();
}

// Function to handle successful button press (reward!)
void handleSuccess(int player) {
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  
  // Turn on the appropriate player's green LED
  if(player == 1) {
    digitalWrite(player1Green, HIGH);
    digitalWrite(player1Red, LOW);
    digitalWrite(player2Green, LOW);
    digitalWrite(player2Red, LOW);
  } else {
    digitalWrite(player2Green, HIGH);
    digitalWrite(player2Red, LOW);
    digitalWrite(player1Green, LOW);
    digitalWrite(player1Red, LOW);
  }
  
  // Play success tone for the winning player
  if(player == 1) {
    // Player 1 success tone (higher pitch)
    tone(buzzerPin, 988, 100);
    delay(100);
    tone(buzzerPin, 1319, 100);
    delay(100);
    tone(buzzerPin, 1568, 200);
    delay(200);
  } else {
    // Player 2 success tone (slightly different - lower pitch)
    tone(buzzerPin, 880, 100);
    delay(100);
    tone(buzzerPin, 1175, 100);
    delay(100);
    tone(buzzerPin, 1397, 200);
    delay(200);
  }
  
  // Flash the winning player's green LED to celebrate
  int flashCount = 5;
  for(int i = 0; i < flashCount; i++) {
    if(player == 1) {
      digitalWrite(player1Green, LOW);
      delay(100);
      digitalWrite(player1Green, HIGH);
      delay(100);
    } else {
      digitalWrite(player2Green, LOW);
      delay(100);
      digitalWrite(player2Green, HIGH);
      delay(100);
    }
  }
  
  delay(1000);
  
  // Reset and start new round
  setup();
}