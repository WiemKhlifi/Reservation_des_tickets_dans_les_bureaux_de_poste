#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Functions.h"
#include "Client.h"
#include "Admin.h"
using namespace std;



int main()
{
    FichierPropre("reservation.txt");
    cout << "               \t\t Bienvenue dans le systeme de reservation dans les bureaux de postes\n\n\n";
    cout << "                         \t            RESEVATION EN LIGNE \n\n\n";
    cout << "                         \t      PRESSEZ ENTRER POUR CONTINUER....\n\n";

    if (cin.get() == '\n')
    {
        system("cls");
        int choix;

        cout << "\n VOUS ETES QUI ?\n";
        cout << "1. ADMIN\n";
        cout << "2. CLIENT\n\n";
        cout << "ENTREZ VOTRE OPTION\n";
        cin >> choix;
        switch (choix)
        {
        case 1:
        {
            Admin A;
            A.verifier_mdp();

            system("cls");

            while (1)
            {
                cout << "                                   BIENVENUE ADMIN \n \n";
                cout << "Entrez votre option : "<<endl;
                cout << "1. Affichage de la liste des reservations des clients d'une poste \n";
                cout << "2. Supprimer une reservation \n";
                cout << "Entrez n'importe quelle autre cle pour quitter \n\n";

                cout << "\nENTREZ VOTRE CHOIX: ";
                int ch1;
                cin >> ch1;
                switch (ch1)
               {
                case 1:
                    A.AffichageAdmin();
                    break;
                case 2:
                    A.SupprimerClient();
                    break;
                default:
                    exit(0);
                }
            }

        }

        case 2:
        {
            Client C ;
            cout << "                                      BIENVENUE CHER CLIENT \n\n";
            reservation r;
            int ch2;

            cout << "Entrez votre numero de compte s'il vous plait : ";
            verifier_compte(r.num_compte);

            cout << "Entrez le code postal de votre region : ";
            verifier_code_postal(r.code_postal);
            system("cls");



            while (1)
            {
                cout << "Entrez votre option : "<<endl;
                cout << "0. Affichage de la liste des reservations dans votre region\n ";
                cout << "1. Nouvelle reservation\n ";
                cout << " . Entrez n'importe quelle autre cle pour quitter\n\n\n ";

                cout << "    \t \t ENTREZ VOTRE CHOIX: ";
                cin >> ch2;
                switch (ch2)
                {
                case 0:
                    C.AffichageClient();
                    break;
                case 1:
                {
                    cout << "-----------------------------------";
                    cout << "\n Choisissez un horaire\n";
                    cout << "-----------------------------------\n";
                    C.verifier_reservation(r);
                    cout << "\n";
                    break;
                }

                default:
                    exit(0);
                }
            }
        }

        default:
            exit(0);
        }
    }

    return 0;
}
