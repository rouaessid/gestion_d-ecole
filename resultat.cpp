#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include <algorithm>
#include"resultat.h"
#include <iomanip>
using namespace std;
resultat::resultat(Inscription ins) : base_donnee(ins)
{ cout<<"inscription"<<endl;
   }
resultat::~resultat() {

    base_donnee.~Inscription();
}
resultat::resultat(const resultat& r) : base_donnee(r.base_donnee)
 {
}
void resultat::afficher_les_admis() {
    vector<Candidat<int>*> tab = base_donnee.get_liste_candidat();
    vector<pair<string, double>> etudiants_admis;
    // Filtrer les étudiants admis
    for (int i = 0; i < tab.size(); i++) {
        if (tab[i]->moyen_total() >= 10) {
            etudiants_admis.push_back(make_pair(tab[i]->getPrenom(), tab[i]->moyen_total()));
        }
    }
    // Trier les étudiants admis par moyenne totale décroissante
    sort(etudiants_admis.begin(), etudiants_admis.end(), [](const pair<string, double>& a, const pair<string, double>& b) {
        return a.second > b.second;
    });
    // Afficher les étudiants admis
    cout << "Étudiants admis (triés par moyenne totale décroissante) :" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << setw(20) << left << "Prénom" << setw(10) << right << "Moyenne" << endl;
    cout << "---------------------------------------------------------" << endl;
    for (const auto& etudiant : etudiants_admis) {
        cout << setw(20) << left << etudiant.first << setw(10) << right << etudiant.second << endl;
    }
    cout << "---------------------------------------------------------" << endl;
}
