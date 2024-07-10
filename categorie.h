#ifndef CATEGORIE_H_INCLUDED
#define CATEGORIE_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"epreuve_oral.h"
#include"epreuve_admission.h"
using namespace std;
class categorie
{
    string nom_categorie;
    int id_categorie;
    vector <epreuve<float>*> liste_epreuve;
    static int nb_categorie ;
public:
    categorie(string="",int=0);
    categorie(const categorie&);
    ~categorie();
    string get_nom(){return nom_categorie;}
    int get_id(){return id_categorie;}
    friend ostream& operator<<(ostream&,const categorie&);
    friend istream& operator>>(istream&,categorie&);
    static void creer(fstream&);
    friend ostream& operator<<(ostream&,const categorie*);
    friend istream& operator>>(istream&,categorie*);
    categorie& operator=(const  categorie&);
    vector<epreuve<float>*> get_liste_epreuve() const;
    void ajouter_epreuve(epreuve<float>*, int);
    void supprimer_epreuve(epreuve<float>*, int);
    static void afficher_nb_categorie();
};

#endif // CATEGORIE_H_INCLUDED
