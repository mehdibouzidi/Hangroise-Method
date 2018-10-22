#include "fonctions.h"

using namespace std;

int minLigne(const std::vector<std::vector<Case> > &matrice, const int &l)
{
    int mini=INFINITY;
    for(int j=0;j<matrice.size();j++)
    {
        if(matrice[l][j]<mini){mini=matrice[l][j].getValeur();}
    }

return mini;}


int minColonne(const std::vector<std::vector<Case> > &matrice, const int &c)
{
    int mini=INFINITY;
    for(int i=0;i<matrice.size();i++)
    {
        if(matrice[i][c]<mini){mini=matrice[i][c].getValeur();}
    }

return mini;
}


int indiceLigneMoinsZero(const std::vector<std::vector<Case> > &matrice)
{
    vector <int> nombreDeZero;
    int cpt(0);
    for(int i=0;i<matrice.size();i++)
    {
        for(int j=0;j<matrice.size();j++)
        {
            if(matrice[i][j].getValeur()==0 &&
                    !matrice[i][j].getEncadre() &&
                    !matrice[i][j].getBarre()) {cpt++;}
        }
        nombreDeZero.push_back(cpt);

        cpt=0;

    }
    int mini=INFINITY;
    int laLigne;
    for(int i=0; i<nombreDeZero.size();i++)
    {
        if(nombreDeZero[i]!=0 && nombreDeZero[i]<mini)
        {mini=nombreDeZero[i]; laLigne=i;}
    }

return laLigne;}


void encadreBarre(std::vector<std::vector<Case> > &matrice)
{
    int indiceLigne;
    int j;


    while(!rienAEncadreBarre(matrice))
    {
        j=0;
        indiceLigne=indiceLigneMoinsZero(matrice);


        while(true)
        {
            if(matrice[indiceLigne][j].getValeur()==0)
            {
                matrice[indiceLigne][j].setEncadre(true);
                break;
            }
            j++;
        }

        for(int k=j;k<matrice.size();k++)
        {
            if(matrice[indiceLigne][k].getValeur()==0 && !matrice[indiceLigne][k].getEncadre())
            {matrice[indiceLigne][k].setBarre(true);}
        }

        for(int i=indiceLigne;i<matrice.size();i++)
        {
            if(matrice[i][j].getValeur()==0 && !matrice[i][j].getEncadre())
            {matrice[i][j].setBarre(true);}
        }
    }

}


bool rienAEncadreBarre(const std::vector<std::vector<Case> > &matrice)
{
    for(int i=0;i<matrice.size();i++)
    {
        for(int j=0;j<matrice.size();j++)
        {
            if(!matrice[i][j].getEncadre() && !matrice[i][j].getBarre() &&matrice[i][j].getValeur()==0) return false;
        }
    }
    return true;
}


int minSpecial(std::vector < std::vector<Case> > & matrice,std::vector<int> const&lignesNonTrac, std::vector<int> const&ColonnesNonTrac)
{
    int minimum=INFINITY;
    for(int i=0;i<lignesNonTrac.size();i++)
    {
        for(int j=0;j<ColonnesNonTrac.size();j++)
        {
            if(matrice[lignesNonTrac[i]][ColonnesNonTrac[j]].getValeur()<minimum){minimum=matrice[lignesNonTrac[i]][ColonnesNonTrac[j]].getValeur();}
        }
    }

    for(int i=0;i<lignesNonTrac.size();i++)
    {
        for(int j=0;j<ColonnesNonTrac.size();j++)
        {
            matrice[lignesNonTrac[i]][ColonnesNonTrac[j]]-=minimum;
        }
    }
return minimum;}
