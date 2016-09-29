#include <ToneLib.h>

#include <avr/pgmspace.h>

#include "melody.h"
#include "common.h"

#define START_DELAY 0       //Time (in ms) program will wait before starting the song.

#define LOOP_DELAY 0        //Time (in ms) program will wait before playing through song again. Increase for longer time, decrease for shorter. 0 will replay song immediately.

//#define BUTTON_START      //Only enable if you have a button wired to output 1 when pressed.
//#define BUTTONPIN 12

//#define LIGHTDISPLAY      //Only enable if you have LEDs wired with the correct offset
//#define LEDOFFSET -1

unsigned long duration = 0;
unsigned long totalduration = 0;
unsigned long offset = 0;

int msize[TRACKS];
unsigned long note[TRACKS];
int freq[TRACKS];
int counter[TRACKS];
Tone buzzer[TRACKS];


void setup(){

  Serial.begin(250000);

  //if button start is enabled, buttonpin must be set to input mode
  #ifdef BUTTON_START
  pinMode(BUTTONPIN, INPUT);
  #endif

  for(int i = 0; i < TRACKS; i++){

    msize[i] = tracks[i].arraySize; //set array size
    note[i] = 0;    //zero out arrays
    freq[i] = 0;    //
    counter[i] = 0; //
    
    buzzer[i].begin(tracks[i].pin); //init buzzer

    #ifdef LIGHTDISPLAY //if light display is enabled, the pin must be set to output mode
    pinMode((tracks[i].pin + LEDOFFSET), OUTPUT);
    #endif

    unsigned long dur = pgm_read_dword(&(tracks[i].durs[msize[i] - 1]));  //calculate total song duration
    totalduration = (totalduration > dur) ? totalduration : dur;          //
    
  }

  buzzer[0].play(440, 250); //plays a note when setup has been completed

  //wait for button to be pressed, if enabled
  #ifdef BUTTON_START
  while(!digitalRead(BUTTONPIN)){
   delay(1);
  }
  #endif

  delay(START_DELAY);

  Serial.println("Playing...");

 
}

void loop(){


  for(int i = 0; i < TRACKS; i++){  //skips duplicate notes at beginning of song (usually garbage notes)

    note[i] = pgm_read_dword(&(tracks[i].durs[counter[i]]));
    while(note[i] == pgm_read_dword(&(tracks[i].durs[counter[i] + 1]))){
      counter[i]++;
      note[i] = pgm_read_dword(&(tracks[i].durs[counter[i]]));
    }
    freq[i] = (counter[i] > 0) ? pgm_read_word(&(tracks[i].freqs[counter[i] - 1])) : 0;
  }


  offset = millis();

  while(duration <= totalduration){ //if song should be playing
    duration = millis() - offset; //how long song has been playing
    
    for(int i = 0; i < TRACKS; i++){
      if(counter[i] < msize[i]){  //make sure we're within bounds of this track

        if(freq[i] > 0){
          buzzer[i].play(freq[i]);  //play buzzer...
        } else {
          buzzer[i].stop();         //or don't
        }

        if(duration >= note[i]){  //moving to next note
          counter[i]++;
          if(counter[i] < msize[i]){
            freq[i] = pgm_read_word(&(tracks[i].freqs[counter[i] - 1]));
            note[i] = pgm_read_dword(&(tracks[i].durs[counter[i]]));
          }
        }
      } else {
        buzzer[i].stop(); //outside of track, keep buzzer quiet
      }
      #ifdef LIGHTDISPLAY //set LED to on/off
      if(buzzer[i].isPlaying()){
        digitalWrite((tracks[i].pin + LEDOFFSET), HIGH);
      } else {
        digitalWrite((tracks[i].pin + LEDOFFSET), LOW);
      }
      #endif
    }
    
  }
  
  duration = 0; //reset all counters
  
  for(int i = 0; i < TRACKS; i++){ //
    counter[i] = 0;
    buzzer[i].stop();
  }
  delay(LOOP_DELAY);
  
}


