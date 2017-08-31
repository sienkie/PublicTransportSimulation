#include <iostream>
#include "Spektakl.h"

using namespace std;

Spektakl::Spektakl(int miejsca, int g, int d, int c) {
    wolne_miejsca = miejsca;
    godzina = g;
    dzien = d;
    czas = c;
}

bool Spektakl::wolne_bilety() {
    return (wolne_miejsca > 0);
}

Spektakl &Spektakl::operator+=(Osoba &osoba) {
    widzowie.push_back(&osoba);
    return *this;
}

int Spektakl::godzina_spektaklu() {
    return godzina;
}

int Spektakl::dzien_spektaklu() {
    return dzien;
}

int Spektakl::czas_trwania() {
    return czas;
}

void Spektakl::sprzedaj_bilet(Osoba *os) {
    if (wolne_bilety()) {
        widzowie.push_back(os);
        wolne_miejsca--;
    }
}

void Spektakl::set_wolne_bilety(int w){
    wolne_miejsca = w;
}

ostream &operator<<(ostream &output, const Spektakl &s) {
    output << "Spektakl(dzień: " << s.dzien << ", godzina: " << s.godzina << ", czas trwania: " << s.czas
           << ", wolne miejsca: " << s.wolne_miejsca << ")";
    return output;
}