#include "Pojazd.h"
#include <sstream>
#include <string>

using namespace std;

bool Pojazd::empty_trasa() {
    return trasa.empty();
}

Trasa *Pojazd::spr_droge() const {
    Trasa *last = nullptr;
    if (!trasa.empty()) {
        last = trasa.front();
    }
    return last;
}

void Pojazd::skroc_trase() {
    if (!trasa.empty()) {
        trasa.pop();
    }
}

int Pojazd::get_nr_linii() const {
    return nr_linii;
}

bool Pojazd::wolne_miejsca() {
    return miejsca > 0;
}

Pojazd &Pojazd::operator+=(Osoba &os) {
    osoby.push_back(&os);
    miejsca--;
    return *this;
}

Pojazd &Pojazd::operator+=(Trasa &t) {
    trasa.push(&t);
    return *this;
}

void Pojazd::koniec_trasy() {
    osoby.clear();
    while (!trasa.empty()) {
        skroc_trase();
    }
    miejsca = pojemnosc;
}

void Pojazd::ktos_wysiada(Osoba *os) {
    int size = osoby.size();
    for (int i = 0; i < size; i++) {
        if (osoby[i] == os) {
            osoby.erase(osoby.begin() + i);
            miejsca++;
            break;
        }
    }
}

vector<Osoba*> Pojazd::get_osoby(){
    return osoby;
}

Tramwaj::Tramwaj(int nr_linii, int pojemnosc) {
    this->nr_linii = nr_linii;
    this->pojemnosc = pojemnosc;
    miejsca = pojemnosc;
}

ostream &operator<<(ostream &output, const Tramwaj &t) {
    string poz = t.spr_droge() ? t.spr_droge()->get_poczatek()->get_nazwa() : "-";
    output << "Tramwaj(linia: " << t.nr_linii << ",obecnie: " << poz
           << ", miejsca: " << t.miejsca << "/" << t.pojemnosc << ")";
    return output;
}