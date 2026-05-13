#include <Arduino.h>

// Configuring pins
const int pwma = 14;
const int ain2 = 27;
const int ain1 = 26;

const int pwmb = 25;
const int bin2 = 33;
const int bin1 = 32;

const int stby = 13;

void setup() {
  Serial.begin(115200);

  // Configuring pins as output
  pinMode(pwma, OUTPUT);
  pinMode(ain1, OUTPUT);
  pinMode(ain2, OUTPUT);
  pinMode(pwmb, OUTPUT);
  pinMode(bin1, OUTPUT);
  pinMode(bin2, OUTPUT);
  pinMode(stby, OUTPUT);

  digitalWrite(ain1, HIGH);
  digitalWrite(ain2, LOW);
  
  digitalWrite(bin1, HIGH);
  digitalWrite(bin2, LOW);
  
  digitalWrite(stby, HIGH);  
}

void loop() {
  digitalWrite(pwma, HIGH);
  digitalWrite(pwmb, HIGH);

  /*
  delay(2000);

  digitalWrite(pwma, LOW);
  digitalWrite(pwmb, LOW);

  delay(2000);
  */
}