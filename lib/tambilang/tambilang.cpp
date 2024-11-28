#include <Arduino.h>
#include "tambilang.h"

// Konstruktor para itakda ang numero ng pin
Tambilang::Tambilang(int pin, bool aktibongMababa) : _pin(pin), _aktibongMababa(aktibongMababa) {}

/*
    Itakda ang pin bilang `INPUT_PULLUP`. Sa ganitong pagsasaayos,
    ang aktibong estado (triggering) ay `LOW`.
*/
void Tambilang::papasokHatak() {
    pinMode(_pin, INPUT_PULLUP);
}

// Funsiyon para itakda ang pin bilang INPUT
void Tambilang::papasok() {
    pinMode(_pin, INPUT);
}

// Funsiyon para itakda ang pin bilang OUTPUT
void Tambilang::palabas() {
    pinMode(_pin, OUTPUT);
}

/*
    Itakda ang estado ng pin. Kapag ang `aktibongMababa` ay `true`,
    kumakatawan ang `LOW` sa "on/true" at ang `HIGH` sa "off/false".
    Kapag `false`, ang `HIGH` ay "on" at `LOW` ay "off".
*/
void Tambilang::isulat(bool halaga) {
    //// digitalWrite(_pin, halaga ? LOW : HIGH);
    digitalWrite(_pin, _aktibongMababa ? !halaga : halaga);
}

// Funsiyon para pataasin ang pin (itakda sa HIGH)
void Tambilang::itaas() {
    digitalWrite(_pin, HIGH);
}

// Funsiyon para pababain ang pin (itakda sa LOW)
void Tambilang::ibaba() {
    digitalWrite(_pin, LOW);
}

// Funsiyon para basahin ang kasalukuyang estado ng pin (HIGH o LOW)
bool Tambilang::basahin() {
    //// return digitalRead(_pin) == HIGH;
    bool halagangHilaw = digitalRead(_pin) == HIGH;
    return _aktibongMababa ? !halagangHilaw : halagangHilaw;    // Isaayos ang halaga batay sa asal ng aktibong-mababa
}