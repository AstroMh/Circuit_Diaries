const int redLed = 10;
const int greenLed = 9;
const int yellowLed = 8;
const int redButton = 2;
const int greenButton = 4;
const int yellowButton = 3;
const int buzzer = 13;

const int RED = 0;
const int GREEN = 1;
const int YELLOW = 2;

const int SOUND_RED = 262;      // C4
const int SOUND_GREEN = 330;    // E4
const int SOUND_YELLOW = 392;   // G4
const int SOUND_WRONG = 200;    // Low buzz
const int SOUND_ROUND = 660;    // Success sound
const int SOUND_START = 440;    // Game start sound

const int MAX_SEQUENCE = 100;
int sequence[MAX_SEQUENCE];
int sequenceLength = 3;
int playerStep = 0;
bool waitingForInput = false;
bool gameOver = false;
int score = 0;  // Track rounds completed

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redButton, INPUT_PULLUP);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);
  
  turnOffAllLEDs();
  noTone(buzzer);
  
  generateSequence();
  
  delay(500);
  
  playStartupSound();
  delay(500);
  
  playSequence();
}

void loop() {
  // Only check for input when waiting
  if(waitingForInput && !gameOver) {
    int buttonPressed = readButtonPress();
    
    if(buttonPressed != -1) {
      playButtonSound(buttonPressed);
      
      if(buttonPressed == sequence[playerStep]) {
        lightLED(buttonPressed);
        delay(300);
        turnOffAllLEDs();
        delay(100);
        
        playerStep++;
        
        // Check if round is complete
        if(playerStep >= sequenceLength) {
          waitingForInput = false;
          score++;
          
          playRoundCompleteSound();
          
          for(int i = 0; i < 2; i++) {
            turnOnAllLEDs();
            delay(200);
            turnOffAllLEDs();
            delay(200);
          }
          
          delay(500);
          
          addToSequence();
          
          playSequence();
        }
      } else {

        playWrongSound();
        
        for(int i = 0; i < 3; i++) {
          turnOnAllLEDs();
          delay(300);
          turnOffAllLEDs();
          delay(200);
        }
        
        playerStep = 0;
        waitingForInput = false;
        
        delay(500);
        
        playSequence();
      }
    }
  }
}


void generateSequence() {
  randomSeed(analogRead(A0));  // Different pattern each reset
  
  for(int i = 0; i < 3; i++) {
    sequence[i] = random(0, 3);  // 0=Red, 1=Green, 2=Yellow
  }
  sequenceLength = 3;
  playerStep = 0;
  waitingForInput = false;
  gameOver = false;
  score = 0;
}

void addToSequence() {
  // Add 2 new random colors
  if(sequenceLength + 2 <= MAX_SEQUENCE) {
    sequence[sequenceLength] = random(0, 3);
    sequence[sequenceLength + 1] = random(0, 3);
    sequenceLength += 2;
  }
}

void playSequence() {
  turnOffAllLEDs();
  waitingForInput = false;
  delay(300);
  
  for(int i = 0; i < sequenceLength; i++) {
    playButtonSound(sequence[i]);
    
    lightLED(sequence[i]);
    delay(400);
    turnOffAllLEDs();
    noTone(buzzer);  
    
    if(i < sequenceLength - 1) {
      delay(200);
    }
  }
  
  delay(500);
  
  // Ready for player input
  waitingForInput = true;
  playerStep = 0;
}

void lightLED(int color) {
  turnOffAllLEDs();
  
  if(color == RED) {
    digitalWrite(redLed, HIGH);
  } else if(color == GREEN) {
    digitalWrite(greenLed, HIGH);
  } else if(color == YELLOW) {
    digitalWrite(yellowLed, HIGH);
  }
}

void turnOffAllLEDs() {
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
}

void turnOnAllLEDs() {
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, HIGH);
}

int readButtonPress() {
  static unsigned long lastDebounceTime = 0;
  static int lastButtonState = -1;
  const unsigned long debounceDelay = 50;
  
  int redState = digitalRead(redButton);
  int greenState = digitalRead(greenButton);
  int yellowState = digitalRead(yellowButton);
  
  int currentButton = -1;
  if(redState == LOW) currentButton = RED;
  else if(greenState == LOW) currentButton = GREEN;
  else if(yellowState == LOW) currentButton = YELLOW;
  
  // Debounce logic
  if(currentButton != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if((millis() - lastDebounceTime) > debounceDelay) {
    if(currentButton != -1) {
      // Button is pressed
      lastButtonState = currentButton;
      return currentButton;
    }
  }
  
  lastButtonState = currentButton;
  return -1;  // No button pressed
}

// -------------SOUND--------------

void playButtonSound(int color) {
  // Each color has a unique tone
  if(color == RED) {
    tone(buzzer, SOUND_RED, 150);
  } else if(color == GREEN) {
    tone(buzzer, SOUND_GREEN, 150);
  } else if(color == YELLOW) {
    tone(buzzer, SOUND_YELLOW, 150);
  }
  delay(150);
  noTone(buzzer);
}

void playWrongSound() {
  // Low descending buzz (error sound)
  tone(buzzer, 300, 200);
  delay(200);
  tone(buzzer, 200, 200);
  delay(200);
  noTone(buzzer);
}

void playRoundCompleteSound() {
  // Happy victory melody
  tone(buzzer, 523, 150);  // C5
  delay(150);
  tone(buzzer, 659, 150);  // E5
  delay(150);
  tone(buzzer, 784, 200);  // G5
  delay(200);
  noTone(buzzer);
}

void playStartupSound() {
  // Game start jingle
  tone(buzzer, 392, 100);  // G4
  delay(100);
  tone(buzzer, 523, 100);  // C5
  delay(100);
  tone(buzzer, 659, 150);  // E5
  delay(150);
  noTone(buzzer);
}

void playGameOverSound() {
  // Sad descending tone
  tone(buzzer, 400, 200);
  delay(200);
  tone(buzzer, 300, 200);
  delay(200);
  tone(buzzer, 200, 300);
  delay(300);
  noTone(buzzer);
}