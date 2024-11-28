#include <Arduino.h>
// Mga karagdagang ingklusyon
#include "tambilang.h"

Tambilang ilaw1(10);

void setup() {
  // Kodigo ng inisyalisasyon
  Serial.begin(115200);
  Serial.println("\n	~~~ KUMUSTA, MUNDO! ~~~\n");
  // Magtakda ng iba pang inisyalisasyon
  
  ilaw1.palabas();
  
  delay(500);
}
void loop() {
  // Pangunahing lohika ng programa
  Serial.println("Lumilikaw...");
  
  ilaw1.kumisap(500, 5);
  
  // delay(50);
}