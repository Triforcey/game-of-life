//color of the dots ({red, green, blue} max value 255 each]
int colorOfPattern[3] = {0, 30, 0};
//color of background
int colorOfBackground[3] = {0, 0, 10};
//-------------------------
boolean buttonVal = LOW;
boolean oldButtonVal = LOW;
int timeValii;
int timeVal;
int button = 8;
int lightCount;
#define WIDTH 8
#define HEIGHT 8
int buttonEnabled = false;
int newPixels[WIDTH][HEIGHT];
#define HISTORY 5
int pixelHistory[HISTORY][WIDTH][HEIGHT];
int historyLength;
int isEmpty;
int isTheSame;

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

int frameDelay = 100;
unsigned long frameStamp = millis() - frameDelay;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code

  pinMode(button, INPUT);

  pixels.begin(); // This initializes the NeoPixel library.
  resetNeopixel();
  pixels.show();
}

int translator[8][2] = {{-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}};

void resetNeopixel() {
  int k = 0;
  for (int i = 0; k < HEIGHT; i++) {
    if (i >= WIDTH) {
      i = 0;
      k++;
    }
    if (random(0, 2)) newPixels[i][k] = true;
    else newPixels[i][k] = false;
    if (newPixels[i][k] == 1) {
      pixels.setPixelColor(i + (k * WIDTH), pixels.Color(colorOfPattern[0], colorOfPattern[1], colorOfPattern[2]));
      pixelHistory[0][k][i] = true;
      //newPixels[i] = 1;
    } else {
      pixels.setPixelColor(i + (k * WIDTH), pixels.Color(colorOfBackground[0], colorOfBackground[1], colorOfBackground[2]));
      pixelHistory[0][i][k] = false;
      //newPixels[i] = 0;
    }
    //pixels.show();
  }
  historyLength = 0;
  timeValii = millis();
  //pixels.show();

  //resetNeopixel();
  //delay(1000);
  frameStamp = millis();
}



void loop() {
  //oldButtonVal;
  //timeVal;
  buttonVal = digitalRead(button);

  if(buttonEnabled && buttonVal == HIGH && millis() - timeVal >= 500 && oldButtonVal == LOW){
    resetNeopixel();
    timeVal = millis();
    timeValii = millis();
  }

  oldButtonVal = buttonVal;

  if (millis() - frameStamp >= frameDelay) {
    frameStamp = millis();
    isEmpty = true;
    isTheSame = true;
    while (isEmpty || isTheSame) {
      for (int i = 0; i < WIDTH; i++) {
        for (int j = 0; j < HEIGHT; j++) {
          int neighbors = 0;
          for (int k = 0; k < 8; k++) {
            int targeted[2] = {translator[k][0] + i, translator[k][1] + j};
            if (targeted[0] >= 0 && targeted[0] < WIDTH && targeted[1] >= 0 && targeted[1] < HEIGHT) {
              if (pixelHistory[0][targeted[0]][targeted[1]]) neighbors++;
            }
          }
          if (neighbors == 3 || neighbors == 2 && pixelHistory[0][i][j]) {
            newPixels[i][j] = true;
            pixels.setPixelColor(i + (j * WIDTH), pixels.Color(colorOfPattern[0], colorOfPattern[1], colorOfPattern[2]));
            isEmpty = false;
          } else {
            newPixels[i][j] = false;
            pixels.setPixelColor(i + (j * WIDTH), pixels.Color(colorOfBackground[0], colorOfBackground[1], colorOfBackground[2]));
          }
        }
      }
      int matches = false;
      for (int i = 0; i < historyLength; i++) {
        matches = true;
        for (int j = 0; j < WIDTH; j++) {
          for (int k = 0; k < HEIGHT; k++) {
            if (newPixels[j][k] != pixelHistory[i][j][k]) {
              matches = false;
              break;
            }
          }
          if (matches) break;
        }
        if (matches) break;
      }
      if (!matches) isTheSame = false;
      if (!isEmpty && !isTheSame) {
        if (historyLength < HISTORY) historyLength++;
        for (int i = 0; i < historyLength; i++) {
          for (int j = 0; j < WIDTH; j++) {
            for (int k = 0; k < HEIGHT; k++) {
              if (i < HISTORY - 1) {
                pixelHistory[i + 1][j][k] = pixelHistory[i][j][k];
              }
              if (i == 0) {
                pixelHistory[i][j][k] = newPixels[j][k];
              }
            }
          }
        }
      }
      else {
        resetNeopixel();
      }
    }
    pixels.show();
  }
}
