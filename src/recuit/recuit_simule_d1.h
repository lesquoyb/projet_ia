#ifndef RECUIT_SIMULE_D1
#define RECUIT_SIMULE_D1

/**

paramètres pour appliquer l'algo du recuit simulé à la recherche de minima de fonctions à une variable réelle

*/

#include "recuit_simule.h"

inline double succ(const double & temperature)
{
return temperature - 1;
}

inline double changementAleatoire(const double & solution)
{
return solution + tirageAleatoire(-1, 1);	// doit-il y avoir un rapport entre la largeur du domaine de recherche et l'amplitude de la perturbation aléatoire ?
}



#endif // RECUIT_SIMULE_D1

