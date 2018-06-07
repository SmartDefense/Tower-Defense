#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <algorithm>
#include <cmath>

#include "Constantes.h"

SDL_Window *fenetre;
SDL_Renderer *renderer;
SDL_Texture  *textureCase,
             *textureChemin,
             *textureChateau,

             *textureTourClassiqueBase,
             *textureTourPoisonBase,
             *textureTourSniperBase,

             *textureTourClassiqueCanon,
             *textureTourSniperCanon,

             *textureEnnemiClassique,
             *textureEnnemiRapide,
             *textureEnnemiTank,
             *textureEnnemiVolant,

             *textureTirClassique,
             *textureTirSniper,

             *textureExplosion[TEMPS_ANIM_TIR],

             *textureBpTourSniper,
             *textureBpTourClassique,
             *textureBpTourPoison,
             *textureBpEffacer,
             *textureBpAnnuler,
             *textureCadence,
             *textureDegatTir,
             *texturePorteeTour,
             *textureVitesseTir,


             *textureAccueil,
             *textureLogo;
TTF_Font *font;

#include "Case.h"
#include "TourClassique.h"
#include "TourSniper.h"
#include "TourPoison.h"
#include "TourAerien.h"
#include "Chemin.h"
#include "Chateau.h"
#include "EnnemiTank.h"
#include "EnnemiRapide.h"
#include "EnnemiClassique.h"
#include "EnnemiVolant.h"
#include "TirClassique.h"
#include "TirSniper.h"

#include "Variables.h"
#include "VariablesSDL.h"

vector<int> vague;                  // Tableau permettant d'ajouter le type d'ennemi et de l'afficher pendant la vague
Case*** listeCases;
vector<Ennemi*> listeEnnemis;
vector<Tir*> listeTirs;

string nbParties="";                // Nombre de parties du joueur
string pseudo ="";                  // Variable contenant le pseudo entré par le joueur
string pseudoCrypte="";
string pseudoDecrypte="";
int nbVagues=80;                    // Nombre de vague totale dans chaque partie
int depart=0;                       // Variable d'état pour commencer à afficher la vague d'ennemis
int occurences=10;                  // Nombre d'ennemis dans la première vague
int argent=200;                         // Argent du joueur
int numLevel=1;                     // Numero du level
int continuer=1;                    // Variable d'état pour quitter la boucle principale et fermer la fenêtre de jeu
int affichageArgent=1;

int TAILLE_X_PLATEAU = 20;
int TAILLE_Y_PLATEAU = 15;
int nbEnnemisSupplementaires =4;    // Nb d'ennemis supplémentaires à chaque vague
int compteurImage=0;                // Compteur d'images permettant d'effectuer des actions à un temps donné dans une boucle while
int rafraichissement=30;

int xChateau=0,
    yChateau=0;

int xVague=-1,                      // Variables permettant de connaitre la position de la case de départ
    yVague=-1;

void quitListeCase()                // Fonction de suppression de la listeCases à la fin de la partie
{
    for(int y=0; y<TAILLE_Y_PLATEAU; y++)
    {
        for(int x=0; x<TAILLE_X_PLATEAU; x++)
        {
            delete listeCases[y][x];
        }
    }
    for(int y=0; y<TAILLE_Y_PLATEAU; y++)
    {
        delete[] listeCases[y];
    }
    delete[] listeCases;
}

void remplissageVague()                 // Fonction remplissant le tableau vague par le nombre d'ennemis voulu
{
    for (int i=0; i<(occurences); i++){
        vague.push_back(rand()%3);      // Tirage aléatoire du type d'ennemi (nombre entre 0 et 2)
    }
    depart=1;                           // Affichage de la vague à la prochaine condition
}

char cryptNombres(int nombre)  // Fonction de cryptage du nb de parties avec le code ASCII
{
return (char(nombre));
}

int decryptNombres(char lettre) // Fonction de décryptage du nb de parties
{
return (int(lettre));
}

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

void infos()                            // Fonction d'enregistrement des données liées au joueur (argent, pseudo crypté, nb de parties ...)
{
    string nomfichier= "infos.txt";                    // String contenant le nom du fichier et son extension
    fstream fichier(nomfichier.c_str(), ios::in);      // Ouverture du fichier info
    if (fichier)                                       // Si le fichier existe ...
    {
        fichier>>nbParties;
        fichier.close();
        fichier.open(nomfichier.c_str(),ios::out | ios::trunc);
        //récupere le nombre de parties

        int nbPartiesDecrypte=decryptShadok(nbParties);
        ++nbPartiesDecrypte;
        string nbPartiesCrypte=cryptShadok(nbPartiesDecrypte);
        string argentCrypte=cryptShadok(argent);

        //incrémente puis écrit dans le fichier (automatiquement converti en string)
        fichier<<(nbPartiesCrypte);
        fichier<<("\n");            // Saut de ligne
        fichier<<(pseudoCrypte);    // Ajout du pseudo crypté
        fichier<<("\n");
        fichier<<(argentCrypte);          // Ajout de la somme d'argent
        fichier<<("\n");
    }
}

void Ecrire(string police, int taille, string texte, int r, int v, int b, int x, int y) // Fonction d'écriture
{
    font = TTF_OpenFont(("fonts/" + police + ".ttf").c_str(), taille);                  // Ouverture de la police
    SDL_Color color = { r, v, b };                                                      // Couleur de police envoyée à la fonction type r,g,b
    SDL_Surface * surface = TTF_RenderText_Blended(font,texte.c_str(), color);          // Rendu de la police sur le fond
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);            // Création de la texture à partir du fond

    int texW = 0;                                                                       // Largeur de la texture en pixels
    int texH = 200;                                                                     // Hauteur de la texture en pixels
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);                                // Appel de la texture
    SDL_Rect dstrect = { x, y, texW, texH };                                            // Position de la zone d'écriture à partir de x et y, position du premier caractère
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);                                  // Copie de la texture dans le renderer

    SDL_DestroyTexture(texture);                                                        // Suppression de la texture
    TTF_CloseFont(font);                                                                // Fermeture de la police
}

void EcrireArgent()                 // Fonction d'écriture paramétrée pour afficher l'argent
{
    font = TTF_OpenFont("fonts/CollegiateFLF.ttf", 40);
    SDL_Color color = { 0,0,0 };
    SDL_Surface * surface = TTF_RenderText_Blended(font,(to_string(argent)+"$").c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 200;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { 1000-texW, 35, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void affichageTexture(SDL_Texture* texture, int x, int y)                               // Fonction d'affichage de chaque texture à la position x,y
{
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,texture,NULL,&position);
}

void cryptAffineLettres()  // Fonction de cryptage du pseudo
{
    std::string majuscule = pseudo;
    std::transform(majuscule.begin(), majuscule.end(), majuscule.begin(), ::toupper); // On met le string en majuscules
    pseudo=majuscule;
    int nblettres=pseudo.size();                                                      // La variable nblettres contient le nb de lettres du pseudo
    int a=3;
    int b=7;
    // Coeffs a et b de la fct affine du type y=ax+b

    vector<int> tableau;                                                             // On crée un tableau vide

    for (int i=0; i<nblettres; i++){
        tableau.push_back(int (pseudo.at(i))-65);                                   // On ajoute le nombre relatif au caractère ASCII avec a=0 jusqu'à z=25
        tableau[i]=((tableau[i]*a+b)%26);                                           // On applique la fct affine au nombre que l'on met modulo 26 pour obtenir un nombre correspondant à un caractère de l'alphabet
        pseudoCrypte+=char(tableau[i]+65);                                          // Le nombre est converti en caractère ASCII et ajouté au string pseudoCrypte
    }
}

void decryptAffineLettres() // Fonction de décryptage du pseudo
{
int nblettres=pseudoCrypte.size();
vector<int> tableau;

for (int i=0; i<nblettres; i++){
    tableau.push_back(int (pseudoCrypte.at(i))-65);                                 // La lettre est castée en int
    tableau[i]=(tableau[i]*9+15)%26;                                                // On remonte à la valeur de x grâce à l'image y de la fonction affine (cf dossier congruences)
    pseudoDecrypte+=char(tableau[i]+65);                                            // L'antécédent x est casté en char
    }
}

void inputPseudo()                                                                  // Fonction de saisie du pseudo
{
    SDL_StartTextInput();
    SDL_Event events;
    int continuerPseudo=1;
    bool changement=true;

    while(continuerPseudo==1 && continuer==1)                                       // Tant que l'on ne quitte pas ou clique sur retour
    {

        while(SDL_PollEvent(&events))                                               // Récupération des évènements
        {
            switch(events.type)
            {
            case SDL_QUIT :                                                         // Fermeture de la fenêtre
                continuer=0;
                break;
            case SDL_TEXTINPUT :                                                    // Saisie du texte dans la variable pseudo
                pseudo += events.text.text;
                changement=true;
                break;
            case SDL_KEYDOWN:
                if(events.key.keysym.scancode==SDL_SCANCODE_BACKSPACE && pseudo.length() > 0)   // Suppression du dernier caractère
                {
                    pseudo.pop_back();
                    changement=true;
                }
                if(events.key.keysym.scancode==SDL_SCANCODE_RETURN && pseudo.length() > 0)                             // Validation par la touche entrée
                {
                    continuerPseudo=0;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;
                if (x>437 && x<591 && y>370 && y<410 && pseudo.length()>2)                  // Si le pseudo contient 3 caractères ou plus, on peut valider
                {
                    continuerPseudo=0;
                }
                break;
            }
        }
        while (pseudo.length()>=17)                                                        // Si le pseudo contient plus de 16 caractères, on efface le 17ème saisi
        {
            //Ecrire("CollegiateInsideFLF",42,"Trop de caracteres",255,255,255,300,500);
            pseudo.pop_back();

        }
        if(changement)                                                                    // S'il y a changement, on l'écrit et l'affiche
        {
            SDL_SetRenderDrawColor(renderer, 0,127,127,255);
            SDL_RenderClear(renderer);
            affichageTexture(textureLogo,200,12);
            Ecrire("CollegiateInsideFLF",42,"Entrez un pseudo :",255,255,255,320,150);
            Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
            int longueurPseudo=pseudo.length()+1;
            Ecrire("CollegiateOutlineFLF",42,pseudo,255,255,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*11)),250); // Placement du pseudo de manière centrée en fonction de sa longueur
            changement=false;
        }
        SDL_RenderPresent(renderer);        // On rafraichit
    }
cryptAffineLettres();
}

int jeu()  // Fonction de gestion et d'affichage de la partie
{
    SDL_Event events;
    bool terminer = false;

    int xSouris, ySouris, xCase, yCase, xCaseTour=-1, yCaseTour=-1; // Variables contenant la position x,y de la souris, ainsi que de la case cliquée
    remplissageVague();

    int itterations=0;      // Variable permettant d'arreter l'affichage des vagues au bout du nombre de vagues voulu
    int creation=0;
    int numeroEnnemi=0;

    while(!terminer && continuer==1)
    {
            if(compteurImage%10==0 && depart==1 && compteurImage>150)               // Affichage des vagues en fct de la valeur du tableau vague
            {
                if (vague[numeroEnnemi]==0){
                    listeEnnemis.push_back(new EnnemiRapide(listeCases[1][1]->getXcentre()-TAILLE_ENNEMI/2,
                                                            listeCases[1][1]->getYcentre()-TAILLE_ENNEMI/2,
                                                            itterations,
                                                            xChateau,
                                                            yChateau));
                }
                else if (vague[numeroEnnemi]==1){
                    listeEnnemis.push_back(new EnnemiClassique(listeCases[1][1]->getXcentre()-TAILLE_ENNEMI/2,
                                                               listeCases[1][1]->getYcentre()-TAILLE_ENNEMI/2,
                                                               itterations,
                                                               xChateau,
                                                               yChateau));

                }
                else if (vague[numeroEnnemi]==2){
                    listeEnnemis.push_back(new EnnemiTank(listeCases[1][1]->getXcentre()-TAILLE_ENNEMI/2,
                                                          listeCases[1][1]->getYcentre()-TAILLE_ENNEMI/2,
                                                          itterations,
                                                          xChateau,
                                                          yChateau));

                }
                numeroEnnemi++;
                creation=1;             // Variable de création du premier ennemi pour éviter de remplir à nouveau le tableau vague lorsque aucun ennemi n'est affiché

            }

        if (numeroEnnemi==occurences){      // Si tous les ennemis sont affichés, on met à 0 la variable de départ
            numeroEnnemi=0;
            depart=0;
        }

         if (listeEnnemis.size()==0 && creation==1 && itterations<nbVagues-1){      // S'il n'y a plus d'ennemi dans la partie, on déchenche la vague suivante
         creation=0;
         vague.clear();
         occurences+=nbEnnemisSupplementaires*2*numLevel;             // La vague suivante contient 4 ennemis en plus
         remplissageVague();
         itterations++;

         }

        while(SDL_PollEvent(&events))       // Récupération des évènements
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_KEYUP:
                SDL_GetMouseState(&xSouris, &ySouris);         // Récupération de la position de la souris
                xCase = (xSouris-MARGE_GAUCHE)/ TAILLE_CASE;   // On définit la case sur laquelle se trouve la souris
                yCase = (ySouris-MARGE_HAUT)/ TAILLE_CASE;

                // Création manuelle des 3 types d'ennemis pour le débogage
                if(events.key.keysym.scancode==SDL_SCANCODE_Q)
                {
                    listeEnnemis.push_back(new EnnemiClassique(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                           listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2,
                                           itterations,
                                           xChateau,
                                           yChateau));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_W)
                {
                    listeEnnemis.push_back(new EnnemiRapide(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                                            listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2,
                                                            itterations,
                                                            xChateau,
                                                            yChateau));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_E)
                {
                    listeEnnemis.push_back(new EnnemiTank(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                                          listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2,
                                                          itterations,
                                                          xChateau,
                                                          yChateau));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_R)
                {
                    listeEnnemis.push_back(new EnnemiVolant(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                                            listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2,
                                                            itterations,
                                                            xChateau,
                                                            yChateau));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_1)
                {
                    listeCases[yCase][xCase]->amelioration(AMELIORATION_CADENCE);
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_2)
                {
                    listeCases[yCase][xCase]->amelioration(AMELIORATION_DEGAT_TIR);
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_3)
                {
                    listeCases[yCase][xCase]->amelioration(AMELIORATION_PORTEE_TOUR);
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_4)
                {
                    listeCases[yCase][xCase]->amelioration(AMELIORATION_VITESSE_TIR);
                }

                // Suppression manuelle de tous les ennemis
                else if(events.key.keysym.scancode==SDL_SCANCODE_RETURN)
                {
                    for(int i=0; i<listeEnnemis.size(); i++)
                    {
                        delete listeEnnemis[i];
                    }
                    listeEnnemis.clear();
                }
                // Touche Echap permettant de quitter la partie
                else if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    terminer=true;
                }
                // Création manuelle des cases / tours pour le débogage
                else if(SDL_SCANCODE_A<=events.key.keysym.scancode && events.key.keysym.scancode<=SDL_SCANCODE_Z){
                    if(listeCases[yCase][xCase]!=NULL)
                    {
                        delete listeCases[yCase][xCase];
                        listeCases[yCase][xCase]=NULL;
                    }
                    if(events.key.keysym.scancode==SDL_SCANCODE_Z)
                    {
                        listeCases[yCase][xCase]=new Case(xCase, yCase, 0);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_X)
                    {
                        listeCases[yCase][xCase]=new Chemin(xCase, yCase,0);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_C)
                    {
                        listeCases[yCase][xCase]=new Chateau(xCase, yCase, 100);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_A)
                    {
                        listeCases[yCase][xCase]=new TourClassique(xCase, yCase,-1);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_S)
                    {
                        listeCases[yCase][xCase]=new TourSniper(xCase, yCase, -1);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_D)
                    {
                        listeCases[yCase][xCase]=new TourPoison(xCase, yCase, -1);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_F)
                    {
                        listeCases[yCase][xCase]=new TourAerien(xCase, yCase, -1);
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:

                // Récupération de la position de la souris
                int x = events.button.x;
                int y = events.button.y;

                if(x>MARGE_GAUCHE && y>MARGE_HAUT)
                {
                    xCase=(x-MARGE_GAUCHE)/ TAILLE_CASE;
                    yCase=(y-MARGE_HAUT)/ TAILLE_CASE;
                    if(listeCases[yCase][xCase]!=NULL)                                      // Si la case contient qqch
                    {
                        if(listeCases[yCase][xCase]->getType()=="Case"
                                || listeCases[yCase][xCase]->getType()=="TourClassique"
                                || listeCases[yCase][xCase]->getType()=="TourSniper"
                                || listeCases[yCase][xCase]->getType()=="TourPoison")
                        {
                            // On enregistre la position de la case cliquée comme une tour
                            xCaseTour = xCase;
                            yCaseTour = yCase;
                        }
                    }
                }
                else if (x>24 && x<124 && y>21 && y<87)         // On quitte la partie avec le bp retour
                {
                    terminer=true;
                }
                else if(xCaseTour!=-1 && listeCases[yCaseTour][xCaseTour]->getType()=="Case")
                {
                    if (x>303 && x<377 && y>10 && y<86                                                  // S'il on clique sur le bp Tour Classique
                        && argent>=ARGENT_TOUR*TourClassique::multiplicateurCout)
                    {
                        //TOUR CLASSIQUE
                        if(listeCases[yCaseTour][xCaseTour]!=NULL)
                        {
                            delete listeCases[yCaseTour][xCaseTour];                                    // On supprime le contenu du tableau pour la case cliquée
                        }
                        listeCases[yCaseTour][xCaseTour]=new TourClassique(xCaseTour, yCaseTour,-1);    // On crée la tour voulue
                        argent-= ARGENT_TOUR*TourClassique::multiplicateurCout;
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                    else if (x>503 && x<577 && y>10 && y<86                                             // S'il on clique sur le bp Tour Sniper
                             && argent>=ARGENT_TOUR*TourSniper::multiplicateurCout)
                    {
                        //TOUR SNIPER
                        if(listeCases[yCaseTour][xCaseTour]!=NULL)
                        {
                            delete listeCases[yCaseTour][xCaseTour];
                        }
                        listeCases[yCaseTour][xCaseTour]=new TourSniper(xCaseTour, yCaseTour, -1);
                        argent-= ARGENT_TOUR*TourSniper::multiplicateurCout;
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                    else if (x>703 && x<777 && y>10 && y<86                                             // S'il on clique sur le bp Tour Poison
                             && argent>=ARGENT_TOUR*TourPoison::multiplicateurCout)
                    {
                        //TOUR POISON
                        if(listeCases[yCaseTour][xCaseTour]!=NULL)
                        {
                            delete listeCases[yCaseTour][xCaseTour];
                        }
                        listeCases[yCaseTour][xCaseTour]=new TourPoison(xCaseTour, yCaseTour, -1);
                        argent-= ARGENT_TOUR*TourPoison::multiplicateurCout;
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                    else if (x>200 && x<280 && y>10 && y<90)                                            // Bp annuler pour pouvoir sélectionner une autre tour
                    {
                        //ANNULER CASE
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                }


                // Si la case est l'une des 3 tours, on peut effectuer des actions sur ces tours
                else if(xCaseTour!=-1 && (listeCases[yCaseTour][xCaseTour]->getType()=="TourClassique"
                                          || listeCases[yCaseTour][xCaseTour]->getType()=="TourSniper"
                                          || listeCases[yCaseTour][xCaseTour]->getType()=="TourPoison"))
                {

                    if (x>500 && x<580 && y>10 && y<90)
                    {
                        //ANNULER TOUR
                        xCaseTour = -1;
                        yCaseTour = -1;
                        affichageArgent=1;
                    }
                    else if (x>400 && x<480 && y>10 && y<90)
                    {
                        //EFFACER TOUR
                        delete listeCases[yCaseTour][xCaseTour];
                        listeCases[yCaseTour][xCaseTour]=new Case(xCaseTour, yCaseTour, 0);
                        xCaseTour = -1;
                        yCaseTour = -1;
                        affichageArgent=1;
                    }
                    ///// AMELIORATIONS /////
                    else if(x>600 && x<680 && y>10 && y<90)
                    {
                        listeCases[yCaseTour][xCaseTour]->amelioration(AMELIORATION_CADENCE);
                        xCaseTour = -1;
                        yCaseTour = -1;
                        affichageArgent=1;
                    }
                    else if(x>700 && x<780 && y>10 && y<90)
                    {
                        listeCases[yCaseTour][xCaseTour]->amelioration(AMELIORATION_DEGAT_TIR);
                        xCaseTour = -1;
                        yCaseTour = -1;
                        affichageArgent=1;
                    }
                    else if(x>800 && x<880 && y>10 && y<90)
                    {
                        listeCases[yCaseTour][xCaseTour]->amelioration(AMELIORATION_PORTEE_TOUR);
                        xCaseTour = -1;
                        yCaseTour = -1;
                        affichageArgent=1;
                    }
                    else if(x>900 && x<980 && y>10 && y<90)
                    {
                        listeCases[yCaseTour][xCaseTour]->amelioration(AMELIORATION_VITESSE_TIR);
                        xCaseTour = -1;
                        yCaseTour = -1;
                        affichageArgent=1;
                    }
                }
            }
        }

        // ACTIONS // Placement des tours en direction des ennemis et tirs pour les détruire
        for(int y=0 ; y<TAILLE_Y_PLATEAU ; y++)
        {
            for(int x=0 ; x<TAILLE_X_PLATEAU ; x++)
            {
                if(listeCases[y][x]!=NULL)
                {
                    listeCases[y][x]->action();
                }
            }
        }

        for(int i=0; i<listeEnnemis.size(); i++)
        {
            listeEnnemis[i]->action();
        }
        for(int i=0; i<listeTirs.size(); i++)
        {
            listeTirs[i]->action();
        }

        // AFFICHAGE //

        SDL_SetRenderDrawColor(renderer, 0,127,127,255);    // Couleur de fond du plateau
        SDL_RenderClear(renderer);

        // Création de la zone contenant les boutons
        SDL_SetRenderDrawColor(renderer, 0, 127, 147, 255);
        SDL_Rect rect = {150,5,860,90};
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);

        // On trace le rectangle
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer,150,5,1010,5);
        SDL_RenderDrawLine(renderer,150,95,1010,95);
        SDL_RenderDrawLine(renderer,150,5,150,95);
        SDL_RenderDrawLine(renderer,1010,5,1010,95);


        // Affichage des cases (tours, chemin, chateau ...)
        for(int y=0 ; y<TAILLE_Y_PLATEAU ; y++)
        {
            for(int x=0 ; x<TAILLE_X_PLATEAU ; x++)
            {
                if(listeCases[y][x]!=NULL)
                {
                    listeCases[y][x]->affiche();
                }
            }
        }

        // Affichage des ennemis et des tirs
        for(int i=0; i<listeEnnemis.size(); i++)
        {
            listeEnnemis[i]->affiche();
        }
        for(int i=0; i<listeTirs.size(); i++)
        {
            listeTirs[i]->affiche();
        }

        if (affichageArgent==1){
        EcrireArgent(); }// Ecriture et affichage de l'argent

        SDL_GetMouseState(&xSouris, &ySouris);

        // Affichage de la portée par un cercle lorsque le pointeur est sur une tour
        if (xSouris>MARGE_GAUCHE && ySouris > MARGE_HAUT)
        {
            xCase = (xSouris-MARGE_GAUCHE)/ TAILLE_CASE;
            yCase = (ySouris-MARGE_HAUT)/ TAILLE_CASE;

            if(listeCases[yCase][xCase]!=NULL)
            {
                listeCases[yCase][xCase]->affichePortee();
            }
        }

        // Si l'on sélectionne une case, elle est encadrée en rouge
        if (xCaseTour!=-1)
        {
            SDL_SetRenderDrawColor(renderer, 255,0,0,100);
            {
                SDL_Point points[5] = {{MARGE_GAUCHE+TAILLE_CASE*xCaseTour, MARGE_HAUT+TAILLE_CASE*yCaseTour},
                    {MARGE_GAUCHE+TAILLE_CASE*(xCaseTour+1), MARGE_HAUT+TAILLE_CASE*yCaseTour},
                    {MARGE_GAUCHE+TAILLE_CASE*(xCaseTour+1), MARGE_HAUT+TAILLE_CASE*(yCaseTour+1)},
                    {MARGE_GAUCHE+TAILLE_CASE*xCaseTour, MARGE_HAUT+TAILLE_CASE*(yCaseTour+1)},
                    {MARGE_GAUCHE+TAILLE_CASE*xCaseTour, MARGE_HAUT+TAILLE_CASE*yCaseTour}
                };
                SDL_RenderDrawLines(renderer, points, 5);
            }
            {
                SDL_Point points[5] = {{MARGE_GAUCHE+TAILLE_CASE*xCaseTour+1, MARGE_HAUT+TAILLE_CASE*yCaseTour+1},
                    {MARGE_GAUCHE+TAILLE_CASE*(xCaseTour+1)-1, MARGE_HAUT+TAILLE_CASE*yCaseTour+1},
                    {MARGE_GAUCHE+TAILLE_CASE*(xCaseTour+1)-1, MARGE_HAUT+TAILLE_CASE*(yCaseTour+1)-1},
                    {MARGE_GAUCHE+TAILLE_CASE*xCaseTour+1, MARGE_HAUT+TAILLE_CASE*(yCaseTour+1)-1},
                    {MARGE_GAUCHE+TAILLE_CASE*xCaseTour+1, MARGE_HAUT+TAILLE_CASE*yCaseTour+1}
                };
                SDL_RenderDrawLines(renderer, points, 5);
            }

            // Affichage du prix de chaque tour + texture des tours
            if(listeCases[yCaseTour][xCaseTour]->getType()=="Case")
            {
                affichageArgent=1;
                affichageTexture(textureBpAnnuler,200,10);
                affichageTexture(textureBpTourClassique,300,10);
                Ecrire("CollegiateInsideFLF",20,to_string(ARGENT_TOUR*TourClassique::multiplicateurCout)+"$",0,0,0,380,40);
                affichageTexture(textureBpTourSniper,500,10);
                Ecrire("CollegiateInsideFLF",20,to_string(ARGENT_TOUR*TourSniper::multiplicateurCout)+"$",0,0,0,580,40);
                affichageTexture(textureBpTourPoison,700,10);
                Ecrire("CollegiateInsideFLF",20,to_string(ARGENT_TOUR*TourPoison::multiplicateurCout)+"$",0,0,0,780,40);
            }
            else
            {
                affichageArgent=0;

                // Affichage du nom de la tour
                if (listeCases[yCaseTour][xCaseTour]->getType()=="TourClassique"){
                    Ecrire("CollegiateInsideFLF",25,"Tour Classique :",0,0,0,180,15);
                }

                else if (listeCases[yCaseTour][xCaseTour]->getType()=="TourSniper"){
                    Ecrire("CollegiateInsideFLF",25,"Tour Sniper :",0,0,0,180,15);
                }

                else if (listeCases[yCaseTour][xCaseTour]->getType()=="TourPoison"){
                    Ecrire("CollegiateInsideFLF",25,"Tour Poison :",0,0,0,180,15);
                }

                affichageTexture(textureBpEffacer,400,10);
                affichageTexture(textureBpAnnuler,500,10);
                affichageTexture(textureCadence,600,10);
                affichageTexture(textureDegatTir,700,10);
                affichageTexture(texturePorteeTour,800,10);
                affichageTexture(textureVitesseTir,900,10);
            }
        }
        else
        {
            affichageTexture(textureLogo,250,12); // Affichage du logo Tower Defense
        }

        // Affichage du bp retour
        Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
        Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);

        if (listeCases[yChateau][xChateau]->action()==1){                               // Si le chateau n'a plus de vie
            compteurImage=0;

            while (compteurImage<150){                                      // Affichage du fond Game Over pendant 5s
                SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                SDL_RenderClear(renderer);
                Ecrire("CollegiateBlackFLF",42,"GAME OVER",255,255,255,440,300);
                SDL_RenderPresent(renderer);
                SDL_Delay(30);
                compteurImage++;
            }
            terminer=true;      // On quitte la partie
        }
        // Rafraichissement de l'écran toutes les 30 ms
        SDL_RenderPresent(renderer);
        SDL_Delay(rafraichissement);
        compteurImage++;


    }
    // Suppression des listes ennemis et tirs
    for(int i=listeEnnemis.size()-1; i>=0; i--)
    {
        delete listeEnnemis[i];
    }
    for(int i=listeTirs.size()-1; i>=0; i--)
    {
        delete listeTirs[i];
    }

    return 0;

}

void initListeCase()  // Initialisation des cases vides
{
    listeCases = new Case**[TAILLE_Y_PLATEAU];
    for(int y=0; y<TAILLE_Y_PLATEAU; y++)
    {
        listeCases[y]=new Case*[TAILLE_X_PLATEAU];
    }
    for(int y=0; y<TAILLE_Y_PLATEAU; y++)
    {
        for(int x=0; x<TAILLE_X_PLATEAU; x++)
        {
            listeCases[y][x]=NULL;
        }
    }
}

void initLevel(int numLevel) // Remplissage des cases en fonction des chiffres du fichier level.txt
{
    quitListeCase();

    // On ouvre le fichier level.txt
    string nomLvl= CHEMIN_LEVELS + "level" + to_string(numLevel) + ".txt";
    ifstream level(nomLvl.c_str(), ios::in);
    string ligne;
    int y=0;

    // On récupère la taille du plateau
    getline(level, ligne);
    TAILLE_X_PLATEAU=stoi(ligne);
    getline(level, ligne);
    TAILLE_Y_PLATEAU=stoi(ligne);
    initListeCase();

    // La taille de la fenêtre est adaptée à la taille du plateau
    SDL_SetWindowSize(fenetre,TAILLE_X_PLATEAU*TAILLE_CASE + MARGE_GAUCHE, TAILLE_Y_PLATEAU*TAILLE_CASE + MARGE_HAUT);

    // Chaque case est crée en fonction de son type
    while(getline(level, ligne))
    {
        for(int x=0; x<ligne.length(); x++)
        {
            if(ligne.at(x)=='1')
            {
                listeCases[y][x]=new Case(x, y, 0 );
            }
            else if(ligne.at(x)=='2')
            {
                listeCases[y][x]=new Chemin(x, y, 0);

            }
            else if(ligne.at(x)=='7')
            {
                listeCases[y][x]=new Chemin(x, y, 1);

            }
            else if(ligne.at(x)=='3')
            {
                listeCases[y][x]=new Chateau(x, y, 100);
                xChateau=x;
                yChateau=y;
            }
            else if(ligne.at(x)=='4')
            {
                listeCases[y][x]=new TourClassique(x, y, 100);
            }
            else if(ligne.at(x)=='5')
            {
                listeCases[y][x]=new TourSniper(x, y, 100);
            }
            else if(ligne.at(x)=='6')
            {
                listeCases[y][x]=new TourPoison(x, y, 100);
            }
        }
        y++;
    }
    jeu(); // Le jeu débute
}

void choixLevel() // Fonction de choix du niveau
{
    // Affichage des éléments graphiques sur la fenêtre
    numLevel=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);
    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
    Ecrire("Arial",65,"+",255,255,255,640,232);
    Ecrire("Arial",65,"-",255,255,255,610,226);
    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
    Ecrire("CollegiateInsideFLF",45,"NIVEAU 1",255,255,255,350,250);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    SDL_RenderPresent(renderer);

    SDL_Event events;
    int continuerLevel=1;

    while(continuerLevel==1 && continuer==1)
    {

        while(SDL_PollEvent(&events))  // Récupération des évènements
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;
            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)   // Revenir en arrière avec le bp Echap
                {
                    continuerLevel=0;
                }
                break;

            case SDL_QUIT :                                          // Quitter le jeu
                continuer=0;
                break;

            case SDL_MOUSEBUTTONUP:

                // Récupération du clic
                int x = events.button.x;
                int y = events.button.y;
                //std::cout << x << SDL_GetError() << std::endl;
                //std::cout << y << SDL_GetError() << std::endl;


                // Si le joueur sélectionne le niveau suivant
                if (x>638 && x<678 && y>250 && y<285)
                {
					numLevel++;
					ifstream fichier(CHEMIN_LEVELS+"level"+to_string(numLevel)+".txt");
					if(!fichier.is_open()){
						numLevel--;
					}
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
                    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
                    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
                    Ecrire("Arial",65,"+",255,255,255,640,232);
                    Ecrire("Arial",65,"-",255,255,255,610,226);
                    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
                    Ecrire("CollegiateInsideFLF",45,"NIVEAU " + to_string(numLevel),255,255,255,350,250);
                    SDL_RenderPresent(renderer);
                }

                // Si le joueur sélectionne le niveau précédent
                if (numLevel>1 && x>607 && x<633 && y>260 && y<278)
                {
                    numLevel--;
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
                    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
                    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
                    Ecrire("Arial",65,"+",255,255,255,640,232);
                    Ecrire("Arial",65,"-",255,255,255,610,226);
                    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
                    Ecrire("CollegiateInsideFLF",45,"NIVEAU " + to_string(numLevel),255,255,255,350,250);
                    SDL_RenderPresent(renderer);
                }

                // Validation du choix
                else if (x>437 && x<585 && y>370 && y<410)
                {
                    continuerLevel=0;
                    initLevel(numLevel);
                }

                // Clic sur le bp retour
                else if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerLevel=0;
                }
                break;
            }
        }
    }
}

void aide()
{
    // Affichage des éléments graphiques
    SDL_Event events;
    int continuerAide=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    Ecrire("CollegiateInsideFLF",50,"AIDE",255,255,255,450,50);
    SDL_RenderPresent(renderer);

    string nomfichier= "regles.txt";                    // String contenant le nom du fichier et son extension
    fstream fichier(nomfichier.c_str(), ios::in);      // Ouverture du fichier regles
    string ligne;
    int saut=0;
    if (fichier)                                       // Si le fichier existe ...
    {

    while(getline(fichier, ligne))                      // Affichage des règles du jeu
    {
     Ecrire("BKANT",28,ligne,255,255,255,50,(137+saut));
     saut+=30;
    }

    SDL_RenderPresent(renderer);
    fichier.close();
    }

    while (continuerAide==1 && continuer==1)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    continuerAide=0;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;

                if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerAide=0;
                }
                break;
            }
        }
    }
}

void menu()
{
    SDL_Event events;
    int continuerMenu=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);
    // Récupération du nombre de parties dans le fichier infos.txt
    string nomfichier= "infos.txt";                    // String contenant le nom du fichier et son extension
    fstream fichier(nomfichier.c_str(), ios::in);      // Ouverture du fichier info
    int nbPartiesDecrypte=0;
    int argentDecrypte=0;
    string ligne;
    string argentCrypte="";
    if (fichier)                                       // Si le fichier existe ...
    {
        fichier>>nbParties;
        nbPartiesDecrypte=decryptShadok(nbParties);
        fichier>>ligne;
        fichier>>argentCrypte;
        argentDecrypte=decryptShadok(argentCrypte);
        fichier.close();
    }

    // Affichage des éléments graphiques
    Ecrire("CollegiateInsideFLF",25,"Pseudo : " + pseudo,255,255,255,30,200);
    Ecrire("CollegiateInsideFLF",50,"MENU",255,255,255,450,50);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    Ecrire("CollegiateInsideFLF",25,"Nombre de parties jouees : " + to_string(nbPartiesDecrypte),255,255,255,30,150);
    Ecrire("CollegiateInsideFLF",25,"Argent : " + to_string(argentDecrypte)+" $",255,255,255,30,250);
    SDL_RenderPresent(renderer);

    while (continuerMenu==1 && continuer==1)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    continuerMenu=0;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;

                // Clic sur le bp retour
                if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerMenu=0;
                }
                break;
            }
        }
    }
}

void debut() // Affichage de l'écran initial
{
    inputPseudo();  // Saisie du pseudo
    int longueurPseudo=pseudo.length()+8;
    affichageTexture(textureAccueil,0,0); // Affichage de l'image d'accueil
    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0); // Affichage du pseudo du joueur
    SDL_RenderPresent(renderer);
    SDL_Event events;
    int continuerDebut=1;

    while(continuerDebut==1 && continuer==1)
    {
        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {

            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONDOWN:
                continue;
                break;

            case SDL_KEYUP:
                if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    continuerDebut=0;
                }
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_MOUSEBUTTONUP:

                // Récupération des clics et affichage du menu suivant en conséquence //
                int x = events.button.x;
                int y = events.button.y;

                if (x>507 && x<726 && y>669 && y<763)
                {
                    // MENU //
                    menu();
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (x>45 && x<428 && y>670 && y<763)
                {
                    // COMMENCER //
                    choixLevel();
                    SDL_SetWindowSize(fenetre,20*TAILLE_CASE + MARGE_GAUCHE, 15*TAILLE_CASE + MARGE_HAUT);
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (x>807 && x<990 && y>669 && y<763)
                {
                    // AIDE //
                    aide();
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                break;
            }
        }
    }
}

int initSDL()
{

    // Initialisation de la SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    if(TTF_Init() == -1)
    {
        cout << "Erreur d'initialisation de TTF_Init : "<< TTF_GetError()<<endl;
        return -1;
    }

    // Création de la fenêtre
    fenetre = SDL_CreateWindow("Tower Defense SDL 2.0",
                               SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED,
                               TAILLE_X_PLATEAU*TAILLE_CASE + MARGE_GAUCHE,
                               TAILLE_Y_PLATEAU*TAILLE_CASE + MARGE_HAUT,
                               SDL_WINDOW_SHOWN);
    if(fenetre == 0)
    {
        cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << endl;
        SDL_Quit();
        return -1;
    }

    //Création du renderer
    renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if(renderer==NULL)
    {
        cout << "Erreur lors de la creation du renderer : " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;

    }
    SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );


    //Surface pour charger toutes les textures
    SDL_Surface* surface;

    surface=IMG_Load((CHEMIN_IMAGES+"bpAmeliorationCadence.png").c_str());
    textureCadence= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpAmeliorationDegatTir.png").c_str());
    textureDegatTir= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpAmeliorationPorteeTour.png").c_str());
    texturePorteeTour= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpAmeliorationVitesseTir.png").c_str());
    textureVitesseTir= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpTourClassique.png").c_str());
    textureBpTourClassique= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpTourSniper.png").c_str());
    textureBpTourSniper= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpTourPoison.png").c_str());
    textureBpTourPoison= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpEffacer.png").c_str());
    textureBpEffacer= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"bpAnnuler.png").c_str());
    textureBpAnnuler= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"logo.png").c_str());
    textureLogo= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"towerDefense.png").c_str());
    textureAccueil= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"case.png").c_str());
    textureCase= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"chemin.png").c_str());
    textureChemin= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"chateau.png").c_str());
    textureChateau= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tourClassiqueBase.png").c_str());
    textureTourClassiqueBase= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tourSniperBase.png").c_str());
    textureTourSniperBase= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tourPoisonBase.png").c_str());
    textureTourPoisonBase= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tourClassiqueCanon.png").c_str());
    textureTourClassiqueCanon= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tourSniperCanon.png").c_str());
    textureTourSniperCanon= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"ennemiClassique.png").c_str());
    textureEnnemiClassique= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"ennemiRapide.png").c_str());
    textureEnnemiRapide= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"ennemiTank.png").c_str());
    textureEnnemiTank= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"ennemiVolant.png").c_str());
    textureEnnemiVolant= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tirClassique.png").c_str());
    textureTirClassique= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tirSniper.png").c_str());
    textureTirSniper= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    for(int i=0;i<TEMPS_ANIM_TIR;i++){
        surface=IMG_Load((CHEMIN_IMAGES+"explosion"+to_string(i)+".png").c_str());
        textureExplosion[i]= SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);
    }

    return 1;
}

int main(int argc, char **argv) // Boucle principale avec appel de chaque fonction jusqu'à la fermeture du jeu
{
    initSDL();
    initListeCase();
    debut();
    quitListeCase();
    infos();
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
