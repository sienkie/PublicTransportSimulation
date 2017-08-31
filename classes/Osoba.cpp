#include <iostream>
#include "Osoba.h"
#include "Symulacja.h"

using namespace std;

Osoba &Osoba::operator+=(Trasa &t) {
    trasa.push(&t);
    return *this;
}

bool Osoba::pusta_droga() {
    return trasa.empty();
}

void Osoba::skroc_droge() {
    if (!trasa.empty()) {
        trasa.pop();
    }
}

Trasa *Osoba::spr_droge() {
    Trasa *last = nullptr;
    if (!trasa.empty()) {
        last = trasa.front();
    }
    return last;
}

bool Osoba::czy_teatr() {
    return (rand() % 100) < pr_teatr * 100;
}

void Osoba::set_mieszkanie(Przystanek *mieszkanie) {
    this->mieszkanie = mieszkanie;
    this->obecna_pozycja = mieszkanie;
}

void Osoba::set_pr_teatr(double pr_teatr) {
    this->pr_teatr = pr_teatr;
}

void Osoba::kup_bilet() {
    Teatr *t = symulacja->get_teatry()[rand() % symulacja->get_teatry().size()];
    for (Spektakl *s: t->get_repertuar()) {
        if (s->wolne_bilety()) {
            s->sprzedaj_bilet(this);
            break;
        }
        // założenie z polecenia: jeśli w wylosowanym teatrze nie ma wolnego miejsca na spektakl odbywający się
        // podczas trwania symulacji to się tym nie przejmujemy
    }
}

void Osoba::idz() {
    if (!trasa.empty()) {
        *(obecna_pozycja) += *(this);
    }
}

Uczen::Uczen(Symulacja *s, Przystanek *mieszkanie, double pr_teatr, Przystanek *szkola) {
    symulacja = s;
    this->mieszkanie = mieszkanie;
    obecna_pozycja = mieszkanie;
    this->szkola = szkola;
    this->pr_teatr = pr_teatr;
    for (int i = 0; i < 5; i++) {
        godziny_konczenia.push_back(rand() % 6 + 12);
    }
}

Uczen::Uczen(Symulacja *s) {
    symulacja = s;
    for (int i = 0; i < 5; i++) {
        godziny_konczenia.push_back(rand() % 6 + 12);
    }
}

void Uczen::set_szkola(Przystanek *szkola) {
    this->szkola = szkola;
}

ostream &operator<<(ostream &output, const Uczen &u) {
    output << "Uczeń(szkoła: " << u.szkola->get_nazwa() << ", obecna pozycja: " << u.obecna_pozycja->get_nazwa() << ")"
           << endl << "Plan: " << endl;
    int i = 1;
    for (int element: u.godziny_konczenia) {
        output << "dzień " << i << ": od 8 do " << element << endl;
        i++;
    }
    return output;
}

bool Dorosly::czy_zakupy() {
    return (rand() % 100) < pr_zakupy * 100;
}

void Dorosly::set_pr_zakupy(double pr_zakupy) {
    this->pr_zakupy = pr_zakupy;
}

Pracujacy::Pracujacy(Symulacja *s, Przystanek *mieszkanie, double pr_teatr, double pr_zakupy, Przystanek *praca,
                     double pr_przejazd) {
    symulacja = s;
    this->mieszkanie = mieszkanie;
    obecna_pozycja = mieszkanie;
    this->pr_teatr = pr_teatr;
    this->pr_zakupy = pr_zakupy;
    this->praca = praca;
    this->pr_przejazd = pr_przejazd;
    czas_wyjazdu = rand() % 5 + 6;
}

Pracujacy::Pracujacy(Symulacja *s) {
    symulacja = s;
    czas_wyjazdu = rand() % 5 + 6;
}

bool Pracujacy::czy_przejazd() {
    return (rand() % 100) < pr_przejazd * 100;
}

void Pracujacy::set_praca(Przystanek *praca) {
    this->praca = praca;
}

void Pracujacy::set_pr_przejazd(double pr_przejad) {
    this->pr_przejazd = pr_przejad;
}

Student::Student(Symulacja *s) {
    symulacja = s;
    int czas, pocz;
    for (int i = 0; i < 5; i++) {
        pocz = rand() % 9 + 8;
        czas = rand() % 9 + 2;
        czas = (pocz + czas) > 20 ? 20 : pocz + czas;
        plan.push_back(int_pair(pocz, czas));
    }
    uniwersytet1 = nullptr;
    uniwersytet2 = nullptr;
}

void Student::set_uniwersytety(Uniwersytet *u1, Uniwersytet *u2) {
    uniwersytet1 = u1;
    if (u2 != nullptr) {
        uniwersytet2 = u2;
        for (int_pair element: plan) {
            godziny_przejazdow.push_back(element.first + (element.second - element.first) / 2.0);
        }
    }
}

uni_pair Student::get_uniwersytety() {
    return uni_pair(uniwersytet1, uniwersytet2);
};

vector<int_pair> Student::get_plan() {
    return plan;
}

vector<double> Student::get_godziny_przejazdow() {
    return godziny_przejazdow;
}

bool Student::drugi_uniwersytet() {
    return (uniwersytet2 != nullptr);
}

Artysta::Artysta(Symulacja *s) {
    symulacja = s;
}

void Artysta::set_plan() {
    vector<int> indeksy;
    int m_pracy = rand() % 3 + 1;
    int ilosc;
    bool in;
    int size = 0;
    while (size < m_pracy) {
        ilosc = rand() % symulacja->get_przystanki().size();
        in = false;
        for (int element : indeksy) {
            if (element == ilosc) {
                in = true;
                break;
            }
        }
        if (!in)
            indeksy.push_back(ilosc);
        size = indeksy.size();
    }
    int pocz;
    int kon;
    for (int i = 0; i < 7; i++) {
        miejsca_pracy.push_back(symulacja->get_przystanki()[indeksy[rand() % indeksy.size()]]);
        pocz = rand() % 15 + 7; //dowolne godziny : zalozenie 7-21
        kon = rand() % 15 + 7;
        if (pocz > kon) {
            plan.push_back(int_pair(kon, pocz));
        } else {
            plan.push_back(int_pair(pocz, kon));
        }
    }

}

vector<int_pair> Artysta::get_plan() {
    return plan;
}

vector<Przystanek *> Artysta::get_miejsca_pracy() {
    return miejsca_pracy;
}

ostream &operator<<(ostream &output, const Artysta &a) {
    output << "Artysta - Plan pracy:" << endl;
    for (int i = 0; i < 7; i++) {
        output << "dzień " << i + 1 << " " << a.miejsca_pracy[i]->get_nazwa() << ": " << a.plan[i].first << " - "
               << a.plan[i].second << endl;
    }
    return output;
}