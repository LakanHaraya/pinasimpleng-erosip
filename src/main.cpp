#include <Arduino.h>
// Mga karagdagang ingklusyon
#include <Wire.h>
#include "pansipat.h"

Pansipat tagasipat;

void setup() {
  // Kodigo ng inisyalisasyon
  Serial.begin(115200);
  Serial.println("\n	~~~ KUMUSTA, MUNDO! ~~~\n");
  // Magtakda ng iba pang inisyalisasyon
  
  tagasipat.magsipatI2C();
  tagasipat.magsipatSPI();
  
  delay(500);
}
void loop() {
  // Pangunahing lohika ng programa
  Serial.println("Lumilikaw...");
  
  
  
  delay(1000);
}