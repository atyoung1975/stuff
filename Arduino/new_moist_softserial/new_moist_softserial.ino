#include <SoftwareSerial.h>
// software serial #1: RX = digital pin 10, TX = digital pin 11
SoftwareSerial portOne(4 , 5);


unsigned int MaxRunTime = 60000;
// Digital Pins for Sensor Power
int PowerPins[] = { 2, 3, 6, 7 };
// Analog Pins for Analog Input
int SensePins[] = { 1, 2, 3, 4};

// Digital Pin Name
String PNames[] = { "SM1", "SM2", "SM3", "SM4" };
size_t PCount = sizeof(SensePins)/sizeof(SensePins[0]);

void measure() {

    // loop over the power pin array and set them all to HIGH
    String message;
  //for (int thisPinOn = 0; thisPinOn < PCount; thisPinOn++) {
    //digitalWrite(PowerPins[thisPinOn], HIGH);
  //}
    //message += "**** Start Measurements *****";
 // int moistVal;
 for (int thisPin = 0; thisPin < PCount; thisPin++) {
   // moistVal = 0;
    //for (int loopy = 0; loopy < 5; loopy++) {
   //   moistVal = moistVal + analogRead(SensePins[thisPin]);
   //   delay(250);
   // }
    message += "@";
    message += PNames[thisPin];
    message += "(";
    message += analogRead(SensePins[thisPin]);
    message += ") ";
    /*
    message += " AVG(";
    message += ((moistVal)/5);
    message += ")";
    */
  }
  //message += "****  End Measurements  *****";
  Serial.println(message);
  //portOne.print(message);
      // loop over the power pin array and set them all to LOW
  for (int thisPinOff = 0; thisPinOff < PCount; thisPinOff++) {
   // digitalWrite(PowerPins[thisPinOff], LOW);
  }
  char cData[10];
  for (int i = 0; i < sizeof(message);i++) {
    Serial.print(message[i]);
    portOne.write(message[i]);
    strcpy(cData[i],message[i]);
  }
  //portOne.println(cData);
  //portOne.println("");
}
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // loop over the pin array and set them all to output:
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    pinMode(PowerPins[thisPin], OUTPUT);
   // digitalWrite(PowerPins[thisPin], LOW);
  }
  // Software Serial
  portOne.begin(9600);
}

void loop() {
    portOne.listen();

    //while(!Serial.available()){
        while (!portOne.available()) {}
         //portOne.read();
         
          
         // break;
      //  }
      
    int i = Serial.parseInt();
  switch(i){

  case 1:
    measure();
    break;
  //default:
    //Serial.println("Unrecognized command, try again!");
    } 
     measure();
}
