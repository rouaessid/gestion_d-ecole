#ifndef CANDIDAT_H_INCLUDED
#define CANDIDAT_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"Personne.h"
#include"categorie.h"
using namespace std;
template <class T>
class Candidat : public Personne<T> {
private:
    int num_carte_etd;
    int nb_mail;
    string* mail;
    categorie categorie_concours_candidat;
public:
    Candidat(int id_p = 0, string nom_p = "", string prenom_p = "", string nationalite_p = "", int age_p = 0, string sexe_p = "",
             string adresse_p = "", int = 0, date date_naissance_p = {}, categorie c = {}, int num = 0, int nb = 0);
    Candidat(const Candidat &c);
    void modif_adresse(string);
    ~Candidat();
    template<class U>
    friend istream &operator>>(istream &, Candidat<U> &);
    template<class U>
    friend ostream &operator<<(ostream &, Candidat <U>&);
    float moyenne_admission();
    float moyenne_oral();
    float moyen_total();
    Candidat<T>& operator=(Candidat<T>& );
    string getPrenom(){return this->prenom;}
};
///*************************************************classe template candidat***************************************************
template<class T>
Candidat<T>::Candidat(int id_p, string nom_p, string prenom_p, string nationalite_p, int age_p, string sexe_p, string adresse_p,
                       int n, date date_naissance_p,categorie c,int num,int nb)
    : Personne<T>(id_p, nom_p, prenom_p, nationalite_p, age_p, sexe_p, adresse_p, n, date_naissance_p),
      num_carte_etd(num),
      nb_mail(nb),
      categorie_concours_candidat(c)
{
      mail = new string[nb_mail];
}
template <class T>
Candidat<T>::Candidat(const Candidat &c) : Personne<T>(c), categorie_concours_candidat(c.categorie_concours_candidat)
{
    num_carte_etd = c.num_carte_etd;
    nb_mail = c.nb_mail;
    mail = new string[nb_mail];
    for (int i = 0; i < nb_mail; ++i)
    {
        mail[i] = c.mail[i];
    }
}

template <class T>
Candidat<T>::~Candidat()
{
    delete[] mail;
}

template <class T>
istream& operator>>(istream& in, Candidat<T>& candidat) {
    try {
        Personne<T>* p = &candidat;
        in >> *p;
        cout << "Numero de carte d'étudiant : ";
        in >> candidat.num_carte_etd;
        cout << "Nombre de mail : ";
        in >> candidat.nb_mail;
        if (candidat.nb_mail < 0) {
            throw out_of_range("Le nombre de mails ne peut pas être négatif.");
        }
        candidat.mail = new string[candidat.nb_mail];
        cout << "Saisie des mail  :" << endl;
        for (int i = 0; i < candidat.nb_mail; i++)
            {
            cout << "Mail " << i + 1 << " : ";
            in >> candidat.mail[i];
            in.ignore();
            }
        cout << "*************Saisie des informations de la categorie_concours de l'etudiant************\n  " << endl;
        in >> candidat.categorie_concours_candidat;
    } catch (const exception& e) {
        cerr << "Erreur: " << e.what() << endl;
        in.clear();
        in.ignore();
    }
    return in;
}
template <class T>
ostream &operator<<(ostream &out, Candidat<T> &candidat)
{
    Personne<T> *p = &candidat;
    out << *p;
    out << "Numero de carte d'étudiant : " << candidat.num_carte_etd << endl;
    out << "Adresses mail de l'etudiant : ";
    for (int i = 0; i < candidat.nb_mail; i++)
    {
        out << candidat.mail[i] << " ";
    }
    out << endl;
    out << "Affichage des informations de la categorie_concours du candidat:\n " << endl;
    out << candidat.categorie_concours_candidat;
    return out;
}

template <class T>
void Candidat<T>::modif_adresse(string nouvelle_adresse) {
    Personne<T>::adresse = nouvelle_adresse;
}

template <class T>
float Candidat<T>::moyenne_admission() {
    vector<epreuve<float> *> tab = this->categorie_concours_candidat.get_liste_epreuve();
    float s1 = 0.0, s2 = 0.0;

    for (int i = 0; i < tab.size(); i++) {
        if (typeid(*tab[i]) == typeid(epreuve_admission<float>)) {
            epreuve_admission<float> *e = dynamic_cast<epreuve_admission<float> *>(tab[i]);
            if (e != nullptr) {
                float n = e->get_note();
                float c = e->get_coeff();
                s1 += n * c;
                s2 += c;
            }
        }
    }

    if (s2 != 0) {
        return s1 / s2;
    } else {
        throw runtime_error("Division par zéro");
    }
}

template <class T>
float Candidat<T>::moyenne_oral() {
    vector<epreuve<float> *> tab = this->categorie_concours_candidat.get_liste_epreuve();
    float s1 = 0.0, s2 = 0.0;

    for (int i = 0; i < tab.size(); i++) {
        if (typeid(*tab[i]) == typeid(epreuve_oral<float>)) {
            epreuve_oral<float> *e = dynamic_cast<epreuve_oral<float> *>(tab[i]);
            if (e != nullptr) {
                float n = e->get_note();
                float c = e->get_coeff();
                s1 += n * c;
                s2 += c;
            }
        }
    }

    if (s2 != 0) {
        return s1 / s2;
    } else {
        throw runtime_error("Division par zéro ");
    }
}

template <class T>
float Candidat<T>::moyen_total()
{
   float m = moyenne_admission() * 2 + moyenne_oral();
   return (m / 3);
}
template<class T>
Candidat<T>& Candidat<T>::operator=(Candidat<T>& c) {
    if (this != &c) {
        Personne<T>* q1 = this;
        Personne<T>* q2 = &c;
        *q1 = *q2;
        delete[] mail;
        categorie_concours_candidat=c.categorie_concours_candidat;
        nb_mail=c.nb_mail;
        num_carte_etd=c.num_carte_etd;
        mail = new string[nb_mail];
        for (int i = 0; i < nb_mail; i++)
            mail[i] = c.mail[i];
    }
    return *this;
}
#endif // CANDIDAT_H_INCLUDED
