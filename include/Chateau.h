#ifndef CHATEAU_H
#define CHATEAU_H

#include <Chemin.h>


class Chateau : public Chemin
{
    public:
        Chateau(int x, int y, int vie);
        virtual ~Chateau();
        void affiche();
        int action();

    protected:
        int vie,
            vieMax;
        SDL_Rect destVie,
                 destVieFond;
        SDL_Texture* textureChateau;

};

#endif // CHATEAU_H
