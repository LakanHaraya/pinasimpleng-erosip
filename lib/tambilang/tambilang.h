#ifndef TAMBILANG_H
#define TAMBILANG_H

#include <Arduino.h>

class Tambilang {
public:
    Tambilang(int pin);
    void papasokHatak();
    void papasok();
    void palabas();
    void isulat(bool halaga);
    void itaas();
    void ibaba();
    bool basahin();
private:
    int numeroPin;
};

#endif