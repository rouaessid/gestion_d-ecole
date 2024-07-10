#ifndef SESSION_H_INCLUDED
#define SESSION_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<map>
#include<list>
#include"date.h"
using namespace std;
class session {
private:
    string annee_scolaire;
    map<string, int> nbre_des_etablissements_par_gouvernorat;
    list<date> date_important_du_session ;

public:
    session();
    session(string, map<string, int>, list<date>);
    session(const session& autre);
    ~session();
    friend ostream& operator<<(ostream&, const session&);
    friend istream& operator>>(istream&, session&);
    static void creer(fstream&);
    friend ostream& operator<<(ostream&, const session*);
    static void afficher_fichier(fstream&);
    static void remplir_fichier();
    void ajouter_date_important();
    void ajouter_etablissement();
    void supprimer_etablissement();
    void modifier_date();
    date& operator[](int );
};

#endif // SESSION_H_INCLUDED
