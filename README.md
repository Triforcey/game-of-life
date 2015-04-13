#Conway's Game of Life - Build with Arduino & Neopixel 8x8 LED Display

##Arduino Dependencies
This Game Of Life Arduino program depends on the following Arduino libraries:
* Adafruit Neopixel Arduino Library

##Description
I read about the Game Of Life algorithm after getting an 8x8 LED Neopixel display from AdaFruit.com. Soon after a family member told me about this thing called The Game of Life. I went searching for an implementation of The Game of Life. I was annoyed as I found out that this was made for pretty much everything except for the AdaFruit Neopixel. So, I went and designed my own. Through lots of trial and error, I finally got out all of the bugs. Recently, I made it so you could easily pick the colors used, as this display is full color.

##Game of Life
How the game of life works is simple. Every pixel or led is a person. If a live person (pixel is on) has less than two out of it's eight neighbors, it dies from loneliness. Also, if it has more than three it dies of overcrowding. If a dead person has exactly three neighbors, it will be born again. All deaths and births for one frame happen at the same time.
