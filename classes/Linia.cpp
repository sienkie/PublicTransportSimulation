#include <iostream>
#include "Linia.h"

Linia::Linia(int nr_linii, vector<Przystanek *> przystanki, vector<int> czasy) {
    this->nr_linii = nr_linii;
    this->przystanki = przystanki;
    this->czasy = czasy;
}

Linia &Linia::operator+=(Tramwaj &p) {
    pojazdy.push_back(&p);
    return *this;
}

void Linia::ustaw_trasy_w_dwie_strony(int od_godz, int do_godz, int odstep) {
    //trasa w dwie strony oznacza: miejsce_1->miejsce_2->miejsce_3-(pętla)->miejsce_3->miejsce_2->miejsce_1 i td...
    int caly_dzien = (do_godz - od_godz) * 60;
    int czas = 0, kursy = 0;
    int size_przestanki = przystanki.size();
    int size_pojazdy = pojazdy.size();
    for (int c : czasy) {
        czas += c;
    }
    for (int pojazd = 0; pojazd < size_pojazdy; pojazd++) {
        caly_dzien = caly_dzien - pojazd * odstep;
        kursy = caly_dzien / czas + 1;
        for (int kurs = (pojazd % 2); kurs < kursy; kurs++) {
            if (kurs % 2 == 0) {
                for (int i = 0; i < size_przestanki; i++) {
                    if (i == size_przestanki - 1) {
                        *(pojazdy[pojazd]) += *(new Trasa(przystanki[i], przystanki[i], czasy[i]));
                    } else {
                        *(pojazdy[pojazd]) += *(new Trasa(przystanki[i], przystanki[i + 1], czasy[i]));
                    }
                }
            } else {
                for (int i = size_przestanki - 1; i >= 0; i--) {
                    if (i == 0) {
                        *(pojazdy[pojazd]) += *(new Trasa(przystanki[i], przystanki[i], czasy[size_przestanki - 1]));
                    } else {
                        *(pojazdy[pojazd]) += *(new Trasa(przystanki[i], przystanki[i - 1], czasy[i - 1]));
                    }
                }
            }
        }
    }
}

void Linia::zmniejsz_ruch(int procent) {
    int ile = (int) (pojazdy.size() * procent / 100.0);
    int i = 0;
    for (Pojazd *p : pojazdy) {
        i++;
        if (i <= ile) {
            p->koniec_trasy();
        }
    }
}

ostream &operator<<(ostream &output, const Linia &l) {
    output << "Linia(nr: " << l.nr_linii << ", pojazdy: " << l.pojazdy.size() << ")" << endl;
    output << "Rozkład: " << endl;
    int size = l.przystanki.size();
    for (int i = 0; i < size; i++) {
        output << i + 1 << " " << l.przystanki[i]->get_nazwa() << " " << l.czasy[i] << endl;
    }
    return output;

}

int Linia::policz_odstep() {
    int czas = 0;
    for (int c : czasy) {
        czas = czas + 2 * c;
    }
    if (pojazdy.size() != 0)
        czas = czas / pojazdy.size();
    return czas;
}

vector<Przystanek*> Linia::get_przystanki(){
    return przystanki;
}

vector<Tramwaj*> Linia::get_tramwaje(){
    return pojazdy;
}