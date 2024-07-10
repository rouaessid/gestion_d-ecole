#ifndef ADMINISTRATEUR_H_INCLUDED
#define ADMINISTRATEUR_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"Personne.h"
using namespace std;
template <class T>
class Administrateur : public Personne<T> {
private:
    int num_admin;
    int nb_r;
    string* region_dirigee;

public:
    Administrateur(T id_p = 0, string nom_p = "", string prenom_p = "", string nationalite_p = "", int age_p = 0,
                    string sexe_p = "", string adresse_p = "", int n = 0, date date_naissance_p = {}, int num_admin_p = 0, int nb_r_p = 0);
    Administrateur(const Administrateur &adm);
    void modif_adresse(string);
    ~Administrateur();
    template<class U>
    friend istream &operator>>(istream &, Administrateur<U> &);
    template<class U>
    friend ostream &operator<<(ostream &,  Administrateur<U> &);
    int getId() { return this->id; }
    Administrateur<T>& operator=( const Administrateur<T>& );
};

///***************************classe templates administrateur*******************************
template <class T>
Administrateur<T>::Administrateur(T id_p, string nom_p, string prenom_p, string nationalite_p, int age_p, string sexe_p, string adresse_p, int n,
                                   date date_naissance_p, int num_admin_p, int nb_r_p)
    : Personne<T>(id_p, nom_p, prenom_p, nationalite_p, age_p, sexe_p, adresse_p, n, date_naissance_p),
     num_admin(num_admin_p), nb_r(nb_r_p), region_dirigee(nullptr) {
    if (nb_r > 0) {
        region_dirigee = new string[nb_r];
    }
}

template <class T>
Administrateur<T>::Administrateur(const Administrateur &admin)
    : Personne<T>(admin), num_admin(admin.num_admin), nb_r(admin.nb_r) {
    if (nb_r > 0) {
        region_dirigee = new string[nb_r];
        for (int i = 0; i < nb_r; ++i) {
            region_dirigee[i] = admin.region_dirigee[i];
        }
    }
}

template <class T>
Administrateur<T>::~Administrateur() {
    delete[] region_dirigee;
}

template <class T>
istream &operator>>(istream &in, Administrateur<T> &administrateur) {
    try {
        Personne<T>* p = &administrateur;
        in >> *p;
        cout << "Numero de l'administrateur : ";
        in >> administrateur.num_admin;
        if (in.fail()) {
            throw invalid_argument("Numero d'administrateur invalide.");
        }
        cout << "Nombre de régions dirigées : ";
        in >> administrateur.nb_r;
        if (in.fail() || administrateur.nb_r <= 0) {
            throw invalid_argument("Nombre de régions dirigées invalide.");
        }
        administrateur.region_dirigee = new string[administrateur.nb_r];

        cout << "Saisie des régions dirigées :" << endl;
        for (int i = 0; i < administrateur.nb_r; i++) {
            cout << "Région " << i + 1 << " : ";
            in >> administrateur.region_dirigee[i];
            if (in.fail()) {
                throw invalid_argument("Région invalide.");
            }
        }
    } catch (const exception& e) {
        cerr << "Erreur: " << e.what() << endl;
        in.clear();
        in.ignore();
    }

    return in;
}
template <class T>
ostream &operator<<(ostream &out, Administrateur<T> &administrateur) {
    Personne<T> *q = &administrateur;
    out << *q;
    out << "Numero de l'administrateur : " << administrateur.num_admin << endl;
    out << "Régions dirigées : ";
    for (int i = 0; i < administrateur.nb_r; i++) {
        out << administrateur.region_dirigee[i] << " ";
    }
    out << endl;

    return out;
}

template <class T>
void Administrateur<T>::modif_adresse(string nouvelle_adresse) {
    this->adresse = nouvelle_adresse;
}
template<class T>
Administrateur<T>& Administrateur<T>::operator=( const Administrateur<T>& a) {
    if (this != &a) {
        Personne<T>::operator=(a);
        delete[] this->region_dirigee;
        this->num_admin = a.num_admin;
        this->nb_r = a.nb_r;
        this->region_dirigee = new string[this->nb_r];
        for (int i = 0; i < this->nb_r; i++)
            this->region_dirigee[i] = a.region_dirigee[i];
    }
    return *this;
}
#endif // ADMINISTRATEUR_H_INCLUDED
