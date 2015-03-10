#ifndef SOMMET
#define SOMMET
#include "gelement.h"

/**
Sommet d'un graphe en général
v est l'information associée au sommet : elle dépend de l'application du graphe
*/
template <class T>
class Sommet : public GElement {
public:
	int degre;
	T valeur;
	
	Sommet(const int clef, const T & v): GElement(clef), degre(0), valeur(v){}
	operator string() const;
    bool operator==(const Sommet<T>&) const;
};

template <class T>
Sommet<T>::operator string () const {
	ostringstream oss;

	oss <<"Sommet("<<endl;
	oss << GElement::operator string()<<endl;
	oss<<"degré = " << degre << endl;
	oss <<"v = " <<  valeur << endl;
	oss<<")";
	return oss.str();
}

template <class T>
bool Sommet<T>::operator==(const Sommet<T>& s) const {
    return (s.degre == degre && s.valeur == valeur);
}

template <class T>
ostream & operator<<(ostream & os, const Sommet<T> & sommet) { return os << (string) sommet; }

#endif // SOMMET
