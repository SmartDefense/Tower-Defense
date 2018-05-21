#ifndef VARIABLES2_H
#define VARIABLES2_H

extern SDL_Window* fenetre;
extern SDL_Renderer* renderer;
extern SDL_Texture  *textureCase,
                    *textureChemin,
                    *textureChateau,

                    *textureTourClassiqueBase,
                    *textureTourPoisonBase,
                    *textureTourSniperBase,

                    *textureTourClassiqueCanon,
                    *textureTourPoisonCanon,
                    *textureTourSniperCanon,

                    *textureEnnemiClassique,
                    *textureEnnemiRapide,
                    *textureEnnemiTank,
                    *textureEnnemiVolant,

                    *textureTirClassique,
                    *textureTirPoison,
                    *textureTirSniper,

                    *textureExplosion[TEMPS_ANIM_TIR];

#endif // VARIABLES2_H
