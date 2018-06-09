#include "Ennemi.h"
#include <math.h>

Ennemi::Ennemi(int x, int y, SDL_Texture* textureEnnemi, int vie, double multiplicateurVitesse, double multiplicateurArgentMort, int vague, bool estAerien,int xChateau,int yChateau,int type):
    vie(vie+(vie*20*(vague+1)/100)),
    vieMax(this->vie),
    direction(0),
    xChateau(xChateau),
    yChateau(yChateau),
    vitesse(VITESSEBASEENNEMI * multiplicateurVitesse),
    poison(false),
    x(x),
    y(y),
    type(type),
    intensitePoison(0),
    destVie({x, y, 3*TAILLE_CASE/4, TAILLE_CASE/6}),
    destVieFond({x, y, 3*TAILLE_CASE/4, TAILLE_CASE/6}),
    multiplicateurVitesse(multiplicateurVitesse),
    multiplicateurArgentMort(multiplicateurArgentMort),
    estAerien(estAerien),
    textureEnnemi(textureEnnemi),
    numImage(0)
{

    if(estAerien){
        double distance = sqrt(pow(listeCases[yChateau][xChateau]->getXcentre()-getXCentre(),2)+pow(listeCases[yChateau][xChateau]->getYcentre()-getYCentre(),2));
        Case chateau=*listeCases[yChateau][xChateau];
        dX=((chateau.getXcentre()-getXCentre())*vitesse)/distance;
        dY=((chateau.getYcentre()-getYCentre())*vitesse)/distance;
        angle=atan2((chateau.getYcentre()-y), (chateau.getXcentre()-x)) *180/M_PI;
        //cout<<angle<<endl;
    }
    //cout<<"Creation :\t Ennemi ("<<x<<","<<y<<")"<<endl;
}

Ennemi::~Ennemi()
{
    ajouteArgent();
    //cout<<"Destruction :\t Ennemi ("<<x<<","<<y<<")"<<endl;
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
    destVieFond.x=destVie.x=x;
    destVieFond.y=destVie.y=y;
    SDL_Rect dest = {(int)(x+0.5), (int)(y+0.5), TAILLE_ENNEMI, TAILLE_ENNEMI};

    if(estAerien){
        int limite=4;
        if(numImage<limite){
            SDL_RenderCopyEx(renderer, textureEnnemiVolant[0], NULL, &dest, angle, NULL, SDL_FLIP_NONE);
            numImage++;
        }else if(numImage<limite*2){
            SDL_RenderCopyEx(renderer, textureEnnemiVolant[1], NULL, &dest, angle, NULL, SDL_FLIP_NONE);
            numImage++;
            if(numImage==8){
                numImage=0;
            }
        }

    }else{
        if(direction==0){
            angle=0;
        }else if(direction==1){
            angle=-90;
        }else if(direction==2){
            angle=180;
        }else if(direction==3){
            angle=90;
        }

        if(type==1){
            int limite =2;

           if(numImage<limite){
                SDL_RenderCopyEx(renderer, textureEnnemiRapide[0], NULL, &dest, angle, NULL, SDL_FLIP_NONE);
                numImage++;

            }else if(numImage<limite*2){
                SDL_RenderCopyEx(renderer, textureEnnemiRapide[1], NULL, &dest, angle, NULL, SDL_FLIP_NONE);
                numImage++;

            }else if (numImage<limite*3){
                SDL_RenderCopyEx(renderer, textureEnnemiRapide[2], NULL, &dest, angle, NULL, SDL_FLIP_NONE);
                numImage++;
            }else if(numImage<limite*4){
                SDL_RenderCopyEx(renderer, textureEnnemiRapide[3], NULL, &dest, angle, NULL, SDL_FLIP_NONE);
                numImage++;
                if(numImage==limite*4){
                    numImage=0;
                }
            }

        }else{
            SDL_RenderCopy(renderer, textureEnnemi, NULL, &dest);
        }
    }


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
    return x + TAILLE_ENNEMI/2;
}

int Ennemi::getYCentre()
{
    return y + TAILLE_ENNEMI/2;
}

int Ennemi::getXCentreFutur(int images)
{
    if(estAerien){
        return getXCentre()+images*dX;
    }
    switch(direction){
    case 0: return getXCentre()+ images*vitesse;
    case 1: return getXCentre();
    case 2: return getXCentre()- images*vitesse;
    case 3: return getXCentre();
    }


}

int Ennemi::getYCentreFutur(int images)
{
    if(estAerien){
        return getYCentre()+images*dY;
    }

    switch(direction){
    case 0: return getYCentre();
    case 1: return getYCentre()- images*vitesse;
    case 2: return getYCentre();
    case 3: return getYCentre()+ images*vitesse;
    }
}

int Ennemi::getVie(){
    return vie;
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
    x=MARGE_GAUCHE+TAILLE_CASE/2+TAILLE_CASE*xCase-TAILLE_ENNEMI/2;
    y=MARGE_HAUT+TAILLE_CASE/2+TAILLE_CASE*yCase-TAILLE_ENNEMI/2;
}

void Ennemi::avance()
{

    int xCase = (x-MARGE_GAUCHE)/ TAILLE_CASE;
    int yCase = (y-MARGE_HAUT)/ TAILLE_CASE;

    if(estAerien){
        //cout<<xChateau<<endl;
        x+=dX;
        y+=dY;

        /*if(deplacementX==x && deplacementY==y){
            if(rand()%2==0){
                x+=vitesse;
                y+=vitesse;
            }else{
                x-=vitesse;
                y-=vitesse;
            }
        }*/

    }else{






        if((y + TAILLE_ENNEMI/2)-vitesse < listeCases[yCase][xCase]->getYcentre()
                && listeCases[yCase][xCase]->getYcentre() < (y + TAILLE_ENNEMI/2)+vitesse
                && (x + TAILLE_ENNEMI/2)-vitesse < listeCases[yCase][xCase]->getXcentre()
                && listeCases[yCase][xCase]->getXcentre() < (x + TAILLE_ENNEMI/2)+vitesse)
        {
            //std::cout <<x + TAILLE_ENNEMI/2 << SDL_GetError() << std::endl;
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
                    x+=deplaX*vitesse;
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
                    y+=deplaY*vitesse;
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
                    x+=deplaX*vitesse;

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
                    y+=deplaY*vitesse;
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
                    x+=deplaX*vitesse;
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
                    y+=deplaY*vitesse;
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
                x+=vitesse;

            }
            else if(direction==1)
            {
                y-=vitesse;
            }
            else if(direction==2)
            {
                x-=vitesse;
            }
            else
            {
                y+=vitesse;
            }
        }

    }




}

void Ennemi::ajouteArgent()
{
    argent+= ARGENT_ENNEMI*multiplicateurArgentMort;
}
