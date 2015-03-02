#ifndef GELEMENT_H
#define GELEMENT_H

#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include "exception.h"


using std::string;
using std::ostream;
using std::ostringstream;

/**
Représente la classe de base des éléments d'un graphe qui peuvent être des sommets ou des arêtes.

A ce niveau, on ne peut que définir que la clef d'un élément.

En effet tout élément d'un graphe est défini par une clef (c-à-d une valeur non nulle et unique)
*/

class GElement{

public:
    int clef;

    GElement(const int clef);
    operator string() const;

};

ostream & operator << (ostream & os, const GElement& gElement);

#endif // GELEMENT_H
