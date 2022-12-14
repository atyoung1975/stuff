// SainSmart Instabots Upright Rover rev. 2.0
// http://www.sainsmart.com

#include <SPI.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

unsigned int Display_Counter, Button_Delay = 0;

struct Axis{
  uint16_t axis_1;
  uint16_t axis_2;
  uint16_t axis_3;
  uint16_t axis_4;
  uint16_t axis_5;
  uint16_t axis_6;
  uint16_t axis_7;
  uint16_t axis_8;
};
Axis axis_x;

struct Gesture{
  float angle;
  float omega;
  int speed; 
  int P;
  int I;
  int D;
  uint16_t null_1; 
  uint16_t null_2;
};
Gesture data;

void setup(){
  pinMode(2, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("SainSmartProduct");
  lcd.setCursor(0,1);
  lcd.print("UprightRover 2.0");
  lcd.cursor();
  //lcd.blink_on();

  Serial.begin(9600);
  Serial.println("Beginning ... "); 
  delay(4000);
}

void loop(){
          lcd.clear();
      lcd.print("Cursor blink");
      lcd.setCursor(0,0);
      lcd.blink();

/**********************************************************************************************************/

  delay(10000);  //Delay time should not be less than 13ms.
        lcd.clear();
      lcd.print("No cursor blink");
      lcd.noBlink();
      delay(10000);  //Delay time should not be less than 13ms.
}
/**********************************************************************************************************/
void PID_Display()
{
  lcd.setCursor(0,0);
  lcd.print("Parameter:P=");
  if(data.P < 1000){
    lcd.print('0');
    if(data.P < 100){
      lcd.print('0');
      if(data.P < 10){
        lcd.print('0');
      }
    }
  }
  lcd.print(data.P);
/**********************************************************************************************************/    
  lcd.setCursor(0,1);
  lcd.print(" I=");
  if(data.I < 1000){
    lcd.print('0');
    if(data.I < 100){
      lcd.print('0');
      if(data.I < 10){
        lcd.print('0');
      }
    }
  }
  lcd.print(data.I);
/**********************************************************************************************************/    
  lcd.print("  D=");
  if(data.D < 1000){
    lcd.print('0');
    if(data.D < 100){
      lcd.print('0');
      if(data.D < 10){
        lcd.print('0');
      }
    }
  }
  lcd.print(data.D);
}
/**********************************************************************************************************/
void Gesture_Display()
{
  lcd.setCursor(0,0);
  lcd.print("Gesture:A=");
  if(10 <= data.angle){
    lcd.print("+");
    lcd.print(data.angle);
  }
  if(0 < data.angle && data.angle < 10){
    lcd.print("+0");
    lcd.print(data.angle);
  }
  if(-10 < data.angle && data.angle < 0){
    data.angle = -data.angle;
    lcd.print("-0");
    lcd.print(data.angle);
  }
  if(data.angle <= -10){
    lcd.print(data.angle);
  }
/**********************************************************************************************************/  
  lcd.setCursor(0,1);
  lcd.print("O=");
  if(100 <= data.omega){
    lcd.print("+");
    lcd.print(data.omega);
  }
  if(10 <= data.omega && data.omega < 100){
    lcd.print("+0");
    lcd.print(data.omega);
  }
  if(0 < data.omega && data.omega < 10){
    lcd.print("+00");
    lcd.print(data.omega);
  }
  if(-10 < data.omega && data.omega <= 0){
    data.omega = -data.omega;
    lcd.print("-00");
    lcd.print(data.omega);
  }
  if(-100 < data.omega && data.omega <= -10){
    data.omega = -data.omega;
    lcd.print("-0");
    lcd.print(data.omega);
  }
  if(data.omega <= -100){
    lcd.print(data.omega);
  }
/**********************************************************************************************************/  
  lcd.setCursor(9,1);
  lcd.print(" S=");
  if(data.speed <= -100){
    lcd.print(data.speed);
  }
  if(-100 < data.speed && data.speed <= -10){
    data.speed = -data.speed;
    lcd.print("-0");
    lcd.print(data.speed);
  }
  if(-10 < data.speed && data.speed <= 0){
    data.speed = -data.speed;
    lcd.print("-00");
    lcd.print(data.speed);
  }
  if(0 < data.speed && data.speed < 10){
    lcd.print("+00");
    lcd.print(data.speed);
  }
  if(10 <= data.speed && data.speed < 100){
    lcd.print("+0");
    lcd.print(data.speed);
  }
  if(100 <= data.speed){
    lcd.print("+");
    lcd.print(data.speed);
  }
}
