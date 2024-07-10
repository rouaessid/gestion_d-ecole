#ifndef EPREUVE_H_INCLUDED
#define EPREUVE_H_INCLUDED
#include<string>
#include <iostream>
#include"date.h"
using namespace std;

template<class T>
class epreuve {
protected:
    int id_epreuve;
    string nom;
    T note;
    T coeff;
    int nb_epreuve;
    date date_ep;
    string* jury;

public:

    epreuve(int, string b, date d, T e, T f, int n);
    epreuve(const epreuve& other);
    ~epreuve();
    template<class U>
    friend ostream& operator<<(ostream& os, const epreuve<U>& e);
    template<class U>
    friend istream& operator>>(istream& is, epreuve<U>& e);
    epreuve& operator=(const epreuve& e);
    T get_note(){return note;};
    T get_coeff(){return coeff;};
    virtual void modifierCoeff(T newCoeff) = 0;

};
/// *******************************classe template  epreuve ************************************
template<class T>
epreuve<T>::epreuve(int a, string b, date d, T e, T f, int n) : id_epreuve(a), nom(b), date_ep(d), note(e), coeff(f), nb_epreuve(n) {
    jury = new string[nb_epreuve];
}

template<class T>
epreuve<T>::epreuve(const epreuve& e) : id_epreuve(e.id_epreuve), nom(e.nom), date_ep(e.date_ep), note(e.note), coeff(e.coeff),
 nb_epreuve(e.nb_epreuve) {
    jury = new string[nb_epreuve];
    for (int i = 0; i < nb_epreuve; ++i) {
        jury[i] = e.jury[i];
    }
}

template<class T>
epreuve<T>::~epreuve() {
    delete[] jury;
}
template<class T>
ostream& operator<<(ostream& os, const epreuve<T>& e) {
    os << "ID de l'epreuve:" << e.id_epreuve << endl
       << "Nom de l'epreuve:" << e.nom << endl;
    os << "date de l'epreuve:" << e.date_ep << endl;
    os << "Note: " << e.note << endl
       << "Coeff: " << e.coeff << endl
       << "Nb Jury: " << e.nb_epreuve << endl
       << "Membre du Jury:" << endl;
    for (int i = 0; i < e.nb_epreuve; ++i) {
        os << e.jury[i] << "|"<<endl;
    }
    return os;
}

template<class T>
istream& operator>>(istream& is, epreuve<T>& e) {
    cout << "ID de l'epreuve:: ";
    is >> e.id_epreuve;
    cout << "Nom de l'epreuve:: ";
    is >> e.nom;
    cout << "Date de l'epreuve:: " << endl;
    is >> e.date_ep;
    cout << "Note: ";
    is >> e.note;
    cout << "Coeff: ";
    is >> e.coeff;
    cout << "Nb Jury: ";
    is >> e.nb_epreuve;
    try {
        if (e.nb_epreuve <= 0)
            throw "Nombre de jurys invalide";
        e.jury = new string[e.nb_epreuve];
        cout << "Entrez les membres du jury:" << endl;
        for (int i = 0; i < e.nb_epreuve; ++i) {
            cout << "Membre du jury " << i + 1 << ": ";
            is >> e.jury[i];
        }
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
        return is;
    }
    return is;
}

template<class T>
epreuve<T>& epreuve<T>::operator=(const epreuve<T>& e) {
    if (this != &e) {
        id_epreuve = e.id_epreuve;
        nom = e.nom;
        note = e.note;
        coeff = e.coeff;
        date_ep = e.date_ep;
        nb_epreuve = e.nb_epreuve;
        delete[] jury;
        jury = new string[nb_epreuve];
        for (int i = 0; i < nb_epreuve; ++i) {
            jury[i] = e.jury[i];
        }
    }
    return (*this);
}

#endif // EPREUVE_H_INCLUDED
