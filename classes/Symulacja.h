#ifndef SYMULACJA_SYMULACJA_H
#define SYMULACJA_SYMULACJA_H

#include <string>
#include "Przystanek.h"
#include "Miejsce.h"
#include "Linia.h"
#include "Kolejka.h"

using namespace std;

class Symulacja {

private:

    int liczba_dni;
    int pro_tramwaje; //procent zmniejszenia tramwajow w weekend
    vector<Przystanek *> przystanki;
    vector<Teatr *> teatry;
    vector<Uniwersytet *> uniwersytety;
    vector<CentrumHandlowe *> centra_handlowe;
    vector<Pracujacy *> pracujacy;
    vector<Student *> studenci;
    vector<Artysta *> artysci;
    vector<Uczen *> uczniowie;
    vector<Linia*> linie_tramwajowe;
    Kolejka* kolejka;
    map<Przystanek*,vector<Przystanek*>> polaczenia;

    //otwarty plik ze statystyką
    //otwarty plik z podsumowaniem

public:

    Symulacja();

    Symulacja(const Symulacja &) = delete;

    ~Symulacja();

    void wczytywanie_danych(string nazwaPliku);

    vector<Przystanek *> get_przystanki();

    vector<Teatr *> get_teatry();

    void set_przystanki(vector<Przystanek *>);

    void set_teatry(vector<Teatr *>);

    Przystanek *get_przystanek(string nazwa);

    vector<Linia*> get_linie();

    void zaplanuj_dzien(int dzien);

    void rozpocznij_dzien();

    void rozpocznij();

    void ustal_polaczenia();

    vector<Przystanek*> znajdz_polaczenia(Przystanek* klucz);

};

#endif //SYMULACJA_SYMULACJA_H

// na końcu miesiąca rozlosowanie teatru