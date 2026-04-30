#include <Adafruit_NeoPixel.h>

//LED ARGB DA PLACA PARA FAZER O BLINK
#define ledBoard 16
#define numLeds 1
//DECLARANDO BIBLIOTECA PARA TRABALHAR COM ARGB
Adafruit_NeoPixel pixels(numLeds, ledBoard);

void setup() {
  //INICIANDO BIBLIOTECA PARA TRABALHAR COM ARGB
  pixels.begin();
}

void loop() {  
  //LED INTERNO DA PLACA
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(30, 30, 0));
  pixels.show();
  delay(500);
  pixels.setPixelColor(0, pixels.Color(0, 0, 0));
  pixels.show();
  delay(500);



}
