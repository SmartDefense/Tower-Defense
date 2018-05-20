#include "Chemin.h"

Chemin::Chemin(int x, int y, int block):
    Case(x, y, block),
    vitesseDeplacement(1),
    nbPassage(1)
{
    Case::textureCase=::textureChemin;
    Case::type="Chemin";
    //cout<<"Creation :\t Chemin ("<<x<<","<<y<<")"<<endl;
}

Chemin::~Chemin(){
    //cout<<"Destruction :\t Chemin ("<<x<<","<<y<<")"<<endl;
}

void Chemin::affiche()
{
    Case::affiche();
}

int Chemin::action()
{
    return -1;
}

void Chemin::amelioration(const int typeAmelioration)
{

}

int Chemin::getVitesseDeplacement()
{
    return vitesseDeplacement;
}
int Chemin::getNbPassage()
{
    return nbPassage;
}
