#ifndef PERSONNE_H_INCLUDED
#define PERSONNE_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"date.h"
using namespace std;
template<typename T>
class Personne
{
protected:
    T id;
    string nationalite;
    string nom;
    string prenom;
    int age;
    string sexe;
    string adresse;
    int* num_telephone;
    int nb;
    date date_naissance;
public:
    Personne(T=0, string="", string="", string="", int=0, string="", string ="",int=0, date =date(0, 0, 0));
    Personne(const Personne&);
    virtual void modif_adresse(string)=0;
    virtual ~Personne(void);
    template<class U>
    friend istream& operator>> (istream&,Personne<U>&);
    template<class U>
    friend ostream& operator<< (ostream&, Personne<U>&);
    Personne<T>& operator= (const Personne<T>& );
};
///****************************templates personne *******************************************************
template<typename T>
Personne<T>::Personne(T id_p, string nom_p, string prenom_p, string nationalite_p, int age_p, string sexe_p,
                       string adresse_p,int n, date date_naissance_p)
{
    id = id_p;
    nom = nom_p;
    prenom = prenom_p;
    nationalite = nationalite_p;
    age = age_p;
    sexe = sexe_p;
    adresse = adresse_p;
    nb=n;
    num_telephone = new int[nb];
    date_naissance = date_naissance_p;
}

template<typename T>
Personne<T>::Personne(const Personne& p)
{
    id = p.id;
    nom = p.nom;
    prenom = p.prenom;
    nationalite = p.nationalite;
    age = p.age;
    sexe = p.sexe;
    adresse = p.adresse;
    nb=p.nb;
    num_telephone = new int[nb];
    for(int i=0;i<nb;i++)
        num_telephone[i]=p.num_telephone[i];
    date_naissance = p.date_naissance;
}
template<typename T>
Personne<T>::~Personne()
{
    delete[] num_telephone;
}
template<typename T>
ostream& operator<< (ostream& out, Personne<T>& p)
{
    out << "Id: " << p.id << endl;
    out << "Nom: " << p.nom << endl;
    out << "Prenom: " << p.prenom << endl;
    out << "Nationalite: " << p.nationalite << endl;
    out << "Age: " << p.age << endl;
    out << "Sexe: " << p.sexe << endl;
    out << "Adresse: " << p.adresse << endl;
    out << "Numeros de téléphone: ";
    for (int i = 0; i < p.nb; i++)
    {
        out << p.num_telephone[i] << "| ";
    }
    out << endl;
    out << "Date de naissance: " << endl;
    out<<p.date_naissance<<endl;

    return out;
}

template<typename T>
istream& operator>>(istream& in, Personne<T>& p) {
    cout << "Saisir les informations personnelles : " << endl;
    cout << "ID : ";
    in >> p.id;
    cout << "Nationalité : ";
    in >> p.nationalite;
    cout << "Nom : ";
    in >> p.nom;
    cout << "Prénom : ";
    in >> p.prenom;
    cout << "Age : ";
    in >> p.age;
    cout << "Sexe : ";
    in >> p.sexe;
    cout << "Adresse : ";
    in >> p.adresse;
    cout << "Nombre de numéros de téléphone de la personne : ";
    in >> p.nb;
    if (p.nb < 0 || p.nb > 10) {
        throw out_of_range("Le nombre de numéros de téléphone doit être compris entre 0 et 10.");
    }
    cout << "Les numéros de téléphone (8chiffres): " << endl;
    for (int i = 0; i < p.nb; i++) {
        cout << "Numéro de téléphone " << i+1 << ": ";
        in >> p.num_telephone[i];
        if (p.num_telephone[i] < 10000000 || p.num_telephone[i] >= 100000000) {
            throw invalid_argument("Le numéro de téléphone doit comporter exactement 8 chiffres.");
        }
    }
    cout<<"date de naissance du candidat\n";
    in >> p.date_naissance;
    return in;
}
template<typename T>
Personne<T>&Personne<T>::operator= (const Personne<T>& p)
{if (this != &p){
    id = p.id;
    nom = p.nom;
    prenom = p.prenom;
    nationalite = p.nationalite;
    age = p.age;
    sexe = p.sexe;
    adresse = p.adresse;
    nb=p.nb;
    num_telephone = new int[nb];
    delete[] num_telephone;
    for(int i=0;i<nb;i++)
        num_telephone[i]=p.num_telephone[i];
    date_naissance = p.date_naissance;
}
return (*this);
}
#endif // PERSONNE_H_INCLUDED
