#include "TourPoison.h"

TourPoison::TourPoison(int x, int y, int priorite):
    Tour(x, y, ::textureTourPoisonBase, NULL, 30, priorite, 10, 25, 5, 3),
    duree(10)
{
	Case::type="TourPoison";
    //cout<<"Creation :\t TourPoison ("<<x<<","<<y<<")"<<endl;
}

TourPoison::~TourPoison(){
    argent+=0.5*ARGENT_TOUR*multiplicateurCout;
}

int TourPoison::action(){
    for(int i=listeEnnemis.size()-1, xEnnemi, yEnnemi; i>=0;i--){
        xEnnemi = listeEnnemis[i]->getXCentre();
        yEnnemi = listeEnnemis[i]->getYCentre();

        //on calcul la distance entre le centre de l'ennemi et celui de la tour...
        double distance = distanceDepuisCentre(xEnnemi, yEnnemi);

        //...pour savoir s'il est a portee
        if(distance<portee){
            listeEnnemis[i]->appliquerEffet(EFFET_POISON, degat, duree);
        }
    }
    return 1;
}

void TourPoison::amelioration(const int typeAmelioration)
{
    switch(typeAmelioration){
    case AMELIORATION_CADENCE:
        if(rechargement>5) rechargement-=5;
        break;
    case AMELIORATION_DEGAT_TIR:
        degat+=5;
        break;
    case AMELIORATION_PORTEE_TOUR:
        portee+=TAILLE_CASE*0.5;
        break;
    }
}
