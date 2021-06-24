#include <arduinoFFT.h>
#include <SPI.h>
#define SAMPLES 64
#define CLK_PIN   13
#define DATA_PIN  11
#define  rgb 32
#define rled 5
#define gled 9
#define bled 11
double vReal[SAMPLES];
double vImag[SAMPLES];
char data_avgs[rgb];
int glow;
arduinoFFT FFT = arduinoFFT();
void setup() {
  ADCSRA = 0b11100101;
  ADMUX = 0b00000000;
//  begin();
  delay(50);
}
void loop() {
      
    for (int i = 0; i < SAMPLES; i++)
    {
      while (!(ADCSRA & 0x10));
      ADCSRA = 0b11110101 ;
      int value = ADC - 512 ;
      vReal[i] = value / 8;
      vImag[i] = 0;
    }
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);
    int step = (SAMPLES / 2) / rgb;
    int c = 0;
    for (int i = 0; i < (SAMPLES / 2); i += step)
    {
      data_avgs[c] = 0;
      for (int k = 0 ; k < step ; k++) {
        data_avgs[c] = data_avgs[c] + vReal[i + k];
      }
      data_avgs[c] = data_avgs[c] / step;
      c++;
    }

    for (int i = 0; i < rgb; i++){
      data_avgs[i] = constrain(data_avgs[i], 0, 40);
      data_avgs[i] = map(data_avgs[i], 0, 40, 0, 255);
      glow = data_avgs[i];
      if(glow<64){  
        analogWrite(bled,glow*4); 
        delay(10); 
        analogWrite(bled,0);
      }
      else if(glow>=64 && glow<128){  
        analogWrite(bled,glow*2); 
        analogWrite(gled,255-glow); 
        delay(10); 
        analogWrite(bled,0); 
        analogWrite(gled,0);
      }
      else if(glow>=128 && glow<192){
        analogWrite(rled,glow*5/4); 
        analogWrite(bled,350-glow); 
        delay(10); 
        analogWrite(bled,0); 
        analogWrite(rled,0);
      }
      else{
        analogWrite(rled,glow); 
        delay(10); 
        analogWrite(rled,0);
      }
    }
}
