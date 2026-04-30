/*
  CÓDIGO PARA MACRO KEYBOARD + 2 PONTENCIOMETROS ENCODE 
  


*/

//#include <Keyboard.h>
#include "Adafruit_TinyUSB.h"

//KEYBOARD LIBRARY
//const uint8_t keys[] = {KEY_F14, KEY_F15, KEY_F16, KEY_F17, KEY_F18, KEY_F19, KEY_F23, KEY_F24, KEY_F20};

//Adafruit_TinyUSB LIBRARY
const uint8_t keys[] = {HID_KEY_F14, HID_KEY_F15, HID_KEY_F16, HID_KEY_F17, HID_KEY_F18, HID_KEY_F19, HID_KEY_F23, HID_KEY_F24, HID_KEY_F20};
uint8_t const desc_hid_report[] = {
  TUD_HID_REPORT_DESC_KEYBOARD()
};
Adafruit_USBD_HID usb_hid;


const uint8_t buttons[] = {5, 6, 7, 8, 9, 10, 11, 12, 13};
int NUM_BUTTONS = 9;


void setup() 
{
  for(int i = 0; i < NUM_BUTTONS; i++)
  {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  //Keyboard.begin();

  usb_hid.setPollInterval(2);
  usb_hid.setReportDescriptor(desc_hid_report, sizeof(desc_hid_report));
  usb_hid.begin();

  while( !USBDevice.mounted() ) delay(1000);
}


void loop() 
{
  if ( !usb_hid.ready() ) return;

  // for(size_t i = 0; i < NUM_BUTTONS; i++)
  // {
  //   if(digitalRead(buttons[i]) == LOW)
  //   {
  //     Keyboard.press(keys[i]);
  //   }
  //   else
  //   {
  //     Keyboard.release(keys[i]);
  //   }
  // }

  static uint8_t previous_report[6] = {0}; // Track previous state
  uint8_t current_report[6] = {0};         // Up to 6 simultaneous key presses
  int key_count = 0;

  // Scan buttons
  for(int i = 0; i < NUM_BUTTONS; i++) 
  {
    if(digitalRead(buttons[i]) == LOW) 
    {
      if(key_count < 6) 
      { 
        current_report[key_count] = keys[i];
        key_count++;
      }
    }
  }

  // Only send a report if the state has changed
  if (memcmp(previous_report, current_report, 6) != 0) 
  {
    // sendKeyboardReport(report_id, modifier, keycodes_array)
    usb_hid.keyboardReport(0, 0, current_report);
    memcpy(previous_report, current_report, 6);
  }

  delay(20); // Debounce delay
}