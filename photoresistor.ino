#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int readValueAnalog = 0;
float tension;
 
void setup() {
  Serial.begin (9600);
  lcd.begin(16, 2);
  pinMode(8, OUTPUT);
}
 
void loop() {
  readValueAnalog = analogRead(A3);
  
  tension = readValueAnalog * 0.0049;
  
  lcd.print(tension,4);
  lcd.print(" V");
  lcd.setCursor(0, 1);
  lcd.print("analog val ");
  lcd.print(readValueAnalog);
  
  if (readValueAnalog < 100) {
     digitalWrite(8, HIGH); 
  } else {
     digitalWrite(8, LOW);    
  }

  Serial.print(readValueAnalog);
  Serial.print(" ");
  Serial.print(tension);
  Serial.println(" = V");
  
  delay(200);
  lcd.clear();
}
