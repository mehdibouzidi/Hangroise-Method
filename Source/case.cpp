#include "case.h"

Case::Case(): valeur(0), encadre(false), barre(false)
{

}

Case::Case(int val, bool enca, bool barr): valeur(val), encadre(enca), barre(barr)
{

}

Case::Case(int val): valeur(val), encadre(false),barre(false)
{

}

int Case::getValeur() const{return valeur;}

bool Case::getEncadre() const{return encadre;}

bool Case::getBarre() const{return barre;}

void Case::setValeur(int const& val){valeur=val;}

void Case::setEncadre(bool  const& b){encadre=b;}

void Case::setBarre(bool const& b){barre=b;}


Case &Case::operator-=(const Case &case2)
{
    valeur-=case2.valeur;

    return *this;
}

Case &Case::operator-=(const int &val2)
{
    valeur-=val2;
    return *this;
}

Case &Case::operator+=(const int &val2)
{
    valeur+=val2;
    return *this;
}



bool Case::estPlusPetit(const int &case2)const{ if(valeur<case2) return true; else return false;}

bool operator<(const Case &case1, const int &case2)
{
    if(case1.estPlusPetit(case2))
        return true;
    else return false;
}
