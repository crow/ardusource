#include <RFduinoBLE.h>
#include "SPI.h"

bool mantraBandOn;

int breathPin = 2;

int const initialMaxSensorValue = 310;
int const initialMinSensorValue = 300;

int calibratedMaxSensorValue;
int calibratedMinSensorValue;

int sensorValue;
int sensorValueDelta;

int rangedSensorValue;


void setup() {
  RFduinoBLE.deviceName = "mantraBand";
    // this is the data we want to appear in the advertisement
  // (if the deviceName and advertisementData are too long to fix into the 31 byte
  // ble advertisement packet, then the advertisementData is truncated first down to
  // a single byte, then it will truncate the deviceName)
  RFduinoBLE.advertisementData = "mantraBand";
  Serial.begin(9600);
  
 // start the BLE stack
 RFduinoBLE.begin();
}

void loop() {
 sensorValue = analogRead(breathPin);
 delay(10);
 sensorValueDelta = analogRead(breathPin);
 Serial.print(sensorValue);       // prints a label
 Serial.print("\n");
// //high 2 = 127 low 2 = 0 high 1 = 370 low 1 = 210
// dynamicCalibration();
// rangedSensorValue = 0 + (sensorValue - calibratedMinSensorValue) * (127 - 0) / (calibratedMaxSensorValue - calibratedMinSensorValue); 
// Serial.print(rangedSensorValue);       // prints a label
// Serial.print("\n");
// RFduinoBLE.s 
 RFduinoBLE.sendInt(sensorValue);
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
}

void RFduinoBLE_onDisconnect() {
}

void RFduinoBLE_onReceive(char *data, int len) {
}

  
  
