#include "TourClassique.h"

TourClassique::TourClassique(int x, int y, int priorite):
    Tour(x, y, ::textureTourClassiqueBase, ::textureTourClassiqueCanon, 30, priorite, 5, 25, 5, 3)
{
	Case::type="TourClassique";
    //cout<<"Creation :\t TourClassique ("<<x<<","<<y<<")"<<endl;
}

TourClassique::~TourClassique()
{
    argent+=0.5*ARGENT_TOUR*multiplicateurCout;
    //cout<<"Destruction :\t TourClassique ("<<x<<","<<y<<")"<<endl;
}

void TourClassique::tir(double dX, double dY, double angle)
{
    listeTirs.push_back(new TirClassique(xCentre-TAILLE_X_TIR/2, yCentre-TAILLE_Y_TIR/2, dX, dY, angle, degat));
    compteurRechargement=rechargement;
}

void TourClassique::amelioration(const int typeAmelioration)
{

}
