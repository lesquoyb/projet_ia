#ifndef TEST_RECUIT_SIMULE_D1
#define TEST_RECUIT_SIMULE_D1

/*
teste l'algorithme du recuit simulé pour rechercher le minimum d'une fonction math réelle à 1 variable

Pour cette application, l'ensemble des solutions, S = R
*/

#include <stdlib.h>     /* pour accéder aux fonctions de génération de nombres pseudo-aléatoires : srand, rand */
#include <time.h>
#include <iostream>
#include <math.h>
#include "algebre_lineaire.h"
#include "recuit_simule.h"
#include "tools_math.h"
#include "recuit_simule_d1.h"

using namespace std;

/*
Le recuit simule est appliqué à la recherche des minima des 2 fonctions suivantes
*/

/*
parabole
*/
inline double cout1(const double & solution)
{
return f1(solution);
}

/*
sinusoïde amortie

*/
inline double cout2(const double & solution){ // le minimum est -5 atteint en 0
    return f2(solution);
}


int test_recuit_simule_d1(){


    srand (time(NULL));		// initialisation du générateur de nombres pseudo-aléatoires

    double  tInitiale = 1000;		// température initiale : affectation telle que deltaCoutMax/tInitiale  ~= 0
    double  tFinale = 0;			// température finale : affectation arbitraire telle que température finale <= température initiale
    int nombreTentativesMax = 50;	// arbitraire : nombre max de tentatives par palier de température
    int nombreSuccesMax = 25;		// arbitraire : nombre max de succès par palier de température
    //double solutionInitiale = -rand() +	rand(); // tirage d'un nombre réel quelconque
    double solutionInitiale = tirageAleatoire(-10,10); // tirage d'un nombre réel quelconque

    double meilleureSolution1;
    double coutMeilleureSolution1;

    //const S recuitSimule(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
    //	double (*cout)(const S & solution), const S (* changementAleatoire)(const S & solution), double (*succ)(const double & temperature))

    cout << "recherche du minimum d'une fonction à une variable par la méthode du recuit simulé" << endl;
    meilleureSolution1 = recuitSimule1( tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax, solutionInitiale,
        cout2, changementAleatoire, succ, coutMeilleureSolution1);

    cout << "le minimum de la fonction est trouvé en : " << meilleureSolution1 <<", le minimum vaut : "<< coutMeilleureSolution1 << endl;


    SolutionCout<double> meilleureSolution2 = recuitSimule( tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax, solutionInitiale,
        cout2, changementAleatoire, succ);

    cout << "meilleure solution et son coût : " << meilleureSolution2 << endl;

    return 0;
}



#endif // TEST_RECUIT_SIMULE_D1

