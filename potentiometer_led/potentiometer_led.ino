#include <Adafruit_NeoPixel.h>

//LED EXTERNO LIGADO AO PINO 14
#define pin_led 14

//TRABALHANDO COM POTENCIOMETRO
#define pot 26
unsigned int valuePot;

void setup() {
  //LED EXTERNO DA PLACA
  pinMode(pin_led, OUTPUT);

  //TRABALHANDO COM POTENCIOMETRO
  pinMode(pot, INPUT);
}

void loop() {
  //POTENCIOMETRO
  // EX 1 - AUMENTANDO OU DIMINUINDO O DELAY COM O POT
  // valuePot = analogRead(pot);
  // digitalWrite(pin_led, HIGH);
  // delay(valuePot);
  // digitalWrite(pin_led, LOW);
  // delay(valuePot);

  //EX 2 - AUMENTANDO A INTENSIDADE DO LED
  valuePot = analogRead(pot);
  byte val = byte((valuePot)/4);
  analogWrite(pin_led, val);
  
}
