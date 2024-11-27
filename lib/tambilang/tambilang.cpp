#include <Arduino.h>
#include "tambilang.h"

// Konstruktor para itakda ang numero ng pin
Tambilang::Tambilang(int pin) {
    numeroPin = pin;
}

// Funsiyon para itakda ang pin nilang OUTPUT
void Tambilang::simulan() {
    pinMode(numeroPin, OUTPUT);
}

// Funsiyon para magtakda ng halaga sa pin (HIGH o LOW)
void Tambilang::isulat(bool halaga) {
    digitalWrite(numeroPin, halaga ? HIGH : LOW);
}

// Funsiyon para pataasin ang pin (itakda sa HIGH)
void Tambilang::itaas() {
    digitalWrite(numeroPin, HIGH);
}

// Funsiyon para pababain ang pin (itakda sa LOW)
void Tambilang::ibaba() {
    digitalWrite(numeroPin, LOW);
}