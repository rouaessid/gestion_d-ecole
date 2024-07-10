#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED
#include <iostream>
using namespace std;
class date {
    int jour, mois, annee;
public:
    date(int j = 0, int m = 0, int a = 0);
    ~date();
    int getjour() { return jour; }
    int getmois() { return mois; }
    int getannee() { return annee; }
    void saisir();
    void afficher();
    friend ostream& operator<<(ostream& os, const date& );
    friend istream& operator>>(istream& is, date& );
};

#endif // DATE_H_INCLUDED
