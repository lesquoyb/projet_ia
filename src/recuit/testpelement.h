
/**
Test des fonctionnalités de PElement : la classe template représentant des listes linéaires récursives
*/
#include <iostream>
#include <string>
#include <stdlib.h>
#include "pelement.h"

using namespace std;


bool plusPetitOuEgal(const double * x, const double * y){
    return *x <= *y;
}

bool plusPetitOuEgal(const string * x, const string * y){
    return x->compare( *y) <= 0;
}

int test_pelement(){
    cout << "test des fonctionnalités de la classe PElement<T>" << endl;

    double x1(2), x2(5), x3(7.5), x4(9);
    string s1 = "carotte", s2 = "cerise", s3 = "orange";
    PElement<double> * l1;
    PElement<string> * l2;

    l1 = NULL;
    l1 = new PElement<double>(&x4,l1);
    l1 = new PElement<double>(&x3,l1);
    l1 = new PElement<double>(&x2,l1);
    l1 = new PElement<double>(&x1,l1);

    l2 = new PElement<string>(&s1,
    new PElement<string>(&s2,
    new PElement<string>(&s3,NULL)));

    int n1, n2;
    n1 = PElement<double>::taille(l1); n2 = PElement<string>::taille(l2);

    cout << "taille de l1  = " << n1 << ", taille de l2 = " << n2 << endl;

    cout << "l1 = " << l1 << endl;
    cout << "l2 = " << l2 << endl;

    double y1(-7),y2(6),y3(13);
    string c1("fraise"),c2("ananas"),c3("pomme");

    PElement<double>::insertionOrdonnee(&y1,l1,plusPetitOuEgal);
    PElement<double>::insertionOrdonnee(&y2,l1,plusPetitOuEgal);
    PElement<double>::insertionOrdonnee(&y3,l1,plusPetitOuEgal);

    PElement<string>::insertionOrdonnee(&c1,l2,plusPetitOuEgal);
    PElement<string>::insertionOrdonnee(&c2,l2,plusPetitOuEgal);
    PElement<string>::insertionOrdonnee(&c3,l2,plusPetitOuEgal);

    cout << "après insertion ordonnée des 3 valeurs "<< y1 <<", "<< y2 << " et "<< y3 << ", "<< endl << "l1 = " << l1 << endl;
    cout << "après insertion ordonnée de 3 valeurs, "<< c1 <<", "<< c2 << " et "<< c3 <<", "<< endl << "l2 = " << l2 << endl;

    double * p1 = PElement<double>::depiler(l1);

    cout << "l1 a été dépilée, l1 = " << l1 << endl;
    cout << "la valeur extraite est : " << *p1 << endl;

    string * p2 = PElement<string>::depiler(l2);

    cout << "l2 a été dépilée, l2 = " << l2 << endl;
    cout << "la valeur extraite est : " << *p2 << endl;

    bool ok1 = PElement<double>::retire(&y2,l1);

    bool ok2 = PElement<string>::retire(&s1,l2);

    if (ok1) cout << y2 << " a été retirée de l1, à présent l1 = " << l1 << endl;

    if (ok2) cout << s1 << " a été retirée de l2, à présent l2 = " << l2 << endl;

    PElement<double>::efface1(l1);

    cout << "l1 a été effacée avec efface1(), à présent l1 = " << l1 << endl;

    PElement<string>::efface1(l2);

    cout << "l2 a été effacée avec efface1(), à présent l2 = " << l2 << endl;

    l1 = new PElement<double>( new double(2),
    new PElement<double>(new double(7),
    new PElement<double>(new double(13),NULL)));

    cout << " l1 a été re-créée avec des valeurs allouées dynamiquement,"<< endl << " l1 = "<<l1 << endl;

    l2 = new PElement<string>(new string("rene"),
    new PElement<string>(new string("la"),
    new PElement<string>(new string("taupe"),NULL)));

    cout << " l2 a été re-créée avec des valeurs allouées dynamiquement,"<< endl << " l2 = "<<l2 << endl;

    PElement<double>::efface2(l1);

    cout << "l1 a été effacée avec efface2(), à présent l1 = " << l1 << endl;

    PElement<string>::efface2(l2);

    cout << "l2 a été effacée avec efface2(), à présent l2 = " << l2 << endl;

return 0;
}
