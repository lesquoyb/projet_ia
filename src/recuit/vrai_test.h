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
#include "connexion.h"



double decrement(const double &old_temp){return old_temp-1;}
//using Graphe<double,ValueData>::CycleEuclidien;


double cout_cycle(const Graphe<double,ValueData>::CycleEulerien &c){
    double total = 0;
    for (PElement< Arete<double, ValueData> >* i = c.arcsList; i != NULL; i = i->suivant){
        if (c.associatedGraphe != NULL) total +=  c.associatedGraphe->getAreteParSommets(i->valeur->debut, i->valeur->fin)->valeur;
    }
    return total;
}



const Graphe<double,ValueData>::CycleEulerien changement_aleatoire(const Graphe<double,ValueData>::CycleEulerien &c){
    return Graphe<double,ValueData>::CycleEulerien::changement_aleatoire(c) ;
}

void vrai_test(){
   // Connexion::linkServer("127.0.0.1");

    double temp_init = 50;
    double temp_final = 0;
    int nb_max_iteration = 100;
    int nb_max_succes = 10;
    Graphe<double,ValueData> graphe;
    ValueData *vA = new ValueData("A", Vecteur2D(0,2)), *vB = new ValueData("B", Vecteur2D(4,4)),
            *vC = new ValueData("C", Vecteur2D(6,4)), *vD = new ValueData("D", Vecteur2D(8,2)),
            *vE = new ValueData("E", Vecteur2D(6,0));
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


    graphe.add_missing_arcs(DBL_MAX); // On rend le graphe complet

    Graphe<double,ValueData>::CycleEulerien solutionInitiale = graphe.getFirstCycle();
   // graphe.toFile("recuit_initial", "a", "b", "c", solutionInitiale);

    cout << "cout solution init: " << cout_cycle(solutionInitiale) << endl;
    cout << "cout solution init: " << solutionInitiale.arcsList << endl;

    SolutionCout< Graphe<double,ValueData>::CycleEulerien > solution = recuitSimule(temp_init, temp_final, nb_max_iteration, nb_max_succes, solutionInitiale, &cout_cycle,&changement_aleatoire, &decrement);

    //graphe.toFile("recuit_final", "a", "b", "c", solution.solution);
    cout << endl << endl << endl << "cout de la solution: " << solution.cout << endl;
    cout << "cout de la solution: " << solution.solution.arcsList << endl;
    //cout << "meilleur chemin: " << solution.solution.arcsList << endl;

   // Connexion::unlinkServer();
}

#endif // VRAI_TEST

