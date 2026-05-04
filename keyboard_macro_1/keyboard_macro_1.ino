/*
  TECLADO 3X2 + 1, 1 ENCODER, DISPLAY 128X32

  CÓDIGO DESENVOLVIDO PARA RP2040 ZERO
  https://www.waveshare.com/wiki/RP2040-Zero

  CASE:
  https://makerworld.com/pt/models/2393578-ackupad-diy-macropad-for-only-10

  KEYCAPS:
  https://makerworld.com/pt/models/132469-xda-style-keycaps-blank

  PEÇAS USADAS 
  1x RP2040 ZERO
  7x Switch Drinkey red + 3x Diode 5v1
  1x Display Oled 128x32
  1x Pontentiometer B10K
  4× M3x16mm Parafuso
  4× M3x5mx4mm Porcas


  PINOS:
  GP0, GP1 = DISPLAY
  GP2 = BUTTON ACTIONS
  GP3, GP4 ENCODER
  GP5 = ENCODER CLICK
  GP6, GP7 = ROWS MATRIX KEYBOARD
  GP8, GP9, GP10 = COLS MATRIX KEYBOARD
  GP16 = LED BOARD
*/

// BIBLIOTECAS PARA O DISPLAY
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// BIBLIOTECA PARA TRABALHAR COM O TECLADO
#include "Adafruit_TinyUSB.h"
// BIBLIOTECA PARA LIGAR O LED INTERNO DA PLACA (LED ARGB)
#include <Adafruit_NeoPixel.h>
//BIBLIOTECA ENCODER
#include <pio_encoder.h>


// DISPLAY OLED 128X32
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1 
// No RP2040 (Arduino IDE), Wire usa por padrão GP4(SDA) e GP5(SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// LED da RP2040-Zero
#define LEDBOARD 16
Adafruit_NeoPixel pixels(1, LEDBOARD);

// SENSOR DE TEMPERATURA
#define SENSOR_TEMP_BOARD 4

//ENCODER
PioEncoder encoder(3);
long lastEncoderValue = 0;
#define BUTTON_ENCODER_PIN 5


// Matriz 2x3: Linhas (Rows) e Colunas (Cols)
const uint8_t rowPins[2] = {6, 7};    
const uint8_t colPins[3] = {8, 9, 10};   

// BOTÃO TROCA DE MODOS
const uint8_t BUTTON_MODE_PIN = 2;


// Descritores com IDs únicos para evitar conflitos
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_CONSUMER( HID_REPORT_ID(1) ),
  TUD_HID_REPORT_DESC_KEYBOARD( HID_REPORT_ID(2) )
};

Adafruit_USBD_HID usb_hid;

const char TITLE[] = "MACRO PAD - CUSTOM";
int modeStep = 1;
int menuTotal = 3;

void setup() {
  pixels.begin();
  pixels.setPixelColor(0, pixels.Color(0, 30, 10)); // Verde Água
  pixels.show();

  encoder.begin();

  initDisplayOLed();

  // Setup da Matriz
  for(int i=0; i<2; i++) pinMode(rowPins[i], INPUT_PULLUP);
  for(int i=0; i<3; i++) 
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }
  
  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();
  
  pinMode(BUTTON_MODE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_ENCODER_PIN, INPUT_PULLUP);

  
  while( !USBDevice.mounted() ) delay(2000);

  clearDisplay();
}

void loop() 
{
  if ( !usb_hid.ready() ) return;
  
  if(digitalRead(BUTTON_MODE_PIN) == LOW)
  {
    actionButtonMode();
  }

  switch (modeStep) 
  {
    case 1: 
      mode1();
      break;
    
    case 2: 
      mode2();
      break;

    case 3: 
      mode3();
      break;
  }

  switch(modeStep)
  {
    case 1:
    case 2:
    case 3:
      encoderActions();
      encoderButtonAction();
      break;
  }
}

void actionButtonMode()
{
  clearDisplay();
    modeStep++;
    if(modeStep > menuTotal)
    {
      modeStep = 1;
    }
    delay(100);
}

void encoderButtonAction()
{
  if (digitalRead(BUTTON_ENCODER_PIN) == LOW) 
  {;
    displayOLedTextTemperature();  
    delay(5000); // Debounce simples
    clearDisplay();
  }
}



//INICIANDO DISPLAY
void initDisplayOLed()
{
  // Define os novos pinos para o barramento Wire (I2C0)
  Wire.setSDA(0); 
  Wire.setSCL(1);

  // Inicializa o I2C nos pinos padrão
  Wire.begin(); 

  // Inicializa o display no endereço 0x3C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); 
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0,0);
  display.println(TITLE);
  //display.setCursor(0,15);
  display.println("GETTING STARTED");
  display.display();
}

void clearDisplay()
{
  display.clearDisplay();
  display.setCursor(0,0);
}

// TEXTO MODO 1
void displayOLedTextMode1()
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(0,0);
  display.println(TITLE);
  //display.setCursor(0,15);
  display.println("MODE 1 - KEYBOARD EXT");
  display.println("F14 - F15 - F16");
  display.println("F17 - F18 - F19");
  display.display();
}

// TEXTO MODO 2
void displayOLedTextMode2()
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(0,0);
  display.println(TITLE);
  //display.setCursor(0,15);
  display.println("MODE 2 - SYSTEM");
  display.println("COPY - CUT - PASTE");
  display.println("MUTE - VOL- - VOL+");
  display.display();
}

// TEXTO MODO 3
void displayOLedTextMode3()
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(0,0);
  display.println(TITLE);
  //display.setCursor(0,15);
  display.println("MODE 3 - HEXADECIMAL");
  display.println("A - B - C");
  display.println("D - E - F");
  display.display();
}

void displayOLedTextTemperature()
{
  float temp = analogReadTemp();
  clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  //display.setCursor(0,0);
  display.println(TITLE);
  //display.setCursor(0,15);
  display.println("TEMPERATURA PLACA");
  display.print(temp);
  display.print(" ");
  display.print((char) 247);
  display.print("C");
  display.display();
}

void matrixActions(uint8_t keys[][3]) 
{
  static uint8_t prev_report[6] = {0};
  uint8_t curr_report[6] = {0};
  int count = 0;

  for (int c=0; c<3; c++) {
    digitalWrite(colPins[c], LOW); // Ativa coluna atual
    delayMicroseconds(30);         // Tempo para o sinal estabilizar

    for (int r=0; r<2; r++) {
      if (digitalRead(rowPins[r]) == LOW) { // Botão detectado
        if (count < 6) curr_report[count++] = keys[r][c];
      }
    }
    digitalWrite(colPins[c], HIGH); // Desativa coluna
  }

  // Só envia se houver mudança de estado
  if (memcmp(prev_report, curr_report, 6) != 0) {
    usb_hid.keyboardReport(2, 0, curr_report);
    memcpy(prev_report, curr_report, 6);
  }
  delay(5);
}

void encoderActions()
{
  long currentEncoderValue = encoder.getCount(); // Lê a contagem atual do PIO
  
  // Se o valor mudou, houve movimento no encoder
  if (currentEncoderValue != lastEncoderValue) {
    
    // Determina a tecla: se aumentou (incrementa), se diminuiu (decrementa)
    uint16_t key = (currentEncoderValue > lastEncoderValue) ? 
                   HID_USAGE_CONSUMER_VOLUME_INCREMENT : 
                   HID_USAGE_CONSUMER_VOLUME_DECREMENT;
    
    // Envia o comando via USB HID
    usb_hid.sendReport(1, &key, sizeof(key));
    delay(10); // Pequeno delay para o PC processar
    
    uint16_t release = 0;
    usb_hid.sendReport(1, &release, sizeof(release));
    
    // Atualiza a última posição gravada
    lastEncoderValue = currentEncoderValue;
  }
}

// MODES
void mode1()
{
  displayOLedTextMode1();
  // Mapeamento: 2x3 = 9 teclas
  uint8_t keys[2][3] = {
    {HID_KEY_F14, HID_KEY_F15, HID_KEY_F16},
    {HID_KEY_F17, HID_KEY_F18, HID_KEY_F19}
  };

  matrixActions(keys);
}

void mode2()
{
  displayOLedTextMode2();
  // Mapeamento: 2x3 = 9 teclas
  uint8_t keys[2][3] = {
    {HID_KEY_COPY, HID_KEY_CUT, HID_KEY_PASTE},
    {HID_KEY_MUTE, HID_KEY_VOLUME_DOWN, HID_KEY_VOLUME_UP}
  };

  matrixActions(keys);
}

void mode3()
{
  displayOLedTextMode3();
  // Mapeamento: 2x3 = 9 teclas
  uint8_t keys[2][3] = {
    {HID_KEY_KEYPAD_A, HID_KEY_KEYPAD_B, HID_KEY_KEYPAD_C},
    {HID_KEY_KEYPAD_D, HID_KEY_KEYPAD_E, HID_KEY_KEYPAD_F}
  };

  matrixActions(keys);
}
