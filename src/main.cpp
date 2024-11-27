#include <Arduino.h>
// Mga karagdagang ingklusyon
#include "tambilang.h"

// Mag-declare ng arrays para sa ilaw at pindutan
Tambilang ilaw[3] = {Tambilang(10), Tambilang(9), Tambilang(8)};
Tambilang pindutan[3] = {Tambilang(2), Tambilang(3), Tambilang(4)};

void setup() {
  // Kodigo ng inisyalisasyon
  Serial.begin(115200);
  Serial.println("\n	~~~ KUMUSTA, MUNDO! ~~~\n");

  // I-setup ang mga ilaw at pindutan
  for (int i = 0; i < 3; i++) {
    ilaw[i].palabas();       // Itakda ang ilaw bilang OUTPUT
    pindutan[i].papasokHatak();  // Itakda ang pindutan bilang INPUT_PULLUP
  }

  delay(500);
}

void loop() {
  // Pangunahing lohika ng programa
  Serial.print("[ ");
  
  // Pagbasa at pag-check ng bawat pindutan
  for (int i = 0; i < 3; i++) {
    // Kung ang pindutan ay nakapindot (0), ilaw ay magsisindi (1)
    if (pindutan[i].basahin()) {  // Kung pindutan ay NAKAPINDOT (LOW)
      ilaw[i].itaas();  // Itaas ang ilaw
      Serial.print("B" + String(i+1) + ": 1, ");  // Print 1 kapag nakapindot
    } else {  // Kung pindutan ay HINDI NAKAPINDOT (HIGH)
      ilaw[i].ibaba();  // Ibaba ang ilaw
      Serial.print("B" + String(i+1) + ": 0, ");  // Print 0 kapag hindi nakapindot
    }
  }

  // Tanggalin ang huling koma at mag-print ng closing bracket
  Serial.println("\b\b ]");

  delay(100);  // Delay para hindi magmukhang mabilis ang output
}
