#ifndef INSCRIPTION_H_INCLUDED
#define INSCRIPTION_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"date.h"
#include"candidat.h"
using namespace std;
class Inscription
{
    date date_inscription;
    float frais;
    vector<Candidat<int>*> liste_candidat;
    static int  nb_inscription;
public:
    Inscription(date = date(0, 0, 0), float = 0.0);
    Inscription(const Inscription&);
    void ajouter_Candidat(Candidat<int>*);
    void supprimer_Candidat(int);
    void modif_frais(float);
    ~Inscription(void);
    friend istream& operator>>(istream&, Inscription&);
    friend ostream& operator<<(ostream&, const Inscription& I);
    Inscription& operator=(const Inscription&);
    vector<Candidat<int>*> get_liste_candidat() const;
    static void creer(fstream&);
    static void afficher_fichier(fstream&);
    static void afficher_nb_inscription();
    friend ostream& operator<<(ostream& , const Inscription* );
};

#endif // INSCRIPTION_H_INCLUDED
