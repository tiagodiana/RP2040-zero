#include "Adafruit_TinyUSB.h"
#include <Adafruit_NeoPixel.h>

//LED ARGB DA PLACA
#define ledBoard 16
#define numLeds 1
Adafruit_NeoPixel pixels(numLeds, ledBoard);

#define potPin 26
unsigned int valuePot;
unsigned int valuePotLater;

uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_CONSUMER()
};

Adafruit_USBD_HID usb_hid;

void setup() 
{
  //INICIANDO BIBLIOTECA PARA TRABALHAR COM ARGB
  pixels.begin();
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(50, 20, 0));
  pixels.show();

  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
 

  pinMode(potPin, INPUT);
  valuePotLater = analogRead(potPin);
  // PIN CONFIGURAÇÃO
  // pinMode(POTPIN, INPUT);
  // valuePotLater = analogRead(POTPIN);


  while( !USBDevice.mounted() ) delay(3000);
}

void loop() {
  if ( !usb_hid.ready() ) return;
  
  pixels.setPixelColor(0, pixels.Color(10, 30, 0));
  pixels.show();

  long sum = 0;
  for(int i = 0; i < 5; i++) sum +=  analogRead(potPin); 
  
  valuePot = sum /5;

  int threshold = valuePot - valuePotLater;
  int sensibility = 30;

  if(abs(threshold) > sensibility)
  {
    // Trava de segurança para o ZERO e para o MÁXIMO (1023)
    if (valuePot < 10 && valuePotLater < 10) return; 
    //if (valuePot > 900 && valuePotLater > 900) return;


    int steps = abs(threshold) / 40; 
    if (steps < 1) steps = 1; // No mínimo 1 comando
    if (steps > 8) steps = 8;
    
    
    uint16_t keycode = 0;
    if(threshold > 0)
    {
     keycode = HID_USAGE_CONSUMER_VOLUME_INCREMENT;
    } else {
      keycode = HID_USAGE_CONSUMER_VOLUME_DECREMENT;
    }

    for(int i=0; i < steps; i++) {
      usb_hid.sendReport(0, &keycode, sizeof(keycode));
      delay(10); // Curto intervalo entre comandos
      uint16_t release = 0;
      usb_hid.sendReport(0, &release, sizeof(release));
      delay(10);
    }

    valuePotLater = valuePot;

    delay(2);
  }


// void potentiometerActions() {
//   long sum = 0;
//   for(int i=0; i<8; i++) sum += analogRead(POTPIN); // Média de 8 leituras
//   int val = sum / 8;

//   int diff = val - valuePotLater;
//   int sensibility = 35; // Ajuste se o volume "pular" sozinho

//   if (abs(diff) > sensibility) {
//     if (val < 10 && valuePotLater < 10) return; // Trava no zero

//     uint16_t key = (diff > 0) ? HID_USAGE_CONSUMER_VOLUME_INCREMENT : HID_USAGE_CONSUMER_VOLUME_DECREMENT;
    
//     usb_hid.sendReport(1, &key, sizeof(key));
//     delay(10);
//     uint16_t release = 0;
//     usb_hid.sendReport(1, &release, sizeof(release));
    
//     valuePotLater = val;
//     delay(5);
//   }
// }


}
