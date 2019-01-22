#include <dht.h>

#define trigPin 10
#define echoPin 13
#define DHT11_PIN 2

dht DHT;

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration, distance;
  float speed;
  
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  speed = 331.4 + (0.606 * DHT.temperature) + (0.0124 * DHT.humidity);
  distance = (duration / 2) * (speed / 10000);
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(DHT.temperature);
    Serial.println(" cm");
    delay(1000);
  }

  delay(1000);
}
