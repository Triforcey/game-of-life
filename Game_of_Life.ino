//color of the dots ({red, green, blue} max value 255 each]
int colorOfPattern[3] = {30, 0, 0};
//color of background
int colorOfBackground[3] = {0, 0, 30};
//-------------------------
boolean buttonVal = LOW;
boolean oldButtonVal = LOW;
int timeValii;
int timeVal;
int button = 8;
int lightCount;
int ledPixels[12][12];
int ledPixelsRaw[12][12];

//randomSeed(analogRead(0));
// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 1000; // delay for half a second

void setup() {
  randomSeed(analogRead(0));
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  
  pinMode(button, INPUT);

  pixels.begin(); // This initializes the NeoPixel library.
  resetNeopixel();
  //pixels.show();
}

void resetNeopixel() {
  int k = 1;
  for(int i = 1; k < 9; i++){
    ledPixels[k][i] = random(0, 2);
    if(ledPixels[k][i] == 1){
      pixels.setPixelColor((k - 1) * 8 + (i - 1), pixels.Color(colorOfPattern[0], colorOfPattern[1], colorOfPattern[2]));
      ledPixelsRaw[k][i] = 1;
      //ledPixels[i] = 1;
    }
    else{
      pixels.setPixelColor((k - 1) * 8 + (i - 1), pixels.Color(colorOfBackground[0], colorOfBackground[1], colorOfBackground[2]));
      ledPixelsRaw[k][i] = 0;
      //ledPixels[i] = 0;
    }
    if(i == 8){
      i = 0;
      k++;
    }
    //pixels.show();
  }
  timeValii = millis();
  pixels.show();
  
  //resetNeopixel();
  //delay(1000);
}



void loop(){
  int k = 1;
  //oldButtonVal;
  //timeVal;
  buttonVal = digitalRead(button);
  
  if(buttonVal == HIGH && millis() - timeVal >= 500 && oldButtonVal == LOW){
    resetNeopixel();
    timeVal = millis();
    timeValii = millis();
  }
  
  oldButtonVal = buttonVal;
  
  //pixels.show();
  
  delay(delayval);
  /*if(millis() - timeValii >= delayval){
    timeValii = millis();*/
  k = 1;
  //resetNeopixel();
  for(int i = 1; k < 9; i++){
    lightCount = 0;
    //if(k - 1 >= 0 && i - 1 >= 0 && i > 0 && k > 0){
      if(ledPixels[k - 1][i - 1] == 1){
      lightCount++;
      }
    //}
    //if(k - 1 >= 0 && i >= 0 && k > 0){
      if(ledPixels[k - 1][i] == 1){
      lightCount++;
      }
    //}
    //if(k - 1 >= 0 && i + 1 >= 0 && i < 8 && k > 0){
      if(ledPixels[k - 1][i + 1] == 1){
      lightCount++;
      }
    //}
    //if(k >= 0 && i - 1 >= 0 && i > 0){
      if(ledPixels[k][i - 1] == 1){
      lightCount++;
      }
    //}
    //if(k >= 0 && i + 1 >= 0 && i < 8){
      if(ledPixels[k][i + 1] == 1){
      lightCount++;
      }
    //}
    //if(k + 1 >= 0 && i - 1 >= 0 && i > 0 && k < 8){
      if(ledPixels[k + 1][i - 1] == 1){
      lightCount++;
      }
    //}
    //if(k + 1 >= 0 && i >= 0 && k < 8){
      if(ledPixels[k + 1][i] == 1){
      lightCount++;
      }
    //}
    //if(k + 1 >= 0 && i + 1 >= 0 && i < 8 && k < 8){
      if(ledPixels[k + 1][i + 1] == 1){
      lightCount++;
      }
    //}
    if(lightCount < 2 || lightCount > 3){
      ledPixelsRaw[k][i] = 0;
      pixels.setPixelColor((k - 1) * 8 + (i - 1), pixels.Color(colorOfBackground[0], colorOfBackground[1], colorOfBackground[2]));
    }
    if(lightCount == 3){
      ledPixelsRaw[k][i] = 1;
      pixels.setPixelColor((k - 1) * 8 + (i - 1), pixels.Color(colorOfPattern[0], colorOfPattern[1], colorOfPattern[2]));
    }
    if(i == 8){
    i = 0;
    k++;
  }
  }
  k = 1;
  for(int i = 1; k < 9; i++){
    ledPixels[k][i] = ledPixelsRaw[k][i];
    if(i == 8){
    i = 0;
    k++;
  }}
  pixels.show();
  //delay(1000);
  //pixels.setPixelColor(0, pixels.Color(50, 0, 0));
  //pixels.show();
  //delay(500);
}//}
