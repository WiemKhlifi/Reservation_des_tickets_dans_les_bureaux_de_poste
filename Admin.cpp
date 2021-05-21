#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include "Functions.h"
#include "Admin.h"
using namespace std;

Admin::Admin(){};
Admin::~Admin(){};



void Admin:: AffichageAdmin()
{
    map<int, string> mape;
    vector<int> tickets;
    long int code;

    cout << "Entrez le code postal de votre poste : ";
    verifier_code_postal(code);

    cout << "\n**************************************************************************\n";
    cout << " La liste des clients : \n\n";

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
            ligne = ligne + " " + champ_un + "\t\t" + champ_deux + "\t\t" + champ_trois + "\t\t" + champ_quatre;

            mape.insert(pair<int, string>(ticket, ligne));
            tickets.push_back(ticket);
        }
    }

    sort(tickets.begin(), tickets.end());

    cout << "\n---------------------------------------------------------------------------------\n";
    cout<<"Code postal\t Numero de compte\t L'horaire reserve\t Ticket";
    cout << "\n---------------------------------------------------------------------------------\n";


    for (int i = 0; i < tickets.size(); i++)
    {
        map<int, string>::iterator it;
        it = mape.find(tickets[i]);
        cout << it->second << endl;
    }

    cout << "\n*********************************************************************************\n";
}

void Admin:: verifier_mdp()
{
    string motDePasse = "ENSIDAWDAW", mdp;
    cout << "Entrez le mot de passe : " << endl;
    cin >> mdp;
    if (motDePasse.compare(mdp) == 0)
        cout<<"Votre mot de passe esst correct ! :D"<<endl;
    else
    {
        cout << "\nVotre mot de passe est incorrect !! \n reessayez s'il vous plait : ";
        verifier_mdp();
    }
}

void Admin::SupprimerClient()
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
