#include "EEPROM.h"

//Configuration Parameters
unsigned int MaxRunTime = 60000;
// Read Board ID from EEPROM
char tentID = EEPROM.read(0); //Tent Ident
char tentNum = EEPROM.read(1); //Tent Number
int sensorCount = EEPROM.read(2); //Number of sensors
int startPPin = EEPROM.read(3); //Starting Sensor Power Pin Position
int startSPin = EEPROM.read(4); //Starting Sensor Pin Position
int DTH11Pin = EEPROM.read(5); //DHT11 Digital Pin

// Digital Pins for Sensor Power
//int PowerPins[] = { 2, 3, 6, 7 };
int PowerPins[] = { 2, 3, 4 };
// Analog Pins for Analog Input
//int SensePins[] = { 1, 2, 3, 4};
int SensePins[] = { 5, 4, 3 };
// Digital Pin Name
String PNames[] = { "P1 - Sensor 1   ", "P1 - Sensor 2   ", "P1 - Sensor 3   ", "Sensor 4   " };
size_t PCount = sizeof(SensePins)/sizeof(SensePins[0]);

void measure() {

    // loop over the power pin array and set them all to HIGH
  for (int thisPinOn = 0; thisPinOn < sensorCount; thisPinOn++) {
    digitalWrite((startPPin + thisPinOn) , HIGH);
    }
    delay(5000);
  //Serial.println("**** Start Measurements *****");
  for (int thisPin = 0; thisPin < sensorCount; thisPin++) {
    //Serial.print("\n");
    Serial.print(tentID);
    //Serial.print("");
    Serial.print(tentNum);
    //Serial.print(,",");
    Serial.print(thisPin);
    Serial.print(",");
    Serial.print(analogRead((startSPin + thisPin)));
    Serial.print("!");
  }
     Serial.print("#");
    //Serial.println("****  End Measurements  *****");
      // loop over the power pin array and set them all to LOW
  for (int thisPinOff = 0; thisPinOff < sensorCount; thisPinOff++) {
    digitalWrite((startPPin + thisPinOff), LOW);
  }
}
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // loop over the pin array and set them all to output:
  for (int thisPin = 0; thisPin < sensorCount; thisPin++) {
    pinMode((startPPin + thisPin), OUTPUT);
    digitalWrite((startPPin + thisPin), LOW);
  }
  // Read config data from EEPROM
}

void loop() {
    
    while(!Serial.available()){
       }
    int i = Serial.parseInt();
  switch(i){

  case 1:
    measure();
    break;

  case 000:
          for (int thisPinOn = 0; thisPinOn < PCount; thisPinOn++) {
            digitalWrite(PowerPins[thisPinOn], LOW);
          };
          break;

  case 999:
          for (int thisPinOn = 0; thisPinOn < PCount; thisPinOn++) {
            digitalWrite(PowerPins[thisPinOn], HIGH);
          };
          break;
  //default:
    //Serial.println("Unrecognized command, try again!");
    } 

}
