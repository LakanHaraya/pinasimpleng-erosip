#ifndef TAMBILANG_H
#define TAMBILANG_H

#include <Arduino.h>

class Tambilang {
public:
    Tambilang(int pin);
    void simulan();
    void isulat(bool halaga);
    void itaas();
    void ibaba();
private:
    int numeroPin;
};

#endif