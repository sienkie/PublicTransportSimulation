#include <iostream>
#include "classes/Symulacja.h"

using namespace std;

int main() {
    srand(time(nullptr));
    Symulacja s;
    s.wczytywanie_danych("dane.txt");
    s.rozpocznij();

}

//  uruchomienie z konsoli
//  c++ -Wall --std=c++14 main.cpp classes/*.cpp
//  ./a.out