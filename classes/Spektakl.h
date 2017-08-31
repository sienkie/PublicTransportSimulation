#ifndef SYMULACJA_SPEKTAKL_H
#define SYMULACJA_SPEKTAKL_H

#include "Osoba.h"

using namespace std;

class Spektakl {

private:

    int wolne_miejsca;
    int godzina;
    int dzien;
    int czas;
    vector<Osoba *> widzowie; //osoby które kupiły bilet

public:

    Spektakl() = delete;

    Spektakl(int miejsca, int g, int d, int c);

    Spektakl(const Spektakl &) = delete;

    ~Spektakl() = default;

    bool wolne_bilety();

    Spektakl &operator+=(Osoba &osoba);

    int godzina_spektaklu();

    int dzien_spektaklu();

    int czas_trwania();

    void sprzedaj_bilet(Osoba* os);

    friend ostream &operator<<(ostream &output, const Spektakl &s);

    void set_wolne_bilety(int w);

};


#endif //SYMULACJA_SPEKTAKL_H
