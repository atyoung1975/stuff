
unsigned int MaxRunTime = 60000;
// Digital Pins for Sensor Power
int PowerPins[] = { 2, 3, 6, 7 };
// Analog Pins for Analog Input
int SensePins[] = { 1, 2, 3, 4};

// Digital Pin Name
String PNames[] = { "Sensor 1   ", "Sensor 2   ", "Sensor 3   ", "Sensor 4   " };
size_t PCount = sizeof(SensePins)/sizeof(SensePins[0]);

void measure() {

    // loop over the power pin array and set them all to HIGH
  for (int thisPinOn = 0; thisPinOn < PCount; thisPinOn++) {
    digitalWrite(PowerPins[thisPinOn], HIGH);
  }
  Serial.println("**** Start Measurements *****");
  int moistVal;
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    moistVal = 0;
    for (int loopy = 0; loopy < 5; loopy++) {
      moistVal = moistVal + analogRead(SensePins[thisPin]);
      delay(1000);
    }
    Serial.print("**  ");
    Serial.print(PNames[thisPin]);
    Serial.print(" Curr(");
    Serial.print(analogRead(SensePins[thisPin]));
    Serial.print(")");
    Serial.print(" AVG(");
    Serial.print((moistVal)/5);
    Serial.println(")");
  }
  Serial.println("****  End Measurements  *****");
      // loop over the power pin array and set them all to LOW
  for (int thisPinOff = 0; thisPinOff < PCount; thisPinOff++) {
    digitalWrite(PowerPins[thisPinOff], LOW);
  }
}
  
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // loop over the pin array and set them all to output:
  for (int thisPin = 0; thisPin < PCount; thisPin++) {
    pinMode(PowerPins[thisPin], OUTPUT);
    digitalWrite(PowerPins[thisPin], LOW);
  }
  // 
}

void loop() {
    while(!Serial.available()){}
    int i = Serial.parseInt();
  switch(i){

  case 1:
    measure();
    break;
  //default:
    //Serial.println("Unrecognized command, try again!");
    } 
}
