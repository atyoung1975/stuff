
#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

unsigned int MaxRunTime = 60000;
// Digital Pin for Relay
int RlyPins[] = { 2, 3, 4, 5, 6, 7, 8, 9 }; 
int TimeOpenSec[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; 
// Digital Pin Name
String PNames[] = { "Water Pump", "Valve 1   ", "Valve 2   ", "Valve 3   ", "NI        ", "NI        ", "NI        ", "NI        "}; 
size_t PCount = sizeof(RlyPins)/sizeof(RlyPins[0]);

int switchButtonPin = 10;
int switchXPin = 0;
int switchYPin = 1;

String LCDMessage = "";

void menu() {
  Serial.println("**** Options *****");
  String statusP = "";
  LCDMessage = "";
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    if ( digitalRead(RlyPins[thisPin])) {
      statusP = "On";
      LCDMessage += "1";
    } else {
      statusP = "Off";
      LCDMessage += "0";
    }
    Serial.print("**  ");
    Serial.print(thisPin+1);
    Serial.print(" ");
    Serial.print(PNames[thisPin]);
    Serial.print(" Current(");
    Serial.print(statusP);
    Serial.print(")");
    Serial.print(" Run Time (");
    Serial.print(TimeOpenSec[thisPin]);
    Serial.println(" seconds)");
  }
  lcd.setCursor(0,1);
  lcd.print(LCDMessage);
  int mTimer = 0;
  while(!Serial.available()){
    mTimer++;
    Serial.println(digitalRead(switchButtonPin));
    if (!digitalRead(switchButtonPin)) {
      Serial.println("Button Pressed");
    }
    
    if (mTimer > 10) {
      break;
    }
    delay(1000);
    }
  // Update Run time
    for (int thisPinA = 0; thisPinA < PCount; thisPinA++) {
      if ( digitalRead(RlyPins[thisPinA])) {
        TimeOpenSec[thisPinA] = TimeOpenSec[thisPinA] + 10;
        if ( TimeOpenSec[thisPinA] > (MaxRunTime / 1000) ) {
          digitalWrite(RlyPins[thisPinA],LOW);
          TimeOpenSec[thisPinA] = 0;
        }
      } else {
        TimeOpenSec[thisPinA] = 0;
      }
    }
  int i = Serial.parseInt();
  switch(i){

  case 1:
    if ( digitalRead(2)) {
      digitalWrite(2,LOW);
    } else {
      digitalWrite(2,HIGH);
    }
    break;
  case 2:
    if ( digitalRead(3)) {
      digitalWrite(3,LOW);
    } else {
      digitalWrite(3,HIGH);
    }
    break;
  case 3:
    if ( digitalRead(4)) {
      digitalWrite(4,LOW);
    } else {
      digitalWrite(4,HIGH);
    }
    break;
  case 4:
    if ( digitalRead(5)) {
      digitalWrite(5,LOW);
    } else {
      digitalWrite(5,HIGH);
    }
    break;
  case 5:
    if ( digitalRead(6)) {
      digitalWrite(6,LOW);
    } else {
      digitalWrite(6,HIGH);
    }
    break;
  case 6:
    if ( digitalRead(7)) {
      digitalWrite(7,LOW);
    } else {
      digitalWrite(7,HIGH);
    }
    break;
  case 7:
    if ( digitalRead(8)) {
      digitalWrite(8,LOW);
    } else {
      digitalWrite(8,HIGH);
    }
    break;
  case 8:
    if ( digitalRead(9)) {
      digitalWrite(9,LOW);
    } else {
      digitalWrite(9,HIGH);
    }
    break;
  case 999:
    Serial.println(" All On ");
    for (int thisPin = 0; thisPin < PCount; thisPin++) {
      digitalWrite(RlyPins[thisPin], LOW);
    }
    break;
  case 111:
    Serial.println(" All Off ");
    for (int thisPin = 0; thisPin < PCount; thisPin++) {
      digitalWrite(RlyPins[thisPin], HIGH);
    }
    break;
  //default:
    //Serial.println("Unrecognized command, try again!");
    } 
 }
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // loop over the pin array and set them all to output:
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    pinMode(RlyPins[thisPin], OUTPUT);
    digitalWrite(RlyPins[thisPin], HIGH);
  }
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("The Pumper V2.0");
  lcd.setCursor(0,1);
  lcd.print("");
  pinMode(switchButtonPin, INPUT);
  // 
}

void loop() {
  menu();
        lcd.clear();
      lcd.print("Cursor blink");
      lcd.blink();
  Serial.println(analogRead(switchXPin));
  Serial.println(analogRead(switchYPin));


}
