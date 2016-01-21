#include <ToneLib.h>

#include <avr/pgmspace.h>


#define DUR_MULTIPLIER 1.0   //If tempo is incorrect, change this value. multiplier > 1 will be slower, multiplier < 1 will be faster.

#define START_DELAY 3000    //Time (in ms) program will wait before starting the song.

#define LOOP_DELAY 3000     //Time (in ms) program will wait before playing through song again. Increase for longer time, decrease for shorter. 0 will replay song immediately.

#define M1BUZZER 3
#define M2BUZZER 4
#define M3BUZZER 5
#define M4BUZZER 6
#define M5BUZZER 7

//#define TRACK2
//#define TRACK3
//#define TRACK4
//#define TRACK5

unsigned long duration = 0;
unsigned long totalduration = 0;
unsigned long offset = 0;

int m1size = 0;
unsigned long m1note = 0;
int m1freq = 0;
int m1counter = 0;
Tone b1;

int m2size = 0;
unsigned long m2note = 0;
int m2freq = 0;
int m2counter = 0;
Tone b2;

int m3size = 0;
unsigned long m3note = 0;
int m3freq = 0;
int m3counter = 0;
Tone b3;

int m4size = 0;
unsigned long m4note = 0;
int m4freq = 0;
int m4counter = 0;
Tone b4;

int m5size = 0;
unsigned long m5note = 0;
int m5freq = 0;
int m5counter = 0;
Tone b5;


//////////////////////////////////////Track 1//////////////////////////////////////////
//durations
const uint32_t m1durs[] PROGMEM = {

};
//frequencies
const uint16_t melody1[] PROGMEM = {

};


//////////////////////////////////////Track 1//////////////////////////////////////////

//////////////////////////////////////Track 2//////////////////////////////////////////
#ifdef TRACK2
const uint32_t m2durs[] PROGMEM = {

};

const uint16_t melody2[] PROGMEM = {

};
#endif
//////////////////////////////////////Track 2//////////////////////////////////////////

//////////////////////////////////////Track 3//////////////////////////////////////////
#ifdef TRACK3
const uint32_t m3durs[] PROGMEM = {

};

const uint16_t melody3[] PROGMEM = {

};
#endif
//////////////////////////////////////Track 3//////////////////////////////////////////

//////////////////////////////////////Track 4//////////////////////////////////////////
#ifdef TRACK4
const uint32_t m4durs[] PROGMEM = {

};

const uint16_t melody4[] PROGMEM = {

};
#endif
//////////////////////////////////////Track 4//////////////////////////////////////////

//////////////////////////////////////Track 5//////////////////////////////////////////
#ifdef TRACK5
const uint32_t m5durs[] PROGMEM = {

};

const uint16_t melody5[] PROGMEM = {

};
#endif
//////////////////////////////////////Track 5//////////////////////////////////////////


void setup(){

  Serial.begin(250000);

  unsigned long placeholderduration = 0;

  b1.begin(M1BUZZER);

  m1size = sizeof(melody1) / sizeof(melody1[0]);
  placeholderduration = pgm_read_dword(&m1durs[m1size-1]);
  
  totalduration = (totalduration > placeholderduration) ? totalduration : placeholderduration;
  placeholderduration = 0;
  
  #ifdef TRACK2

  b2.begin(M2BUZZER);
  
  m2size = sizeof(melody2) / sizeof(melody2[0]);
  
  placeholderduration = pgm_read_dword(&m2durs[m2size-1]);
  
  totalduration = (totalduration > placeholderduration) ? totalduration : placeholderduration;
  placeholderduration = 0;
  #endif

  #ifdef TRACK3

  b3.begin(M3BUZZER);
  
  m3size = sizeof(melody3) / sizeof(melody3[0]);
  placeholderduration = pgm_read_dword(&m3durs[m3size-1]);
  
  totalduration = (totalduration > placeholderduration) ? totalduration : placeholderduration;
  placeholderduration = 0;
  #endif

  #ifdef TRACK4

  b4.begin(M4BUZZER);
  
  m4size = sizeof(melody4) / sizeof(melody4[0]);
  
  placeholderduration = pgm_read_dword(&m4durs[m4size-1]);
  
  totalduration = (totalduration > placeholderduration) ? totalduration : placeholderduration;
  placeholderduration = 0;
  #endif

  #ifdef TRACK5

  b5.begin(M5BUZZER);
  
  m5size = sizeof(melody5) / sizeof(melody5[0]);
  
  placeholderduration = pgm_read_dword(&m5durs[m5size-1]);
  
  totalduration = (totalduration > placeholderduration) ? totalduration : placeholderduration;
  placeholderduration = 0;
  #endif

  b1.play(440, 250); //plays a note when setup has been completed

  Serial.println(millis());

  delay(START_DELAY);

  Serial.println("Playing...");

 
}

void loop(){


  m1note = pgm_read_dword(&m1durs[m1counter]);

  while(m1note == pgm_read_dword(&m1durs[m1counter + 1])){
    m1counter++;
    m1note = pgm_read_dword(&m1durs[m1counter]);
  }
  m1freq = (m1counter > 0) ? pgm_read_dword(&melody1[m1counter-1]) : 0;

  #ifdef TRACK2

  m2note = pgm_read_dword(&m2durs[m2counter]);

  while(m2note == pgm_read_dword(&m2durs[m2counter + 1])){
    m2counter++;
    m2note = pgm_read_dword(&m2durs[m2counter]);
  }
  m2freq = (m2counter > 0) ? pgm_read_dword(&melody2[m2counter-1]) : 0;

  #endif

  #ifdef TRACK3

  m3note = pgm_read_dword(&m3durs[m3counter]);

  while(m3note == pgm_read_dword(&m3durs[m3counter + 1])){
    m3counter++;
    m3note = pgm_read_dword(&m3durs[m3counter]);
  }
  m3freq = (m3counter > 0) ? pgm_read_dword(&melody3[m3counter-1]) : 0;

  #endif

  #ifdef TRACK4

  m4note = pgm_read_dword(&m4durs[m4counter]);

  while(m4note == pgm_read_dword(&m4durs[m4counter + 1])){
    m4counter++;
    m4note = pgm_read_dword(&m4durs[m4counter]);
  }
  m4freq = (m4counter > 0) ? pgm_read_dword(&melody4[m4counter-1]) : 0;

  #endif

  #ifdef TRACK5

  m5note = pgm_read_dword(&m5durs[m5counter]);

  while(m5note == pgm_read_dword(&m5durs[m5counter + 1])){
    m5counter++;
    m5note = pgm_read_dword(&m5durs[m5counter]);
  }
  m5freq = (m5counter > 0) ? pgm_read_dword(&melody5[m5counter-1]) : 0;

  #endif

  offset = millis();

  Serial.println(totalduration);

  while(duration <= totalduration){
    //Serial.println("Looping!");
    duration = millis() - offset;
    //Serial.println(duration);
    /////////////////////////////Track 1///////////////////////////////////////
    
    if(m1counter < m1size){
      //Serial.println("Within array!");
      if(m1freq > 0){
        b1.play(m1freq); 
        Serial.println(m1freq);
      } else {
        b1.stop(); 
      }
      
      if(duration >= m1note){
        m1counter++;
        while(m1counter + 1 > m1size && pgm_read_dword(&m1durs[m1counter]) == pgm_read_dword(&m1durs[m1counter + 1])){
          m1counter ++;
        }
        if(m1counter < m1size){
          m1freq = pgm_read_dword(&melody1[m1counter - 1]);
          m1note = pgm_read_dword(&m1durs[m1counter]);
        }
        
      }
      
    } else {
      b1.stop();
    }

    #ifdef TRACK2


    if(m2counter < m2size){
      //Serial.println("Within array!");
      if(m2freq > 0){
        b2.play(m2freq);        
      } else {
        b2.stop(); 
      }
      
      if(duration >= m2note){
        m2counter++;
        while(m2counter + 1 > m2size && pgm_read_dword(&m2durs[m2counter]) == pgm_read_dword(&m2durs[m2counter + 1])){
          m2counter ++;
        }
        if(m2counter < m2size){
          m2freq = pgm_read_dword(&melody2[m2counter - 1]);
          m2note = pgm_read_dword(&m2durs[m2counter]);
        }
        
      }
      
    } else {
      b2.stop();
    }

    #endif


    #ifdef TRACK3


    if(m3counter < m3size){
      //Serial.println("Within array!");
      if(m3freq > 0){
        b3.play(m3freq);        
      } else {
        b3.stop(); 
      }
      
      if(duration >= m3note){
        m3counter++;
        while(m3counter + 1 > m3size && pgm_read_dword(&m3durs[m3counter]) == pgm_read_dword(&m3durs[m3counter + 1])){
          m3counter ++;
        }
        if(m3counter < m3size){
          m3freq = pgm_read_dword(&melody3[m3counter - 1]);
          m3note = pgm_read_dword(&m3durs[m3counter]);
        }
        
      }
      
    } else {
      b3.stop();
    }

    #endif


    #ifdef TRACK4


    if(m4counter < m4size){
      //Serial.println("Within array!");
      if(m4freq > 0){
        b4.play(m4freq);        
      } else {
        b4.stop(); 
      }
      
      if(duration >= m4note){
        m4counter++;
        while(m4counter + 1 > m4size && pgm_read_dword(&m4durs[m4counter]) == pgm_read_dword(&m4durs[m4counter + 1])){
          m4counter ++;
        }
        if(m4counter < m4size){
          m4freq = pgm_read_dword(&melody4[m4counter - 1]);
          m4note = pgm_read_dword(&m4durs[m4counter]);
        }
        
      }
      
    } else {
      b4.stop();
    }

    #endif


    #ifdef TRACK5


    if(m5counter < m5size){
      //Serial.println("Within array!");
      if(m5freq > 0){
        b5.play(m5freq);        
      } else {
        b5.stop(); 
      }
      
      if(duration >= m5note){
        m5counter++;
        while(m5counter + 1 > m5size && pgm_read_dword(&m5durs[m5counter]) == pgm_read_dword(&m5durs[m5counter + 1])){
          m5counter ++;
        }
        if(m5counter < m5size){
          m5freq = pgm_read_dword(&melody5[m5counter - 1]);
          m5note = pgm_read_dword(&m5durs[m5counter]);
        }
        
      }
      
    } else {
      b5.stop();
    }

    #endif
    
  }
  duration = 0;
  
  m1counter = 0;
  
  m2counter = 0;
  
  m3counter = 0;
  
  m4counter = 0;
  
  m5counter = 0;
  b1.stop();
  #ifdef TRACK2
  b2.stop();
  #endif
  #ifdef TRACK3
  b3.stop();
  #endif
  #ifdef TRACK4
  b4.stop();
  #endif
  #ifdef TRACK5
  b5.stop();
  #endif
  delay(LOOP_DELAY);
  
}


