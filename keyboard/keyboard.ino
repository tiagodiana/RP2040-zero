/*
  CÓDIGO PARA MACRO KEYBOARD 3x3
  
  CASE:
  https://makerworld.com/pt/models/496646-9-key-mechanical-macropad

  KEYCAPS:
  https://makerworld.com/pt/models/132469-xda-style-keycaps-blank

  PEÇAS USADAS
  1x Raspberry Pi pico-like RP 2040 com conector USB-C
  9x Diodos 1N4148
  4x Parafuso M3 8MM
  4x Insertos roscados M3
  1x Parafuso M3 2MM
  9x Switches Cherry MX ou similar
  9x Keycap ou impresso em 3D
  Fio
  Filamento
  4x Pés de borracha autoadesivos de 8MM (opcional)

*/

//#include <Keyboard.h>
#include "Adafruit_TinyUSB.h"

//KEYBOARD LIBRARY
//const uint8_t keys[] = {KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F23, KEY_F24, KEY_F20};

//Adafruit_TinyUSB LIBRARY
const uint8_t keys[3][3] = {
  {HID_KEY_F14, HID_KEY_F15, HID_KEY_F16},
  {HID_KEY_F17, HID_KEY_F18, HID_KEY_F19},
  {HID_KEY_F23, HID_KEY_F24, HID_KEY_F20}  
};
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};
Adafruit_USBD_HID usb_hid;


// Matriz 2x3: Linhas (Rows) e Colunas (Cols)
const uint8_t colPins[3] = {2, 3, 4};    
const uint8_t rowPins[3] = {8, 7, 6};   



void setup() 
{
  // Setup da Matriz
  for(int i=0; i<3; i++) pinMode(rowPins[i], INPUT_PULLUP);
  for(int i=0; i<3; i++) 
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();

  while( !USBDevice.mounted() ) delay(1000);
}


void loop() 
{
  if ( !usb_hid.ready() ) return;

  static uint8_t prev_report[9] = {0}; // Reduzido para 6 (padrão HID)
  uint8_t curr_report[9] = {0};
  int count = 0;

  for (int c=0; c<3; c++) {
    digitalWrite(colPins[c], LOW); 
    delayMicroseconds(50); // Aumentado levemente para estabilidade no RP2040

    for (int r=0; r<3; r++) {
      if (digitalRead(rowPins[r]) == LOW) {
        if (count < 9) { 
          curr_report[count++] = keys[r][c];
        }
      }
    }
    digitalWrite(colPins[c], HIGH);
  }

  // Se nada foi pressionado, o curr_report estará zerado, enviando "key up"
  if (memcmp(prev_report, curr_report, 9) != 0) {
    usb_hid.keyboardReport(0, 0, curr_report); // ID do report costuma ser 0 ou 1
    memcpy(prev_report, curr_report, 6);
  }
  
  delay(10); // Debounce de 10ms é o "sweet spot" para Cherry MX
}
