#ifndef TAMBILANG_H
#define TAMBILANG_H

#include <Arduino.h>

class Tambilang {
public:
    Tambilang(int pin, bool aktibongMababa = true);
    void papasokHatak();
    void papasok();
    void palabas();
    void isulat(bool halaga);
    void itaas();
    void ibaba();
    bool basahin();
    void baligtarin();
    void kumisap(int tagalMs = 500, int ulit = 1);
    bool basahinTinanggalbog(unsigned long sandalingTanggalbogMs = 50);
    void pulso(int tagalMs = 500);
    bool aktibo();
    void itakdaHatakPataas(bool estado = true);

    //* Para sa analog pin
    //?? Bakit nandito???
    void tawangkiPeke(int halaga);
private:
    int _pin;
    bool _aktibongMababa;
};

#endif