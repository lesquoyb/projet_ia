#ifndef VRAI_TEST
#define VRAI_TEST


#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <iostream>
#include <math.h>

#include "algebre_lineaire.h"
#include "recuit_simule.h"
#include "tools_math.h"
#include "vector2d.h"
#include "recuit_simule_d2.h"

double decrement(const double &old_temp){return old_temp-1;}
//using Graphe<double,string>::CycleEuclidien;


double cout_cycle(const Graphe<double,string>::CycleEulerien &c){
    double total = 0;
    for (PElement< Arete<double, string> >* i = c.arcsList; i != NULL; i = i->suivant){
        total += i->valeur->valeur;
    }
    return total;
}



const Graphe<double,string>::CycleEulerien changement(const Graphe<double,string>::CycleEulerien &c){
    /*TODO*/

    return c;
}

void vrai_test(){

    cout << "lololo" <<endl;
    double temp_init = 50;
    double temp_final = 0;
    int nb_max_iteration = 500;
    int nb_max_succes = 100;
    Graphe<double,string> graphe;
    graphe.creeSommet("A");
    graphe.creeSommet("B");
    graphe.creeSommet("C");
    graphe.creeSommet("D");
    graphe.creeSommet("E");

    for( PElement<Sommet<string> >* i = graphe.lSommets ;  i != NULL ; i = i->suivant ){
        for(PElement<Sommet<string> >* j = graphe.lSommets ;  j != NULL ; i = j->suivant){
            graphe.creeArete(i->valeur,j->valeur,50*rand());
        }
    }

    /* TODO */
    //graphe.complet();
    Graphe<double,string>::CycleEulerien solutionInitiale = graphe.getFirstCycle();
    cout << "graphe: " << graphe <<endl;

    SolutionCout< Graphe<double,string>::CycleEulerien > solution = recuitSimule(temp_init, temp_final, nb_max_iteration, nb_max_succes, solutionInitiale, &cout_cycle, &changement, &decrement);

    cout << "cout de la solution: " << solution.cout << endl;
    cout << "meilleur chemin: " << solution.solution << endl;

}

#endif // VRAI_TEST

