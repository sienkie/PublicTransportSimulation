#include <iostream>
#include "Trasa.h"

using namespace std;

Trasa::Trasa(Przystanek *p, Przystanek *k, int czas) {
    poczatek = p;
    koniec = k;
    czas_przejazdu = czas; //w minutach
}

Przystanek *Trasa::get_poczatek() {
    return poczatek;
}

Przystanek *Trasa::get_koniec() {
    return koniec;
}

int Trasa::get_czas() {
    return czas_przejazdu;
};

ostream &operator<<(ostream &output, const Trasa &t) {
    output << "Trasa(" << t.poczatek->get_nazwa() << "-" << t.koniec->get_nazwa() << ", czas: " << t.czas_przejazdu
           << ")";
    return output;
}