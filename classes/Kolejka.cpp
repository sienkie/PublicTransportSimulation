#include <iostream>
#include "Kolejka.h"

Kolejka::Kolejka() {
    czas = 0;
    cout << "Inicjacja kolejki" << endl;
}

Kolejka::~Kolejka() {
    cout << "Destruktor kolejki" << endl;
}

void Kolejka::wyczysc_kolejke() {
    lista_zdarzen.clear();
}

void Kolejka::wykonaj_zdarzenie() {
//wykonuje pierwsze zdarzenie i skraca liste zdarzeń

}

Kolejka &Kolejka::operator+=(Zdarzenie *z) {
    // dodaje zdarzenie w odpowiednie miejsce względem czasu
    return *this;
}

bool Kolejka::empty() {
    return lista_zdarzen.empty();
}