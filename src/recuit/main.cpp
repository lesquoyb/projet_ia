#include <iostream>
#include "testpelement.h"
#include "test_gelement.h"
#include "vector2d.h"
#include "test_recuit_simule_d2.h"
//#include "vrai_test.h"
#include "valuedata.h"
#include "connexion.h"

using namespace std;

int main()
{
    //test_pelement();
    //test_gelement();
    //test_recuit_simule_d2();

    cout << endl << endl <<endl << "Test du vrai recuit simulé " << endl;


    // Partie BaPeuhtiste
    vrai_test();

    // Partie Mattew

    ValueData *vA = new ValueData("A", Vecteur2D(1,1)), *vB = new ValueData("B", Vecteur2D(2,2)),
            *vC = new ValueData("C", Vecteur2D(3,2)), *vD = new ValueData("D", Vecteur2D(4,1)),
            *vE = new ValueData("E", Vecteur2D(3,0));
    Graphe<double,ValueData> graphe;
    graphe.creeSommet(*vA);
    graphe.creeSommet(*vB);
    graphe.creeSommet(*vC);
    graphe.creeSommet(*vD);
    graphe.creeSommet(*vE);

    PElement<Arete<double,ValueData> > *temp = graphe.lAretes;

    for( PElement<Sommet<ValueData> >* i = graphe.lSommets ;  i != NULL ; i = i->suivant ){
        for(PElement<Sommet<ValueData> >* j = graphe.lSommets ;  j != NULL ; j = j->suivant){
            graphe.creeArete(i->valeur,j->valeur,50*rand());
        }
    }

    Connection::linkServer("192.168.56.1");
    Connection::commit("s{2,1,3,2,#222222}");
    Connection::push();

    PElement<Arete<double,ValueData> > *temp = graphe.lAretes;
    while (temp != NULL) {
        Connection::commit("s{" + temp->valeur->debut->valeur.position.x + "," + temp->valeur->debut->valeur.position.y + "," +
                           temp->valeur->fin->valeur.position.x + "," + temp->valeur->fin->valeur.position.y + ",#222222}";
        temp = temp->suivant;
    }
    Connection::push();


    //graphe.toFile("recuit", "Recuit Simule", "Résultat du recuit simule", "plop");


}

