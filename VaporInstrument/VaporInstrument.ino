/*
Vapor Instruments
*/

#include <RFduinoBLE.h>

//TODO define each pin as it actually in on the circuit

//Define input pins
int thermocoupleInputPin = 3;

//Define output pins
int vibratorOutputPin = 5;
int heaterControlOutputPin = 6;

int vibeDelay = 2000;


//Define BLE/device-bound output
float ambientTemp = 0;
float elementTemp = 0;


void setup() {
  // put your setup code here, to run once:
  // led used to indicate that the RFduino is advertising
  
  //set pinModes for inputs
  pinMode(thermocoupleInputPin, INPUT);
  
  //set pinModes for outputs
  pinMode(vibratorOutputPin, OUTPUT);
  pinMode(heaterControlOutputPin, OUTPUT);


//  //TODO add in 'name your instrument'
  RFduinoBLE.deviceName = "HitBit";
  RFduinoBLE.advertisementData = "vapor";
  //RFduinoBLE.advertisementInterval = MILLISECONDS(100);
  //RFduinoBLE.txPowerLevel = 0;  // (-20dbM to +4 dBm)
  
  // led used to indicate that the RFduino is connected
  //pinMode(connection_led, OUTPUT);

  // start the BLE stack
  RFduinoBLE.begin();
}

void loop() {
    // sample once per second
  RFduino_ULPDelay( SECONDS(1) );

//  digitalWrite(vibratorOutputPin, HIGH);   // sets the heater ON
//  digitalWrite(heaterControlOutputPin, HIGH);   // sets the heater ON
//  delay(vibeDelay);                  // waits for delay duration
//  digitalWrite(vibratorOutputPin, LOW);    // sets the heater off
//  digitalWrite(heaterControlOutputPin, LOW);   // sets the heater ON
//  delay(vibeDelay);                  // waits for delay duration

  //poll ambient temp
  ambientTemp = RFduino_temperature(CELSIUS);
  //poll element temp
  elementTemp = analogRead(thermocoupleInputPin);    // read the input pin
  
  //send ambient and element temp to BLE radio
  RFduinoBLE.sendFloat(ambientTemp);
  //RFduinoBLE.sendFloat(elementTemp);
  
  // to send one char
  // RFduinoBLE.send((char)temp);

  // to send multiple chars
  // RFduinBLE.send(&data, len);
}

void RFduinoBLE_onAdvertisement(bool start)
{
  // turn the green led on if we start advertisement, and turn it
  // off if we stop advertisement
  
//  if (start)
//    digitalWrite(advertisement_led, HIGH);
//  else
//    digitalWrite(advertisement_led, LOW);
}

void RFduinoBLE_onConnect()
{
  //make upward sound/vibration
  //digitalWrite(connection_led, HIGH);
  vibeDelay = 500;
}

void RFduinoBLE_onDisconnect()
{
  //make downward sound/vibration
  //digitalWrite(connection_led, LOW);
  
  //for low power mode do:   RFduino_ULPDelay(INFINITE);
vibeDelay = 5000;
}
// returns the dBm signal strength indicated by the receiver after connection (-0dBm to -127dBm)
void RFduinoBLE_onRSSI(int rssi)
{
}

void RFduinoBLE_onReceive(char *data, int len)
{
  vibeDelay = 100;
  //pin is first, val is second
  //check this assumption, should have length of 2 from iOS app
  if (len == 2) {
    uint8_t pin = data[0];
    uint8_t val = data[1];
    
    switch (pin) {
      //vibratorControlOutputPin
      case 5:
        if (val == 0) {
          digitalWrite(vibratorOutputPin, LOW);
        }
        //if anything other than 0 then turn pin ON
        else {
          digitalWrite(vibratorOutputPin, HIGH);
        }
        break;
      //heaterControlOutputPin
      case 6:
        if (val == 0) {
          digitalWrite(heaterControlOutputPin, LOW);
        }
        //if anything other than 0 then turn pin ON
        else {
          digitalWrite(heaterControlOutputPin, HIGH);
        }        
        break;
  }
 
    
    
    
    
    if (pin == vibratorOutputPin) {
      digitalWrite(vibratorOutputPin, HIGH);   // sets the LED on
    }
  }

  
  

  


}
