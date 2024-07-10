#ifndef EPREUVE_ADMISSION_H_INCLUDED
#define EPREUVE_ADMISSION_H_INCLUDED
#include"epreuve.h"
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
using namespace std;
template<class T>
class epreuve_admission : public epreuve<T> {
    int nb_questions;
    string* type_questions;
public:
    epreuve_admission(int a = 0, string b = "", date d = date(0, 0, 0), T e = 0.0, T f = 0.0, int n = 0, int nb = 0);
    epreuve_admission(const epreuve_admission&);
    ~epreuve_admission();
    template<class U>
    friend ostream& operator<<(ostream&, epreuve_admission<U>&);
    template<class U>
    friend istream& operator>>(istream&, epreuve_admission<U>&);
    epreuve_admission& operator=(epreuve_admission&);
    void modifierCoeff(T newCoeff);
    static void creer(fstream&);
    static void remplir(fstream&);
    static void afficher(fstream&);
};
///************************classe templates epreuve admisssion***********************
template<class T>
epreuve_admission<T>::epreuve_admission(int a, string b, date d, T e, T f, int n, int nb) : epreuve<T>(a, b, d, e, f, n), nb_questions(nb) {
    type_questions = new string[nb_questions];
}

template<class T>
epreuve_admission<T>::epreuve_admission(const epreuve_admission& e) : epreuve<T>(e), nb_questions(e.nb_questions) {
    type_questions = new string[nb_questions];
    for (int i = 0; i < nb_questions; ++i) {
        type_questions[i] = e.type_questions[i];
    }
}

template<class T>
epreuve_admission<T>::~epreuve_admission() {
    delete[] type_questions;
}

template<class T>
ostream& operator<<(ostream& os, epreuve_admission<T>& e) {
    epreuve<T>* q = &e;
    os << *q;
    os << "Nombre des questions dans l'epreuve  " << e.nb_questions << endl;
    os << "Types of Questions: " << endl;
    for (int i = 0; i < e.nb_questions; ++i) {
        os << e.type_questions[i] << endl;
    }
    return os;
}

template<class T>
istream& operator>>(istream& is, epreuve_admission<T>& e) {
    try {
        epreuve<T>* q = &e;
        is >> *q;

        cout << "Nombre de questions: ";
        is >> e.nb_questions;
        if (e.nb_questions <= 0)
            throw "Nombre de questions invalide";

        e.type_questions = new string[e.nb_questions];
        cout << "Entrez les types de questions:" << endl;
        for (int i = 0; i < e.nb_questions; ++i) {
            cout << "Type de question " << i + 1 << ": ";
            is >> e.type_questions[i];
        }
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
        return is;
    }
    return is;
}

template<class T>
epreuve_admission<T>& epreuve_admission<T>::operator=(epreuve_admission<T>& e) {
    if (this != &e) {
        epreuve<T>* q1 = this;
        epreuve<T>* q2 = &e;
        *q1 = *q2;
        delete[] type_questions;
        nb_questions = e.nb_questions;
        type_questions = new string[nb_questions];
        for (int i = 0; i < nb_questions; i++)
            type_questions[i] = e.type_questions[i];
    }
    return *this;
}

template<class T>
void epreuve_admission<T>::modifierCoeff(T newCoeff) {
    epreuve<T>::coeff = newCoeff;
}

template<class T>
void epreuve_admission<T>::creer(fstream& f) {
    f.open("d:\\fichierepreuve-admission.txt", ios::out);
    if (!f.is_open()) {
        cerr << "Erreur: Impossible de créer ou d'ouvrir le fichier" << endl;
        throw "Impossible d'ouvrir le fichier pour l'écriture";
    }
}

template<class T>
void epreuve_admission<T>::remplir(fstream& f) {
    char rep = 'o'; // Initialiser à 'o' pour entrer dans la boucle
    epreuve_admission e;
    cout << "Saisir les épreuves d'admission" << endl;
    while (rep == 'o' || rep == 'O') {
        e.saisir(); // Saisir les informations de l'épreuve
        if (!f.is_open()) {
            cerr << "Erreur: Le fichier n'est pas ouvert correctement" << endl;
            throw "Fichier non ouvert";
        }
        f << e << endl; // Écrire l'épreuve dans le fichier

        cout << "Vous voulez rajouter ? Si oui, saisir O|o, sinon saisir une autre touche " << endl;
        cin >> rep; // Lire la réponse de l'utilisateur

        // Nettoyer le flux d'entrée
        cin.ignore();
    }
}

template<class T>
void epreuve_admission<T>::afficher(fstream& f) {
    char ch[100];
    f.seekg(0);
    while (1) {
        f.getline(ch, 100);
        if (f.eof()) break;
        cout << ch << endl;
    }
}

#endif // EPREUVE_ADMISSION_H_INCLUDED
