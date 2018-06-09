#include "Tour.h"
#include <math.h>

Tour::Tour(int x, int y, SDL_Texture* textureTourBase, SDL_Texture* textureTourCanon, int rechargement, int priorite, int degat, int vitesseTir, int vitesseCanon, double portee, bool peutToucherTerrestre, bool peutToucherAerien):
    Case(x, y , 0),
    rechargement(rechargement),
    compteurRechargement(0),
    priorite(priorite),
    degat(degat),
    vitesseTir(vitesseTir),
    vitesseCanon(vitesseCanon),
    angleCanon(0),
    fondTourAleatoire(rand()%NB_TOUR_FOND),
    directionFondAleatoire(rand()%360),
    portee(portee*TAILLE_CASE),
    peutToucherAerien(peutToucherAerien),
    peutToucherTerrestre(peutToucherTerrestre),
    textureTourBase(textureTourBase),
    textureTourCanon(textureTourCanon)
{
    Case::type="Tour";
}

Tour::~Tour(){}

Tour::moduloPositif(int nombre, int modulo){
    return (nombre % modulo + modulo) % modulo;
}

void Tour::affiche()
{
    Case::affiche();
    SDL_RenderCopyEx(renderer, textureTourFond[fondTourAleatoire], NULL, &dest, directionFondAleatoire, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, textureTourBase, NULL, &dest, directionCaseAleatoire, NULL, SDL_FLIP_NONE);
    SDL_RenderCopyEx(renderer, textureTourCanon, NULL, &dest, angleCanon, NULL, SDL_FLIP_NONE);

    int tempsDepuisTir=abs(rechargement-compteurRechargement);
    if(tempsDepuisTir<TEMPS_ANIM_TIR){
            SDL_RenderCopyEx(renderer, textureExplosion[tempsDepuisTir], NULL, &dest, angleCanon, NULL, SDL_FLIP_NONE);
    }
}

void Tour::affichePortee(){
    SDL_SetRenderDrawColor(renderer, 127,0,0, 50);
    int xDessin=0,
        yDessin=portee;

    while(yDessin>xDessin){
        SDL_RenderDrawPoint(renderer, xDessin  + xCentre,  yDessin  + yCentre);
        SDL_RenderDrawPoint(renderer, yDessin  + xCentre,  xDessin  + yCentre);
        SDL_RenderDrawPoint(renderer, -xDessin + xCentre,  yDessin  + yCentre);
        SDL_RenderDrawPoint(renderer, -yDessin + xCentre,  xDessin  + yCentre);
        SDL_RenderDrawPoint(renderer, xDessin  + xCentre,  -yDessin + yCentre);
        SDL_RenderDrawPoint(renderer, yDessin  + xCentre,  -xDessin + yCentre);
        SDL_RenderDrawPoint(renderer, -xDessin + xCentre,  -yDessin + yCentre);
        SDL_RenderDrawPoint(renderer, -yDessin + xCentre,  -xDessin + yCentre);

        xDessin++;
        if(pow(xDessin, 2)+pow(((int)(yDessin)-1/2), 2)-portee*portee>0){
            yDessin--;
        }
    }
}

void Tour::viseeEnnemi(int idEnnemi, double distance){
    //...pour savoir s'il est a portee
    int temps=distance/vitesseTir;
    int xEnnemi=listeEnnemis[idEnnemi]->getXCentreFutur(temps);
    int yEnnemi=listeEnnemis[idEnnemi]->getYCentreFutur(temps);

    //calcul l'angle du tir sur [0;360[
    int angle = atan2((yEnnemi-yCentre), (xEnnemi-xCentre)) *180/M_PI;
    if(angle<0){angle+=360;}

    //si l'angle du canon est différent de celui du tir, on tourne la tour
    if(moduloPositif(angle-angleCanon, 360)<=180){
        angleCanon+=vitesseCanon;
        if(angleCanon>360) angleCanon-=360;
        if(moduloPositif(angle-angleCanon, 360)>180) angleCanon=angle;
    }
    else if(moduloPositif(angle-angleCanon, 360)>180){
        angleCanon-=vitesseCanon;
        if(angleCanon<360) angleCanon+=360;
        if(moduloPositif(angle-angleCanon, 360)<180) angleCanon=angle;
    }

    //si on est presque aligne et qu'on peut tirer ...
    if(compteurRechargement==0 && angle==angleCanon){
        //on calcul les deplacements cartésiens du tir et on lance le tir
        double dX=((xEnnemi-xCentre)*vitesseTir)/distance;
        double dY=((yEnnemi-yCentre)*vitesseTir)/distance;
        tir(dX,dY, angle);
    }
}

int Tour::action()
{
    if(priorite==PRIORITE_PREMIER){
        //on parcours la liste d'ennemis ...
        for(unsigned int i=0; i<listeEnnemis.size();i++){
            //on calcul la distance entre le centre de l'ennemi et celui de la tour...
            double distance = distanceDepuisCentre(listeEnnemis[i]->getXCentre(),
                                                   listeEnnemis[i]->getYCentre());
            if(distance<portee && ((!listeEnnemis[i]->getAerien() && peutToucherTerrestre) || (listeEnnemis[i]->getAerien() && peutToucherAerien))){
                viseeEnnemi(i, distance);
                break;
            }
        }
    }else if(priorite==PRIORITE_PLUS_PRES){
        int distanceMin=1000000000;
        int idMin=-1;
        //on parcours la liste d'ennemis ...
        for(unsigned int i=0; i<listeEnnemis.size();i++){
            //on calcul la distance entre le centre de l'ennemi et celui de la tour...
            double distance = distanceDepuisCentre(listeEnnemis[i]->getXCentre(),
                                                   listeEnnemis[i]->getYCentre());
            if(distance<distanceMin && distance<portee && ((!listeEnnemis[i]->getAerien() && peutToucherTerrestre) || (listeEnnemis[i]->getAerien() && peutToucherAerien))){
                distanceMin=distance;
                idMin=i;
            }
        }
        if(idMin!=-1) viseeEnnemi(idMin, distanceMin);
    }else if(priorite==PRIORITE_PLUS_FAIBLE){
        int vieMin=1000000000;
        int distanceVieMin=-1;
        int idMin=-1;
        //on parcours la liste d'ennemis ...
        for(unsigned int i=0; i<listeEnnemis.size();i++){
            //on calcul la distance entre le centre de l'ennemi et celui de la tour...
            double distance = distanceDepuisCentre(listeEnnemis[i]->getXCentre(),
                                                   listeEnnemis[i]->getYCentre());
            int vie = listeEnnemis[i]->getVie();
            if(vie<vieMin && distance<portee && ((!listeEnnemis[i]->getAerien() && peutToucherTerrestre) || (listeEnnemis[i]->getAerien() && peutToucherAerien))){
                vieMin=vie;
                distanceVieMin=distance;
                idMin=i;
            }
        }
        if(idMin!=-1) viseeEnnemi(idMin, distanceVieMin);
    }else if(priorite==PRIORITE_PLUS_FORT){
        int vieMax=0;
        int distanceVieMax=-1;
        int idMax=-1;
        //on parcours la liste d'ennemis ...
        for(unsigned int i=0; i<listeEnnemis.size();i++){
            //on calcul la distance entre le centre de l'ennemi et celui de la tour...
            double distance = distanceDepuisCentre(listeEnnemis[i]->getXCentre(),
                                                   listeEnnemis[i]->getYCentre());
            int vie = listeEnnemis[i]->getVie();
            if(vie>vieMax && distance<portee && ((!listeEnnemis[i]->getAerien() && peutToucherTerrestre) || (listeEnnemis[i]->getAerien() && peutToucherAerien))){
                vieMax=vie;
                distanceVieMax=distance;
                idMax=i;
            }
        }
        if(idMax!=-1) viseeEnnemi(idMax, distanceVieMax);
    }
    if(compteurRechargement!=0) compteurRechargement--;
    return -1;
}

void Tour::tir(double dX, double dY, double angle)
{
}

void Tour::amelioration(const int typeAmelioration)
{
}
