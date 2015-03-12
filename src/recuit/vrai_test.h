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
#include "valuedata.h"



double decrement(const double &old_temp){return old_temp-1;}
//using Graphe<double,ValueData>::CycleEuclidien;


double cout_cycle(const Graphe<double,ValueData>::CycleEulerien &c){
    double total = 0;
    for (PElement< Arete<double, ValueData> >* i = c.arcsList; i != NULL; i = i->suivant){
        total += i->valeur->valeur;
    }
    return total;
}



const Graphe<double,ValueData>::CycleEulerien changement_aleatoire(const Graphe<double,ValueData>::CycleEulerien &c){
    return Graphe<double,ValueData>::CycleEulerien::changement_aleatoire(c) ;
}

void vrai_test(){


    double temp_init = 50;
    double temp_final = 0;
    int nb_max_iteration = 100;
    int nb_max_succes = 10;
    Graphe<double,ValueData> graphe;
    ValueData *vA = new ValueData("A", Vecteur2D(1,1)), *vB = new ValueData("B", Vecteur2D(2,2)),
            *vC = new ValueData("C", Vecteur2D(3,2)), *vD = new ValueData("D", Vecteur2D(4,1)),
            *vE = new ValueData("E", Vecteur2D(3,0));
    graphe.creeSommet(*vA);
    graphe.creeSommet(*vB);
    graphe.creeSommet(*vC);
    graphe.creeSommet(*vD);
    graphe.creeSommet(*vE);


    for( PElement<Sommet<ValueData> >* i = graphe.lSommets ;  i != NULL ; i = i->suivant ){
        for(PElement<Sommet<ValueData> >* j = i->suivant ;  j != NULL ; j = j->suivant){
            graphe.creerLien(i->valeur,j->valeur, double(rand() % 50));
        }
    }

   /*ne sers à rien mfker */
    graphe.add_missing_arcs(DBL_MAX); // On rend le graphe complet

    Graphe<double,ValueData>::CycleEulerien solutionInitiale = graphe.getFirstCycle();

    //solutionInitiale.toFile("recuit_initial.txt", "a", "b", "c");

    cout << "cout solution init: " << cout_cycle(solutionInitiale) << endl;
    SolutionCout< Graphe<double,ValueData>::CycleEulerien > solution = recuitSimule(temp_init, temp_final, nb_max_iteration, nb_max_succes, solutionInitiale, &cout_cycle,&changement_aleatoire, &decrement);

  //  solution.solution.toFile("recuit_final.txt", "a", "b", "c");
    cout << "cout de la solution: " << solution.cout << endl;
    //cout << "meilleur chemin: " << solution.solution.arcsList << endl;

}

#endif // VRAI_TEST

