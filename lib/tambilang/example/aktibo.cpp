#include <Arduino.h>
#include "tambilang.h"

// Pin para sa LED (output) at pindutan (input)
Tambilang ilaw(10, false);   // LED sa pin 10, active-high
Tambilang pindutan(4, true); // Pindutan sa pin 3, active-low

void setup() {
    Serial.begin(115200);
    ilaw.palabas();          // Itakda ang LED bilang OUTPUT
    ilaw.isulat(false);      // Siguraduhing patay ang LED
    pindutan.papasokHatak(); // Itakda ang pindutan bilang INPUT_PULLUP
}

void loop() {
    // Suriin kung ang pindutan ay nasa active state
    if (pindutan.aktibo()) {
        ilaw.itaas(); // Buksan ang LED (active-low, HIGH ang signal)
    } else {
        ilaw.ibaba(); // Patayin ang LED
    }

    Serial.println(pindutan.aktibo() ? "Pindutan: ACTIVE" : "Pindutan: INACTIVE");
    delay(100);
}
