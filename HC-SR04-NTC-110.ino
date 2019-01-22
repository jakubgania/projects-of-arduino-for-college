#include <LiquidCrystal.h>
#include <math.h>

#define trigPin 10
#define echoPin 13
#define delayTime 200

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double thermistor(int RawADC) {
 double temp;
 temp = log(10000.0 * ((1024.0/RawADC - 1))); 
 temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp * temp ))* temp );
 temp = temp - 273.15;          
 return temp;
}

void setup() {
  Serial.begin (9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  lcd.begin(16, 2);
}

void loop() {
  int val, val2;
  double spdSnd, temp, temp2, tempAverage;                
            
  val = analogRead(0);
  val2 = analogRead(5);        
  temp = thermistor(val);
  temp2 = thermistor(val2);
  
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  tempAverage = (temp + temp2) / 2;
  spdSnd = 331.4 + (0.606 * tempAverage) + 0.62;
  distance = (duration / 2) * (spdSnd / 10000);
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
    
    lcd.print("Out of range");
    delay(delayTime);
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.print(" cm - ");
    Serial.print("Temperature = ");
    Serial.print(temp);
    Serial.println(" *");

    lcd.print(distance, 1);
    lcd.print(" cm");
    lcd.setCursor(0, 1);
    lcd.print(temp);
    lcd.print((char)223);
    lcd.print(" ");
    lcd.print(temp2);
    lcd.print((char)223); 
    delay(delayTime);
  }
 
  delay(delayTime);
  lcd.clear();
}
