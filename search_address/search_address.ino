#include <Wire.h>
//0x3C
// Defina os pinos que você conectou (Exemplo: SDA no GP0 e SCL no GP1)
#define PIN_SDA 0
#define PIN_SCL 1

void setup() {
  Wire.setSDA(PIN_SDA);
  Wire.setSCL(PIN_SCL);
  Wire.begin();

  Serial.begin(115200);
  while (!Serial); // Aguarda abrir o monitor serial
  Serial.println("\nI2C Scanner");
}

void loop() {
  byte error, address;
  int nDevices = 0;

  Serial.println("Escaneando...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo I2C encontrado no endereço 0x");
      if (address < 16) Serial.print("0");
      Serial.print(address, HEX);
      Serial.println(" !");
      nDevices++;
    }
  }

  if (nDevices == 0) Serial.println("Nenhum dispositivo encontrado\n");
  else Serial.println("Fim do scan\n");

  delay(5000); 
}
