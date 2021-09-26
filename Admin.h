#ifndef ADMIN_H
#define ADMIN_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

class Admin
{
    public:
    Admin();
    ~Admin();
    void verifier_mdp();
    void AffichageAdmin(); //Afficher la liste TRIEE des reservations d'une poste :il faut donner le code postal  + verifier le code + affichage des lignes qui contiennet le meme code postal
    void SupprimerClient();// Suprimer le client :demander num_compte et le code_postal du client + verifier +supprimer le client
};


#endif
