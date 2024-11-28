#include <Arduino.h>
#include "tambilang.h"

// Konstruktor para itakda ang numero ng pin
Tambilang::Tambilang(int pin, bool aktibongMababa) : _pin(pin), _aktibongMababa(aktibongMababa) {}

/*
    ### Magtakda ng `INPUT_PULLUP`

    Itakda ang pin bilang `INPUT_PULLUP`. Sa ganitong pagsasaayos,
    ang aktibong estado (triggering) ay `LOW`.
*/
void Tambilang::papasokHatak() {
    pinMode(_pin, INPUT_PULLUP);
}

/*
    ### Magtakda ng `INPUT`

    Funsiyon para itakda ang pin bilang INPUT
*/
void Tambilang::papasok() {
    pinMode(_pin, INPUT);
}

// Funsiyon para itakda ang pin bilang OUTPUT
void Tambilang::palabas() {
    pinMode(_pin, OUTPUT);
}

/*
    Itakda ang estado ng pin.

    Kapag ang `aktibongMababa` ay `true`:
        - `isulat(true)` -> Pin ay `LOW` (on)
        - `isulat(false)` -> Pin ay `HIGH` (off)
    Kapag ang `aktibongMababa` ay `false`:
        - `isulat(true)` -> Pin ay `HIGH` (on)
        - `isulat(false)` -> Pin ay `LOW` (off)
*/
void Tambilang::isulat(bool halaga) {
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
    bool halagangHilaw = digitalRead(_pin) == HIGH;
    return _aktibongMababa ? !halagangHilaw : halagangHilaw;    // Isaayos ang halaga batay sa asal ng aktibong-mababa
}

/*
    ### Pagbaligtad ng Estado

    Mabilis na baligtarin ang estado ng isang digital pin (mula `HIGH`
    patungo sa `LOW`, o kabaligtaran).
*/
void Tambilang::baligtarin() {
    bool kasalukuyangEstado = digitalRead(_pin);
    digitalWrite(_pin, !kasalukuyangEstado);
}

/*
    ### Kumisap

    Mabilis na pagpapabuhay at pagpapatay ng aparato sa
    loob ng tiyak na sandali.
*/
void Tambilang::kumisap(int tagalMs, int ulit) {
    for (int i = 0; i < ulit; i++) {
        digitalWrite(_pin, _aktibongMababa ? LOW : HIGH);
        delay(tagalMs);
        digitalWrite(_pin, _aktibongMababa ? HIGH : LOW);
        delay(tagalMs);
    }
}

/*
    ### Pagpigil ng Noise sa Pindutan

    Para sa maayos na pagbabasa ng pindutan at pag-iwas sa \"pagtalbog\"
    na nangyayari kapag pinindot o nagbabago ito.
*/
bool Tambilang::basahinTinanggalbog(unsigned long sandalingTanggalbogMs) {
    static unsigned long hulingPagbasa = 0;
    static bool hulingEstado = false;
    bool kasalukuyangEstado = basahin();
    unsigned long kasalukuyangSandali = millis();
    if (kasalukuyangEstado != hulingEstado && (kasalukuyangSandali - hulingPagbasa) >= sandalingTanggalbogMs) {
        hulingPagbasa = kasalukuyangSandali;
        hulingEstado = kasalukuyangEstado;
        return kasalukuyangEstado;
    }
    return hulingEstado;
}

/*
    ### Magbigay ng Maikling `HIGH` o `LOW` Pulse

    Magagamit para mag-trigger ng relay, servo controller, o iba
    pang hardware na nangangailangan ng maikling pulse.
*/
void Tambilang::pulso(int tagalMs){
    digitalWrite(_pin, _aktibongMababa ? LOW : HIGH);   // ON
    delay(tagalMs);
    digitalWrite(_pin, _aktibongMababa ? HIGH : LOW);   // OFF
}

/*
    ### Ibalik kung `ACTIVE` o `INACTIVE`

    Magbibigay ng high-level abstraction kung ang pin ay nasa
    \"active\" state o hindi, batay sa `aktibongMababa`.
*/
bool Tambilang::aktibo() {
    return basahin();
}

/*
    ### Pilit na Hatak Pataas para sa INPUT Mode
    
    Kung nais mo ng mas malinaw na kontrol sa pull-up resistor.
*/
void Tambilang::itakdaHatakPataas(bool estado) {
    pinMode(_pin, estado ? INPUT_PULLUP : INPUT);
}

/*
    ### Para sa Pekeng Analog Output

    Kung ang pin ay nasa PWM-capable (hal. Arduino pins 3, 5,
    6, 9, 10, 11 sa Uno), maaaring magdagdag ng functionality
    para sa analog output.
*/
void Tambilang::tawangkiPeke(int halaga) {
    analogWrite(_pin, halaga);  // Halaga ay nasa pagitan ng 0 (0% duty cycle) at 255 (100% duty cycle)
}
