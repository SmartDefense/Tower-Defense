#include "Case.h"
#include <math.h>


Case::Case(int x, int y, int block):
    x(x),
    y(y),
    block(block),
    nbPassage(1),
    xCentre(x*TAILLE_CASE + TAILLE_CASE/2 + MARGE_GAUCHE),
    yCentre(y*TAILLE_CASE + TAILLE_CASE/2 + MARGE_HAUT),
    type("Case"),
    nombreAleatoire(rand()%NB_IMAGE_CASE),
    dest({x*TAILLE_CASE+MARGE_GAUCHE, y*TAILLE_CASE+MARGE_HAUT, TAILLE_CASE, TAILLE_CASE}),
    textureCaseFond(::textureCaseFond)
{
    //cout<<"Creation :\t Case ("<<x<<","<<y<<")"<<endl;
}

Case::~Case(){
    //cout<<"Destruction :\t Case ("<<x<<","<<y<<")"<<endl;
}

void Case::ajouteNbPassage()
{
   nbPassage++;
}
int Case::getNbPassage()
{
    return nbPassage;
}

void Case::affiche()
{
    SDL_RenderCopy(renderer, textureCaseFond, NULL, &dest);
    if(type=="Case"){
        SDL_RenderCopy(renderer, textureCase[nombreAleatoire], NULL, &dest);
    }


}

void Case::affichePortee(){

}
int Case::getBlock()
{
    return block;
}

int Case::action()
{
    return 0;
}

void Case::amelioration(const int typeAmelioration)
{}

double Case::distanceDepuisCentre(int x2, int y2)
{
    return sqrt(pow(x2-xCentre , 2) + pow(y2-yCentre, 2));
}

string Case::getType()
{
    return type;
}
int Case::getXcentre()
{
    return xCentre;
}
int Case::getYcentre()
{
    return yCentre;
}

