/*************************************************** 
  This is an example for our Adafruit 12-channel PWM/LED driver

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/products/

  These drivers uses SPI to communicate, 2 pins are required to  
  interface: Data and Clock. The boards are chainable

  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_TLC59711.h"
#include <SPI.h>

// How many boards do you have chained?
#define NUM_TLC59711 1

#define data   12
#define clock  11

Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711, clock, data);
//Adafruit_TLC59711 tlc = Adafruit_TLC59711(NUM_TLC59711);

void setup() {
  Serial.begin(9600);
  
  Serial.println("TLC59711 test");
  
  // Uncomment this line if using UNO/AVR since 10 has to be an output
  // for hardware SPI to work
  //pinMode(10, OUTPUT);

  tlc.begin();
  tlc.write();
}

void loop() {
  tlc.setLED(0, 255, 0, 0); // Bottom Right Red
  tlc.write();
  delay(1000);
  tlc.setLED(0, 0, 255, 0); // Bottom Right White 
      tlc.write();
  delay(1000);
  tlc.setLED(0, 0, 0, 255); // Top
      tlc.write();

  delay(1000);
  tlc.setLED(1, 255, 0, 0); // Bottom Left
      tlc.write();

  delay(1000);
  tlc.setLED(1, 0,0,0);
  tlc.write();
  delay(1000);
}


// Fill the dots one after the other with a color
void colorWipe(uint16_t r, uint16_t g, uint16_t b, uint8_t wait) {
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, r, g, b);
      tlc.write();
      delay(wait);
  }
}
 
// Rainbow all LEDs at the same time, same color
void rainbow(uint8_t wait) {
  uint32_t i, j;

  for(j=0; j<65535; j+=10) {
    for(i=0; i<4*NUM_TLC59711; i++) {
      Wheel(i, (i+j) & 65535);
    }
    tlc.write();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint32_t i, j;

  for(j=0; j<65535; j+=10) { // 1 cycle of all colors on wheel
    for(i=0; i < 4*NUM_TLC59711; i++) {
      Wheel(i, ((i * 65535 / (4*NUM_TLC59711)) + j) & 65535);
    }
    tlc.write();
    delay(wait);
  }
}

// Input a value 0 to 4095 to get a color value.
// The colours are a transition r - g - b - back to r.
void Wheel(uint8_t ledn, uint16_t WheelPos) {
  if(WheelPos < 21845) {
    tlc.setLED(ledn, 3*WheelPos, 65535 - 3*WheelPos, 0);
  } else if(WheelPos < 43690) {
    WheelPos -= 21845;
    tlc.setLED(ledn, 65535 - 3*WheelPos, 0, 3*WheelPos);
  } else {
    WheelPos -= 43690;
    tlc.setLED(ledn, 0, 3*WheelPos, 65535 - 3*WheelPos);
  }
}

//All RGB Channels on full colour
//Cycles trough all brightness settings from 0 up to 127
void increaseBrightness(){
  for(uint16_t i=0; i<8*NUM_TLC59711; i++) {
      tlc.setLED(i, 65535, 65535, 65535);
  }
  for(int i = 0; i < 128; i++){
    //tlc.simpleSetBrightness(i);
    tlc.write();
    delay(1000);
  }
}
