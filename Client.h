#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

class Client
{
public:
    Client();
    ~Client();
    void verifier_reservation(reservation &res); // avant d'ajouter une reservation on va effectuer tous les tests necessaire
    void AffichageClient(); // Afficher la liste TRIEE des reservations d'une poste :il faut donner le code postal  + verifier le code + affichage uniquement du premier champ(code postal) et troisieme champ(horaire) à partir du fichier "reservation.txt"
};


#endif
