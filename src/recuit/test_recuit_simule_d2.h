#ifndef TEST_RECUIT_SIMULE_D2
#define TEST_RECUIT_SIMULE_D2

/*
teste l'algorithme du recuit simulé pour rechercher le minimum d'une fonction math réelle à 2 variables


Pour cette application, l'ensemble des solutions, S = R^2 = {(x,y) avec x dans R et y dans R}
*/

#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <math.h>

#include "algebre_lineaire.h"
#include "recuit_simule.h"
#include "tools_math.h"
#include "vector2d.h"
#include "recuit_simule_d2.h"

//#include "MesMaths.h"

using namespace std;

/*
Le recuit simule est appliqué à la recherche des minimas  des 2 fonctions suivantes à 2 variables
*/

/**
paraboloïde de sommet (2,2,3)
*/
inline double cout1(const Vecteur2D & solution)
{
return f1(solution);
}

/**
onde circulaire amortie de minimum -5 en (0,0)

*/
inline double cout2(const Vecteur2D & solution) // le minimum est -5 atteint en (0,0)
{
return f2(solution);
}

int test_recuit_simule_d2()
//int main5()
{
char ch;
srand (time(NULL));		// initialisation du générateur de nombres pseudo-aléatoires

double  tInitiale = 1000;		// température initiale : affectation telle que deltaCoutMax/tInitiale  ~= 0
double  tFinale = 0;			// température finale : affectation arbitraire telle que température finale <= température initiale
int nombreTentativesMax = 100;	// arbitraire : nombre max de tentatives par palier de température
int nombreSuccesMax = 50;		// arbitraire : nombre max de succès par palier de température
//double solutionInitiale = -rand() +	rand(); // tirage d'un nombre réel quelconque
Vecteur2D solutionInitiale ( tirageAleatoire(-10,10), tirageAleatoire(-10,10)); // tirage d'un point quelconque

Vecteur2D meilleureSolution;
double coutMeilleureSolution;

//const S recuitSimule(const double & tInitiale, const double & tFinale, const int nombreTentativesMax, const int nombreSuccesMax, const S & solutionInitiale,
//	double (*cout)(const S & solution), const S (* changementAleatoire)(const S & solution), double (*succ)(const double & temperature))
cout << "recherche du minimum d'une fonction à 2 variables réelles par la méthode du recuit simulé" << endl;
cin >> ch;
meilleureSolution = recuitSimule1( tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax, solutionInitiale,
    cout1, changementAleatoire, succ, coutMeilleureSolution);

cout << "le minimum de la fonction est trouvé en : " << meilleureSolution <<", le minimum vaut : "<< coutMeilleureSolution << endl;
cin >> ch;

SolutionCout<Vecteur2D> meilleureSolution2 = recuitSimule( tInitiale, tFinale, nombreTentativesMax, nombreSuccesMax, solutionInitiale,
    cout1, changementAleatoire, succ);

cout << "meilleure solution et son coût : " << meilleureSolution2 << endl;


cin >> ch;
return 0;
}


#endif // TEST_RECUIT_SIMULE_D2

