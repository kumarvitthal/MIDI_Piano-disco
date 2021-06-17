# MIDI_Piano-disco
This is an Arduino based project, where RBG LED strip is controlled by a Keyboard(Piano). Keyboard generates the MIDI signal and it is bridged to the Arduino. Based on the midi message, the intensity of red, green, and blue component of the led is varied.

MIDI is a music description language in digital form. It is used to communicate between musical instrumentation. A midi message consist at maximum of three bytes:
The first one is Status Byte. It holds the information that is noteOn/Off and channel number.
The other two bytes are Data Bytes. They hold information about Note Number (Eg= 36 i.e. C3) and Note Velocity.

**Communication**
Use a midi-USB cable to connect your Keyboard to the PC. Download "hairless midi" as it will connect the midi device to the serial of the Arduino and debug the messages too. Check the baud rate of hairless midi.

**Circuit**
In the circuit, we use three n-channel MOSFETs, resistors, DC 12V supply. 
The gate of the MOSFETs is connected to PWM pins of the arduino in order to control the brightness. The drain of the MOSFETs is connected to the R,G,B pins of the LED strip. The source of the MOSFETs is connected to the 12V DC. The common pin of the LED is then connected to the ground. 
