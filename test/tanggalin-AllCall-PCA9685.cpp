/*
  Hindi makikita ang ALLCALL address na 0x70 sa pansipat
*/

#include <Arduino.h>
#include <Wire.h>
#include "pansipat.h"

#define PCA9685_ADDR 0x40

Pansipat sipatI2C;

void setup() {
    Serial.begin(115200);
    Wire.begin();

    // Mag-akses sa rehistro ng MODE1 upang di-paganahin ang ALLCALL
    Wire.beginTransmission(PCA9685_ADDR);
    Wire.write(0x00);   // rehistro ng MODE1
    Wire.write(0x10);   // Linisin anh ALLCALL bit (Bit 0)
    Wire.endTransmission();
    delay(200);
}

void loop() {
  sipatI2C.magsipatI2C();
  delay(1000);
}
