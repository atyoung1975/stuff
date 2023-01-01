#include "EEPROM.h"
#include "DHT.h"

//Configuration Parameters
unsigned int MaxRunTime = 60000;
// Read Board ID from EEPROM
char tentID = EEPROM.read(0); //Tent Ident
char tentNum = EEPROM.read(1); //Tent Number
int sensorCount = EEPROM.read(2); //Number of sensors
int startPPin = EEPROM.read(3); //Starting Sensor Power Pin Position
int startSPin = EEPROM.read(4); //Starting Sensor Pin Position
int DTH11Pin = EEPROM.read(5); //DHT11 Digital Pin

// DHT Config
#define DHTPIN DTH11Pin     // what digital pin we're connected to
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void measure() {

    // loop over the power pin array and set them all to HIGH
  for (int thisPinOn = 0; thisPinOn < sensorCount; thisPinOn++) {
    digitalWrite((startPPin + thisPinOn) , HIGH);
    }
    delay(5000);
   for (int thisPin = 0; thisPin < sensorCount; thisPin++) {
    Serial.print(tentID);
    Serial.print(tentNum);
    Serial.print(thisPin);
    Serial.print(",");
    Serial.print(analogRead((startSPin + thisPin)));
    Serial.print("!");
  }

  if (DTH11Pin) {
    Serial.print(tentID);
    Serial.print(tentNum);
    Serial.print("T");
    Serial.print(",");
    Serial.print(dht.readTemperature(true));
    Serial.print("!"); 
    Serial.print(tentID);
    Serial.print(tentNum);
    Serial.print("H");
    Serial.print(",");
    Serial.print(dht.readHumidity());
    Serial.print("!"); 
  }
       Serial.print("#");
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
}

void loop() {
    
    while(!Serial.available()){
       }
    int i = Serial.parseInt();
  switch(i){

  case 1:
    measure();
    break;

    } 

}
