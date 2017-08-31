#include "Zdarzenie.h"
#include "Kolejka.h"

int Zdarzenie::get_czas() {
    return czas;
}

TramwajNaPrzystanku::TramwajNaPrzystanku(Kolejka *k, int czas, Tramwaj *tramwaj) {
    kolejka = k;
    this->czas = czas;
    this->tramwaj = tramwaj;
}

int czy_ktos_wsiada(vector<Osoba *> kolejka, Przystanek *nastepny_przystanek) {
    int os = -1, i = 0;
    for (Osoba *osoba: kolejka) {
        if (osoba->spr_droge()->get_koniec() == nastepny_przystanek) {
            os = i;
            break;
        }
        i++;
    }
    return os;
}

void TramwajNaPrzystanku::wykonaj_sie() {
    //1. najpierw skroc wszystkim w srodku trase
    //2. wypusc tych co chca wysiasc
    //3. wpusc ludzi z przystanku
    //4. włóż do kolejki zdarzenie pojawienia się o wskazanym czasie na kolejnym przystanku
    //5. odjazd tramwaju - skroc sobie trasę
    for (Osoba *os: tramwaj->get_osoby()) {
        os->skroc_droge();
        if (os->pusta_droga()) {
            tramwaj->ktos_wysiada(os); // osoba dotarła do celu
        } else if (os->spr_droge()->get_koniec() != tramwaj->spr_droge()->get_koniec()) { //osoba musi się przesiąść
            tramwaj->ktos_wysiada(os);
            *(tramwaj->spr_droge()->get_poczatek()) += *os; //osoba ustawia się do kolejki na przystanku
        }
    }
    int indeks;
    vector<Osoba *> przystanek_kolejka = tramwaj->spr_droge()->get_poczatek()->get_kolejka();
    while (tramwaj->wolne_miejsca()) {
        indeks = czy_ktos_wsiada(przystanek_kolejka, tramwaj->spr_droge()->get_koniec());
        if (indeks == -1) {
            break;
        } else {
            przystanek_kolejka.erase(przystanek_kolejka.begin() + indeks);
        }
    }
    tramwaj->spr_droge()->get_poczatek()->set_kolejka(przystanek_kolejka);
    tramwaj->spr_droge()->get_czas();
    *kolejka += (new TramwajNaPrzystanku(kolejka, tramwaj->spr_droge()->get_czas(), tramwaj));
    tramwaj->skroc_trase();
};

ostream &operator<<(ostream &output, const TramwajNaPrzystanku &z) {
    output << "TramwajNaPrzystanku(nr: " << z.tramwaj->get_nr_linii() << ", przystanek: "
           << z.tramwaj->spr_droge()->get_poczatek()->get_nazwa() << ", czas: " << z.czas / 60 << "." << z.czas % 60
           << ")";
    return output;
}