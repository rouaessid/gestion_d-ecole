#include<vector>
#include <iostream>
#include<string>
#include<typeinfo>
#include"inscription.h"
using namespace std;
int Inscription::nb_inscription=0;// attribut statique
void Inscription::afficher_nb_inscription(){
 cout<<"\n le nombre des inscriptions dans le concours est "<<nb_inscription<<endl;
}
Inscription::Inscription(date d, float f) {
 date_inscription=d;
 frais=f;
}
Inscription::Inscription(const Inscription& I) {
    date_inscription = I.date_inscription;
    frais = I.frais;
    for(int i = 0; i < I.liste_candidat.size(); i++) {
        Candidat<int>* c = new Candidat<int>(*I.liste_candidat[i]);
        liste_candidat.push_back(c);
    }
}
Inscription::~Inscription(void)
{
    for(int i=0;i<liste_candidat.size();i++)
        delete liste_candidat[i];
    liste_candidat.clear();
}
vector<Candidat<int>*> Inscription::get_liste_candidat() const
{
    return liste_candidat;
}
void Inscription::modif_frais(float new_frais)
{
    frais = new_frais;
}

void Inscription::ajouter_Candidat(Candidat<int>* c)
{
    liste_candidat.push_back(c);
}
void Inscription::supprimer_Candidat(int pos)
{
    if (pos < 0 || pos >= liste_candidat.size())
    {
        cout << "Position invalide. Aucun candidat supprimé." << endl;
        return;
    }
    else
    {
        cout << "Suppression d'un candidat à la position " << pos << endl;
        delete liste_candidat[pos];
        liste_candidat.erase(liste_candidat.begin() + pos);
    }
}
istream& operator>>(istream& in, Inscription& I) {
    char rep;
    Candidat<int>* c;
    cout << "Date de l'inscription : "<<endl;
    in >> I.date_inscription;
    cout << "Frais de l'inscription en DT  : ";
    try {
        in >> I.frais;
        if (I.frais > 100) {
            throw "Les frais d'inscription doivent être inférieurs ou égaux à 100";
        }
    } catch (const char* message) {
        cerr << "Erreur : " << message << endl;
        return in;
    }
    cout << "\n*** Ajout des candidats inscrits ***" << endl;
    do {
        cout << "\nSaisie des informations du candidat \n :" << endl;
        c = new Candidat<int>;
        in >> *c;
        I.liste_candidat.push_back(c);
        cout << "\nVoulez-vous rajouter un autre candidat ? (o/O pour oui) : ";
        in >> rep;
    } while (rep == 'o' || rep == 'O');

    return in;
}
ostream& operator<<(ostream& out, const Inscription& I) {
    out << "Date de l'inscription : " << I.date_inscription << endl;
    out << "Frais de l'inscription en DT : " << I.frais << endl;
    out << "Liste des candidats inscrits :" << endl;

    for (int i = 0; i < I.liste_candidat.size(); i++) {
        out << "----------------------------------" << endl;
        out << "  Candidat numéro " << i + 1 << ":" << endl;
        out << "----------------------------------" << endl;
        out << *(I.liste_candidat[i]) << endl;
    }

    return out;
}
Inscription& Inscription::operator=(const Inscription& ins) {
    if (this != &ins)

    {
        date_inscription = ins.date_inscription;
        frais = ins.frais;
        for (Candidat<int>* c : liste_candidat)
        {
            delete c;
        }
        liste_candidat.clear();
        for (Candidat<int>* c : ins.liste_candidat)
        {
            Candidat<int>* new_candidat = new Candidat<int>(*c);
            liste_candidat.push_back(new_candidat);
        }
    }
    return *this;
}
void Inscription::creer(fstream& f)  {
    f.open("d:\\fichierinscription.txt", ios::in | ios::out | ios::trunc);
    if (!f.is_open()) {
        throw runtime_error("impossible d'ecrire dans le fichier.");
    }
}
ostream& operator<<(ostream& out, const Inscription* I) {
    try {
        out << "date de l'inscription : " << I->date_inscription << endl;
        out << "frais de l'inscription : " << I->frais << endl;
        out << "Liste des candidats inscrits :" << endl;
        for (int i = 0; i < I->liste_candidat.size(); i++) {
            out << "**** candidat numéro " << i << " ****" << endl;
            out << *(I->liste_candidat[i]) << endl;
        }
    } catch (const exception& e) {
        cerr << "Une exception est survenue lors de la sortie : " << e.what() << endl;

    }
    return out;
}
void Inscription::afficher_fichier(fstream&f)
{
    char ch[100];
    f.seekg(0);
    while(1)
    {
        f.getline(ch,100);
        if(f.eof())break;
        cout<<ch<<endl;
    }
}
