int rled = 2;
int gled = 3;
int bled = 4;
//cc midi messages three bytes
byte statusByte;
byte ControllerNumber;
byte ControllerValue;
//cc midi message channel 1  1011 0000
byte ccmidi = 176;

void setup(){
  pinMode(rled,OUTPUT);
  pinMode(gled,OUTPUT);
  pinMode(bled,OUTPUT);
  //test the leds
  for(int i=0;i<255;i++){
    for(int j=0;j<255;j++){
      for(int k=0;k<255;k++){
        analogWrite(bled,k);
        delay(1);
      }
      analogWrite(gled,j);
      delay(1);
    }
    analogWrite(rled,i);
    delay(1);
  }
  //start the serial into the boud rate of 115200
  Serial.begin(115200);
}
void loop(){
  //wait for a midi message
  while(Serial.available() <3);
  //run the function that will control the leds
  readmidi();
  
  }
void readmidi(){
  
  do{
    //check if there is any message
    if (Serial.available()){
      //store the data into the variables 
      statusByte = Serial.read();
      ControllerNumber = Serial.read();
      ControllerValue = Serial.read(); 
      //check if the message is a cc midi message
      if (statusByte==ccmidi){
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
        //Serial monitor wont work when you open the COM port of Arduino in hairless midi
//         Serial.print(statusByte);
//         Serial.print(ControllerNumber);
//         Serial.print(ControllerValue);
        //controll the leds acording to the data bytes
        if(ControllerNumber>=21 && ControllerNumber<=24) analogWrite(rled,ControllerValue*2);
        if(ControllerNumber>=25 && ControllerNumber<=28) analogWrite(gled,ControllerValue*2);
        if(ControllerNumber>=29 && ControllerNumber<=32) analogWrite(bled,ControllerValue*2); 
      }
    }
  }
  //repeat until there is no message
  while (Serial.available() > 2);
}
