
#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

unsigned int MaxRunTime = 60000;
// Digital Pin for Relay
int RlyPins[] = { 4, 5, 6, 7, 8, 9, 10, 11 }; 
int TimeOpenSec[] = { 0, 0, 0, 0, 0, 0, 0, 0 }; 
// Digital Pin Name
String PNames[] = { "Water Pump", "Valve 1   ", "Valve 2   ", "Valve 3   ", "NI        ", "NI        ", "NI        ", "NI        "}; 
size_t PCount = sizeof(RlyPins)/sizeof(RlyPins[0]);
int rlyArry[] = {0,0,0,0,0,0,0,0,0,0};

bool inMenu = false;
int switchButtonPin = 2;
int switchXPin = 0;
int switchYPin = 1;
bool onScreenSelect = false;

String LCDMessage = "";

void mainLCD(){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The Pumper V2.0");
      lcd.setCursor(0,1);
      lcd.blink_off();
}

void rlyCycle(int relay){
      if ( digitalRead(relay)) {
        digitalWrite(relay,LOW);
      } else {
        digitalWrite(relay,HIGH);
      }
}

void AllOff(){
      Serial.println(" All Off ");
    for (int thisPin = 0; thisPin < PCount; thisPin++) {
      digitalWrite(RlyPins[thisPin], HIGH);
    }
}

void AllOn(){
      Serial.println(" All On ");
    for (int thisPin = 0; thisPin < PCount; thisPin++) {
      digitalWrite(RlyPins[thisPin], LOW);
    }
}

void onOff(){
  String statusP = "";
  LCDMessage = "";
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    if ( !digitalRead(RlyPins[thisPin])) {
      statusP = "On";
      LCDMessage += "1";
    } else {
      statusP = "Off";
      LCDMessage += "0";
    }
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.blink_off();
    lcd.setCursor(0,1);
    lcd.print(LCDMessage);
  }
}

void pumpMenu() {
      int buttCount = 0;
      inMenu = true;
      int mTimer = 0;
      unsigned int cursorXPOS = 0;
      lcd.setCursor(0,0);
      lcd.print("Pump Menu       ");
      onOff();
      lcd.setCursor(0,1);
      lcd.blink();
      while (inMenu){
        while (!digitalRead(switchButtonPin)){
          buttCount++;
          delay(1000);
          // Update LCD Screen on loop count during button press
          lcd.setCursor(12,0);
          lcd.print(buttCount);
          // Update LCD Screen with exit
          if (buttCount >= 5) {
            lcd.setCursor(0,1);
            lcd.print("Release to exit!");
          }
          // Update LCD Screen with menu
          if (buttCount >= 2 && buttCount <5) {
            lcd.setCursor(0,1);
            lcd.print("Release to Pick!");
          }
        }
        // Exit
        if (buttCount > 5) {
          buttCount = 0;
          inMenu = false;
          break;
        }
        else if (buttCount >= 2 && buttCount <5){
          Serial.println("Button Press POS: ");
          Serial.println(cursorXPOS);
          buttCount = 0;
        }
        mTimer++;
        if (mTimer > 120) {
          lcd.clear();
          lcd.setCursor(0,1);          
          lcd.print("Menu Timeout");
          delay(5000);
          break;
        }
        lcd.setCursor(13,1);    
        lcd.print("   ");     
        lcd.setCursor(13,1);    
        lcd.print((120-mTimer));
        delay(500);     
      }
      inMenu = false;
      mainLCD();
      onOff();
}

void menu() {
  Serial.println("**** Options *****");
  String statusP = "";
  int buttCount = 0;
  onOff();
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    if ( !digitalRead(RlyPins[thisPin])) {
      statusP = "On";
    } else {
      statusP = "Off";
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

  int mTimer = 0;
//*Button Handler
         while (!digitalRead(switchButtonPin)){
          buttCount++;
          lcd.setCursor(0,0);
          lcd.print("Button:     ");
          lcd.setCursor(12,0);
          lcd.print(buttCount);
          Serial.print("Button Press: ");
          Serial.println(buttCount);
          delay(1000);
          if (buttCount >= 5) {
            lcd.setCursor(0,1);
            lcd.print("Release All Off!");
          }
          if (buttCount >= 2 && buttCount <5) {
            lcd.setCursor(0,1);
            lcd.print("Release for menu");
          }
        }
        if (buttCount >= 5) {
          buttCount = 0;
          Serial.println("Button Press For All Off");
          AllOff();
          mainLCD();
        }
        else if (buttCount >= 2 && buttCount <5){
          Serial.println("Button Press For Menu");
          pumpMenu();
          buttCount = 0;
        }
 // Button Handler 
  while(!Serial.available()){
    mTimer++;
    if (mTimer > 10) {
      break;
    }
    delay(500);
    }
  // Update Run time
    for (int thisPinA = 0; thisPinA < PCount; thisPinA++) {
      if ( !digitalRead(RlyPins[thisPinA])) {
        TimeOpenSec[thisPinA] = TimeOpenSec[thisPinA] + 5;
        if ( TimeOpenSec[thisPinA] > (MaxRunTime / 1000) ) {
          digitalWrite(RlyPins[thisPinA],HIGH);
          TimeOpenSec[thisPinA] = 0;
        }
      } else {
        TimeOpenSec[thisPinA] = 0;
      }
    }
  int i = Serial.parseInt();
  switch(i){
  case 555:
    Serial.println("1-8 Activate individual relay");
    Serial.println("1260 Interlock relay 1 and 2 for 60 sec");
    Serial.println("1360 Interlock relay 1 and 3 for 60 sec");
    Serial.println("1460 Interlock relay 1 and 4 for 60 sec");
    Serial.println("1560 Interlock relay 1 and 5 for 60 sec");
    Serial.println("1660 Interlock relay 1 and 6 for 60 sec");
    Serial.println("1760 Interlock relay 1 and 7 for 60 sec");
    Serial.println("1860 Interlock relay 1 and 8 for 60 sec");
    Serial.println("111 All Relays Off");
    Serial.println("777 Cycle through all relays 60 sec with interlock relay 1");
    Serial.println("888 Cycle through all relays 60 sec");
    Serial.println("999 All Relays On");
    break;
  case 1:
    rlyCycle(4);
    break;
  case 2:
    rlyCycle(5);
    break;
  case 3:
    rlyCycle(6);
    break;
  case 4:
    rlyCycle(7);
    break;
  case 5:
    rlyCycle(8);
    break;
  case 6:
    rlyCycle(9);
    break;
  case 7:
    rlyCycle(10);
    break;
  case 8:
    rlyCycle(11);
    break;
  case 999:
    AllOn();
    break;
  case 111:
    AllOff();
    break;
  default:
    Serial.println("Unrecognized command, try again!");
    String s1 = String(i);
    Serial.println(s1.substring(2,3));
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
  mainLCD();
  pinMode(switchButtonPin, INPUT);
  // 
  digitalWrite(switchButtonPin, HIGH); // Set Buton pin high
}

void loop() {
  LCDMessage = "";
  // Clear menu array
  for (int thisPin = 0; thisPin < (sizeof(rlyArry)/sizeof(rlyArry[0])); thisPin++) {
    rlyArry[thisPin] = 0;
  }
  menu();
}
