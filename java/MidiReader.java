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
		long timestamp_old = 0;
		int duration = 0;
		int duration_next = 0;
		int frequency = 0;
		int frequency_old;
		int trackNumber = 0;
		int buzzerpin = 0;
		double timestampConverter = 1;
		
		
		
		System.out.println("Creating melody.h...");
		if(new File("./arduino/MidiPlayer/melody.h").exists()){
			System.out.print("melody.h already exists. Is it okay to overwrite it? (y/n) ");
			if(!scan.nextLine().equals("y")){
				System.out.println("Quitting...");
				System.exit(1);
				}
		}
		
		writer = new PrintWriter("./arduino/MidiPlayer/melody.h", "UTF-8");
		System.out.println("Created melody.h");
		
		

		while (true) {

			System.out.print("Enter the name of the MIDI file: ");
			filename = scan.nextLine();

			try {

				sequence = MidiSystem.getSequence(new File("./midi/" + filename));

			} catch (Exception exception) {
				System.out.println("Error reading file " + filename + ": " + exception);
				continue;
			}
			break;
		}
		
		
		timestampConverter = ((sequence.getMicrosecondLength() / 1000.0) / sequence.getTickLength());
		

		for (Track track : sequence.getTracks()) {
			trackNumber++;
			timestamp = 0;
			timestamp_old = 0;
			writer.println("#define TRACK" + trackNumber);
			System.out.print("Which buzzer pin is track " + trackNumber + " on? ");
			buzzerpin = scan.nextInt();
			writer.println("#define M" + trackNumber + "BUZZER " + buzzerpin);
			writer.println();
			writer.println("const uint32_t m" + trackNumber + "durs[] PROGMEM = {");
			for (int i = 0; i < track.size(); i++) {
				MidiEvent event = track.get(i);
				// System.out.print("@" + event.getTick() + "\t");
				MidiMessage message = event.getMessage();
				if (message instanceof ShortMessage) {
					ShortMessage sm = (ShortMessage) message;
					// if (sm.getCommand() == NOTE_ON) {
					// System.out.print(" NOTE ON  ");
					// } else if (sm.getCommand() == NOTE_OFF) {
					// System.out.print(" NOTE OFF  ");
					// } else {
					// System.out.println("Command:" +
					// sm.getCommand());
					// }

					// System.out.print("@" + event.getTick() + "\t"); // uncomment for debug

					timestamp_old = timestamp;
					timestamp = event.getTick();
					MidiEvent event_next = track.get(i + 1);
					ShortMessage sm_next = null;
					if (event_next.getMessage() instanceof ShortMessage) {
						sm_next = (ShortMessage) (event_next.getMessage());
					}

					if (duration_next != 0) {
						if (event_next.getTick() == timestamp && sm_next.getCommand() == NOTE_OFF && sm.getCommand() == NOTE_OFF) { // Multiple note detection
							duration = 0;
							// duration_next continues to next note in chord
						} else {
							duration = duration_next; // last note in chord, duration set correctly
							duration_next = 0;
						}

					} else {

						if (event_next.getTick() == timestamp && sm_next.getCommand() == NOTE_OFF && (sm.getCommand() == NOTE_OFF || sm.getCommand() == NOTE_ON)) { // Multiple note detection
							duration = 0;
							duration_next = (int) (timestamp - timestamp_old);

						} else {
							duration = (int) (timestamp - timestamp_old);
						}
					}

					writer.print(((long)(timestamp*timestampConverter)) + ",");

				} else {
					// Sysetm.out.println("Other command: " + sm.getCommand());
				}
			}

			writer.println();
			writer.println("};");
			writer.println();
			timestamp = 0;
			timestamp_old = 0;

			writer.println("const uint16_t melody" + trackNumber + "[] PROGMEM = {");
			for (int i = 0; i < track.size(); i++) {
				MidiEvent event = track.get(i);
				// System.out.print("@" + event.getTick() + "\t");
				MidiMessage message = event.getMessage();
				if (message instanceof ShortMessage) {
					ShortMessage sm = (ShortMessage) message;
					// if (sm.getCommand() == NOTE_ON) {
					// System.out.println("NOTE ON");
					// } else if (sm.getCommand() == NOTE_OFF) {
					// System.out.print("NOTE OFF");
					// } else {
					// System.out.println("Command:" + sm.getCommand());
					// }

					// System.out.print("@" + event.getTick() + "\t"); // uncomment for debug

					timestamp = event.getTick();
					timestamp_old = 0;

					if (sm.getCommand() == NOTE_OFF) {

						frequency = 0;

					} else if (sm.getCommand() == NOTE_ON) {

						frequency = (int) ((Math.pow(2.0, (sm.getData1() - 69.0) / 12.0)) * 440.0); // converts key # to frequency (in Hertz)

						/*for (int j = 1; j <= 5; j++) {
							timestamp_old = track.get(i - j).getTick();
							ShortMessage sm_old = null;
							if (track.get(i - j).getMessage() instanceof ShortMessage) {
								sm_old = (ShortMessage) track.get(i - j).getMessage();
							}
							if (timestamp_old == timestamp && sm_old.getCommand() == NOTE_ON) {
								frequency_old = (int) ((Math.pow(2.0, (sm_old.getData1() - 69.0) / 12.0)) * 440.0);

								frequency = (frequency > frequency_old) ? frequency : frequency_old;
							} else {
								break;
							}

						}*/

					}

					writer.print(frequency + ",");

				} else {
					// System.out.println("Other message: " + message.getClass());
				}

			}
			
			writer.println();
			writer.println("};");
			writer.println();
			writer.println();

		}
		
		scan.close();
		writer.close();
		System.out.println("Finished writing to melody.h!");

	}

}