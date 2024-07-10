#ifndef EPREUVE_ORAL_H_INCLUDED
#define EPREUVE_ORAL_H_INCLUDED
#include"epreuve.h"
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
using namespace std;
template<typename T>
class epreuve_oral : public epreuve<T> {
    string num_sujet_Oral;
    int nb_niveau;
    string* niveau_Difficulte;
    string thematiqueGenerale;
public:
    epreuve_oral(int a = 0, string b = "", date d = date(0, 0, 0), T e = 0.0, T f = 0.0, int n = 0, string num = "",
                 string thematique = "", int nb = 0);
    epreuve_oral(const epreuve_oral&);
    ~epreuve_oral();
    template<class U>
    friend ostream& operator<<(ostream&, const epreuve_oral<U>&);
    template<class U>
    friend istream& operator>>(istream&, epreuve_oral<U>&);
    epreuve_oral& operator=(epreuve_oral&);
    void modifierCoeff(T newCoeff);
    static void creer(fstream&);
    static void remplir(fstream&);
    static void afficher(fstream&);
};
template<typename T>
epreuve_oral<T>::epreuve_oral(int a, string b, date d, T e, T f, int n,
string num, string thematique, int nb) : epreuve<T>(a, b, d, e, f, n), num_sujet_Oral(num), thematiqueGenerale(thematique), nb_niveau(nb) {
    niveau_Difficulte = new string[nb_niveau];
}

template<typename T>
epreuve_oral<T>::epreuve_oral(const epreuve_oral& e) : epreuve<T>(e), num_sujet_Oral(e.num_sujet_Oral), thematiqueGenerale(e.thematiqueGenerale),
 nb_niveau(e.nb_niveau) {
    niveau_Difficulte = new string[nb_niveau];
    for (int i = 0; i < nb_niveau; ++i) {
        niveau_Difficulte[i] = e.niveau_Difficulte[i];
    }
}

template<typename T>
epreuve_oral<T>::~epreuve_oral() {
    delete[] niveau_Difficulte;
}

template<typename T>
ostream& operator<<(ostream& os, const epreuve_oral<T>& e) {
    const epreuve<T>* q = &e;
    os << *q;
    os << "Num Sujet Oral: " << e.num_sujet_Oral << endl
       << "Niveaux de Difficulte à traiter : ";
    for (int i = 0; i < e.nb_niveau; ++i) {
        os << e.niveau_Difficulte[i] << endl;
    }
    os << "Thematique Generale du sujet : " << e.thematiqueGenerale << endl;
    return os;
}

template<typename T>
istream& operator>>(istream& is, epreuve_oral<T>& e) {
    try {
        epreuve<T>* q = &e;
        is >> *q;

        cout << "Num Sujet Oral: ";
        is >> e.num_sujet_Oral;

        cout << "Donner le nombre des niveaux de difficultés à traiter dans l'épreuve : ";
        is >> e.nb_niveau;
        if (e.nb_niveau <= 0)
            throw "Nombre de niveaux de difficulté invalide";

        e.niveau_Difficulte = new string[e.nb_niveau];
        cout << "Saisir les Niveaux de Difficulte: ";
        for (int i = 0; i < e.nb_niveau; ++i) {
            is >> e.niveau_Difficulte[i];
        }

        cout << "Thematique Generale du sujet : ";
        is >> e.thematiqueGenerale;
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
        return is;
    }
    return is;
}
template<typename T>
epreuve_oral<T>& epreuve_oral<T>::operator=(epreuve_oral<T>& e) {
    if (this != &e) {
        epreuve<T>* q1 = this;
        epreuve<T>* q2 = &e;
        *q1 = *q2;
        delete[] niveau_Difficulte;
        num_sujet_Oral = e.num_sujet_Oral;
        nb_niveau = e.nb_niveau;
        thematiqueGenerale = e.thematiqueGenerale;
        niveau_Difficulte = new string[nb_niveau];
        for (int i = 0; i < nb_niveau; ++i) {
            niveau_Difficulte[i] = e.niveau_Difficulte[i];
        }
    }
    return *this;
}

template<typename T>
void epreuve_oral<T>::modifierCoeff(T newCoeff) {
    this->coeff = newCoeff;
}
template<typename T>
void epreuve_oral<T>::creer(fstream& f) {
    f.open("d:\\fichierepreuve-oral.txt", ios::out);
    if (!f.is_open()) {
        cerr << "Erreur: Impossible de créer ou d'ouvrir le fichier" << endl;
        throw "Impossible d'ouvrir le fichier pour l'écriture";
    }
}
template<typename T>
void epreuve_oral<T>::remplir(fstream& f) {
    char rep = 'o'; // Initialiser à 'o' pour entrer dans la boucle
    epreuve_oral e;
    cout << "Saisir les épreuves oraux" << endl;
    while (rep == 'o' || rep == 'O') {
        e.saisir(); // Saisir les informations de l'épreuve
        if (!f.is_open()) {
            cerr << "Erreur: Le fichier n'est pas ouvert correctement" << endl;
            throw "Fichier non ouvert";
        }
        f << e << endl;

        cout << "Vous voulez rajouter ? Si oui, saisir O|o, sinon saisir une autre touche " << endl;
        cin >> rep;
        cin.ignore();
    }
}

template<typename T>
void epreuve_oral<T>::afficher(fstream& f) {
    char ch[100];
    f.seekg(0);
    while (1) {
        f.getline(ch, 100);
        if (f.eof())
            break;
        cout << ch << endl;
    }
}

#endif // EPREUVE_ORAL_H_INCLUDED
