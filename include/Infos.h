#ifndef INFOS_H_INCLUDED
#define INFOS_H_INCLUDED

#include "Constantes.h"

string cryptShadok(int nombre)             // Fonction de cryptage du nb de parties
{
    string shadokCrypte="";
    string nbShadok="";
    int n=0;
    int diviseur=4;

    while (nombre!=0){                       // Tant qu'il extiste un reste dans la division du nombre par 4

        n = nombre%4;                   // On stocke le reste de la division euclidienne par 4 dans n
        nbShadok+=to_string(n);
        nombre=nombre/diviseur;         // On effectue le quotient du nombre par 4
    }

    for (int i=(nbShadok.size())-1; i>=0; i--){         // Les chiffres sont remplacés par les lettres correspondantes

        if (nbShadok.at(i)=='0'){
            shadokCrypte+="GA";
        }
        else if (nbShadok.at(i)=='1'){
            shadokCrypte+="BU";
        }
        else if (nbShadok.at(i)=='2'){
            shadokCrypte+="ZO";
        }
        else {
            shadokCrypte+="MEU";
        }
    }
    return shadokCrypte;               // Le message est renvoyé
}

int decryptShadok(string shadok)          //Fonction de décryptage du nb de parties
{
    int a=0;
    int nombre=0;
    int longueurChaine=0;
    vector<int> tableau;
    for (int i=0; i<shadok.size(); i++){   // On remplace chaque mot par le chiffre correspondant

        if (shadok.at(i)=='G'){
            tableau.push_back(0);
            longueurChaine++;
        }
        else if (shadok.at(i)=='B'){
            tableau.push_back(1);
            longueurChaine++;
        }
        else if (shadok.at(i)=='Z'){
            tableau.push_back(2);
            longueurChaine++;
        }
        else if (shadok.at(i)=='M'){
            tableau.push_back(3);
            longueurChaine++;
        }
    }


    for (int i=longueurChaine-1; i>=0; i--){      // Pour chaque nombre du dernier au premier, on le multiplie par 4**a avec a un entier initialisé à 0 et incrémenté à chaque tour de boucle

         nombre+=(tableau[i]*pow(4,a));
         a++;
    }
    return (nombre);
}

string cryptAffinePseudo(string pseudoTemp)  // Fonction de cryptage du pseudo
{
    string pseudoCrypte="";
    transform(pseudoTemp.begin(), pseudoTemp.end(), pseudoTemp.begin(), ::toupper); // On met le string en majuscules
    int nblettres=pseudoTemp.size();                                                      // La variable nblettres contient le nb de lettres du pseudo
    int a=3;
    int b=7;
    // Coeffs a et b de la fct affine du type y=ax+b

    for (int i=0; i<nblettres; i++){
        /*tableau.push_back(int (majuscule.at(i))-65);                                   // On ajoute le nombre relatif au caractère ASCII avec a=0 jusqu'à z=25
        tableau[i]=((tableau[i]*a+b)%26);                                           // On applique la fct affine au nombre que l'on met modulo 26 pour obtenir un nombre correspondant à un caractère de l'alphabet*/
        pseudoCrypte+=char((((int(pseudoTemp.at(i))-65)*a+b)%26)+65);                                          // Le nombre est converti en caractère ASCII et ajouté au string pseudoCrypte
    }
    return pseudoCrypte;
}

string decryptAffineLettres(string pseudoCrypte) // Fonction de décryptage du pseudo
{
    int nblettres=pseudoCrypte.size();
    string pseudoDecrypte="";
    vector<int> tableau;

    for (int i=0; i<nblettres; i++){
        tableau.push_back(int (pseudoCrypte.at(i))-65);                                 // La lettre est castée en int
        tableau[i]=(tableau[i]*9+15)%26;                                                // On remonte à la valeur de x grâce à l'image y de la fonction affine (cf dossier congruences)
        pseudoDecrypte+=char(tableau[i]+65);                                            // L'antécédent x est casté en char
    }
    return pseudoDecrypte;
}

void infos()                            // Fonction d'enregistrement des données liées au joueur (argent, pseudo crypté, nb de parties ...)
{
    string nbPartiesCrypte;
    fstream fichier("infos.txt", ios::in);      // Ouverture du fichier info
    if (fichier)                                       // Si le fichier existe ...
    {
        fichier>>nbPartiesCrypte;
        fichier.close();
        fichier.open("infos.txt",ios::out | ios::trunc);
        //récupere le nombre de parties

        int nbPartiesDecrypte=decryptShadok(nbPartiesCrypte);
        ++nbPartiesDecrypte;
        cout<<argent<<endl;
        string nbPartiesCrypte=cryptShadok(nbPartiesDecrypte);
        string argentCrypte=cryptShadok(argent);

        //incrémente puis écrit dans le fichier (automatiquement converti en string)
        fichier<<(nbPartiesCrypte);
        fichier<<("\n");            // Saut de ligne
        fichier<<(cryptAffinePseudo(pseudo));    // Ajout du pseudo crypté
        fichier<<("\n");
        fichier<<(argentCrypte);          // Ajout de la somme d'argent
        fichier<<("\n");
    }
}

void recupInfos(){
    // Récupération du nombre de parties dans le fichier infos.txt
    fstream fichier("infos.txt", ios::in);      // Ouverture du fichier info
    string nbPartiesCrypte;
    string pseudoHighscoreCrypte;
    string highscoreCrypte;
    if (fichier)                                       // Si le fichier existe ...
    {
        fichier>>nbPartiesCrypte;
        fichier>>pseudoHighscoreCrypte;
        fichier>>highscoreCrypte;
        fichier.close();
        nbParties=decryptShadok(nbPartiesCrypte);
        pseudoHighscore=decryptShadok(pseudoHighscoreCrypte);
        highscore=decryptShadok(highscoreCrypte);
    }
}

#endif // INFOS_H_INCLUDED
