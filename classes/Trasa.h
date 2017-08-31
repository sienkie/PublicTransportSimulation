#ifndef SYMULACJA_TRASA_H
#define SYMULACJA_TRASA_H

#include "Przystanek.h"

class Trasa {

private:

    Przystanek *poczatek;
    Przystanek *koniec;
    int czas_przejazdu;

public:

    Trasa() = delete;

    Trasa(Przystanek *p, Przystanek *k, int czas);

    Trasa(const Trasa &) = delete;

    ~Trasa() = default;

    Przystanek *get_poczatek();

    Przystanek *get_koniec();

    int get_czas();

    friend ostream &operator<<(ostream &output, const Trasa &t);

};


#endif //SYMULACJA_TRASA_H
