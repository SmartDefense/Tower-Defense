#include "Chateau.h"

Chateau::Chateau(int x, int y, int vie):
    Chemin(x, y, 0),
    vie(vie),
    vieMax(vie),
    destVie({x*TAILLE_CASE+TAILLE_CASE/8+MARGE_GAUCHE, (y+1)*TAILLE_CASE-2*TAILLE_CASE/6+MARGE_HAUT, 3*TAILLE_CASE/4, TAILLE_CASE/6}),
    destVieFond({x*TAILLE_CASE+TAILLE_CASE/8+MARGE_GAUCHE, (y+1)*TAILLE_CASE-2*TAILLE_CASE/6+MARGE_HAUT, 3*TAILLE_CASE/4, TAILLE_CASE/6}),
    textureChateau(::textureChateau)
{
    Case::type="Chateau";
    //cout<<"Creation :\t Chateau ("<<x<<","<<y<<")"<<endl;
}

Chateau::~Chateau(){
    //cout<<"Destruction :\t Chateau ("<<x<<","<<y<<")"<<endl;
}

void Chateau::affiche()
{
    //affiche le fond textureChemin
    Chemin::affiche();
    //affiche textureChateau
    SDL_RenderCopy(renderer, textureChateau, NULL, &dest);

    //affiche la barre de vie
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &destVieFond);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &destVie);
}

int Chateau::action()
{
    for(unsigned int i=0;i<listeEnnemis.size();i++){
        if(distanceDepuisCentre(listeEnnemis[i]->getXCentre(), listeEnnemis[i]->getYCentre())<TAILLE_CASE/4){
            listeEnnemis.erase(listeEnnemis.begin()+i);
            vie--;
            listeEnnemis[i]->ajouteCaseParcours();
        }
    }
    destVie.w=destVieFond.w*(((double)vie)/vieMax);
    if(vie<=0){
        destVie.w=0;
        return 1;
    }
    return -1;
}
