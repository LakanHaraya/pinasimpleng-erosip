#include <Arduino.h>
#include "tambilang.h"

// Pin para sa LED (output) at pindutan (input)
Tambilang ilaw1(10, false);   // LED sa pin 10, active-high
Tambilang pindutan1(4, true); // Pindutan sa pin 4, active-low

void setup() {
    ilaw1.palabas();          // Itakda ang LED bilang OUTPUT
    ilaw1.isulat(false);      // Siguraduhing patay ang LED
    pindutan1.papasokHatak(); // Itakda ang pindutan bilang INPUT_PULLUP
}

void loop() {
    // Kapag pinindot ang pindutan, magbigay ng pulso
    if (pindutan1.basahinTinanggalbog(50)) { // 50ms debounce time
        ilaw1.pulso(1000); // Magbigay ng 1000ms pulse
    }
}
