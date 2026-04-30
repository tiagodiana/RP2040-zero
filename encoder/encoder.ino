#include <pio_encoder.h>


PioEncoder encoder(2);
long encoderValueLater = -999;

void setup() {
  encoder.begin();

  Serial.begin(9600);
  while(!Serial);
}

void loop() {

  long encodeValue = encoder.getCount();
  if(encodeValue > encoderValueLater)
  delay(10);
}
