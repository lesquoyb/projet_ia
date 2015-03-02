#ifndef RECUIT_SIMULE_D2
#define RECUIT_SIMULE_D2


/**
paramètres pour appliquer l'algo de recuit simulé à la recherche de minima de fonctions à 2 variables réelles

*/

#include "recuit_simule_d1.h"

inline const Vecteur2D changementAleatoire(const Vecteur2D & solution)
{
return Vecteur2D( changementAleatoire( solution.x), changementAleatoire( solution.y));
}

#endif // RECUIT_SIMULE_D2

