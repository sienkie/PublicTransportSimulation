#include <iostream>
#include <string>
#include "Przystanek.h"

using namespace std;

Przystanek::Przystanek(string n) {
    nazwa = n;
}

Przystanek &Przystanek::operator+=(Osoba &os) {
    kolejka.push_back(&os);
    return *this;
};

Osoba *Przystanek::pop() {
    Osoba *last = nullptr;
    if (kolejka.size() != 0) {
        last = kolejka.front();
        kolejka.erase(kolejka.begin());
    }
    return last;
};

ostream &operator<<(ostream &output, const Przystanek &p) {
    output << "Przystanek_" << p.nazwa << "(ilość osób: " << p.kolejka.size() << ")";
    return output;
}

void Przystanek::clear() {
    kolejka.clear();
}

bool Przystanek::empty() {
    return kolejka.empty();
}

string Przystanek::get_nazwa() {
    return nazwa;
}

vector<Osoba *> Przystanek::get_kolejka(){
    return  kolejka;
}

void Przystanek::set_kolejka(vector<Osoba*> v){
    kolejka = v;
}