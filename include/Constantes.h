#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <string>
#include <iostream>
using namespace std;

const int FPS = 30;
const int FREQUENCE_EFFET = 30;

const int TAILLE_CASE = 50;
const int MARGE_GAUCHE=0.6*TAILLE_CASE;
const int MARGE_HAUT=2*TAILLE_CASE;
const int TAILLE_ENNEMI = 0.6*TAILLE_CASE;
const int TAILLE_X_TIR = 30;
const int TAILLE_Y_TIR = 6;

const int ARGENT_ENNEMI = 10;
const int ARGENT_TOUR = 25;

const int TEMPS_ANIM_TIR = 5;
const int NB_IMAGE_ENNEMI_VOLANT = 2;
const int NB_IMAGE_ENNEMI_RAPIDE = 4;
const int NB_CASE_FOND = 10;
const int NB_TOUR_FOND = 2;


const int AMELIORATION_VITESSE_TIR = 0;
const int AMELIORATION_CADENCE = 1;
const int AMELIORATION_DEGAT_TIR = 2;
const int AMELIORATION_PORTEE_TOUR = 3;
const int AMELIORATION_VITESSE_DEPLACEMENT = 4;

const int PRIORITE_PREMIER = 0;
const int PRIORITE_PLUS_PRES = 1;
const int PRIORITE_PLUS_FAIBLE = 2;
const int PRIORITE_PLUS_FORT = 3;
const int PRIORITE_ALEATOIRE = 4;

const int EFFET_POISON = 1000;

const string CHEMIN_IMAGES="images/";
const string CHEMIN_LEVELS="levels/";
const double  VITESSEBASEENNEMI = 0.04;


#endif // CONSTANTES_H
