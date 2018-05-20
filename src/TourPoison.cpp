#include "TourPoison.h"

TourPoison::TourPoison(int x, int y, int priorite):
    Tour(x, y, ::textureTourPoisonBase, ::textureTourPoisonCanon, 30, priorite, 1, 12, 5, 3),
    duree(10)
{
	Case::type="TourPoison";
    //cout<<"Creation :\t TourPoison ("<<x<<","<<y<<")"<<endl;
}

TourPoison::~TourPoison(){
    argent+=0.5*ARGENT_TOUR*multiplicateurCout;
}

void TourPoison::tir(double dX, double dY, double angle)
{
    listeTirs.push_back(new TirPoison(xCentre-TAILLE_X_TIR/2, yCentre-TAILLE_Y_TIR/2, dX, dY, angle, degat, duree));
    compteurRechargement=rechargement;
}

void TourPoison::amelioration(const int typeAmelioration)
{

}
