#include <Keyboard.h>

const uint8_t buttons[] = {5, 6, 7, 8, 9, 10, 11, 12, 13};
const uint8_t keys[] = {KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F23, KEY_F24, KEY_F20};
int NUM_BUTTONS = 9;


const uint8_t potPin = 26;

void controlVolumePontentiometer()
{

}

void setup() 
{
  for(int i = 0; i < NUM_BUTTONS; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  Keyboard.begin();
}


void loop() 
{
  for(size_t i = 0; i < NUM_BUTTONS; i++)
  {
    if(digitalRead(buttons[i]) == LOW)
    {
      Keyboard.press(keys[i]);
    }
    else
    {
      Keyboard.release(keys[i]);
    }
  }
}