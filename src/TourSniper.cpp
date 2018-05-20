#include "TourSniper.h"

TourSniper::TourSniper(int x, int y, int priorite):
    Tour(x, y, ::textureTourSniperBase, ::textureTourSniperCanon, 90, priorite, 10, 30, 2, 6.5)
{
    Case::type="TourSniper";
	//cout<<"Creation :\t TourSniper ("<<x<<","<<y<<")"<<endl;
}

TourSniper::~TourSniper()
{
    argent+=0.5*ARGENT_TOUR*multiplicateurCout;
    //cout<<"Destruction :\t TourSniper ("<<x<<","<<y<<")"<<endl;
}


void TourSniper::tir(double dX, double dY, double angle)
{
    listeTirs.push_back(new TirSniper(xCentre-TAILLE_X_TIR/2, yCentre-TAILLE_Y_TIR/2, dX, dY, angle, degat));
    compteurRechargement=rechargement;
}

void TourSniper::amelioration(const int typeAmelioration)
{

}
