/*
  Melody

  Plays a melody

  circuit:
  - 8 ohm speaker on digital pin 8

  created 21 Jan 2010
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/digital/toneMelody/

  CUSTOMIZATION: TIAGO R. DIANA
  USAGE A RP2040, SPEAKER IN PIN 15
*/

#include "pitches.h"

#define speakerPin 15


void playMelody(int *melody,  int *noteDurations, int totalNoteDuration, float rateSong)
{
   // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < totalNoteDuration; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(speakerPin, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * rateSong;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(speakerPin);
  }
}


//MELODIES
void carelessWhisper()
{
  float rateSong = 1.22;
  // notes in the melody:
  int melody[] = {
    NOTE_E6, NOTE_D6, NOTE_A5, NOTE_F5, NOTE_E6, NOTE_D6, NOTE_A5, NOTE_F5,
    NOTE_C6, NOTE_AS5, NOTE_F5, NOTE_D5, NOTE_C6, NOTE_AS5, NOTE_F5, NOTE_D5,
    NOTE_AS5, NOTE_A5, NOTE_F5, NOTE_D5, NOTE_AS4, 0,
    NOTE_A4, NOTE_AS4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5
  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    3, 4, 3, 3, 2, 4, 3, 2,
    3, 4, 3, 3, 2, 4, 3, 2,
    3, 4, 3, 3, 1, 8,
    3, 3, 3, 3, 3, 3, 3, 3
  };
  

  int totalNoteDuration = sizeof(noteDurations) / sizeof(noteDurations[0]);

  playMelody(melody, noteDurations, totalNoteDuration, rateSong);
  playMelody(melody, noteDurations, totalNoteDuration, rateSong);
  
}

void sweetChildOMine()
{
  float rateSong = 1.12;
  // notes in the melody:
  int melody[] = {
    NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_E5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_E5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_G5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_G5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_D5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_E5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_E5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_G5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_G5, NOTE_D6, NOTE_A5, NOTE_G5, NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5,
    NOTE_E6, NOTE_A5, NOTE_D6, NOTE_A5, NOTE_E6, NOTE_A5, NOTE_FS6, NOTE_A5, 
    NOTE_G6, NOTE_A5, NOTE_FS6, NOTE_A5, NOTE_E6, NOTE_A5, NOTE_D6

  };

  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
  };
  

  int totalNoteDuration = sizeof(noteDurations) / sizeof(noteDurations[0]);

  playMelody(melody, noteDurations, totalNoteDuration, rateSong);
}



void setup() {
    sweetChildOMine();
}

void loop() {
}
