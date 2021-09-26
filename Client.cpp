#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "Functions.h"
#include "Client.h"
using namespace std;

Client::Client() {};
Client::~Client() {};

void Client::AffichageClient()
{
    map<int, string> mape;
    vector<int> tickets;
    long int code;

    cout << "Entrez le code postal de votre poste : ";
    verifier_code_postal(code);

    cout << "\n*************************************************\n";
    cout << " La liste des reservations : \n\n";

    string str_code = to_string(code);
    string champ_un, champ_deux, champ_trois, champ_quatre;
    ifstream fichier("reservation.txt");

    while (getline(fichier, champ_un, ','))
    {
        getline(fichier, champ_deux, ',');
        getline(fichier, champ_trois, ',');
        getline(fichier, champ_quatre, '\n');

        if (champ_un == str_code)
        {
            int ticket = stoi(champ_quatre);
            string ligne = "";
            ligne = ligne + "        " + champ_un + "\t\t\t " + " " + champ_trois ;

            mape.insert(pair<int, string>(ticket, ligne));
            tickets.push_back(ticket);
        }
    }

    sort(tickets.begin(), tickets.end());
    cout << "\n------------------------------------------\n";
    cout<<" Le code postal      Les horaires reserves";
    cout << "\n-----------------------------------------\n";


    for (int i = 0; i < tickets.size(); i++)
    {
        map<int, string>::iterator it;
        it = mape.find(tickets[i]);
        cout << it->second <<endl;
    }

    cout << "\n*************************************************\n";
}
void Client::verifier_reservation(reservation &res)
{
    Saisir_horaire(res.horaire, res.ticket);
    bool bool1 = 0, bool2 = 0, bool3 = 0, bool4 = 0;
    string str_num = to_string(res.num_compte);
    string str_code = to_string(res.code_postal);
    string str_ticket = to_string(res.ticket);

    string champ_un, champ_deux, champ_trois, champ_quatre;
    fstream fichier("reservation.txt", ios::in | ios::out);

    while (getline(fichier, champ_un, ',') && fichier.good())
    {
        getline(fichier, champ_deux, ',');
        getline(fichier, champ_trois, ',');
        getline(fichier, champ_quatre, '\n');
        if (champ_un == str_code && champ_deux == str_num)
        {
            bool1 = true;
            break;
        }

        else if (champ_un == str_code && champ_quatre == str_ticket && champ_deux != str_num)
        {
            bool2 = true;
            break;
        }
        else if (champ_un == str_code && champ_quatre != str_ticket && champ_deux != str_num)
        {
            bool3 = true;
            int quatre = stoi(champ_quatre);
            if (abs(quatre - res.ticket) <= 600)
            {
                bool4 = true;
                break;
            }
        }

    }
    fichier.close();

    if (bool1)
    {
        cout << "Vous avez deja une reservation !! " << endl;
        cout << " 1. TAPEZ 1 pour annuler votre reservation  \n";
        cout << " 2. TAPEZ 2 pour  mettre a jour votre reservation \n";
        cout << "Entrez n'importe quelle autre cle pour quitter \n\n";

        cout << "\n       ENTREZ VOTRE CHOIX: ";
        int choix;
        cin >> choix;

        switch (choix)
        {
        case 1:
            SupprimerClient();
            break;

        case 2:
        {
            bool bool5 = true;
            SupprimerClient();
            cout<<"Saisir un nouveau horaire s'il vous plait";
            Saisir_horaire(res.horaire, res.ticket);
            string str_ticket = to_string(res.ticket);

            string champ_un, champ_deux, champ_trois, champ_quatre;
            fstream fichier("reservation.txt", ios::in | ios::out);

            while (getline(fichier, champ_un, ',') && fichier.good())
            {
                getline(fichier, champ_deux, ',');
                getline(fichier, champ_trois, ',');
                getline(fichier, champ_quatre, '\n');
                int quatre = stoi(champ_quatre);

                if (champ_trois.compare(res.horaire) == 0 || abs(quatre - res.ticket) <= 600)
                {
                    bool5 = false;
                }
            }
            fichier.close();

            if (bool5)
                AjoutClient(res);

            else
            {
                cout<<"Saisir un horaire valide \n"; //yema l9a nafes wa9t wala fazet 10 min à respecter
                verifier_reservation(res);
            }

            break;
        }

        default:
            exit(0);
        }
    }

    else if (bool2)
    {
        cout << "\nDesole ,l'horaire est deja reserve.\n";
        cout << "Saisir un autre horaire \n";
        verifier_reservation(res);
    }

    else if (bool3)
    {

        if (!bool4)
            AjoutClient(res);

        else
        {
            cout << "Deux operations successives devraient etre separees de 10 minutes , veuillez verifiez votre horaire s'il vous plait \n";
            verifier_reservation(res);
        }
    }
    else
        AjoutClient(res);
}
