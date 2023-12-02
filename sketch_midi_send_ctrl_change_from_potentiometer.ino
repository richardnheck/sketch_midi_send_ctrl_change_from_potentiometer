#include <MIDI.h>

struct MySettings : public midi::DefaultSettings
{
  static const long BaudRate = 115200;  // Set a baud rate that Hairless midi can handle.  The default settings do not work
};
MIDI_CREATE_CUSTOM_INSTANCE(HardwareSerial, Serial, MIDI, MySettings);

const int potPin = A0;  // Analog pin for the potentiometer
const int midiChannel = 1;  // MIDI channel (1-16)
const int controlChangeNumber = 1;  // MIDI control change number (0-127)

void setup() {
  // Initialize the MIDI library
  MIDI.begin();
}

void loop() {
  // Read the value from the potentiometer
  int potValue = analogRead(potPin);

  // Map the potentiometer value to the MIDI control change range (0-127)
  int midiValue = map(potValue, 0, 1023, 0, 127);

  // Send MIDI control change message
  MIDI.sendControlChange(controlChangeNumber, midiValue, midiChannel);

  delay(10);  // Add a small delay to avoid sending too many messages in a short time
}
