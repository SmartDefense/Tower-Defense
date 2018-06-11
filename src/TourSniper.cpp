#include "TourSniper.h"

TourSniper::TourSniper(int x, int y, int priorite):
    Tour(x, y, ::textureTourSniperBase, ::textureTourSniperCanon, 90, priorite, 200, 30, 2, 6.5, true, false)
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
    listeTirs.push_back(new TirSniper(xCentre-TAILLE_X_TIR/2, yCentre-TAILLE_Y_TIR/2, dX, dY, angle, degat, peutToucherTerrestre, peutToucherAerien));
    compteurRechargement=rechargement;
}

void TourSniper::amelioration(const int typeAmelioration)
{
    switch(typeAmelioration){
    case AMELIORATION_CADENCE:
        if(rechargement>5) rechargement-=10;
        break;
    case AMELIORATION_DEGAT_TIR:
        degat+=50;
        break;
    case AMELIORATION_PORTEE_TOUR:
        portee+=TAILLE_CASE;
        break;
    case AMELIORATION_VITESSE_TIR:
        vitesseTir+=2;
        break;
    }
}
