#include "EnnemiClassique.h"

EnnemiClassique::EnnemiClassique(int x, int y, int vague,int xChateau,int yChateau):
    Ennemi(x, y, ::textureEnnemiClassique, 150,2,1, vague, false,xChateau,yChateau)
{
    //ctor
}
