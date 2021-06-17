#include<MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE();
#define rled 5
#define gled 9
#define bled 11
int note, velocity;

void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(bled,OUTPUT);
  //test the leds
  for (int glow = 0 ; glow <= 255; glow += 5) {
    analogWrite(rled, glow);
    delay(10);
  }
  for (int glow = 255 ; glow >= 0; glow -= 5) {
    analogWrite(rled, glow);
    delay(10);
  }
  for (int glow = 0 ; glow <= 255; glow += 5) {
    analogWrite(gled, glow);
    delay(10);
  }
  for (int glow = 255 ; glow >= 0; glow -= 5) {
    analogWrite(gled, glow);
    delay(10);
  }
  for (int glow = 0 ; glow <= 255; glow += 5) {
    analogWrite(bled, glow);
    delay(10);
  }
  for (int glow = 255 ; glow >= 0; glow -= 5) {
    analogWrite(bled, glow);
    delay(10);
  }
  //MIDI_CHANNEL_OMNI receives all 16 channels
  MIDI.begin(MIDI_CHANNEL_OMNI);  
  //start the serial into the boud rate of 115200
  Serial.begin(115200);
}
void loop(){
  //check for a midi message
  if (MIDI.read()){
    byte ntype = MIDI.getType();
    note = MIDI.getData1();
    velocity = MIDI.getData2();
    //Check if midi message is received
    digitalWrite(LED_BUILTIN, HIGH);
    delay(10);
    digitalWrite(LED_BUILTIN, LOW);
    delay(10);
    //controll the leds acording to the data bytes
    if(note<=56){ 
      analogWrite(gled,velocity*2); 
      delay(10); 
      analogWrite(gled, 0);
    }
    else if(note>=56 && note<=76){ 
      analogWrite(bled,velocity*2); 
      delay(10); 
      analogWrite(bled, 0);
    }
    else if(note>=76){ 
      analogWrite(rled,velocity);
      delay(10); 
      analogWrite(rled,0);
    }
  }
}
