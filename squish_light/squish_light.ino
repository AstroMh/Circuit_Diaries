const int ledPin = 11;
const unsigned long BAUD = 9600;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, OUTPUT);
  Serial.begin(BAUD);
  Serial.println("[+] Ready to recieve brightness value (0-255).");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();

    if (inputString.length() > 0) {
      int brightness = inputString.toInt();

      brightness = constrain(brightness, 0, 255);

      analogWrite(ledPin, brightness);
    } 
  }
}
