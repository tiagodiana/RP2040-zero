#include <Adafruit_TinyUSB.h>
#include <MIDI.h>

// Definição dos pinos
const int rowPins[3] = {8, 7, 6}; // Linhas
const int colPins[3] = {2, 3, 4}; // Colunas

// Mapeamento das notas MIDI para cada botão (3x3)
const int notes[3][3] = {
  {60, 61, 62},
  {63, 64, 65},
  {66, 67, 68} z
};

// Guarda o estado anterior para não repetir a nota sem parar
bool lastState[3][3] = {false};


// 2. Configuração MIDI USB
Adafruit_USBD_MIDI usb_midi;
MIDI_CREATE_INSTANCE(Adafruit_USBD_MIDI, usb_midi, MIDI);


void setup() {
  // Configura Linhas como Entrada com Pull-up (evita flutuação)
  for (int i = 0; i < 3; i++) {
    pinMode(rowPins[i], INPUT_PULLUP);
  }

  // Configura Colunas como Saída e coloca em HIGH
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], HIGH);
  }

  MIDI.begin(MIDI_CHANNEL_OMNI);
  while (!TinyUSBDevice.mounted()) delay(1);
}

void loop() {
  for (int c = 0; c < 3; c++) {
    // Ativa a coluna atual colocando-a em LOW
    digitalWrite(colPins[c], LOW);
    
    // Pequeno delay para estabilização elétrica (opcional)
    delayMicroseconds(50);

    for (int r = 0; r < 3; r++) {
      // Se a linha for lida como LOW, o botão foi pressionado
      bool isPressed = (digitalRead(rowPins[r]) == LOW);

      if (isPressed && !lastState[r][c]) {
        // Botão acabou de ser apertado
        MIDI.sendNoteOn(notes[r][c], 127, 1);
        lastState[r][c] = true;
      } 
      else if (!isPressed && lastState[r][c]) {
        // Botão acabou de ser solto
        MIDI.sendNoteOff(notes[r][c], 0, 1);
        lastState[r][c] = false;
      }
    }
    
    // Desativa a coluna (volta para HIGH) antes de passar para a próxima
    digitalWrite(colPins[c], HIGH);
  }
  
  delay(10); // Debounce simples para evitar ruído
}
