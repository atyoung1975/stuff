#include "EEPROM.h"
void setup() {
  Serial.begin(9600);
  EEPROM.update(0, 'N'); //Tent Ident
  EEPROM.update(1, '1'); //Tent Number
 EEPROM.update(2, 5); //Number of sensors
  EEPROM.update(3, 2); //Starting Sensor Power Pin Position
  EEPROM.update(4, 8); //Starting Sensor Pin Position
  EEPROM.update(5, 10); //DTH11 Pin
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
