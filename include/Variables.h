#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>

#include "Case.h"
#include "Ennemi.h"
#include "Tir.h"
#include "Constantes.h"

extern Case*** listeCases;
extern vector<Ennemi*> listeEnnemis;
extern vector<Tir*> listeTirs;
extern int argent;
extern int numVague;

extern int TAILLE_X_PLATEAU;
extern int TAILLE_Y_PLATEAU;

#endif // VARIABLES_H
