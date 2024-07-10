#include <iostream>
#include"date.h"
#include"session.h"
#include<fstream>
#include"administration.h"
#include"categorie.h"
#include"inscription.h"
#include"candidat.h"
#include"resultat.h"
using namespace std;

// Fonction pour afficher l'en-tête du programme
void afficher_entete() {
    cout << "**************************************************************\n";
    cout << "*                Bienvenue dans la Gestion du               *\n";
    cout << "*             concours Nationale d'agregation               *\n";
    cout << "**************************************************************\n\n";
}

// Fonction pour afficher l'en-tête d'un sous-menu
void afficher_entete_sous_menu(const string& titre) {
    cout << "\n**************************************************************\n";
    cout << "*                        " << titre << "               *\n";
    cout << "**************************************************************\n\n";
}

int main() {
    afficher_entete();
    int choix_Principal, choixsession, choixins, choixad, choixfich, choixfich1, choixfich2;
    Inscription i;
    session s;
    fstream f;
    fstream f2;

    while (true) {
        // Menu Principal
        cout << "********** Menu Principal **********\n\n";
        cout << "1. Gestion de la session du concours\n";
        cout << "2. Inscription des candidats\n";
        cout << "3. Affichage des Resultats du concours\n";
        cout << "4. Gestion de l'administration\n";
        cout << "5. Gestion des fichiers\n";
        cout << "6. Quitter\n\n";
        cout << "Choix : ";
        cin >> choix_Principal;

        switch (choix_Principal) {
            case 1: {
                // Gestion de la session
                afficher_entete_sous_menu("Gestion de la session");
                while (true) {
                    // Menu Gestion de la session
                    cout << "1. Remplissage\n";
                    cout << "2. Affichage\n";
                    cout << "3. Ajouter un etablissement du concours\n";
                    cout << "4. Supprimer un etablissement du concours\n";
                    cout << "5. Ajouter une date importante à la session\n";
                    cout << "6. Modifier une date importante de la session\n";
                    cout << "7. Afficher la nème date de la session\n";
                    cout << "8. Retour au menu principal\n\n";
                    cout << "Choix : ";
                    cin >> choixsession;

                    switch (choixsession) {
                        case 1:
                            // Remplissage
                            cout<<"------------------------------------------------------\n"<<endl;
                            cin >> s;
                            cout<<"----------------------menu-------------------------------\n"<<endl;
                            break;
                        case 2:
                            // Affichage
                            cout<<"------------------------------------------------------\n"<<endl;
                            cout << s;
                            cout<<"----------------------menu--------------------------------\n"<<endl;
                            break;
                        case 3:
                            // Ajouter un établissement du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            s.ajouter_etablissement();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 4:
                            // Supprimer un établissement du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            s.supprimer_etablissement();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 5:
                            // Ajouter une date importante du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            s.ajouter_date_important();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 6:
                            // Modifier une date importante du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            s.modifier_date();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 7:
                            // Afficher la nème date du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            int n;
                            cout << "Veuillez saisir l'indice de la date à afficher : ";
                            cin >> n;
                            cout << s[n];
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 8:
                            // Retour au menu principal
                            break;
                        default:
                            cout << "Choix invalide.\n";
                    }

                    if (choixsession == 8) {
                        break; // Sortir de la boucle interne et retourner au menu principal
                    }
                }
                break;
            }
            case 2: {
                // Inscription
                afficher_entete_sous_menu("Gestion de l'inscription");
                while (true) {
                    // Menu Gestion de l'inscription
                    cout << "1. Remplissage\n";
                    cout << "2. Affichage\n";
                    cout << "3. Ajouter un Candidat\n";
                    cout << "4. Supprimer un candidat\n";
                    cout << "5. Modifier le frais de l'inscription\n";
                    cout << "6. Retour au menu principal\n\n";
                    cout << "Choix : ";
                    cin >> choixins;

                    switch (choixins) {
                        case 1:
                            // Remplissage
                            cout<<"------------------------------------------------------\n"<<endl;
                            cin >> i;
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 2:
                            // Affichage
                             cout<<"------------------------------------------------------\n"<<endl;
                            cout << i;
                             cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 3:
                            // Ajouter un candidat
                            cout<<"------------------------------------------------------\n"<<endl;
                            {Candidat<int>* a = new Candidat<int>();
                            cin >> *a;
                            i.ajouter_Candidat(a);
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;}
                        case 4:
                            // Supprimer un candidat
                            cout<<"------------------------------------------------------\n"<<endl;
                            int pos;
                            cout << "Saisir l'indice du candidat à supprimer : ";
                            cin >> pos;
                            i.supprimer_Candidat(pos);
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 5:
                            // Modifier le frais de l'inscription
                            cout<<"------------------------------------------------------\n"<<endl;
                            float frais;
                            cout << "Saisir le nouveau frais de l'inscription : ";
                            cin >> frais;
                            i.modif_frais(frais);
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 6:
                            // Retour au menu principal
                            break;
                        default:
                            cout << "Choix invalide.\n";
                    }

                    if (choixins == 6) {
                        break; // Sortir de la boucle interne et retourner au menu principal
                    }
                }
                break;
            }
            case 3:
                // Affichage des résultats du concours
                cout<<"------------------------------------------------------\n"<<endl;
                {afficher_entete_sous_menu("Affichage des Résultats du concours");
                resultat r(i); // Suppose que la classe Resultat est correctement définie
                r.afficher_les_admis();
                cout<<"---------------------menu---------------------------------\n"<<endl;
                break;}
            case 4: {
                // Gestion de l'administration
                afficher_entete_sous_menu("Gestion de l'administration");
                administration ad; // Création d'une instance d'Administration
                while (true) {
                    // Menu Gestion de l'administration
                    cout << "1. Remplissage\n";
                    cout << "2. Affichage\n";
                    cout << "3. Ajouter un administrateur du concours\n";
                    cout << "4. Supprimer un administrateur du concours\n";
                    cout << "5. Ajouter un département à l'administration du concours\n";
                    cout << "6. Supprimer un département à l'administration du concours\n";
                    cout << "7. Afficher la nème Administrateur du concours\n";
                    cout << "8. Retour au menu principal\n\n";
                    cout << "Choix : ";
                    cin >> choixad;

                    switch (choixad) {
                        case 1:
                            // Remplissage
                            cout<<"------------------------------------------------------\n"<<endl;
                            cin >> ad;
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 2:
                            // Affichage
                            cout<<"------------------------------------------------------\n"<<endl;
                            cout << ad;
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 3:
                            // Ajouter un administrateur du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            ad.ajouter_personnel();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 4:
                            // Supprimer un administrateur du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            ad.supprimer_personnel();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 5:
                            // Ajouter un département à l'administration du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            ad.ajouter_departement();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 6:
                            // Supprimer un département à l'administration du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            ad.supprimer_departement();
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 7:
                            // Afficher la nème administrateur du concours
                            cout<<"------------------------------------------------------\n"<<endl;
                            int n1;
                            cout << "Veuillez saisir l'indice de l'administrateur à afficher : ";
                            cin >> n1;
                            cout << ad[n1];
                            cout<<"---------------------menu---------------------------------\n"<<endl;
                            break;
                        case 8:
                            // Retour au menu principal
                            break;
                        default:
                            cout << "Choix invalide.\n";
                    }

                    if (choixad == 8) {
                        break; // Sortir de la boucle interne et retourner au menu principal
                    }
                }
                break;
            }
            case 5: {
                // Gestion des fichiers
                afficher_entete_sous_menu("Gestion des fichiers");
                while (true) {
                    // Menu Gestion des fichiers
                    cout << "1. Fichier session\n";
                    cout << "2. Fichier inscription\n";
                    cout << "3. Retour au menu principal\n\n";
                    cout << "Choix : ";
                    cin >> choixfich;
                    switch (choixfich) {
                        case 1: {
                            // Gestion du fichier session
                            afficher_entete_sous_menu("Gestion du fichier session");
                            while (true) {
                                cout << "1. Création\n";
                                cout << "2. Remplissage\n";
                                cout << "3. Affichage\n";
                                cout << "4. Retour au menu des fichiers\n\n";
                                cout << "Choix : ";
                                cin >> choixfich1;
                                switch (choixfich1) {
                                    case 1:
                                        cout<<"------------------------------------------------------\n"<<endl;
                                        session::creer(f);
                                        cout<<"creation effectuée avec succés "<<endl;
                                        cout<<"---------------------menu---------------------------------\n"<<endl;
                                        break;
                                    case 2:
                                        // Remplissage
                                        cout<<"------------------------------------------------------\n"<<endl;
                                        f << &s;
                                        cout<<"fichier remplie avec succés "<<endl;
                                        cout<<"---------------------menu---------------------------------\n"<<endl;
                                        break;
                                    case 3:
                                        // Affichage
                                        cout<<"------------------------------------------------------\n"<<endl;
                                        session::afficher_fichier(f);
                                        cout<<"---------------------menu---------------------------------\n"<<endl;
                                        break;
                                    case 4:
                                        // Retour au menu des fichiers
                                        break;
                                    default:
                                        cout << "Choix invalide.\n";
                                }
                                if (choixfich1 == 4) {
                                    break; // Sortir de la boucle interne et retourner au menu des fichiers
                                }
                            }
                            break;
                        }
                        case 2:
                            // Gestion du fichier inscription
                            afficher_entete_sous_menu("Gestion du fichier inscription");
                            while (true) {
                                cout << "1. Création\n";
                                cout << "2. Remplissage\n";
                                cout << "3. Affichage\n";
                                cout << "4. Retour au menu des fichiers\n\n";
                                cout << "Choix : ";
                                cin >> choixfich2;
                                switch (choixfich2) {
                                    case 1:
                                        // Création
                                        cout<<"------------------------------------------------------\n"<<endl;
                                        Inscription::creer(f2);
                                        cout<<"creation effectuée avec succés "<<endl;
                                        cout<<"---------------------menu---------------------------------\n"<<endl;
                                        break;
                                    case 2:
                                        // Remplissage
                                        cout<<"------------------------------------------------------\n"<<endl;
                                        f2 << &i;
                                        cout<<"fichier remplie avec succés "<<endl;
                                        cout<<"---------------------menu---------------------------------\n"<<endl;
                                        break;
                                    case 3:
                                        // Affichage
                                        cout<<"------------------------------------------------------\n"<<endl;
                                        Inscription::afficher_fichier(f2);
                                        cout<<"---------------------menu---------------------------------\n"<<endl;
                                        break;
                                    case 4:
                                        // Retour au menu des fichiers
                                        break;
                                    default:
                                        cout << "Choix invalide.\n";
                                }
                                if (choixfich2 == 4) {
                                    break; // Sortir de la boucle interne et retourner au menu des fichiers
                                }
                            }
                            break;
                        case 3:
                            // Retour au menu principal
                            break;
                        default:
                            cout << "Choix invalide.\n";
                    }

                    if (choixfich == 3) {
                        break; // Sortir de la boucle interne et retourner au menu principal
                    }
                }
                break;
            }
            case 6:
                // Quitter le programme
                return 0;
            default:
                cout << "Choix invalide.\n";
        }
    }

    return 0;
}




