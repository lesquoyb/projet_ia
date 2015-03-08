#ifndef ERREUR
#define ERREUR

using namespace std;

#include <string>
#include <iostream>

class Erreur
{
public:
    const static int LONGUEURMESSAGE = 100;
    char message[1 + LONGUEURMESSAGE];
    Erreur();
    Erreur(const char * messageErreur);

    operator string() const;
};

ostream & operator << (ostream & os, const Erreur & erreur);

#endif
