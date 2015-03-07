#include <iostream>
#include "testpelement.h"
#include "test_gelement.h"
#include "vector2d.h"
#include "test_recuit_simule_d2.h"
#include "vrai_test.h"
#include "valuedata.h"


using namespace std;

int main()
{
    //test_pelement();
    //test_gelement();
    //test_recuit_simule_d2();

    cout << endl << endl <<endl << "Test du vrai recuit simulé " << endl;

    // Partie BaPeuhtiste
    //vrai_test();

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

    for( PElement<Sommet<ValueData> >* i = graphe.lSommets ;  i != NULL ; i = i->suivant ){
        for(PElement<Sommet<ValueData> >* j = graphe.lSommets ;  j != NULL ; j = j->suivant){
            graphe.creeArete(i->valeur,j->valeur,50*rand());
        }
    }

    cout << "titre = recuit simule" << endl;
    cout << "legende = Résultat du recuit simule" << endl;
    cout << "resume = résultat du recuit simule" << endl;
    cout << "type de scene = courbes" << endl;
    cout << "coin bas gauche de la figure sur l'écran en coordonnées monde = ( -1, -1)" << endl;
    cout << "coin haut droit de la figure sur l'écran en coordonnées monde = ( 10, 10)" << endl;
    cout << "nombre de points remarquables =" << graphe.nombreSommets() << endl;
    PElement<Sommet<ValueData> > *tempsom = graphe.lSommets;
    while (tempsom != NULL) {
        cout << "point remarquable = 2 black (" << tempsom->valeur->valeur.position.x << "," << tempsom->valeur->valeur.position.x << ") " << tempsom->valeur->valeur.nom << endl;
        tempsom = tempsom->suivant;
    }

    cout << "nombre de courbes = " << graphe.nombreAretes() << endl;
    PElement<Arete<double,ValueData> > *temp = graphe.lAretes;
    while (temp != NULL) {
        cout << "couleur =  green" << endl;
        cout << "nombre de points = 2" << endl;
        cout << "( " << temp->valeur->debut->valeur.position.x << ", " << temp->valeur->debut->valeur.position.y << ")" << endl;
        cout << "( " << temp->valeur->fin->valeur.position.x << ", " << temp->valeur->fin->valeur.position.y << ")" << endl;
        temp = temp->suivant;
    }

    return 0;
}

