#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "Functions.h"
using namespace std;

void verifier_compte(long int &num_compte)
{
    cin >> num_compte;
    string str_num = to_string(num_compte);
    ifstream comptes("LesComptes.txt");
    string str;
    bool verf_compte = false;

    while (getline(comptes, str, ','))
    {
        if (str.compare(str_num) == 0)
        {
            verf_compte = true;
            break;
        }
    }
    comptes.close();

    if (verf_compte == true)
        cout << "\n Votre numero de compte est valide "<<endl;
    else
    {
        cout << "\n Reessayez votre numero de compte n'est pas valide "<<endl;
        verifier_compte(num_compte);
    }
}

void verifier_code_postal(long int &code_postal)
{
    cin >> code_postal;
    string str_code = to_string(code_postal);
    ifstream postal("CodePostal.txt");
    string str;
    bool verf_code = false;
    while (getline(postal, str, ','))
    {
        if (str.compare(str_code) == 0)
        {
            verf_code = true;
            break;
        }
    }
    postal.close();

    if (verf_code == true)
        cout << "\n Votre code postal est valide \n";
    else
    {
        cout << "\n Reessayez , votre code postal n'est pas valide \n";
        verifier_code_postal(code_postal);
    }
}

void Saisir_horaire(string &horaire, int &ticket)
{

    int h, m;
    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant = *localtime(&secondes);

    printf("%d/%d ; %d:%d:%d\n", instant.tm_mday , instant.tm_mon + 1, instant.tm_hour, instant.tm_min, instant.tm_sec);
    cout << "Tapez l'heure" << endl;
    cin >> h;
    if (((h >= 8) && (h <= 12) && (h > instant.tm_hour)) || ((h >= 14) && (h <= 17) && (h > instant.tm_hour)))
    {
        cout << "Tapez les minutes" << endl;
        cin >> m;
        if ((m >= 0) && (m < 60))
        {

            ticket = m * 60 + h * 3600;
        }
        else
        {
            cout << "Vous devez choisir un nombre entre 00 et 59" << endl;
            Saisir_horaire(horaire, ticket);
        }
    }
    else if (((h >= 8) && (h <= 12) && (h = instant.tm_hour)) || ((h >= 14) && (h <= 17) && (h = instant.tm_hour)))
    {
        cout << "Tapez les minutes" << endl;
        cin >> m;
        if ((m >= 0) && (m < 60) && (m > (instant.tm_min) + 10))
        {

            ticket = m * 60 + h * 3600;
        }
        else
        {
            cout << "Tant que vous avez choisi l'heure actuelle ,il faut la depasser d'une duree minimale  de 10 minutes " << endl;
            Saisir_horaire(horaire, ticket);
        }
    }
    else
    {
        cout << "Il faut respecter l'horaire administratif" << endl;
        Saisir_horaire(horaire, ticket);
    }

    horaire = to_string(h) + ":" + to_string(m);
}

void AjoutClient(const reservation &res)
{

    fstream fichier;
    fichier.open("reservation.txt", ios::out | ios::app);
    if (!fichier)
    {
        cout << "\n le fichier n'existe pas";
        exit(0);
    }
    string Res = "";

    Res += to_string(res.code_postal) + ",";
    Res += to_string(res.num_compte) + ",";
    Res += res.horaire + ",";
    Res += to_string(res.ticket);

    fichier << Res << endl;
    fichier.close();
    cout << "Vous avez reserve a l'horaire " << res.horaire << " et votre ticket est la suivante : " << res.ticket << "\n La poste tunisienne vous remercie pour votre fidelite.\n";
}


void FichierPropre(string nomfichier)
{
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);

    if (instant.tm_hour >= 17 && instant.tm_hour < 8)
    {
        fstream fichier;
        fichier.open("reservation.txt", ios::out | ios::trunc);
    }
}


void SupprimerClient()
{
    long int num_compte, code_postal;
    int nombreligne_f = 0, nombreligne_t = 0;

    cout << "\nEntrez le numero de compte du client a supprimer : ";
    verifier_compte(num_compte);

    string str_num = to_string(num_compte);

    string champ_un, champ_deux, champ_trois, champ_quatre, ligne = "";
    char *nomfichier = "reservation.txt";
    ifstream fichier(nomfichier);
    ofstream temp("temp.txt");

    while (getline(fichier, champ_un, ','))
    {
        getline(fichier, champ_deux, ',');
        getline(fichier, champ_trois, ',');
        getline(fichier, champ_quatre, '\n');

        if (champ_deux != str_num)
        {
            ligne = ligne + champ_un + "," + champ_deux + "," + champ_trois + "," + champ_quatre;
            temp << ligne << endl;
            ligne = "";
            nombreligne_t++;
        }
        nombreligne_f++;
    }

    temp.close();
    fichier.close();

    remove(nomfichier);
    rename("temp.txt", nomfichier);

    if (nombreligne_f == nombreligne_t && cin.get() == '\n')
    {
        cout << "\nMais la reservation n'est pas trouvee. \n ";

        string option = "continuer";
        while (option != "quitter")
        {
            cout << "\nSi vous voulez sortir ,ecrire quitter sinon ecrire continuer. \n\n";

            cin >> option;

            if (option == "continuer")
            {
                cout << "\nEntrez les bonnes informations s'il vous plait. \n ";
                SupprimerClient();
            }
        }
    }
    else
        cout << "\nL'operation est effectuee avec succes !! \n ";
}


