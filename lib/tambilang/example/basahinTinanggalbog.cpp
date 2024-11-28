#include <Arduino.h>
// Mga karagdagang ingklusyon
#include "tambilang.h"

Tambilang ilaw1(10);
Tambilang pindutan1(4);

void setup() {
  // Kodigo ng inisyalisasyon
  Serial.begin(115200);
  Serial.println("\n	~~~ KUMUSTA, MUNDO! ~~~\n");
  // Magtakda ng iba pang inisyalisasyon
  
  ilaw1.palabas();
  pindutan1.papasokHatak();

  ilaw1.isulat(false);
  
  delay(500);
}
void loop() {
  // Pangunahing lohika ng programa
  Serial.println("Lumilikaw...");
  
  if (pindutan1.basahinTinanggalbog(50)) {
    ilaw1.baligtarin();
    delay(200);
  }
  
  // delay(50);
}