#include <iostream>
#include "testpelement.h"
#include "test_gelement.h"
#include "vector2d.h"
#include "test_recuit_simule_d2.h"
#include "vrai_test.h"
#include "valuedata.h"
#include "connexion.h"

using namespace std;

int main() {
    //test_pelement();
    //test_gelement();
    //test_recuit_simule_d2();

    cout << endl << endl <<endl << "Test du vrai recuit simulé " << endl;


    // Partie BaPeuhtiste
    //vrai_test();

    // Partie Mattew
    Connexion::linkServer("127.0.0.1");

    ValueData *vA = new ValueData("A", Vecteur2D(1,1)), *vB = new ValueData("B", Vecteur2D(2,2)),
            *vC = new ValueData("C", Vecteur2D(3,2)), *vD = new ValueData("D", Vecteur2D(4,1)),
            *vE = new ValueData("E", Vecteur2D(3,0));
    Graphe<double,ValueData> graphe;
    graphe.creeSommet(*vA);
    graphe.creeSommet(*vB);
    graphe.creeSommet(*vC);
    graphe.creeSommet(*vD);
    graphe.creeSommet(*vE);


    for( PElement<Sommet<ValueData> >* i = graphe.lSommets ;  i != NULL ; i = i->suivant ){
        for(PElement<Sommet<ValueData> >* j = graphe.lSommets ;  j != NULL ; j = j->suivant){
            graphe.creeArete(i->valeur,j->valeur,50*rand());
        }
    }

    Graphe<double,ValueData> graphe2 = graphe.solutionInitiale();

    graphe2.ServeurSend();
    //graphe.toFile("recuit", "Recuit Simule", "Résultat du recuit simule", "plop");


}

