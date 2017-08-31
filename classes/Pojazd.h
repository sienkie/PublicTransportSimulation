#ifndef SYMULACJA_POJAZD_H
#define SYMULACJA_POJAZD_H

#include "Trasa.h"

class Pojazd {

protected:

    int nr_linii;
    queue<Trasa *> trasa;
    int pojemnosc;
    int miejsca; //wolne miejsca
    vector<Osoba *> osoby;

public:

    Pojazd() = default;

    Pojazd(const Pojazd &) = delete;

    virtual ~Pojazd() {};

    virtual Pojazd& operator+=(Trasa &t);

    virtual bool empty_trasa();

    virtual Trasa *spr_droge() const;

    virtual void skroc_trase();

    virtual int get_nr_linii() const;

    virtual bool wolne_miejsca();

    virtual Pojazd& operator+=(Osoba &os);

    virtual void koniec_trasy(); //wyczyszczenie trasy i osób

    virtual void ktos_wysiada(Osoba *os);

    virtual vector<Osoba*> get_osoby();

};

class Tramwaj : public Pojazd {

public:

    Tramwaj() = delete;

    Tramwaj(int nr_linii, int pojemnosc);

    Tramwaj(const Tramwaj &) = delete;

    ~Tramwaj() = default;

    friend ostream &operator<<(ostream &output, const Tramwaj &t);

    //jedz -> jesli masz nie pusta trase

    //wez ludzi z przystanku (najpierw skroc wszystkim w srodku trase) (wypusc tych co chca wysiasc -> puste trasy lub nie zgodne)

};

#endif //SYMULACJA_POJAZD_H
