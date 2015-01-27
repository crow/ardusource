#include <RFduinoBLE.h>
#include "LPD8806.h"
#include "SPI.h"

//#include "avr/io.h"
//#include "avr/wdt.h"wdt.h
//
//#define Reset_AVR() wdt_enable(WDTO_30MS); while(1) {}


int nLEDs = 6;

bool lightVestOn;

int pattern;

int dataPin  = 1;
int clockPin = 0;
int rangedBreathSensorValue;

int heartPin = 5;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void setup() {
  RFduinoBLE.deviceName = "lightVest";
  // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "lightVest";

  //Serial.begin(9600);
  
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
  // switch to lower power mode
// if (!lightVestOn) {
//   RFduino_ULPDelay(INFINITE);
// }

 //setColor(strip.Color(rangedBreathSensorValue,  127,  127));

}

void RFduinoBLE_onConnect() {
 colorChase(strip.Color(127,  127,  127), 100);
 strip.setPixelColor(1, strip.Color(0,  50,  0)); // Set new pixel 'on'
 strip.show(); 
}

void RFduinoBLE_onDisconnect() {
 colorChase(strip.Color(0,  0,  127), 100);
 strip.setPixelColor(1, strip.Color(50,  0,  0)); // Set new pixel 'on'
 strip.show(); 
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
    //Blink
    if (pattern = 3) {
    
    }
    //Chase
    if (pattern = 4) {
    
    }
    
    
  }
    if (len >= 3)
  {
    // get the RGB values
   
    rangedBreathSensorValue = data[0];
    uint8_t heartSensorValue = data[1];
    //setColor(strip.Color(rangedBreathSensorValue,  rangedBreathSensorValue,  rangedBreathSensorValue));
    setHue(rangedBreathSensorValue, 255, 100);
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

                setColor(strip.Color(r,  g,  b));

	}
}
