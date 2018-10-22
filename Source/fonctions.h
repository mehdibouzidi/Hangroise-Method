#ifndef FONCTIONS
#define FONCTIONS
#include <vector>
#include <iostream>
#include <cmath>
#include "case.h"
/*******************    Relatives à la 1ere Phase *******************/
int minLigne(std::vector< std::vector<Case> > const & matrice, int const& l);
int minColonne(std::vector< std::vector<Case> > const & matrice, int const& c);

/*******************    Relatives à la 2eme Phase *******************/
int indiceLigneMoinsZero(std::vector< std::vector<Case> > const & matrice);
bool rienAEncadreBarre(std::vector< std::vector<Case> > const & matrice);
void encadreBarre(std::vector< std::vector<Case> >  & matrice);

/*******************    Relatives à la 3eme Phase *******************/


/*******************    Relatives à la 4eme Phase *******************/

int minSpecial(std::vector < std::vector<Case> > & matrice,std::vector<int> const&lignesNonTrac, std::vector<int> const&ColonnesNonTrac);


#endif // FONCTIONS

