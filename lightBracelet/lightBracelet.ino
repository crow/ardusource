#include <RFduinoBLE.h>
#include "LPD8806.h"
#include "SPI.h"

int nLEDs = 7;

bool braceletOn;

int dataPin  = 2;
int clockPin = 3;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

void setup() {
  RFduinoBLE.deviceName = "lightBracelet";
    // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "lightBracelet";
  Serial.begin(9600);
  // Start up the LED strip
  strip.begin();
  // Update the strip, to start they are all 'off'
  strip.show();

}

void loop() {
  // put your main code here, to run repeatedly:

}
