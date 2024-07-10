#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"session.h"
#include <algorithm>
using namespace std;
session::session() {
}
session::session(string annee, map<string, int> etablissements, list<date> dates) {
    annee_scolaire = annee;
    nbre_des_etablissements_par_gouvernorat = etablissements;
    date_important_du_session = dates;
}
session::session(const session& s) {
    annee_scolaire = s.annee_scolaire;
    nbre_des_etablissements_par_gouvernorat = s.nbre_des_etablissements_par_gouvernorat;
    date_important_du_session = s.date_important_du_session;
}
session::~session() {
}
ostream& operator<<(ostream& out, const session& s) {
    out << "Année scolaire : " << s.annee_scolaire << endl;
    out << "Nombre d'établissements par gouvernorat :" << endl;
    map<string, int>::const_iterator it;
    for (it = s.nbre_des_etablissements_par_gouvernorat.begin(); it != s.nbre_des_etablissements_par_gouvernorat.end(); ++it) {
        out << " - " << it->first << " : " << it->second << endl;
    }

    out << "Dates importantes de la session :" << endl;
    list<date>::const_iterator date_it;
    for (date_it = s.date_important_du_session.begin(); date_it != s.date_important_du_session.end(); ++date_it) {
        out << *date_it << endl;
    }
    return out;
}

istream& operator>>(istream& in, session& s) {
    cout << "Entrez l'année scolaire : ";
    in >> s.annee_scolaire;
    char rep;
    cout << "***veuillez saisir le gouvernorat ainsi que le nombre d'établissements dédiés au concours***" << endl;
    do {
        string gouvernorat;
        int nb_etablissement;
        cout << "Entrez le nom du gouvernorat : ";
        in >> gouvernorat;
        cout << "Entrez le nombre des établissements de cette gouvernorat : ";
        in >> nb_etablissement;
        s.nbre_des_etablissements_par_gouvernorat[gouvernorat] = nb_etablissement;
        cout << "\n Voulez-vous ajoutez d'autres etablissements  ? (o/n) : ";
        in >> rep;
    } while (rep == 'o' || rep == 'O');
   cout << " \n***saisir les dates importants de la session(  date_deb /date_fin /date de correction des epreuves ...  )******"  << endl;
    string rep2;
    int i = 1;
    while (true)
    {
        cout << "\n***saisir la date " << i << "***" << endl;
        date d;
        in>>d;
        i++;
        s.date_important_du_session.push_back(d);
        cout << "voulez vous rajoutez d'autres dates marquants ?(O|o)?" << endl;
        in >> rep;
        if (rep2 != "o" && rep2 != "O")
            break;
    }
    return in;
}
void session::ajouter_etablissement() {
    string gouvernorat;
    int nb_etablissements;
    cout << "Donnez le nom du gouvernorat à ajouter : ";
    cin >> gouvernorat;
    cout << "Saisissez le nombre d'établissements dans ce gouvernorat : ";
    cin >> nb_etablissements;
    nbre_des_etablissements_par_gouvernorat.insert(make_pair(gouvernorat, nb_etablissements));
    cout << "*****Ajout effectué avec succès.*****" << endl;
}
void session::supprimer_etablissement() {
    string gouvernorat;
    cout << "Donnez le nom du gouvernorat à supprimer : ";
    cin >> gouvernorat;

    // Utilisation de L'algorithme de recherche find
    map<string, int>::iterator it = nbre_des_etablissements_par_gouvernorat.find(gouvernorat);

    if (it != nbre_des_etablissements_par_gouvernorat.end()) {
        nbre_des_etablissements_par_gouvernorat.erase(it);
        cout << "Le gouvernorat '" << gouvernorat << "' a été supprimé avec succès." << endl;
    } else {
        cout << "Le gouvernorat '" << gouvernorat << "' n'existe pas dans la liste." << endl;
    }
}

void session::ajouter_date_important() {
    cout << "Saisissez une nouvelle date importante : " << endl;
    date nouvelle_date;
    cin>>nouvelle_date;
    date_important_du_session.push_back(nouvelle_date);
    cout << "La nouvelle date importante a été ajoutée avec succès." << endl;
}
void session::modifier_date() {
    if (date_important_du_session.empty()) {
        cout << "La liste des dates importantes est vide." << endl;
        return;
    }
    int indice;
    cout << "Entrez l'indice de la date importante que vous souhaitez modifier : ";
    cin >> indice;
    if (indice < 1 || indice > date_important_du_session.size()) {
        cout << "Indice invalide. La modification de la date importante a échoué." << endl;
        return;
    }
    list<date>::iterator it = date_important_du_session.begin();
    for (int i = 1; i < indice; ++i) {
        ++it;
    }
    cout << "Saisissez la nouvelle date : " << endl;
    date nouvelle_date;
    cin >> nouvelle_date;
    *it = nouvelle_date;
    cout << "La date importante a été modifiée avec succès." << endl;
}
date& session::operator[](int n) {
    if (n < 0 || n >= date_important_du_session.size()) {
        return date_important_du_session.front();
    }
     list<date>::iterator it = date_important_du_session.begin();
    for (int i = 0; i < n; ++i) {
        ++it;
    }
    return *it;
}
//---------------------------creer fichier session------------------------------------
void session::creer(fstream& f) {
    try {
        f.open("d:\\fichiersession.txt", ios::in | ios::out | ios::trunc);
        if (!f.is_open()) {
            throw runtime_error("Impossible d'ouvrir le fichier.");
        }
    } catch (const exception& e) {
        cerr << "Erreur : " << e.what() << endl;
        exit(-1);
    }
}
//-----------------------lire fichier_session ------------------------------
void session::afficher_fichier(fstream&f)
{
    char ch[100];
    f.seekg(0);
    while(1)
    {   f.getline(ch,100);
        if(f.eof())break;
        cout<<ch<<endl;
    }
}
//-----------------------ecrire dans fichier------------------------------
ostream& operator<<(ostream& out, const session* s) {
    try {
        out << "Année scolaire : " << s->annee_scolaire << endl;
        out << "Nombre d'établissements par gouvernorat :" << endl;
        map<string, int>::const_iterator it;
        for (it = s->nbre_des_etablissements_par_gouvernorat.begin(); it != s->nbre_des_etablissements_par_gouvernorat.end(); ++it) {
            out << " - " << it->first << " : " << it->second << endl;
        }
        out << "Dates importantes de la session :" << endl;
        list<date>::const_iterator date_it;
        for (date_it = s->date_important_du_session.begin(); date_it != s->date_important_du_session.end(); ++date_it) {
            out << *date_it << endl;
        }
    } catch (const exception& e) {
        cerr << "Une exception est survenue lors de l'affichage de la session : " << e.what() << endl;
    }
    return out;
}
