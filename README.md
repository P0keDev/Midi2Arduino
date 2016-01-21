# Midi2Arduino

Setting up Midi2Arduino:

- Install the ToneLib library (libraries/ToneLib) as you would any 3rd party library.
- Navigate to C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino and remove Tone.cpp (this is important!) I suggest backing up Tone.cpp to another location if you ever want it again. If you delete it completely, you'll have to reinstall the Arduino IDE to get it back.
- Copy and paste the frequencies and durations in melodyX and mXdurs, respectively. If you use more than the 1st track, make sure to uncomment the define statements at the top (#define TRACKX) and make sure your buzzer pins are defined correctly (#define MXBUZZER PIN).
- Upload the program to your board, and it should begin playing. If not, make sure your buzzer pins are correct.

__Each board can only use a certain number of tracks__

The Arduino Uno can use up to 2, the Arduino Mega can use up to 5.
