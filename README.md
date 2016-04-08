# Midi2Arduino

**Note: An Arduino Mega is highly recommended for running this program! Any other boards are currently NOT supported.**

### Setting up Midi2Arduino:

- Download and unzip the GitHub repository somewhere on your computer.
- Install the ToneLib library (libraries/ToneLib) as you would any 3rd party library.
- Navigate to C:\Program Files (x86)\Arduino\hardware\arduino\avr\cores\arduino and remove Tone.cpp (this is important!) I suggest backing up Tone.cpp to another location if you ever want it again. If you delete it completely, you'll have to reinstall the Arduino IDE to get it back.

### Using Midi2Arduino:

- Place your MIDI file in the /midi directory (or use one of the pre-supplied MIDIs)
- Double-click run.bat and choose your MIDI file. For example, "Spider Dance.mid". Then, enter the appropriate buzzer pins for your board. Make sure to save melody.h somewhere else if you want to keep it!
- Navigate to /arduino/MidiPlayer and upload MidiPlayer.ino to your board. 
- The song should begin to play!

### Creating your own MIDI files

*Coming soon!*


###### Make sure to check out [my Youtube Channel](https://www.youtube.com/channel/UCkn26hEGG7ti14K8dsaPTEA) for more info and demonstrations.
