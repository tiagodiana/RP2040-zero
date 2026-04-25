//LED EXTERNO LIGADO AO PINO 14
#define pin_led 14

void setup() {
  //LED EXTERNO DA PLACA
  pinMode(pin_led, OUTPUT);

}

void loop() {
  //LED EXTERNO
  digitalWrite(pin_led, HIGH);
  delay(500);
  digitalWrite(pin_led, LOW);
  delay(500);
}
