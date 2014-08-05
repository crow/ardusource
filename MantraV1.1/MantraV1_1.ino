const int sensorPin = A0;    // select the input pin for the potentiometer
const int ledPin = 13; 
const int buttonPin = 2;  // select the pin for the LED
int sensorValue = 0; // variable to store the value coming from the sensor
int sensorDelta = 0;
int sensorDeltaRet = 0;
int sensorValueDelayXLater=0;

const int sensorMin = 00;      // sensor minimum, discovered through experiment
const int sensorMax = 900;    // sensor maximum, discovered through experiment
int val = 0;
// include the library code:
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
void setup() {
  
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);  
  
  lcd.begin(16, 2);
  // Print a message to the LCD.
 // lcd.print("Reading A0");
  
}

void printRawSensorValue(){
    // read the value from the sensor:
  sensorValue = analogRead(sensorPin); 
  lcd.setCursor(0, 0);
  lcd.print("a0:");
  lcd.setCursor(4, 0);
  lcd.print(sensorValue);
}

int getAndPrintSensorDelta(int deltaT){
  sensorValue = analogRead(sensorPin);  //upddate the sensor value to allow more responsiveness between cases
  delay(deltaT); //delta t
  sensorValueDelayXLater = analogRead(sensorPin); 
  sensorDeltaRet = sensorValue - sensorValueDelayXLater; //sensorVal(t)-sensorVal(t+DelayX) 
  lcd.setCursor(0, 1);
  lcd.print(sensorDeltaRet);
  return sensorDeltaRet;
}

void loop() {
  lcd.setCursor(8, 0);
 // lcd.print(millis()/1000);
  int val = analogRead(sensorPin);

  printRawSensorValue();

  // read the value from the sensor:
  
  
  sensorValue = analogRead(sensorPin);    
  sensorDelta = getAndPrintSensorDelta(100);



//something weird is going on with how you're setting the cursor...


if (sensorDelta < 0) {

if (sensorValue <= 350){ 
lcd.setCursor(4, 1);  
lcd.print("123456789>");
}
if (sensorValue <= 355){
lcd.setCursor(4, 1);
lcd.print("12345678> ");
}
if (sensorValue <= 360){
lcd.setCursor(4, 1);
lcd.print("1234567>  ");
}
if (sensorValue <= 365){
lcd.setCursor(4, 1);
lcd.print("123456>   ");
}
if (sensorValue >= 370){
  lcd.setCursor(4, 1);
lcd.print("12345>    ");
}
if (sensorValue <= 375){
  lcd.setCursor(4, 1);
lcd.print("1234>     ");
}
if (sensorValue <= 380){
  lcd.setCursor(4, 1);
lcd.print("123>      ");
}
if (sensorValue <= 385){
  lcd.setCursor(4, 1);
lcd.print("12>       ");
}
if (sensorValue >= 390){
  lcd.setCursor(4, 1);
lcd.print("1>        ");
}
}

if( sensorDelta >= 0){

if (sensorValue <= 350  ){ //if inhale
lcd.setCursor(4, 1);
lcd.print("123456789<");
}
if (sensorValue <= 355  ){
  lcd.setCursor(4, 1);
lcd.print("12345678< ");
}
if (sensorValue <= 360  ){
  lcd.setCursor(4, 1);
lcd.print("1234567<  ");
}
if (sensorValue <= 365  ){
  lcd.setCursor(4, 1);
lcd.print("123456<   ");
}
if (sensorValue >= 370  ){
  lcd.setCursor(4, 1);
lcd.print("12345<    ");
}
if (sensorValue <= 375  ){
  lcd.setCursor(4, 1);
lcd.print("1234<     ");
}
if (sensorValue <= 380  ){
  lcd.setCursor(4, 1);
lcd.print("123<      ");
}
if (sensorValue <= 385  ){
  lcd.setCursor(4, 1);
lcd.print("12<       ");
}
if (sensorValue >= 390  ){
  lcd.setCursor(4, 1);
lcd.print("1<        ");
}
}
//  switch (sensorValue) {
//  case 250:    // your hand is on the sensor
//   lcd.print("dark            ");
//    break;
//  case 300:    // your hand is close to the sensor
//    sensorValue = analogRead(sensorPin);  
//    lcd.print("dim             ");
//    break;
//  case 350:    // your hand is a few inches from the sensor
//    sensorValue = analogRead(sensorPin);  
//    lcd.print("medium          ");
//    break;
//  case 400:    // your hand is nowhere near the sensor
//    sensorValue = analogRead(sensorPin);  
//    lcd.print("bright          ");
//    break;
//  case 450:    // your hand is nowhere near the sensor
//    sensorValue = analogRead(sensorPin);  
//    lcd.print("very bright     ");
//    break;
//  } 



}
