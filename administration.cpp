#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<list>
#include"administration.h"
using namespace std;
administration::administration(list<Administrateur<int>> listeAdministrateurs, set<string> dep)
{
    personnel = listeAdministrateurs;
    departement_administratif = dep;
}

administration::~administration()
{
}

administration::administration(const administration& a)
{
    this->personnel = a.personnel;
    this->departement_administratif = a.departement_administratif;
}

istream& operator>>(istream& is, administration& admin)
{
    admin.personnel.clear();
    admin.departement_administratif.clear();
    string rep;
    int i = 1;
    cout << "***saisir les informations du personnel****** \n" << endl;
    while (true)
    {
        cout << "***saisir les informations de l'administrateur " << i << "***** \n " << endl;
        Administrateur<int> adminTemp;
        is >> adminTemp;
        admin.personnel.push_back(adminTemp);
        cout << "\n voulez vous rajoutez un autre adminsitrateur (O|o)?" << endl;
        is >> rep;
        if (rep != "o" && rep != "O")
            break;
        i++;
    }
    string rep2;
    cout << "****saisir les departements administratifs de cette session ****\n" << endl;
    while (true)
    {
        string departement;
        is >> departement;
        admin.departement_administratif.insert(departement);
        cout << "voulez vous rajoutez d'autres departements (O|o)?" << endl;
        is >> rep2;
        if (rep2 != "o" && rep2 != "O")
            break;
    }
    return is;
}
ostream& operator<<(ostream& os, administration& admin)
{
    os << "**********Personnel****************:\n" << endl;
    for (list<Administrateur<int>>::iterator it = admin.personnel.begin(); it != admin.personnel.end(); ++it)
    {
        os << *it << "\n";
    }

    os << "***************Départements administratifs*****************\n" << endl;
    for (set<string>::iterator it = admin.departement_administratif.begin(); it != admin.departement_administratif.end(); ++it)
    {
        os << *it << "\n";
    }

    return os;
}
void administration::ajouter_personnel()
{
    Administrateur<int> a;
    cin>>a;
    personnel.push_back(a);
}

void administration::supprimer_personnel()
{
    int id;
    cout << "Entrez l'identifiant de l'administrateur à supprimer : ";
    cin >> id;
    personnel.remove_if([id](Administrateur<int>& admin) { return admin.getId() == id; });
    cout << "\n L'administrateur avec l'identifiant " << id << " a été supprimé." << endl;
}

void administration::ajouter_departement()
{
    string departement;
    cout << "Entrez le nom du département à ajouter : ";
    cin >> departement;
    departement_administratif.insert(departement);
}
void administration::supprimer_departement()
{
    string departement;
    cout << "Entrez le nom du département à supprimer : ";
    cin >> departement;
    departement_administratif.erase(departement);
}
Administrateur<int>& administration::operator[](int n) {
    if (n < 0 || n >= personnel.size()) {
        return personnel.front();
    }
     list<Administrateur<int>>::iterator it = personnel.begin();
    for (int i = 0; i < n; ++i) {
        ++it;
    }
    return *it;
}
