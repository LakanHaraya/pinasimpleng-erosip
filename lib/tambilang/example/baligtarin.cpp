#include <Arduino.h>
// Mga karagdagang ingklusyon
#include "tambilang.h"

Tambilang ilaw1(10);
Tambilang ilaw2(8);

void setup() {
  // Kodigo ng inisyalisasyon
  Serial.begin(115200);
  Serial.println("\n	~~~ KUMUSTA, MUNDO! ~~~\n");
  // Magtakda ng iba pang inisyalisasyon
  
  ilaw1.palabas();
  ilaw2.palabas();

  ilaw1.itaas();
  ilaw2.ibaba();
  
  delay(500);
}
void loop() {
  // Pangunahing lohika ng programa
  Serial.println("Lumilikaw...");
  
  ilaw1.baligtarin();
  ilaw2.baligtarin();
  
  delay(50);
}