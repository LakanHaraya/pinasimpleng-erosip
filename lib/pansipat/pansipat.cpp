#include <Arduino.h>
#include <Wire.h>
#include "pansipat.h"

// Pansipat ng adres I2C
bool Pansipat::magsipatAdresI2C(byte adres) {
  Wire.beginTransmission(adres);
  byte mali = Wire.endTransmission();
  return mali == 0;  // Ibalik true kung may device na tumugon
}

// Pansipat ng mga aparatong I2C
void Pansipat::magsipatI2C() {
  Wire.begin();
  Serial.println("Sinisipat ang mga aparatong I2C...");
  int natagpuangAparato = 0;
  for (byte adres = 1; adres < 127; adres++) {
    if (magsipatAdresI2C(adres)) {
      Serial.print("Natagpuang aparato sa 0x");
      Serial.println(adres, HEX);
      natagpuangAparato++;
    }
  }
  if (natagpuangAparato == 0) {
    Serial.println("Walang natagpuan");
  } else {
    Serial.println("Natapos ang pagsipat");
  }
}

// Pansipat ng mga aparatong SPI
void Pansipat::magsipatSPI() {
  Serial.println("Pansipat SPI, hindi pa naipatutupad");
}