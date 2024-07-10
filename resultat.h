#ifndef RESULTAT_H_INCLUDED
#define RESULTAT_H_INCLUDED
#include <iostream>
#include<string>
#include<fstream>
#include<typeinfo>
#include<vector>
#include"inscription.h"
using namespace std;
class resultat
{
    Inscription base_donnee;
 public:
    resultat(Inscription ins = {});
    ~resultat();
    resultat(const resultat&);

   void afficher_les_admis();
};


#endif // RESULTAT_H_INCLUDED
