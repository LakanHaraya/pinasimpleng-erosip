#include <Arduino.h>
#include "pamalikpik.h"

void setup() {
  Serial.begin(115200);
  initRudderElevator();
}

void loop() {
  updateRudderElevator();
}
