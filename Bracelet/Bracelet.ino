#include <RFduinoBLE.h>
#include <Adafruit_NeoPixel.h>
#include "SPI.h"

#define PIN 2

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, PIN, NEO_GRB + NEO_KHZ800);

int pattern;
int dataPin  = 1;
int clockPin = 0;
int rangedBreathSensorValue;

int toggler;

void setup() {
  RFduinoBLE.deviceName = "Bracelet";
  // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "Bracelet";
  
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();
  
  //default pattern is rainbow breath
  pattern = 1;
  
  // start the BLE stack
  RFduinoBLE.begin();
}

void loop() {
  
    strip.setBrightness(01);
    rainbow(20);

}

void RFduinoBLE_onConnect() {
 colorChase(strip.Color(127,  127,  127), 100);
}

void RFduinoBLE_onDisconnect() {
 colorChase(strip.Color(0,  0,  127), 100);
}

//data format
// on/off, r, g, b, a, led1
void RFduinoBLE_onReceive(char *data, int len) {
  // each transmission should contain power state, RGB triple, pattern
  //when length is 5
  rangedBreathSensorValue = data[0];
  uint8_t heartSensorValue = data[1];

  if (len >= 5)
  {
    // get the RGB values
    pattern = data[0];
    //Rainbow breath
    if (pattern = 1) {   
      rangedBreathSensorValue = data[0];
      uint8_t heartSensorValue = data[1];
      //setColor(strip.Color(rangedBreathSensorValue,  rangedBreathSensorValue,  rangedBreathSensorValue));
      setHue(rangedBreathSensorValue, 255, 100);
    }
    //Solid color
    if (pattern = 2) {
      uint8_t r = data[1];
      uint8_t g = data[2];
      uint8_t b = data[3];
    }
    //Rainbow
    if (pattern = 3) {
      rainbow(20);
    }
    //Chase
    if (pattern = 4) {
    
    }  
  }
    if (len >= 3)
  {
     if (toggler = 1)
     {
       rainbow(1000);
       toggler=2;
     }
     if (toggler = 2)
     {
       toggler=3;
     }
          if (toggler = 3)
     {
       toggler=1;
       strip.Color(data[0], data[1], data[2]); 
     }
  }
}

void colorChase(uint32_t c, uint8_t wait) {
  int i;
  
  // Start by turning all pixels off:
  pixelsOff();

  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.show();              // Refresh LED states
    strip.setPixelColor(i, 0); // Erase pixel, but don't refresh!
    delay(1);
  }

  strip.show(); // Refresh to turn off last pixel
}

void setColor(uint32_t c) {
  int i;
  
   //pixelsOff();
  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c); // Set new pixel 'on'
     //strip.show();
  }
  strip.show(); // Refresh to turn off last pixel
}

void pixelsOff() {
  int i;
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
}
  
  
void setHue(int hue, int sat, int val) {
	// hue: 0-259, sat: 0-255, val (lightness): 0-255
	int r, g, b, base;

	if (sat == 0) { // Achromatic color (gray).

	} else  {
		base = ((255 - sat) * val)>>8;
		switch(hue/60) {
			case 0:
				r = val;
				g = (((val-base)*hue)/60)+base;
				b = base;
				break;
			case 1:
				r = (((val-base)*(60-(hue%60)))/60)+base;
				g = val;
				b = base;
				break;
			case 2:
				r = base;
				g = val;
				b = (((val-base)*(hue%60))/60)+base;
				break;
			case 3:
				r = base;
				g = (((val-base)*(60-(hue%60)))/60)+base;
				b = val;
				break;
			case 4:
				r = (((val-base)*(hue%60))/60)+base;
				g = base;
				b = val;
				break;
			case 5:
				r = val;
				g = base;
				b = (((val-base)*(60-(hue%60)))/60)+base;
				break;
		}
                //SET TO 1/3RD BRIGHTNESS
                setColor(strip.Color(r/3,  g/3,  b/3));

	}
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

