#ifndef SYMULACJA_OSOBA_H
#define SYMULACJA_OSOBA_H

#include "Trasa.h"
#include "Przystanek.h"

class Uniwersytet;

class Symulacja;

class Osoba {

protected:

    Symulacja *symulacja;
    Przystanek *mieszkanie;
    Przystanek *obecna_pozycja;
    queue<Trasa *> trasa;
    double pr_teatr;

public:

    Osoba() = default;

    Osoba(const Osoba &) = delete;

    virtual ~Osoba() {};

    virtual void set_mieszkanie(Przystanek *mieszkanie);

    virtual void set_pr_teatr(double pr_teatr);

    virtual Osoba &operator+=(Trasa &t);

    virtual bool pusta_droga();

    virtual Trasa *spr_droge();

    virtual void skroc_droge();

    virtual void idz();

//    virtual void ustal_trase(Przystanek * cel); // z miejsca w ktorym jestes do podanego

//    virtual void powrot_do_domu(); // z miejsca w ktorym jestes do domu ustal_trase---> idz()

    virtual bool czy_teatr();

    virtual void kup_bilet();

};

class Uczen : public Osoba {

private:

    Przystanek *szkola;
    vector<int> godziny_konczenia;

public:

    Uczen() = delete;

    Uczen(Symulacja *s);

    Uczen(Symulacja *s, Przystanek *mieszkanie, double pr_teatr, Przystanek *szkola);

    Uczen(const Uczen &) = delete;

    ~Uczen() = default;

    void set_szkola(Przystanek *szkola);

    friend ostream &operator<<(ostream &output, const Uczen &u);

};

class Dorosly : public Osoba {

protected:

    double pr_zakupy;

public:

    Dorosly() = default;

    Dorosly(const Dorosly &) = delete;

    virtual ~Dorosly() {};

    virtual bool czy_zakupy(); //czy zakupy w dni robocze

    virtual void set_pr_zakupy(double pr_zakupy);

    //jedz_do_centrum : losuj centrum handlowe / ustaw trase przejazdu / wylosuj i zwroć czas powrotu do domu
    // ---> idź() ---> po tym czasie włozyć zdarzenie powrót do domu

    // w weekendy dla każdego dorosłego wylosuje sie godzine wlożenia jedz do centrum

};

class Pracujacy : public Dorosly {

private:

    Przystanek *praca;
    int czas_wyjazdu; //wyjazdu_do_pracy
    double pr_przejazd;

public:

    Pracujacy() = delete;

    Pracujacy(Symulacja *s);

    Pracujacy(Symulacja *s, Przystanek *mieszkanie, double pr_teatr, double pr_zakupy, Przystanek *praca,
              double pr_przejazd);

    Pracujacy(const Pracujacy &) = delete;

    ~Pracujacy() = default;

    void set_praca(Przystanek *praca);

    void set_pr_przejazd(double pr_przejad);

    bool czy_przejazd();

//    void przejazd();
    //losuj dowolne miejsce do przejazdu ---> ustal trasę: praca - miejsce - praca ---> idź()

};

typedef pair<int, int> int_pair;
typedef pair<Uniwersytet *, Uniwersytet *> uni_pair;

class Student : public Dorosly {

private:

    Uniwersytet *uniwersytet1;
    Uniwersytet *uniwersytet2; //część ma nullptr
    vector<int_pair> plan;
    vector<double> godziny_przejazdow;

public:

    Student() = delete;

    Student(Symulacja *s);

    Student(const Student &) = delete;

    ~Student() = default;

    void set_uniwersytety(Uniwersytet *u1, Uniwersytet *u2);

    uni_pair get_uniwersytety();

    vector<int_pair> get_plan();

    vector<double> get_godziny_przejazdow();

    bool drugi_uniwersytet();


};

class Artysta : public Dorosly {

private:

    vector<Przystanek *> miejsca_pracy;
    vector<int_pair> plan;

public:

    Artysta() = delete;

    Artysta(const Symulacja *s) = delete;

    Artysta(Symulacja *s);

    ~Artysta() = default;

    void set_plan();

    vector<int_pair> get_plan();

    vector<Przystanek *> get_miejsca_pracy();

    friend ostream &operator<<(ostream &output, const Artysta &a);

};

#endif //SYMULACJA_OSOBA_H