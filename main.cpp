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

SDL_Window *fenetre;
SDL_Renderer *renderer;
SDL_Texture  *textureCase,
             *textureChemin,
             *textureChateau,

             *textureTourClassiqueBase,
             *textureTourPoisonBase,
             *textureTourSniperBase,

             *textureTourClassiqueCanon,
             *textureTourPoisonCanon,
             *textureTourSniperCanon,

             *textureEnnemiClassique,
             *textureEnnemiRapide,
             *textureEnnemiTank,
             *textureEnnemiVolant,

             *textureTirClassique,
             *textureTirPoison,
             *textureTirSniper,

             *textureBpTourSniper,
             *textureBpTourClassique,
             *textureBpTourPoison,
             *textureBpEffacer,
             *textureBpAnnuler,

             *textureAccueil,
             *textureLogo;
TTF_Font *font;

#include "Case.h"
#include "TourClassique.h"
#include "TourSniper.h"
#include "TourPoison.h"
#include "Chemin.h"
#include "Chateau.h"
#include "EnnemiTank.h"
#include "EnnemiRapide.h"
#include "EnnemiClassique.h"
#include "EnnemiVolant.h"
#include "TirClassique.h"
#include "TirSniper.h"
#include "TirPoison.h"


#include "Constantes.h"
#include "Variables.h"
#include "VariablesSDL.h"
vector<int> vague;
Case*** listeCases;
vector<Ennemi*> listeEnnemis;
vector<Tir*> listeTirs;

string messageCrypte="";
string messageDecrypte="";
int nbVagues=10;
int depart=0;
int occurences=10;
int argent;
int num=1;
int continuer=1;
int nbParties=0;
int TAILLE_X_PLATEAU = 20;
int TAILLE_Y_PLATEAU = 15;
string pseudo ="";
int compteurEnnemiVague=0,
    compteurImage=0;
int xVague=-1,
    yVague=-1;


void quitListeCase()
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

void remplissageVague(){
    for (int i=0; i<occurences; i++){
        vague.push_back(rand()%3);
    }
    depart=1;
}

void infos()
{
    nbParties=-42;
    string nomfichier= "infos.txt";
    fstream fichier(nomfichier.c_str(), ios::in);
    if (fichier)
    {
        fichier>>nbParties;
        fichier.close();
        fichier.open(nomfichier.c_str(),ios::out | ios::trunc);
        //récupere le nombre de partie (automatiquement converti en int (car nbPartie est iun int))
        ++nbParties;
        fichier<<(nbParties); //incrémente puis écrit dans le fihier (automatiquement converti en string)
        fichier<<("\n");
        fichier<<(messageCrypte);
        fichier<<("\n");
        fichier<<(argent);
        fichier<<("\n");
    }
}

void Ecrire(string police, int taille, string texte, int r, int v, int b, int x, int y)
{
    font = TTF_OpenFont(("fonts/" + police + ".ttf").c_str(), taille);
    SDL_Color color = { r, v, b };
    SDL_Surface * surface = TTF_RenderText_Blended(font,texte.c_str(), color);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

    int texW = 0;
    int texH = 200;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    SDL_Rect dstrect = { x, y, texW, texH };
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);

    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}

void EcrireArgent(){
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

void affichageTexture(SDL_Texture* texture, int x, int y)
{
    SDL_Rect position;
    position.x = x;
    position.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
    SDL_RenderCopy(renderer,texture,NULL,&position);
}

void cryptAffine(){
    std::string majuscule = pseudo;
    std::transform(majuscule.begin(), majuscule.end(), majuscule.begin(), ::toupper);
    pseudo=majuscule;
    int nblettres=pseudo.size();
    int a=17;
    int b=23;
    vector<int> tableau;


    for (int i=0; i<nblettres; i++){
        tableau.push_back(int (pseudo.at(i))-65);
        tableau[i]=((tableau[i]*a+b)%26);
        messageCrypte+=char(tableau[i]+65);
    }
}

void decryptAffine(){
int a=17;
int b=3;
int nblettres=messageCrypte.size();
vector<int> tableau;

for (int i=0; i<nblettres; i++){
    tableau.push_back(int (messageCrypte.at(i))-65);
    tableau[i]=(tableau[i]*9+15)%26;
    messageDecrypte+=char(tableau[i]+65);
}
cout<<messageDecrypte<<endl;
}

void inputPseudo()
{
    SDL_StartTextInput();
    SDL_Event events;
    int continuerPseudo=1;
    bool changement=true;

    while(continuerPseudo==1 && continuer==1)
    {

        while(SDL_PollEvent(&events))
        {
            switch(events.type)
            {
            case SDL_QUIT :
                continuer=0;
                break;
            case SDL_TEXTINPUT :
                pseudo += events.text.text;
                changement=true;
                break;
            case SDL_KEYDOWN:
                if(events.key.keysym.scancode==SDL_SCANCODE_BACKSPACE && pseudo.length() > 0)
                {
                    pseudo.pop_back();
                    changement=true;
                }
                if(events.key.keysym.scancode==SDL_SCANCODE_RETURN)
                {
                    continuerPseudo=0;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                int x = events.button.x;
                int y = events.button.y;
                if (x>437 && x<591 && y>370 && y<410 && pseudo.length()>2)
                {
                    continuerPseudo=0;
                }
                break;
            }
        }
        while (pseudo.length()>=17)
        {
            Ecrire("CollegiateInsideFLF",42,"Trop de caracteres",255,255,255,300,500);
            pseudo.pop_back();

        }
        if(changement)
        {
            SDL_SetRenderDrawColor(renderer, 0,127,127,255);
            SDL_RenderClear(renderer);
            affichageTexture(textureLogo,200,12);
            Ecrire("CollegiateInsideFLF",42,"Entrez un pseudo :",255,255,255,320,150);
            Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
            int longueurPseudo=pseudo.length()+1;
            Ecrire("CollegiateOutlineFLF",42,pseudo,255,255,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*11)),250);
            changement=false;
        }
        SDL_RenderPresent(renderer);
    }
cryptAffine();

}

int jeu()
{
    SDL_Event events;
    bool terminer = false;

    argent=200;
    int xSouris, ySouris, xCase, yCase, xCaseTour=-1, yCaseTour=-1;
    remplissageVague();
    int itterations=0;
    int creation=0;
    int numeroEnnemi=0;
    while(!terminer && continuer==1)
    {

            if(compteurImage%10==0 && depart==1 && compteurImage>150)
            {
                if (vague[numeroEnnemi]==0){
                    listeEnnemis.push_back(new EnnemiRapide(listeCases[1][1]->getXcentre()-TAILLE_ENNEMI/2,
                       listeCases[1][1]->getYcentre()-TAILLE_ENNEMI/2));
                }
                else if (vague[numeroEnnemi]==1){
                    listeEnnemis.push_back(new EnnemiClassique(listeCases[1][1]->getXcentre()-TAILLE_ENNEMI/2,
                       listeCases[1][1]->getYcentre()-TAILLE_ENNEMI/2));

                }
                else if (vague[numeroEnnemi]==2){
                    listeEnnemis.push_back(new EnnemiTank(listeCases[1][1]->getXcentre()-TAILLE_ENNEMI/2,
                       listeCases[1][1]->getYcentre()-TAILLE_ENNEMI/2));

                }
                numeroEnnemi++;
                creation=1;

            }

        if (numeroEnnemi==occurences){
            numeroEnnemi=0;
            depart=0;
        }


         if (listeEnnemis.size()==0 && creation==1 && itterations<nbVagues-1){
         creation=0;
         vague.clear();
         occurences+=5;
         remplissageVague();
         itterations++;

         }

        //listeEnnemis.push_back(new Ennemi(10,10, textureEnnemiClassique, -1,-1,-1));
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
                SDL_GetMouseState(&xSouris, &ySouris);
                xCase = (xSouris-MARGE_GAUCHE)/ TAILLE_CASE;
                yCase = (ySouris-MARGE_HAUT)/ TAILLE_CASE;

                if(events.key.keysym.scancode==SDL_SCANCODE_T)
                {
                    //listeEnnemis.push_back(new Ennemi(xSouris-TAILLE_ENNEMI/2, ySouris-TAILLE_ENNEMI/2, textureEnnemiClassique, -1,-1,-1));
                    listeEnnemis.push_back(new EnnemiClassique(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                           listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_E)
                {
                    listeEnnemis.push_back(new EnnemiRapide(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                                            listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_Y)
                {
                    listeEnnemis.push_back(new EnnemiTank(listeCases[yCase][xCase]->getXcentre()-TAILLE_ENNEMI/2,
                                                          listeCases[yCase][xCase]->getYcentre()-TAILLE_ENNEMI/2));
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_V)
                {
                    xVague=xCase;
                    yVague=yCase;
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_R)
                {
                    for(int i=0; i<listeEnnemis.size(); i++)
                    {
                        delete listeEnnemis[i];
                    }
                    listeEnnemis.clear();
                }
                else if(events.key.keysym.scancode==SDL_SCANCODE_ESCAPE)
                {
                    terminer=true;
                }

                else if(SDL_SCANCODE_KP_1<=events.key.keysym.scancode && events.key.keysym.scancode<=SDL_SCANCODE_KP_9)
                {
                    if(listeCases[yCase][xCase]!=NULL)
                    {
                        delete listeCases[yCase][xCase];
                        listeCases[yCase][xCase]=NULL;
                    }
                    if(events.key.keysym.scancode==SDL_SCANCODE_KP_1)
                    {
                        listeCases[yCase][xCase]=new Case(xCase, yCase, 0);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_KP_2)
                    {
                        listeCases[yCase][xCase]=new Chemin(xCase, yCase,0);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_KP_4)
                    {
                        listeCases[yCase][xCase]=new TourClassique(xCase, yCase,-1);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_KP_5)
                    {
                        listeCases[yCase][xCase]=new TourSniper(xCase, yCase, -1);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_KP_6)
                    {
                        listeCases[yCase][xCase]=new TourPoison(xCase, yCase, -1);
                    }
                    else if(events.key.keysym.scancode==SDL_SCANCODE_KP_3)
                    {
                        listeCases[yCase][xCase]=new Chateau(xCase, yCase, 100);
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:

                int x = events.button.x;
                int y = events.button.y;

                if(x>MARGE_GAUCHE && y>MARGE_HAUT)
                {
                    xCase=(x-MARGE_GAUCHE)/ TAILLE_CASE;
                    yCase=(y-MARGE_HAUT)/ TAILLE_CASE;
                    if(listeCases[yCase][xCase]!=NULL)
                    {
                        if(listeCases[yCase][xCase]->getType()=="Case"
                                || listeCases[yCase][xCase]->getType()=="TourClassique"
                                || listeCases[yCase][xCase]->getType()=="TourSniper"
                                || listeCases[yCase][xCase]->getType()=="TourPoison")
                        {
                            xCaseTour = xCase;
                            yCaseTour = yCase;
                        }
                    }
                }
                else if (x>24 && x<124 && y>21 && y<87)
                {
                    terminer=true;
                }
                else if(xCaseTour!=-1 && listeCases[yCaseTour][xCaseTour]->getType()=="Case")
                {
                    if (x>303 && x<377 && y>10 && y<86
                        && argent>=ARGENT_TOUR*TourClassique::multiplicateurCout)
                    {
                        //TOUR CLASSIQUE
                        if(listeCases[yCaseTour][xCaseTour]!=NULL)
                        {
                            delete listeCases[yCaseTour][xCaseTour];
                        }
                        listeCases[yCaseTour][xCaseTour]=new TourClassique(xCaseTour, yCaseTour,-1);
                        argent-= ARGENT_TOUR*TourClassique::multiplicateurCout;
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                    else if (x>503 && x<577 && y>10 && y<86
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
                    else if (x>703 && x<777 && y>10 && y<86
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
                    else if (x>200 && x<280 && y>10 && y<90)
                    {
                        //ANNULER CASE
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                }
                else if(xCaseTour!=-1 && (listeCases[yCaseTour][xCaseTour]->getType()=="TourClassique"
                                          || listeCases[yCaseTour][xCaseTour]->getType()=="TourSniper"
                                          || listeCases[yCaseTour][xCaseTour]->getType()=="TourPoison"))
                {
                    if (x>500 && x<580 && y>10 && y<90)
                    {
                        //ANNULER TOUR
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                    else if (x>400 && x<480 && y>10 && y<90)
                    {
                        //EFFACER TOUR
                        delete listeCases[yCaseTour][xCaseTour];
                        listeCases[yCaseTour][xCaseTour]=new Case(xCaseTour, yCaseTour, 0);
                        xCaseTour = -1;
                        yCaseTour = -1;
                    }
                }
            }
        }

        //actions
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

        //affichage;

        SDL_SetRenderDrawColor(renderer, 0,127,127,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 127, 147, 255);
        SDL_Rect rect = {150,5,860,90};
        SDL_RenderDrawRect(renderer, &rect);
        SDL_RenderFillRect(renderer, &rect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderDrawLine(renderer,150,5,1010,5);
        SDL_RenderDrawLine(renderer,150,95,1010,95);
        SDL_RenderDrawLine(renderer,150,5,150,95);
        SDL_RenderDrawLine(renderer,1010,5,1010,95);

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
        for(int i=0; i<listeEnnemis.size(); i++)
        {
            listeEnnemis[i]->affiche();
        }
        for(int i=0; i<listeTirs.size(); i++)
        {
            listeTirs[i]->affiche();
        }
        EcrireArgent();

        SDL_GetMouseState(&xSouris, &ySouris);
        if (xSouris>MARGE_GAUCHE && ySouris > MARGE_HAUT)
        {
            xCase = (xSouris-MARGE_GAUCHE)/ TAILLE_CASE;
            yCase = (ySouris-MARGE_HAUT)/ TAILLE_CASE;

            if(listeCases[yCase][xCase]!=NULL)
            {
                listeCases[yCase][xCase]->affichePortee();
            }
        }

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
            if(listeCases[yCaseTour][xCaseTour]->getType()=="Case")
            {
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
                string type=listeCases[yCaseTour][xCaseTour]->getType();  //C'est plus simple
                Ecrire("CollegiateInsideFLF",25,type.substr(0,4)+" "+type.substr(4),0,0,0,180,15);
                /*if (listeCases[yCaseTour][xCaseTour]->getType()=="TourClassique"){
                    Ecrire("CollegiateInsideFLF",25,"Tour Classique :",0,0,0,180,15);
                }

                else if (listeCases[yCaseTour][xCaseTour]->getType()=="TourSniper"){
                    Ecrire("CollegiateInsideFLF",25,"Tour Sniper :",0,0,0,180,15);
                }

                else if (listeCases[yCaseTour][xCaseTour]->getType()=="TourPoison"){
                    Ecrire("CollegiateInsideFLF",25,"Tour Poison :",0,0,0,180,15);
                }*/

                affichageTexture(textureBpEffacer,400,10);
                affichageTexture(textureBpAnnuler,500,10);
            }
        }
        else
        {
            affichageTexture(textureLogo,250,12);
            //Ecrire("CollegiateInsideFLF",50,"TOWER DEFENSE",0,49,192,330,27);
        }

        Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
        Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
        if (listeCases[13][16]->action()==1){
            compteurImage=0;

            while (compteurImage<150){                                      // Affichage du fond Game Over pendant 5s
                SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                SDL_RenderClear(renderer);
                Ecrire("CollegiateBlackFLF",42,"GAME OVER",255,255,255,440,300);
                SDL_RenderPresent(renderer);
                SDL_Delay(30);
                compteurImage++;
            }
            terminer=true;
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
        compteurImage++;


    }


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

void initListeCase()
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

void initLevel(int numLevel)
{

    quitListeCase();

    string nomLvl= CHEMIN_LEVELS + "level" + to_string(numLevel) + ".txt";
    ifstream level(nomLvl.c_str(), ios::in);
    int y=0;
    string ligne;

    getline(level, ligne);
    TAILLE_X_PLATEAU=stoi(ligne);
    getline(level, ligne);
    TAILLE_Y_PLATEAU=stoi(ligne);
    initListeCase();

    SDL_SetWindowSize(fenetre,TAILLE_X_PLATEAU*TAILLE_CASE + MARGE_GAUCHE, TAILLE_Y_PLATEAU*TAILLE_CASE + MARGE_HAUT);

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
    jeu();
}

void choixLevel()
{
    num=1;
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
                    continuerLevel=0;
                }
                break;

            case SDL_QUIT :
                continuer=0;
                break;

            case SDL_MOUSEBUTTONUP:

                int x = events.button.x;
                int y = events.button.y;
                //std::cout << x << SDL_GetError() << std::endl;
                //std::cout << y << SDL_GetError() << std::endl;

                if (x>638 && x<678 && y>250 && y<285)
                {
					num++;
					ifstream fichier(CHEMIN_LEVELS+"level"+to_string(num)+".txt");
					if(!fichier.is_open()){
						num--;
					}
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
                    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
                    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
                    Ecrire("Arial",65,"+",255,255,255,640,232);
                    Ecrire("Arial",65,"-",255,255,255,610,226);
                    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
                    Ecrire("CollegiateInsideFLF",45,"NIVEAU " + to_string(num),255,255,255,350,250);
                    SDL_RenderPresent(renderer);
                }

                if (num>1 && x>607 && x<633 && y>260 && y<278)
                {
                    num--;
                    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
                    SDL_RenderClear(renderer);

                    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
                    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
                    Ecrire("CollegiateInsideFLF",50,"CHOIX DU NIVEAU",255,255,255,275,50);
                    Ecrire("Arial",65,"+",255,255,255,640,232);
                    Ecrire("Arial",65,"-",255,255,255,610,226);
                    Ecrire("CollegiateBlackFLF",37,"Valider",255,255,255,440,370);
                    Ecrire("CollegiateInsideFLF",45,"NIVEAU " + to_string(num),255,255,255,350,250);
                    SDL_RenderPresent(renderer);
                }

                else if (x>437 && x<585 && y>370 && y<410)
                {
                    continuerLevel=0;
                    initLevel(num);
                }

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
    SDL_Event events;
    int continuerAide=1;
    SDL_SetRenderDrawColor(renderer, 0,127,127,255);
    SDL_RenderClear(renderer);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    Ecrire("CollegiateInsideFLF",50,"AIDE",255,255,255,450,50);
    SDL_RenderPresent(renderer);
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

    string nomfichier= "infos.txt";
    ifstream document(nomfichier.c_str(), ios::in);
    string ligne;
    getline(document, ligne);
    nbParties=stoi(ligne);
    Ecrire("CollegiateInsideFLF",25,"Pseudo : " + pseudo,255,255,255,30,200);
    Ecrire("CollegiateInsideFLF",50,"MENU",255,255,255,450,50);
    Ecrire("WingdingReview",40,"ñ",255,255,255,50,50);
    Ecrire("CollegiateInsideFLF",25,"Retour",255,255,255,30,25);
    Ecrire("CollegiateInsideFLF",25,"Nombre de parties jouees : " + to_string(nbParties),255,255,255,30,150);
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

                if (x>24 && x<124 && y>21 && y<87)
                {
                    continuerMenu=0;
                }
                break;
            }
        }
    }
}

void debut()
{
    inputPseudo();
    int longueurPseudo=pseudo.length()+8;
    affichageTexture(textureAccueil,0,0);
    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
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

                int x = events.button.x;
                int y = events.button.y;

                // std::cout << events.button.x << SDL_GetError() << std::endl;
                // std::cout << events.button.y << SDL_GetError() << std::endl;
                if (x>507 && x<726 && y>669 && y<763)
                {
                    //MENU
                    //std::cout << "menu" << SDL_GetError() << std::endl;
                    menu();
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (x>45 && x<428 && y>670 && y<763)
                {
                    //COMMENCER
                    choixLevel();
                    SDL_SetWindowSize(fenetre,20*TAILLE_CASE + MARGE_GAUCHE, 15*TAILLE_CASE + MARGE_HAUT);
                    affichageTexture(textureAccueil,0,0);
                    Ecrire("CollegiateInsideFLF",42,"Bonjour " + pseudo,106,143,255,((TAILLE_X_PLATEAU*TAILLE_CASE+MARGE_GAUCHE)/2-(longueurPseudo*12)),0);
                    SDL_RenderPresent(renderer);
                }
                else if (x>807 && x<990 && y>669 && y<763)
                {
                    //AIDE
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

    surface=IMG_Load((CHEMIN_IMAGES+"tourPoisonCanon.png").c_str());
    textureTourPoisonCanon= SDL_CreateTextureFromSurface(renderer, surface);
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

    surface=IMG_Load((CHEMIN_IMAGES+"tirClassique.png").c_str());
    textureTirClassique= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tirSniper.png").c_str());
    textureTirSniper= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface=IMG_Load((CHEMIN_IMAGES+"tirPoison.png").c_str());
    textureTirPoison= SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);


    return 1;
}

int main(int argc, char **argv)
{
    initSDL();
    initListeCase();
    debut();
    infos();
    quitListeCase();
    SDL_DestroyWindow(fenetre);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
