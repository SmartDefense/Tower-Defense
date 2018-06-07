#ifndef VARIABLES_H
#define VARIABLES_H

#include <vector>

#include "Case.h"
#include "Ennemi.h"
#include "Tir.h"
#include "Constantes.h"

/*extern Case*** listeCases;
extern vector<Ennemi*> listeEnnemis;
extern vector<Tir*> listeTirs;
extern int argent;
extern int numVague;

extern int TAILLE_X_PLATEAU;
extern int TAILLE_Y_PLATEAU;

extern int nbParties;                      // Nombre de parties du joueur
extern string pseudoHighscore;                  // Variable contenant le pseudo entré par le joueur
extern int highscore;
extern string pseudo;

extern int continuer;*/


extern vector<int> vague;                  // Tableau permettant d'ajouter le type d'ennemi et de l'afficher pendant la vague
extern Case*** listeCases;
extern vector<Ennemi*> listeEnnemis;
extern vector<Tir*> listeTirs;

extern int nbParties;                      // Nombre de parties du joueur
extern string pseudoHighscore;                  // Variable contenant le pseudo entré par le joueur
extern int highscore;

extern string pseudo;
extern int nbVagues;                    // Nombre de vague totale dans chaque partie
extern int depart;                       // Variable d'état pour commencer à afficher la vague d'ennemis
extern int occurences;                  // Nombre d'ennemis dans la première vague
extern int argent;                         // Argent du joueur
extern int numLevel;                     // Numero du level
extern int continuer;                    // Variable d'état pour quitter la boucle principale et fermer la fenêtre de jeu
extern int affichageArgent;

extern int TAILLE_X_PLATEAU;
extern int TAILLE_Y_PLATEAU;
extern int nbEnnemisSupplementaires;    // Nb d'ennemis supplémentaires à chaque vague
extern int compteurImage;                // Compteur d'images permettant d'effectuer des actions à un temps donné dans une boucle while
extern int rafraichissement;

extern int xChateau, yChateau;

extern int xVague, yVague;// Variables permettant de connaitre la position de la case de départ

#endif // VARIABLES_H
