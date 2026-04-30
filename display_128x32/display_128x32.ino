#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1 

// No RP2040 (Arduino IDE), Wire usa por padrão GP4(SDA) e GP5(SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
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
  //display.setCursor(0,0);
  display.println("RP2040 + OLED");
  //display.setCursor(0,15);
  display.println("Conectado com sucesso");
  display.println("Portas: GP0 - GP1");
  display.display();
}

void loop() {
  // Seu código aqui
}