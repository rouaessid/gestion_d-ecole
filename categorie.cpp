#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"categorie.h"
using namespace std;
int categorie::nb_categorie=0;// attribut statique
void categorie ::afficher_nb_categorie()
{
    cout<<"\n le nombre des categories dans le concours cette ann�e est "<<nb_categorie<<endl;
}
categorie::categorie(string nom, int id) {
 nom_categorie=nom;
 id_categorie=id;
}

categorie::categorie(const categorie &c) {
    nom_categorie = c.nom_categorie;
    id_categorie = c.id_categorie;
    epreuve<float>* e;
    for (int i = 0; i < c.liste_epreuve.size(); i++) {
        if (typeid(*c.liste_epreuve[i]) == typeid(epreuve_admission<float>))
            e = new epreuve_admission<float>(static_cast<const epreuve_admission<float>&>(*c.liste_epreuve[i]));
        else if (typeid(*c.liste_epreuve[i]) == typeid(epreuve_oral<float>))
            e = new epreuve_oral<float>(static_cast<const epreuve_oral<float>&>(*c.liste_epreuve[i]));
        liste_epreuve.push_back(e);
    }
}


categorie::~categorie(void) {
    for (int i = 0; i < liste_epreuve.size(); i++)
        delete liste_epreuve[i];
    liste_epreuve.clear();
}

void categorie::ajouter_epreuve(epreuve<float>* e, int pos) {
    try {
        if (pos < 0 || pos > liste_epreuve.size()) {
            throw "Position invalide";
        }

        if (typeid(*e) == typeid(epreuve_admission<float>)) {
            cout << "Ajout d'une �preuve d'admission � la position " << pos << endl;
            liste_epreuve.insert(liste_epreuve.begin() + pos, e);
        } else if (typeid(*e) == typeid(epreuve_oral<float>)) {
            cout << "Ajout d'une �preuve orale � la position " << pos << endl;
            liste_epreuve.insert(liste_epreuve.begin() + pos, e);
        } else {
            throw "Type d'�preuve non reconnu";
        }
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
    }
}

void categorie::supprimer_epreuve(epreuve<float>* e, int pos) {
    try {
        if (pos < 0 || pos >= liste_epreuve.size()) {
            throw "Position invalide";
        }

        if (typeid(*e) == typeid(epreuve_oral<float>)) {
            if (typeid(*liste_epreuve[pos]) == typeid(epreuve_oral<float>)) {
                cout << "Suppression de l'�preuve orale � la position " << pos << endl;
                delete liste_epreuve[pos];
                liste_epreuve.erase(liste_epreuve.begin() + pos);
            } else {
                throw "L'�preuve sp�cifi�e n'est pas une �preuve orale";
            }
        } else if (typeid(*e) == typeid(epreuve_admission<float>)) {
            if (typeid(*liste_epreuve[pos]) == typeid(epreuve_admission<float>)) {
                cout << "Suppression de l'�preuve d'admission � la position " << pos << endl;
                delete liste_epreuve[pos];
                liste_epreuve.erase(liste_epreuve.begin() + pos);
            } else {
                throw "L'�preuve sp�cifi�e n'est pas une �preuve d'admission";
            }
        } else {
            throw "Type d'�preuve non reconnu";
        }
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
    }
}

istream& operator>>(istream& in, categorie& c) {
    try {
        char rep;
        int choix;
        cout << "Nom de la cat�gorie: ";
        in >> c.nom_categorie;
        cout << "Identifiant de la cat�gorie: ";
        in >> c.id_categorie;
        cout << "*** Ajout des �preuves de la cat�gorie ***" << endl;
        do {
            cout << "\nTapez 1 pour une �preuve d'admission, 2 pour une �preuve orale: ";
            in >> choix;
            if (choix != 1 && choix != 2) {
                throw "Choix invalide";
            }
            cout << endl;
            if (choix == 1) {
                cout << "Saisie de l'�preuve d'admission:" << endl;
                epreuve_admission<float> *e = new epreuve_admission<float>;
                in >> *e;
                c.liste_epreuve.push_back(e);
            } else if (choix == 2) {
                cout << "Saisie de l'�preuve orale:" << endl;
                epreuve_oral<float>* e = new epreuve_oral<float>;
                in >> *e;
                c.liste_epreuve.push_back(e);
            }
            cout << "\nVoulez-vous rajouter une autre �preuve ? (o/O pour oui)" << endl;
            in >> rep;
        } while (rep == 'o' || rep == 'O');
    } catch (const char* msg) {
        cerr << "Erreur: " << msg << endl;
    }
    return in;
}

ostream& operator<<(ostream& out, const categorie& c) {
    out << "Cat�gorie: " << c.nom_categorie << endl;
    out << "Identifiant de la categorie : " << c.id_categorie << endl;
    out << "************** Liste des �preuves de la cat�gorie **************" << endl << endl;
    for (int i = 0; i < c.liste_epreuve.size(); i++) {
        out << "--------------------------------------------------------------" << endl;
        out << "  �preuve num�ro " << i + 1 << ":" << endl;
        out << "--------------------------------------------------------------" << endl;
        if (typeid(*c.liste_epreuve[i]) == typeid(epreuve_admission<float>))
            out << "Type: �preuve d'admission" << endl;
        else if (typeid(*c.liste_epreuve[i]) == typeid(epreuve_oral<float>))
            out << "Type: �preuve orale" << endl;
        out << *c.liste_epreuve[i] << endl << endl;
    }
    return out;
}
categorie& categorie::operator=(const categorie& other) {
    if (this != &other) {
        for (epreuve<float>* e : liste_epreuve) {
            delete e;
        }
        liste_epreuve.clear();
        nom_categorie = other.nom_categorie;
        id_categorie = other.id_categorie;
        for (const epreuve<float>* e : other.liste_epreuve) {
            if (const epreuve_admission<float>* e_admission = static_cast<const epreuve_admission<float>*>(e)) {
                liste_epreuve.push_back(new epreuve_admission<float>(*e_admission));
            } else if (const epreuve_oral<float>* e_oral = static_cast<const epreuve_oral<float>*>(e)) {
                liste_epreuve.push_back(new epreuve_oral<float>(*e_oral));
            }
        }
    }
    return *this;
}
vector<epreuve<float>*> categorie::get_liste_epreuve() const {
    return liste_epreuve;
}

