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
  Serial.println("Sinisipat ang mga aparatong I2C...\n");
  int natagpuangAparato = 0;

  for (byte adres = 1; adres < 127; adres++) {
    if (magsipatAdresI2C(adres)) {
      if (natagpuangAparato == 0) {
        Serial.println("Natagpuang Adres I2C:\n============");
      }
      Serial.print("    "); // Indentation na 4 spaces
      Serial.print("0x");
      if (adres < 16) {
        Serial.print("0"); // Para sa mga address na mas mababa sa 0x10
      }
      Serial.println(adres, HEX);
      natagpuangAparato++;
    }
  }
  if (natagpuangAparato == 0) {
    Serial.println("    Walang natagpuan\n");
  } else {
    Serial.println("============\n");
  }
}

// Pansipat ng mga aparatong SPI
void Pansipat::magsipatSPI() {
  Serial.println("Pansipat SPI, hindi pa naipatutupad");
}