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
  for(int i=255;i>=0;i-=15){
    analogWrite(rled,i);
    for(int j=255;j>=0;j-=5){
      analogWrite(gled,j);
      for(int k=255;k>=0;k-=1){
        analogWrite(bled,k);
      }
    }
  }
  MIDI.begin(MIDI_CHANNEL_OMNI);
  //start the serial into the boud rate of 115200
  Serial.begin(115200);
}
void loop(){
  //check for a midi message
  if (MIDI.read()){
      note = MIDI.getData1();
      velocity = MIDI.getData2();
      //check if the message is a cc midi message
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        //controll the leds acording to the data bytes
        analogWrite(rled,velocity*2);
        analogWrite(gled,note+velocity);
        analogWrite(bled,note*2);
  }
}


  
  
