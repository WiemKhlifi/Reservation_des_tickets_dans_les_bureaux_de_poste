#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
using namespace std;

struct reservation{
    long int code_postal , num_compte ;
    string horaire;
    int ticket ; //temps converti en secondes
};
typedef struct reservation reservation;

void verifier_compte(long int &num_compte); // verifier l'existance du numero de compte et le resaisir en cas d'une fausse saisie
void verifier_code_postal(long int &code_postal); // verifier l'existance du code postal et le resaisir en cas d'une fausse saisie
void Saisir_horaire(string &horaire , int &ticket); // saisir un horaire qui respecte l'horaire adminstratif
void AjoutClient(const reservation &res); // Ajouter un client dans le fihcier reservation
void FichierPropre(string nomfichier); //nettoyer le fichier "reservation.txt" apres la fin du jour c'est à dire à 17h
void SupprimerClient(); // supprimer la reservation effectué par le client du fichier "reservation.txt"


