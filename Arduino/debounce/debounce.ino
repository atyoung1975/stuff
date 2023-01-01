void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600);
  pinMode(10, INPUT);
  digitalWrite(10, HIGH);
}

void loop() {
  int buttCount = 0;
  // put your main code here, to run repeatedly:
  if (!digitalRead(10)) {
    Serial.println("Button Detected"); 
    Serial.println(buttCount); 
    for (int wait = 0; wait < 5; wait++) {
      Serial.println("Button Loop"); 
      if (!digitalRead(10)) {
        Serial.println("Button Count"); 
        buttCount++;
        delay(10);
      }
    }
  }
  if (buttCount >= 5){
    Serial.println("Button Pressed");  
  }
  
  delay(1000);
}
