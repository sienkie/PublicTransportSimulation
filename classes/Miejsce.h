#ifndef SYMULACJA_MIEJSCE_H
#define SYMULACJA_MIEJSCE_H

#include <string>
#include <map>
#include "Przystanek.h"
#include "Spektakl.h"

using namespace std;

class Miejsce {

protected:

    string nazwa;
    Przystanek *przystanek;

public:

    Miejsce() = default;

    Miejsce(const Miejsce &) = delete;

    virtual ~Miejsce() {};

    virtual string get_nazwa();

    virtual Przystanek* get_przystanek();

};

class CentrumHandlowe : public Miejsce {

public:

    CentrumHandlowe() = delete;

    CentrumHandlowe(string n, Przystanek *p);

    CentrumHandlowe(const CentrumHandlowe &) = delete;

    ~CentrumHandlowe() = default;

};

class Uniwersytet : public Miejsce {

public:

    Uniwersytet() = delete;

    Uniwersytet(string n, Przystanek *p);

    Uniwersytet(const Uniwersytet &) = delete;

    ~Uniwersytet() = default;

    friend ostream &operator<<(ostream &output, const Uniwersytet &u);

};

class Teatr : public Miejsce {

private:

    int liczba_miejsc;
    vector<Spektakl *> repertuar;  // wektor ze spektaklami na całą symulację

public:

    Teatr() = delete;

    Teatr(string n, Przystanek *p, int miejsca, int dni);

    Teatr(const Teatr &) = delete;

    ~Teatr();

    void ustal_repertuar(int miejsca, int dni);

    vector<int> losuj_dni_tygodnia(int zakres, int dni);

    vector<Spektakl *> get_repertuar();

    friend ostream &operator<<(ostream &output, const Teatr &s);

};


#endif //SYMULACJA_MIEJSCE_H