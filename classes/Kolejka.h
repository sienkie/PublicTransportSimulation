#ifndef SYMULACJA_KOLEJKA_H
#define SYMULACJA_KOLEJKA_H

#include <list>
#include <iterator>

using namespace std;

class Zdarzenie;

class Kolejka {

private:

    int czas; //aktualny czas w minutach
    list<Zdarzenie *> lista_zdarzen;

public:

    Kolejka();

    Kolejka(const Kolejka&) = delete;

    ~Kolejka();

    void wyczysc_kolejke();

    void wykonaj_zdarzenie(); //wykonuje piersze zdarzenie i skraca liste zdarzeń

    Kolejka& operator+=(Zdarzenie* z);

    bool empty();

};


#endif //SYMULACJA_KOLEJKA_H
