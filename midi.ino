#include<MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
int rled = 9;
int gled = 10;
int bled = 11;
int note, velocity;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(bled,OUTPUT);
  //test the leds
  for(int i=255;i>=0;i--) analogWrite(rled,i);
  for(int j=255;j>=0;j--) analogWrite(gled,j);
  for(int k=255;k>=0;k--) analogWrite(bled,k);
  
  MIDI.begin(MIDI_CHANNEL_OMNI); //MIDI_CHANNEL_OMNI receives all 16 channels
  //start the serial into the boud rate of 115200
  Serial.begin(115200);
}

void loop(){
  //check for a midi message
  if (MIDI.read()){
    byte ntype = MIDI.getType();
    note = MIDI.getData1();
    velocity = MIDI.getData2();
    
    digitalWrite(LED_BUILTIN, HIGH);
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
    delay(500);
    //controll the leds acording to the data bytes
    analogWrite(bled,note*3-35);delay(100); analogWrite(bled,0);
    if(ntype == 0x90){ analogWrite(rled,velocity*2);delay(100); analogWrite(rled, 0);} // NoteOn is 0x90 
    if(ntype == 0x80){ analogWrite(gled,velocity);delay(100); analogWrite(gled, 0);} // NoteOff is 0x80
  }
}
