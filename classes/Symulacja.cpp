#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "Symulacja.h"
#include "Zdarzenie.h"

using namespace std;

Symulacja::Symulacja() {
    cout << "Inicjowanie symulacji" << endl;
    //kolejka zdarzeń

};

Symulacja::~Symulacja() {
    cout << "Zakończenie symulacji" << endl;
};

void Symulacja::wczytywanie_danych(string nazwaPliku) {
    cout << "WCZYTYWANIE DANYCH" << endl;

    ifstream dane(nazwaPliku);
    if (!dane) {
        cout << "Nie mogę otworzyć pliku " << nazwaPliku << "!" << endl;
        exit(1);
    }

//    srand(time(NULL));
    int procent_studentow = 0, size = 0, pojemnosc = 0;

    //zmienne pomocnicze
    int przystanki = -1;
    int linie = -1;
    int uniwersytety = -1;
    int teatry = -1;
    int centra = -1;

    string wiersz;
    int nrWiersza = 0;

    while (getline(dane, wiersz)) {
        nrWiersza++;
        stringstream strWiersz(wiersz);
        string slowo;
        if (nrWiersza == 1) {
            cout << "Ilość dni symulacji: " << atoi(wiersz.c_str()) << endl;
            liczba_dni = atoi(wiersz.c_str());
        }
        if (nrWiersza == 2) {
            int ludzie = 0;
            while (strWiersz >> slowo) {
                ludzie++;
                if (ludzie == 1) {
                    cout << "Liczba pracujących: " << atoi(slowo.c_str()) << endl;
                    for (int i = 0; i < atoi(slowo.c_str()); i++) {
                        pracujacy.push_back(new Pracujacy(this));
                    }
                } else if (ludzie == 2) {
                    cout << "Liczba studentów: " << atoi(slowo.c_str()) << endl;
                    for (int i = 0; i < atoi(slowo.c_str()); i++) {
                        studenci.push_back(new Student(this));
                    }
                } else if (ludzie == 3) {
                    cout << "Liczba artystów: " << atoi(slowo.c_str()) << endl;
                    for (int i = 0; i < atoi(slowo.c_str()); i++) {
                        artysci.push_back(new Artysta(this));
                    }
                } else if (ludzie == 4) {
                    cout << "Liczba uczniów: " << atoi(slowo.c_str()) << endl;
                    for (int i = 0; i < atoi(slowo.c_str()); i++) {
                        uczniowie.push_back(new Uczen(this));
                    }
                }
            }
        }
        if (nrWiersza == 3) {
            cout << "Pr wyjazdu pracującego w ciągu dnia: " << atof(wiersz.c_str()) << endl;
            for (Pracujacy *p : pracujacy) {
                p->set_pr_przejazd(atof(wiersz.c_str()));
            }
        }
        if (nrWiersza == 4) {
            cout << "Pr zakupów w tygodniu: " << atof(wiersz.c_str()) << endl;
            for (Pracujacy *p : pracujacy) {
                p->set_pr_zakupy(atof(wiersz.c_str()));
            }
            for (Student *s : studenci) {
                s->set_pr_zakupy(atof(wiersz.c_str()));
            }
            for (Artysta *a : artysci) {
                a->set_pr_zakupy(atof(wiersz.c_str()));
            }
        }
        if (nrWiersza == 5) {
            cout << "Procent studentów z dwoma miejscami studiów: " << atoi(wiersz.c_str()) << endl;
            procent_studentow = atof(wiersz.c_str());
        }
        if (nrWiersza == 6) {
            cout << "Procent zmniejszenia liczby tramwajów w weekendy: " << atoi(wiersz.c_str()) << endl;
            pro_tramwaje = atoi(wiersz.c_str());
        }
        if (nrWiersza == 7) {
            int ludzie = 0;
            while (strWiersz >> slowo) {
                ludzie++;
                if (ludzie == 1) {
                    cout << "Pr pójścia do teatru pracujących: " << atof(slowo.c_str()) << endl;
                    for (Pracujacy *p : pracujacy) {
                        p->set_pr_teatr(atof(wiersz.c_str()));
                    }
                } else if (ludzie == 2) {
                    cout << "Pr pójścia do teatru studentów: " << atof(slowo.c_str()) << endl;
                    for (Student *p : studenci) {
                        p->set_pr_teatr(atof(wiersz.c_str()));
                    }
                } else if (ludzie == 3) {
                    cout << "Pr pójścia do teatru artystów: " << atof(slowo.c_str()) << endl;
                    for (Artysta *p : artysci) {
                        p->set_pr_teatr(atof(wiersz.c_str()));
                    }
                } else if (ludzie == 4) {
                    cout << "Pr pójścia do teatru uczniów: " << atof(slowo.c_str()) << endl;
                    for (Uczen *p : uczniowie) {
                        p->set_pr_teatr(atof(wiersz.c_str()));
                    }
                }
            }

        }
        if (nrWiersza == 8) {
            cout << "Pojemność tramwaju: " << atoi(wiersz.c_str()) << endl;
            pojemnosc = atoi(wiersz.c_str());
        }
        if (nrWiersza == 9) {
            przystanki = nrWiersza + atoi(wiersz.c_str());
            cout << "Liczba przystanków: " << atoi(wiersz.c_str()) << endl;
        } else if (przystanki > 0 && przystanki >= nrWiersza) {
            cout << "Przystanek: " << wiersz << endl;
            this->przystanki.push_back(new Przystanek(wiersz)); // tworzenie przystanków
            if (przystanki == nrWiersza) {
                przystanki = -1;
                linie = 0;
            }
        } else if (przystanki == -1 and linie == 0) {
            linie = nrWiersza + atoi(wiersz.c_str());
            cout << "Liczba linii tramwajowych: " << atoi(wiersz.c_str()) << endl;

            //ustalenie mieszkań/miejsc pracy /miejsc szkół ===> jeszcze nie uniwersytetów
            size = this->przystanki.size();
            for (Pracujacy *p : pracujacy) {
                p->set_mieszkanie(this->przystanki[rand() % size]);
                p->set_praca(this->przystanki[rand() % size]);
            }
            for (Student *p : studenci) {
                p->set_mieszkanie(this->przystanki[rand() % size]);
            }
            for (Uczen *p : uczniowie) {
                p->set_mieszkanie(this->przystanki[rand() % size]);
                p->set_szkola(this->przystanki[rand() % size]);
            }

        } else if (linie > 0) {
            cout << "Linia tramwajowa: " << endl;
            int liczba_tramwajow = 0;
            vector<Przystanek *> przystanki_tramwajow;
            vector<int> czasy_tramwajow;
            int nr = -1;
            while (strWiersz >> slowo) {
                nr++;
                if (nr == 0) {
                    cout << " - ilość tramwajów: " << atoi(slowo.c_str()) << endl;
                    liczba_tramwajow = atoi(slowo.c_str());
                } else {
                    if (nr % 2 == 1) {
                        cout << " - przystanek: " << slowo << endl;
                        Przystanek *p = get_przystanek(slowo);
                        if (p != nullptr) {
                            przystanki_tramwajow.push_back(p);
                        }
                    } else {
                        cout << " - czas przejazdu / czas oczekiwania na pętli: " << atoi(slowo.c_str()) << endl;
                        czasy_tramwajow.push_back(atoi(slowo.c_str()));
                    }
                }
            }
            if (przystanki_tramwajow.size() != czasy_tramwajow.size()) {
                cout << "Błąd w pliku z danymi symulacji" << endl;
                exit(1);
            } else {
                linie_tramwajowe.push_back(
                        new Linia(linie_tramwajowe.size() + 1, przystanki_tramwajow, czasy_tramwajow));
                for (int i = 0; i < liczba_tramwajow; i++) {
                    *(linie_tramwajowe[linie_tramwajowe.size() - 1]) += *(new Tramwaj(linie_tramwajowe.size(),
                                                                                      pojemnosc));
                }
            }
            if (linie == nrWiersza) {
                linie = -1;
                uniwersytety = 0;
            }
        } else if (linie == -1 && uniwersytety == 0) {
            uniwersytety = nrWiersza + atoi(wiersz.c_str());
            cout << "Liczba uniwersytetów: " << atoi(wiersz.c_str()) << endl;
        } else if (uniwersytety > 0) {
            cout << "Uniwersytet: " << endl;
            int nr = -1;
            string nazwa_uni;
            while (strWiersz >> slowo) {
                nr++;
                if (nr == 0) {
                    cout << " - nazwa uniwersytetu: " << slowo << endl;
                    nazwa_uni = slowo;
                } else {
                    cout << " - miejsce: " << slowo << endl;
                    Przystanek *p = get_przystanek(slowo);
                    if (p != nullptr) {
                        this->uniwersytety.push_back(new Uniwersytet(nazwa_uni, p));
                    }
                }
            }
            if (uniwersytety == nrWiersza) {
                uniwersytety = -1;
                teatry = 0;
                //ustalenie uniwersytetow
                procent_studentow = (int) (studenci.size() * procent_studentow / 100.0);
                int s = studenci.size();
                int size_uni = this->uniwersytety.size();
                for (int i = 0; i < s; i++) {
                    if (i <= procent_studentow) {
                        studenci[i]->set_uniwersytety(this->uniwersytety[rand() % size_uni],
                                                      this->uniwersytety[rand() % size_uni]);
                    } else {
                        studenci[i]->set_uniwersytety(this->uniwersytety[rand() % size_uni], nullptr);
                    }
                }
            }
        } else if (uniwersytety == -1 && teatry == 0) {
            teatry = nrWiersza + atoi(wiersz.c_str());
            cout << "Liczba teatrów: " << atoi(wiersz.c_str()) << endl;
        } else if (teatry > 0) {
            cout << "Teatr: " << endl;
            int nr = -1;
            string nazwa_teatru, miejsce;
            while (strWiersz >> slowo) {
                nr++;
                if (nr == 0) {
                    cout << " - nazwa teatru: " << slowo << endl;
                    nazwa_teatru = slowo;
                } else if (nr == 1) {
                    cout << " - miejsce: " << slowo << endl;
                    miejsce = slowo;
                } else {
                    cout << " - ilość miejsc na widowni: " << atoi(slowo.c_str()) << endl;
                    Przystanek *p = get_przystanek(slowo);
                    if (p != nullptr) {
                        this->teatry.push_back(new Teatr(nazwa_teatru, p, atoi(slowo.c_str()), liczba_dni));
                    }
                }
            }
            if (teatry == nrWiersza) {
                teatry = -1;
                centra = 0;
            }
        } else if (teatry == -1 && centra == 0) {
            centra = nrWiersza + atoi(wiersz.c_str());
            cout << "Liczba centrów handlowych: " << atoi(wiersz.c_str()) << endl;
        } else if (centra > 0) {
            cout << "Centrum Handlowe: " << endl;
            int nr = -1;
            string nazwa_centrum;
            while (strWiersz >> slowo) {
                nr++;
                if (nr == 0) {
                    cout << " - nazwa centrum: " << slowo << endl;
                    nazwa_centrum = slowo;
                } else {
                    cout << " - miejsce: " << slowo << endl;
                    Przystanek *p = get_przystanek(slowo);
                    if (p != nullptr) {
                        this->centra_handlowe.push_back(new CentrumHandlowe(nazwa_centrum, p));
                    }
                }
            }
        }
    }
};

vector<Przystanek *> Symulacja::get_przystanki() {
    return przystanki;
}

void Symulacja::set_przystanki(vector<Przystanek *> v) {
    przystanki = v;
}

vector<Teatr *> Symulacja::get_teatry() {
    return teatry;
}

void Symulacja::set_teatry(vector<Teatr *> v) {
    teatry = v;
}

Przystanek *Symulacja::get_przystanek(string nazwa) {
    for (Przystanek *p: przystanki) {
        if (p->get_nazwa() == nazwa) {
            return p;
        }
    }
    return nullptr;
}

vector<Linia *> Symulacja::get_linie() {
    return linie_tramwajowe;
}

void Symulacja::rozpocznij() {
    cout << "POCZĄTEK SYMULACJI" << endl;
    for (int dzien = 1; dzien < liczba_dni + 1; dzien++) {
        zaplanuj_dzien(dzien);
        // + spisanie statystyk
    }
}

void Symulacja::zaplanuj_dzien(int dzien) {
    cout<<"Dzien: "<< dzien << endl;
    //1. dla każdej linii tramwajowej: ustal trasy
    for (Linia *linia : linie_tramwajowe) {
        linia->ustaw_trasy_w_dwie_strony(6, 23, linia->policz_odstep());
    }
    //2. jeśli weekend - dla każdej linii zmniejsz_ruch()
    if (dzien % 7 == 6 || dzien % 7 == 0) {
        for (Linia *linia: linie_tramwajowe) {
            linia->zmniejsz_ruch(pro_tramwaje);
        }
    }
    //3. dodanie do kolejki dla każdego tramwaju: TramwajNaPrzystanku dla pierwszego przystanku na trasie
    for (Linia *linia: linie_tramwajowe) {
        int czas = linia->policz_odstep();
        int i = 0;
        for (Tramwaj *tramwaj: linia->get_tramwaje()) {
            *kolejka += (new TramwajNaPrzystanku(kolejka, 6 * 60 + (i * czas), tramwaj));
            cout << tramwaj->get_nr_linii() << " " << tramwaj->spr_droge()->get_poczatek()->get_nazwa() << " "
                 << (6 * 60 + (i * czas)) / 60 << "." << (6 * 60 + (i * czas)) % 60 << endl;
            i++;
        }
    }
    //4. jeśli (dzien % 30 == 1) dla każdej osoby: czy_teatr -> kup_bilet
    //5. dodanie do kolejki dla każdego teatru rozpoczęcia spektakli danego dnia
    //-> zdarzenie godzine przed spektaklem wyliczy dla każdej osoby z widzow o której ma wyjść z pracy i włoży odpowiednie zdarzenie
    // (funkcje ustal_trase / idz)
    //6. dla każdej osoby wyliczenie trasy do pracy/uniwersytetu i idz() o określonej porze
    //7. dla każdego pracujacego: czy_przejazd() -> jeśli tak to dodaj zdarzenie 'przejazd'
    //->(funkcja ustal_trase + dodanie trasy odwrotnej / idz)
    //8. dla każdego zakończenia spektaklu - zdarzenie w kolejce -> każda osoba powrot_to_domu() (+ każda osoba: czy_teatr -> kup_bilet)
    //9. dla każdej osoby która nie idzie do teatru -> czy_zakupy() -> odpowiednie zdarzenie zakupów i powrotu do domu o wyliczonej porze

    //10. rozpocznij_dzien()
}

void Symulacja::rozpocznij_dzien() {
    //dopóki kolejka nie jest pusta: wykonaj zdarzenie -> skroc kolejke
    //zakończenie dnia:
    //1. każdy tramwaj ma pustą trasę
    //2. każda osoba ma obecna_pozycja == mieszkanie oraz pustą trasę
}

vector<Przystanek *> Symulacja::znajdz_polaczenia(Przystanek *klucz) {
    return polaczenia[klucz];
}

void Symulacja::ustal_polaczenia() {
    for (Linia *linia: linie_tramwajowe) {
        int size = linia->get_przystanki().size();
        for (int i = 0; i < size - 1; i++) {
            polaczenia[linia->get_przystanki()[i]].push_back(linia->get_przystanki()[i + 1]);
            polaczenia[linia->get_przystanki()[i + 1]].push_back(linia->get_przystanki()[i]);
        }
    }
}