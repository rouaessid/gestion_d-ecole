#include <iostream>
#include"date.h"
using namespace std;

date::date(int a,int b,int c)
{   jour=a;
    mois=b;
    annee=c;
}
date::~date() {}
ostream& operator<<(ostream& os, const date& dt) {
    os << dt.jour << "/" << dt.mois << "/" << dt.annee;
    return os;
}
istream& operator>>(istream& is, date& dt) {
    try {
        cout << "Jour: ";
        is >> dt.jour;
        if (dt.jour < 1 || dt.jour > 31)
            throw "Jour invalide";
        cout << "Mois: ";
        is >> dt.mois;
        if (dt.mois < 1 || dt.mois > 12)
            throw "Mois invalide";
        cout << "Annee: ";
        is >> dt.annee;
        if (dt.annee < 1900 || dt.annee > 2100)
            throw "Annee invalide";
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
        return is;
    }
    return is;
}
