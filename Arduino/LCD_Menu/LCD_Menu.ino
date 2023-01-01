/*
* ISR Debounce
*/

// use 2ms debounce time
#define DEBOUNCE_TICKS (word)microsecondsToClockCycles(2000)

extern volatile unsigned long timer0_overflow_count;
word keytick;  // record time of keypress

void setup() {     
  Serial.begin(9600);           
 attachInterrupt(digitalPinToInterrupt(2),KeyPress,CHANGE);
}

void KeyPress() {
 keytick=(word)timer0_overflow_count;
 Serial.println("press");
}

// returns true if key pressed
boolean KeyCheck() {
 if (keytick!=0) {
   if (((word)timer0_overflow_count-keytick)>DEBOUNCE_TICKS) {
     keytick=0;
     return true;
   }
 }
 return false;
}

void loop()                     
{
 if (KeyCheck()) {
  Serial.println("button");
   // do something useful
 }
}
