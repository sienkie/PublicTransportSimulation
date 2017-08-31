#ifndef SYMULACJA_PRZYSTANEK_H
#define SYMULACJA_PRZYSTANEK_H

#include <queue>
#include <string>

using namespace std;

class Osoba;

class Przystanek {

private:

    vector<Osoba *> kolejka;
    string nazwa;

public:

    Przystanek() = delete;

    Przystanek(string n);

    Przystanek(const Przystanek &) = delete;

    Przystanek &operator+=(Osoba &os);

    Osoba *pop();

    friend ostream &operator<<(ostream &output, const Przystanek &p);

    void clear();

    bool empty();

    string get_nazwa();

    vector<Osoba *> get_kolejka();

    void set_kolejka(vector<Osoba*> v);

};

#endif //SYMULACJA_PRZYSTANEK_H