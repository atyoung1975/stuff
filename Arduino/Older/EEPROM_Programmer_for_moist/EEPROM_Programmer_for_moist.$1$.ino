#include "EEPROM.h"
void setup() {
  Serial.begin(9600);
  EEPROM.update(0, 'F'); //Tent Ident
  EEPROM.update(1, '2'); //Tent Number
 EEPROM.update(2, 1); //Number of sensors
  EEPROM.update(3, 2); //Starting Sensor Power Pin Position
  EEPROM.update(4, 0); //Starting Sensor Pin Position
  EEPROM.update(5, 3); //DTH11 Pin
  Serial.print("char stored at EEPROM address 0: ");
  Serial.write(EEPROM.read(0));
    Serial.write(EEPROM.read(1));
    Serial.write("-");
      Serial.write(EEPROM.read(2));
          Serial.write("-");
      Serial.write(EEPROM.read(3));
          Serial.write("-");
      Serial.write(EEPROM.read(4));
}

void loop() {}
