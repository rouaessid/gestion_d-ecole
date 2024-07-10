#ifndef ADMINISTRATION_H_INCLUDED
#define ADMINISTRATION_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include<list>
#include"administrateur.h"
#include <set>
using namespace std;
class administration
{
private:
    list<Administrateur<int>> personnel;
    set<string> departement_administratif;

public:
    ~administration();
    administration(const administration&);
    administration(list<Administrateur<int>> personnel = {}, set<string> departement_administratif = {});
    friend ostream& operator<<(ostream&, administration&);
    friend istream& operator>>(istream&, administration&);
    void ajouter_personnel();
    void supprimer_personnel();
    void ajouter_departement();
    void supprimer_departement();
    list<Administrateur<int>> getPersonnel(){return personnel;};
    Administrateur<int>& operator[](int );

};

#endif // ADMINISTRATION_H_INCLUDED
