#include <Arduino.h>
// Mga karagdagang ingklusyon
#include <tambilang.h>

// Mag-declare ng arrays para sa ilaw at pindutan
Tambilang ilaw[3] = {Tambilang(10), Tambilang(9), Tambilang(8, false)};
Tambilang pindutan[3] = {Tambilang(2, false), Tambilang(3, true), Tambilang(4, false)};

// Array para sa dating estado ng mga pindutan
bool datingEstado[3] = {false, false, false};

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
  bool mayPagbabago = false;  // Flag para sa pagbabago ng estado

  // Pangunahing lohika ng programa
  for (int i = 0; i < 3; i++) {
    bool kasalukuyangEstado = pindutan[i].basahin();  // Basahin ang kasalukuyang estado
    
    // I-check kung nagbago ang estado
    if (kasalukuyangEstado != datingEstado[i]) {
      mayPagbabago = true;  // May pagbabago
      datingEstado[i] = kasalukuyangEstado;  // I-update ang dating estado

      // I-update ang ilaw batay sa kasalukuyang estado
      if (kasalukuyangEstado) {
        ilaw[i].ibaba();  // Ibaba ang ilaw (LOW)
      } else {
        ilaw[i].itaas();  // Itaas ang ilaw (HIGH)
      }
    }
  }

  // Mag-print lamang kung may pagbabago
  if (mayPagbabago) {
    Serial.print("[ ");
    for (int i = 0; i < 3; i++) {
      Serial.print("B" + String(i+1) + ": " + String(!datingEstado[i]));  
      if (i < 2) Serial.print(", ");
    }
    Serial.println(" ]");
  }

  delay(100);  // Delay para hindi magmukhang mabilis ang output
}
