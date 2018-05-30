#include "Ennemi.h"

Ennemi::Ennemi(int x, int y, SDL_Texture* textureEnnemi, int vie, double multiplicateurVitesse, double multiplicateurArgentMort, int vague, bool estAerien):
    poison(false),
    vie(vie+(vie*20*(vague+1)/100)),
    vieMax(this->vie),
    textureEnnemi(textureEnnemi),
    dest({ x, y, TAILLE_ENNEMI, TAILLE_ENNEMI }),
    direction(0),
    vitesse(VITESSEBASEENNEMI * multiplicateurVitesse),
    destVieFond({x, y, 3*TAILLE_CASE/4, TAILLE_CASE/6}),
    destVie({x, y, 3*TAILLE_CASE/4, TAILLE_CASE/6}),
    multiplicateurArgentMort(multiplicateurArgentMort),
    multiplicateurVitesse(multiplicateurVitesse),
    estAerien(estAerien)
{
    //cout<<"Creation :\t Ennemi ("<<dest.x<<","<<dest.y<<")"<<endl;
}

Ennemi::~Ennemi()
{
    ajouteArgent();
    //cout<<"Destruction :\t Ennemi ("<<dest.x<<","<<dest.y<<")"<<endl;
    for(int i=0; i<listeEnnemis.size(); i++)
    {
        if(listeEnnemis[i]==this)
        {
            listeEnnemis.erase(listeEnnemis.begin()+i);
        }
    }
}

bool Ennemi::getAerien()
{
    return estAerien;
}

void Ennemi::affiche()
{
    destVieFond.x=destVie.x=dest.x;
    destVieFond.y=destVie.y=dest.y;
    SDL_RenderCopy(renderer, textureEnnemi, NULL, &dest);

    //affiche la barre de vie

    SDL_SetRenderDrawColor(renderer, 255, 255,255, 255);
    SDL_RenderFillRect(renderer, &destVieFond);
    if(poison)
    {
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &destVie);

}
void Ennemi::enregistrerPoss(int yCase, int xCase)
{
    listePoss.push_back(pair<int, int>(xCase,yCase));
}

void Ennemi::action()
{

    avance();
    if(!poison)
    {
        intensitePoison=0;
    }
    else
    {
        poison--;
        if(poison%FREQUENCE_EFFET==0) prendDegat(intensitePoison);
    }
}

void Ennemi::prendDegat(int degat)
{
    vie-=degat;
    if(vie<=0)
    {
        delete this;
    }
    else
    {
        destVie.w=destVieFond.w*(((double)vie)/vieMax);
    }
}
void Ennemi::ajouteCaseParcours()
{
    for(int i=0;i<listePoss.size();i++){
        listeCases[listePoss[i].second][listePoss[i].first]->ajouteNbPassage();
    }
}

void Ennemi::appliquerEffet(const int effet, int intensite, int duree)
{
    if(effet==EFFET_POISON)
    {
        poison=duree*FREQUENCE_EFFET;
        intensitePoison=intensite;
    }
}

int Ennemi::getXCentre()
{
    return dest.x + TAILLE_ENNEMI/2;
}

int Ennemi::getYCentre()
{
    return dest.y + TAILLE_ENNEMI/2;
}

int Ennemi::getXCentreFutur(int images)
{
    switch(direction){
    case 0: return getXCentre()+ images*vitesse;
    case 1: return getXCentre();
    case 2: return getXCentre()- images*vitesse;
    case 3: return getXCentre();
    }
}

int Ennemi::getYCentreFutur(int images)
{
    switch(direction){
    case 0: return getYCentre();
    case 1: return getYCentre()- images*vitesse;
    case 2: return getYCentre();
    case 3: return getYCentre()+ images*vitesse;
    }
}


void Ennemi::remplissagePoss(int yCase,int xCase, int poss[][2])
{
    for(int i =0 ; i<3 ; i++)
    {
        if(poss[i][0]==0 && poss[i][1]==0)
        {
            poss[i][0]=yCase;
            poss[i][1]=xCase;
            break;
        }
    }
}

void Ennemi::recentrage(int xCase, int yCase)
{
    dest.x=MARGE_GAUCHE+TAILLE_CASE/2+TAILLE_CASE*xCase-TAILLE_ENNEMI/2;
    dest.y=MARGE_HAUT+TAILLE_CASE/2+TAILLE_CASE*yCase-TAILLE_ENNEMI/2;
}

void Ennemi::avance()
{

    int xCase = (dest.x-MARGE_GAUCHE)/ TAILLE_CASE;
    int yCase = (dest.y-MARGE_HAUT)/ TAILLE_CASE;

    if((dest.y + TAILLE_ENNEMI/2)-vitesse < listeCases[yCase][xCase]->getYcentre()
            && listeCases[yCase][xCase]->getYcentre() < (dest.y + TAILLE_ENNEMI/2)+vitesse
            && (dest.x + TAILLE_ENNEMI/2)-vitesse < listeCases[yCase][xCase]->getXcentre()
            && listeCases[yCase][xCase]->getXcentre() < (dest.x + TAILLE_ENNEMI/2)+vitesse)
    {
        //std::cout <<dest.x + TAILLE_ENNEMI/2 << SDL_GetError() << std::endl;
        // std::cout <<listeCases[yCase][xCase]->getXcentre()<< SDL_GetError() << std::endl;
        enregistrerPoss(yCase,xCase);
        string droite,
               gauche,
               dessus,
               dessous;

        if(xCase<TAILLE_X_PLATEAU && listeCases[yCase][xCase+1]!= NULL)
        {
            droite = listeCases[yCase][xCase+1]->getType();
        }
        else
        {
            droite = "Vide";
        }
        if(xCase>0 && listeCases[yCase][xCase-1]!= NULL )
        {
            gauche = listeCases[yCase][xCase-1]->getType();
        }
        else
        {
            gauche = "Vide";
        }
        if(yCase>0 && listeCases[yCase-1][xCase]!= NULL)
        {
            dessus = listeCases[yCase-1][xCase]->getType();
        }
        else
        {
            dessus = "Vide";
        }
        if(yCase<TAILLE_Y_PLATEAU && listeCases[yCase+1][xCase]!= NULL)
        {
            dessous = listeCases[yCase+1][xCase]->getType();
        }
        else
        {
            dessous = "Vide";
        }
        int nbPoss = 0 ;
        int poss[3][2]= {0,0,0,0,0,0};

        if(direction==0)
        {
            //cout <<droite << endl;
            if(dessus!="Vide" && (yCase >0 && (dessus=="Chemin" || dessus=="Chateau")))
            {
                nbPoss++;
                remplissagePoss(yCase-1,
                                xCase,
                                poss);
            }
            if(droite!="Vide" && (xCase <TAILLE_X_PLATEAU && (droite=="Chemin" || droite=="Chateau")))
            {
                //cout <<droite << endl;
                nbPoss++;
                remplissagePoss(yCase,
                                xCase+1,
                                poss);
            }
            if(dessous!="Vide" && (yCase<TAILLE_Y_PLATEAU &&(dessous=="Chemin" || dessous=="Chateau")))
            {
                nbPoss++;
                remplissagePoss(yCase+1,
                                xCase,
                                poss);
            }
        }
        else if(direction==1)
        {
            if( xCase <TAILLE_X_PLATEAU &&(droite=="Chemin" || droite=="Chateau") )
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase,
                                xCase+1,
                                poss);
            }
            if( yCase <TAILLE_Y_PLATEAU && (dessus=="Chemin" || dessus=="Chateau"))
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase-1,
                                xCase,
                                poss);
            }
            if(yCase>0 && (gauche=="Chemin" || gauche=="Chateau"))
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase,
                                xCase-1,
                                poss);
            }
        }
        else if (direction==2)
        {
            if( xCase <TAILLE_X_PLATEAU && (dessous=="Chemin" || dessous=="Chateau"))
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase+1,
                                xCase,
                                poss);
            }
            if( yCase <TAILLE_Y_PLATEAU && (dessus=="Chemin" || dessus=="Chateau"))
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase-1,
                                xCase,
                                poss);
            }
            if(yCase>0 && (gauche=="Chemin" || gauche=="Chateau"))
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase,
                                xCase-1,
                                poss);
            }
        }
        else
        {

            if( xCase < TAILLE_X_PLATEAU && (dessous=="Chemin" || dessous=="Chateau"))
            {
                //int[] possi = new possi[2];
                nbPoss++;
                remplissagePoss(yCase+1,
                                xCase,
                                poss);
            }
            if( yCase <TAILLE_Y_PLATEAU && (gauche=="Chemin" || gauche=="Chateau"))
            {

                //int possi[] = new possi[2];
                nbPoss++;
                //cout<<nbPoss<<endl;
                remplissagePoss(yCase,
                                xCase-1,
                                poss);
            }
            if(yCase>0 && (droite=="Chemin" || droite=="Chateau"))
            {
                //int possi[] = new possi[2];
                nbPoss++;
                remplissagePoss(yCase,
                                xCase+1,
                                poss);
            }

        }

        for(int i =0 ; i<nbPoss ; i++)
        {
            int block = listeCases[poss[i][0]][poss[i][1]]->getBlock();
            if(block==1 && nbPoss!=1)
            {
                poss[i][0]=0;
                poss[i][1]=0;
            }
        }

        for(int i =0 ; i<2; i++)
        {
            if(poss[i][0]==0 && poss[i][1]==0)
            {
                poss[i][0]=poss[i+1][0];
                poss[i][1]=poss[i+1][1];
            }
        }
        int NbPossi=-42;
        for(int i=0 ; i<3 ; i++)
        {
            if(poss[i][0]==0 && poss[i][1]==0)
            {
                NbPossi=i;
                break;
            }
        }
        if(NbPossi==-42)
        {
            nbPoss=3;
        }
        else
        {
            nbPoss=NbPossi;
        }

        if (nbPoss==1)
        {
            int deplaX = poss[0][1]-xCase;
            int deplaY = poss[0][0]-yCase;

            if(deplaX!=0)
            {
                recentrage(xCase,yCase);
                dest.x=dest.x+deplaX*vitesse;
                if(deplaX==1)
                {
                    direction=0;
                }
                else
                {
                    direction=2;
                }
            }
            else
            {
                recentrage(xCase,yCase);
                dest.y=dest.y+deplaY*vitesse;
                if(deplaY==1)
                {
                    direction=3;
                }
                else
                {
                    direction=1;
                }
            }

        }
        else if(nbPoss==2)
        {
            int proba1 = listeCases[poss[0][0]][poss[0][1]]->getNbPassage();
            int proba2 = listeCases[poss[1][0]][poss[1][1]]->getNbPassage();

            vector<int> tableauProba;
            for (int i= 0 ; i<proba1 ; i++){
                tableauProba.push_back(0);
            }
            for (int i= 0 ; i<proba2 ; i++){
                tableauProba.push_back(1);
            }


            int nbAlea = tableauProba[rand()%(tableauProba.size())];


            int deplaX = poss[nbAlea][1]-xCase;
            int deplaY = poss[nbAlea][0]-yCase;

            if(deplaX!=0)
            {
                recentrage(xCase,yCase);
                dest.x=dest.x+deplaX*vitesse;

                if(deplaX==1)
                {
                    direction=0;
                }
                else
                {
                    direction=2;
                }

            }
            else
            {
                recentrage(xCase,yCase);
                dest.y=dest.y+deplaY*vitesse;
                if(deplaY==1)
                {
                    direction=3;
                }
                else
                {
                    direction=1;
                }
            }

        }
        else if(nbPoss==3)
        {
            int proba1 = listeCases[poss[0][0]][poss[0][1]]->getNbPassage();
            int proba2 = listeCases[poss[1][0]][poss[1][1]]->getNbPassage();
            int proba3 = listeCases[poss[2][0]][poss[2][1]]->getNbPassage();

            vector<int> tableauProba;
            for (int i= 0 ; i<proba1 ; i++){
                tableauProba.push_back(0);
            }
            for (int i= 0 ; i<proba2 ; i++){
                tableauProba.push_back(1);
            }
            for (int i= 0 ; i<proba3 ; i++){
                tableauProba.push_back(2);
            }

            int nbAlea = tableauProba[rand()%(tableauProba.size())];


            int deplaX = poss[nbAlea][1]-xCase;
            int deplaY = poss[nbAlea][0]-yCase;


            if(deplaX!=0)
            {
                recentrage(xCase,yCase);
                dest.x=dest.x+deplaX*vitesse;
                if(deplaX==1)
                {
                    direction=0;
                }
                else
                {
                    direction=2;
                }
            }
            else
            {
                recentrage(xCase,yCase);
                dest.y=dest.y+deplaY*vitesse;
                if(deplaY==1)
                {
                    direction=3;
                }
                else
                {
                    direction=1;
                }
            }

        }
        else
        {
            if(direction==0)
            {
                direction=2;
            }
            else if(direction==1)
            {
                direction=3;
            }
            else if(direction==2)
            {
                direction=0;
            }
            else
            {
                direction=1;
            }
        }

    }
    else
    {

        if(direction==0)
        {
            dest.x=dest.x+vitesse;

        }
        else if(direction==1)
        {
            dest.y=dest.y-vitesse;
        }
        else if(direction==2)
        {
            dest.x=dest.x-vitesse;
        }
        else
        {
            dest.y=dest.y+vitesse;
        }
    }






}

void Ennemi::ajouteArgent()
{
    argent+= ARGENT_ENNEMI*multiplicateurArgentMort;
}
