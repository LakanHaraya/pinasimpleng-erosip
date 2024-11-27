#ifndef PANSIPAT_H
#define PANSIPAT_H

#include <Arduino.h>
#include <Wire.h>

class Pansipat {
public:
    bool magsipatAdresI2C(byte adres);
    void magsipatI2C();
    void magsipatSPI();     // Ipatupad sa hinaharap
};

#endif