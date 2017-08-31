#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include "Miejsce.h"

using namespace std;

string Miejsce::get_nazwa() {
    return nazwa;
}

Przystanek *Miejsce::get_przystanek() {
    return przystanek;
}

CentrumHandlowe::CentrumHandlowe(string n, Przystanek *p) {
    nazwa = n;
    przystanek = p;
}

Uniwersytet::Uniwersytet(string n, Przystanek *p) {
    nazwa = n;
    przystanek = p;
}

Teatr::Teatr(string n, Przystanek *p, int miejsca, int dni) {
    nazwa = n;
    przystanek = p;
    liczba_miejsc = miejsca;
    ustal_repertuar(miejsca, dni);
}

Teatr::~Teatr() {
    for (Spektakl *element: repertuar) {
        delete element;
    }
}

void Teatr::ustal_repertuar(int miejsca, int dni) {
//    srand(time(NULL));
    int m = dni / 30; //na każdy miesiąc oddzielnie losowany repertuar
    int spektakle_w_tyg;
    int size;
    vector<int> dni_spektakli;
    for (int i = 0; i < m; i++) {
        spektakle_w_tyg = rand() % 5 + 1;
        dni_spektakli = losuj_dni_tygodnia(5, spektakle_w_tyg);
        for (int d = 1; d <= 30; d++) {
            if (d % 7 == 0 || d % 7 == 6) {
                repertuar.push_back(new Spektakl(miejsca, 17, 30 * i + d, rand() % 3 + 1));
                repertuar.push_back(new Spektakl(miejsca, 19, 30 * i + d, rand() % 3 + 1));
            } else {
                size = dni_spektakli.size();
                for (int k = 0; k < size; k++) {
                    if (dni_spektakli[k] == d % 7) {
                        repertuar.push_back(new Spektakl(miejsca, 19, 30 * i + d, rand() % 3 + 1));
                    }
                }
            }
        }
    }
    spektakle_w_tyg = rand() % 5 + 1;
    dni_spektakli = losuj_dni_tygodnia(5, spektakle_w_tyg);
    for (int d = 1; d <= dni % 30; d++) {
        if (d % 7 == 0 || d % 7 == 6) {
            repertuar.push_back(new Spektakl(miejsca, 17, 30 * m + d, rand() % 3 + 1));
            repertuar.push_back(new Spektakl(miejsca, 19, 30 * m + d, rand() % 3 + 1));

        } else {
            size = dni_spektakli.size();
            for (int k = 0; k < size; k++) {
                if (dni_spektakli[k] == d % 7) {
                    repertuar.push_back(new Spektakl(miejsca, 19, 30 * m + d, rand() % 3 + 1));
                }
            }
        }
    }
}

vector<int> Teatr::losuj_dni_tygodnia(int zakres, int dni) { //np w dniach roboczych (zakres = 5) losuj 3 dni
    vector<int> tydzien;
    vector<int> wynik;
    for (int i = 1; i <= zakres; i++) {
        tydzien.push_back(i);
    }
    if (zakres == dni) {
        return tydzien;
    }
    int id;
    for (int i = 0; i < dni; i++) {
        id = rand() % (tydzien.size() - 1);
        wynik.push_back(tydzien[id]);
        tydzien.erase(tydzien.begin() + id);
    }
    return wynik;
}

vector<Spektakl *> Teatr::get_repertuar() {
    return repertuar;
}

ostream &operator<<(ostream &output, const Teatr &t) {
    output << "Teatr(nazwa: " << t.nazwa << ", miejsca: " << t.liczba_miejsc << " ,liczba spektakli:"
           << t.repertuar.size() << ")" << endl;
    int size = t.repertuar.size();
    for (int i = 0; i < size; i++) {
        output << " " << *(t.repertuar[i]) << endl;
    }
    return output;
}

ostream &operator<<(ostream &output, const Uniwersytet &u) {
    output << "Uniwersytet(nazwa: " << u.nazwa << ", adres: " << u.przystanek->get_nazwa() << ")";
    return output;
}