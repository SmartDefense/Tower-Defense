#ifndef VARIABLES2_H
#define VARIABLES2_H

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

extern SDL_Window* fenetre;
extern SDL_Renderer* renderer;
extern SDL_Texture  *textureChemin,
                    *textureCaseFond,
                    *textureChateau,

                    *textureTourClassiqueBase,
                    *textureTourPoisonBase,
                    *textureTourSniperBase,
                    *textureTourAerienBase,

                    *textureTourClassiqueCanon,
                    *textureTourSniperCanon,
                    *textureTourAerienCanon,

                    *textureEnnemiClassique,
                    *textureEnnemiRapideSimple,
                    *textureEnnemiTank,
                    *textureEnnemiVolantSimple,

                    *textureTirClassique,
                    *textureTirSniper,
                    *textureTirAerien,

                    *textureExplosion[TEMPS_ANIM_TIR],

                    *textureEnnemiVolant[NB_IMAGE_ENNEMI_VOLANT],
                    *textureEnnemiRapide[NB_IMAGE_ENNEMI_RAPIDE],
                    *textureCase[NB_CASE_FOND],
                    *textureTourFond[NB_TOUR_FOND],

                    *textureBpTourSniper,
                    *textureBpTourClassique,
                    *textureBpTourPoison,
                    *textureBpTourAerien,
                    *textureBpEffacer,
                    *textureBpAnnuler,
                    *textureBpRetour,
                    *textureBpValider,
                    *textureCadence,
                    *textureDegatTir,
                    *texturePorteeTour,
                    *textureVitesseTir,

                    *textureBpCommencer,
                    *textureBpMenu,
                    *textureBpAide,

                    *textureAccueil,
                    *textureLogo;
extern TTF_Font *fontArgent,
                *font;

#endif // VARIABLES2_H
