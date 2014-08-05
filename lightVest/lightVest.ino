#include <RFduinoBLE.h>
#include "LPD8806.h"
#include "SPI.h"

int nLEDs = 116;

bool vestOn;

int const initialMaxSensorValue = 310;
int const initialMinSensorValue = 300;

int calibratedMaxSensorValue;
int calibratedMinSensorValue;

int dataPin  = 2;
int clockPin = 3;

int breathPin = 4;
int heartPin = 5;

int sensorValue;
int sensorValueDelta;

int rangedSensorValue;


LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);



void setup() {
  RFduinoBLE.deviceName = "lightVest";
  // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "lightVest";

  Serial.begin(9600);
  
  // Start up the LED strip
  strip.begin();

  // Update the strip, to start they are all 'off'
  strip.show();

//  //set GIPO pins to outputs
//  pinMode(2, OUTPUT);
//  pinMode(3, OUTPUT);  


  
//    // start the GZLL stack
//  RFduinoGZLL.begin(role);
  
  // start the BLE stack
  RFduinoBLE.begin();
}

void loop() {
  // switch to lower power mode
 // RFduino_ULPDelay(INFINITE);
 sensorValue = analogRead(heartPin);
 delay(10);
 sensorValueDelta = analogRead(heartPin);
// Serial.print(sensorValue);       // prints a label
// Serial.print("\n");
 //high 2 = 127 low 2 = 0 high 1 = 370 low 1 = 210
 dynamicCalibration();
 rangedSensorValue = 0 + (sensorValue - calibratedMinSensorValue) * (127 - 0) / (calibratedMaxSensorValue - calibratedMinSensorValue); 
 setColor(rangedSensorValue);
 Serial.print(rangedSensorValue);       // prints a label
 Serial.print("\n");
}

void dynamicCalibration() {
  if (initialMinSensorValue > sensorValue) {
      calibratedMinSensorValue = sensorValue;
  }
  if (initialMaxSensorValue < sensorValue) {
      calibratedMaxSensorValue = sensorValue;
  }
}

void RFduinoBLE_onConnect() {
  // the default starting color on the iPhone is white
 //colorChase(strip.Color(127,  127,  127), 100);
}

void RFduinoBLE_onDisconnect() {
 //colorChase(strip.Color(0,  0,  0), 100);
}


//data format
// on/off, r, g, b, a, led1
void RFduinoBLE_onReceive(char *data, int len) {
  // each transmission should contain power state, RGB triple, pattern
  //when length is 5
  if (len >= 5)
  {
    // get the RGB values
    uint8_t vestOn = data[0];
    uint8_t r = data[1];
    uint8_t g = data[2];
    uint8_t b = data[3];
    uint8_t pattern = data[4];
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
  
   pixelsOff();
  // Then display one pixel at a time:
  for(i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(strip.Color(127,  127,  127), c); // Set new pixel 'on'
  }
  strip.show(); // Refresh to turn off last pixel
}

void pixelsOff() {
  int i;
  for(i=0; i<strip.numPixels(); i++) strip.setPixelColor(i, 0);
}
  
  
