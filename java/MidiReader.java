import java.io.File;
import java.io.PrintWriter;
import java.util.Scanner;

import javax.sound.midi.MidiEvent;
import javax.sound.midi.MidiMessage;
import javax.sound.midi.MidiSystem;
import javax.sound.midi.Sequence;
import javax.sound.midi.ShortMessage;
import javax.sound.midi.Track;

public class MidiReader {
	public static final int NOTE_ON = 0x90;
	public static final int NOTE_OFF = 0x80;

	public static void main(String[] args) throws Exception {

		String filename;
		Scanner scan = new Scanner(System.in);
		
		PrintWriter writer = null;

		Sequence sequence;

		long timestamp = 0;
		int frequency = 0;
		int trackNumber = 0;
		double timestampConverter = 1;
		
		int tracks;
		int pin[];
		int length[];
		
		
		
		System.out.println("Creating melody.h...");
		if(new File("./arduino/MidiPlayer/melody.h").exists()){
			System.out.print("melody.h already exists. Is it okay to overwrite it? (y/n) ");
			if(!scan.nextLine().equals("y")){
				System.out.println("Quitting...");
				System.exit(1);
			} 
		} else {
			new File("./arduino/MidiPlayer/").mkdirs();
		}
		
		writer = new PrintWriter("./arduino/MidiPlayer/melody.h", "UTF-8");
		System.out.println("Created melody.h");

		while (true) {	//loops until working filename is entered

			System.out.print("Enter the name of the MIDI file: ");
			filename = scan.nextLine();

			try {

				sequence = MidiSystem.getSequence(new File("./midi/" + filename));	//creating MIDI sequence

			} catch (Exception exception) {
				System.out.println("Error reading file " + filename + ": " + exception);
				continue;
			}
			break;
		}
		
		
		timestampConverter = ((sequence.getMicrosecondLength() / 1000.0) / sequence.getTickLength());	//conversion rate for MIDI ticks to milliseconds
		
		tracks = sequence.getTracks().length;	//getting tracks
		pin = new int[tracks];					//info arrays
		length = new int[tracks];
		
		
		writer.println("#include \"common.h\"");		//writing out melody.h file
		writer.println();
		writer.println("#define TRACKS " + tracks);
		writer.println();

		for (Track track : sequence.getTracks()) {		//looping through tracks (1 track to 1 buzzer)
			trackNumber++;
			timestamp = 0;
			length[trackNumber - 1] = 0;
			System.out.print("Which buzzer pin is track " + trackNumber + " on? ");	//getting buzzer pin
			pin[trackNumber - 1] = scan.nextInt();
			writer.println("const uint32_t d" + trackNumber + "[] PROGMEM = {");
			for (int i = 0; i < track.size(); i++) {	//iterating through notes to get timestamps
				MidiEvent event = track.get(i);
				MidiMessage message = event.getMessage();
				if (message instanceof ShortMessage) {	//making sure message is valid message
					timestamp = event.getTick();

					writer.print(((long)(timestamp*timestampConverter)) + ",");	//converting to milliseconds and writing to melody.h
					length[trackNumber - 1]++;
				} 
			}

			writer.println();
			writer.println("};");
			writer.println();

			writer.println("const uint16_t m" + trackNumber + "[] PROGMEM = {");
			for (int i = 0; i < track.size(); i++) {	//iterating through notes to get frequencies
				MidiEvent event = track.get(i);
				MidiMessage message = event.getMessage();
				if (message instanceof ShortMessage) {	//making sure message is valid message
					ShortMessage sm = (ShortMessage) message;

					if (sm.getCommand() == NOTE_OFF) {	//whether event is the end of note...
						frequency = 0;
					} else if (sm.getCommand() == NOTE_ON) {	//or start of note
						frequency = (int) ((Math.pow(2.0, (sm.getData1() - 69.0) / 12.0)) * 440.0); // converts key # to frequency (in Hertz)
					}

					writer.print(frequency + ",");	//writing to melody.h

				} 
			}
			
			writer.println();
			writer.println("};");
			writer.println();
			writer.println();

		}
		
		writer.println("Track tracks[] = {");	//writing out array of Track structs
		for(int i = 0; i<tracks; i++){
			writer.println("{" + pin[i] + ", m" + (i+1) + ", d" + (i+1) + ", " + length[i] + "},");
		}
		writer.println("};");
		
		scan.close();
		writer.close();
		System.out.println("Finished writing to melody.h!");

	}

}