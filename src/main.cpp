#include <Arduino.h>
#include "tambilang.h"

// Tambilang instance para sa isang pindutan
Tambilang pindutan(4); // Pindutan sa pin 4, active-low

// LED para ipakita ang estado ng pindutan
Tambilang ilaw(10); // LED sa pin 10, active-low

void setup() {
    Serial.begin(115200);
    ilaw.palabas();           // Itakda ang LED bilang OUTPUT
    ilaw.isulat(false);       // Patayin ang LED
    pindutan.itakdaHatakPataas(true); // Gamitin ang INPUT_PULLUP
}

void loop() {
    if (pindutan.aktibo()) { // Kapag aktibo ang pindutan
        ilaw.itaas();        // Buksan ang LED
    } else {
        ilaw.ibaba();        // Patayin ang LED
    }

    // Ipakita ang estado ng pindutan sa Serial Monitor
    Serial.println(pindutan.aktibo() ? "Pindutan: ACTIVE" : "Pindutan: INACTIVE");
    delay(100); // Delay para hindi mabilis ang output
}
