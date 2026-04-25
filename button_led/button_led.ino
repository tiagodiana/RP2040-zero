#define ledPin 14
#define buttonPin 15

int buttonState = 0;
int buttonStateLater = 0;

int ledState = 0;


void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  buttonState = digitalRead(buttonPin);
  ledState = !digitalRead(ledPin);

  if(buttonState == HIGH && (buttonState != buttonStateLater))
  {
    digitalWrite(ledPin, ledState);
    delay(50);
  }

  buttonStateLater = buttonState;
}
