#ifndef CASE_H
#define CASE_H


class Case
{
public:
    Case();
    Case(int val,bool enca,bool barr);
    Case(int val);

    /*** Setters ***/
    void setValeur(int const& val);
    void setEncadre(bool const& b);
    void setBarre(bool const& b);


    /*** Guetters ***/
    int getValeur()const;
    bool getEncadre()const;
    bool getBarre()const;



    /*** Surcharge ***/
    Case& operator-=(Case const& case2);
    Case& operator-=(int const& val2);
    Case& operator+=(int const& val2);

    bool estPlusPetit(int const& case2)const;
private:
    int valeur;
    bool encadre;
    bool barre;
};
bool operator<(Case const& case1,int const& case2);
#endif // CASE_H
