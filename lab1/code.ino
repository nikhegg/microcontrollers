const int buttonPin = 13;
const int ledPin1 = 12;
const int ledPin2 = 11;

bool isBlinking = false;
bool lastButtonState = LOW;
unsigned long prevMs = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);
  if(currentButtonState == LOW && lastButtonState == HIGH) {
    isBlinking = !isBlinking;
    delay(50);               
  }
  lastButtonState = currentButtonState;
  if(isBlinking) {
    unsigned long currentMs = millis();
	if(currentMs - prevMs < 300) return; // Change 300 to any another blink interval
    prevMs = currentMs;
	bool pinState1 = digitalRead(ledPin1);
	digitalWrite(ledPin1, !pinState1);
	digitalWrite(ledPin2, pinState1);
  } else {
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
  }
}