#ifndef SYMULACJA_LINIA_H
#define SYMULACJA_LINIA_H

#include "Pojazd.h"

class Linia {
// to jest linia tramwajowa zarzadzająca pojazdami tego typu
// w przypadku potrzeby wprowadzenia dodatkowych pojazdów z liniami można zastosować hierarchię Linii i dziedziczenie

private:

    vector<Tramwaj *> pojazdy;
    vector<Przystanek *> przystanki;
    vector<int> czasy;
    //niezmiennik: czasy.size() == przystanki.size()
    int nr_linii;


public:

    Linia() = delete;

    Linia(const Linia &) = delete;

    Linia(int nr_linii, vector<Przystanek *> przystanki, vector<int> czasy);

    ~Linia() = default;

    Linia &operator+=(Tramwaj &p);

    void ustaw_trasy_w_dwie_strony(int od_godz, int do_godz, int odstep); // np od 6 do 23, co 10 min

    void zmniejsz_ruch(int procent);

    int policz_odstep();

    vector<Tramwaj *> ();

    vector<Przystanek *> get_przystanki();

    friend ostream &operator<<(ostream &output, const Linia &l);

};


#endif //SYMULACJA_LINIA_H
