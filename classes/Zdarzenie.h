#ifndef SYMULACJA_ZDARZENIE_H
#define SYMULACJA_ZDARZENIE_H

#include "Pojazd.h"
#include "Osoba.h"
#include "Kolejka.h"

class Zdarzenie {

protected:

    int czas;
    Kolejka *kolejka;

public:

    Zdarzenie() = default;

    Zdarzenie(const Zdarzenie &) = delete;

    virtual ~Zdarzenie() {};

    virtual void wykonaj_sie() {};

    virtual int get_czas();

};

class TramwajNaPrzystanku : public Zdarzenie {

private:
    Tramwaj *tramwaj;

public:

    TramwajNaPrzystanku() = delete;

    TramwajNaPrzystanku(Kolejka *k, int czas, Tramwaj *tramwaj);

    ~TramwajNaPrzystanku() = default;

    void wykonaj_sie();

    friend ostream &operator<<(ostream &output, const TramwajNaPrzystanku &z);
};

#endif //SYMULACJA_ZDARZENIE_H
