#ifndef ARETE
#define ARETE

/**
représente une arête d'un graphe en général.
Une arête est définie par un sommet-début et par un sommet-fin et par une information v.

On ne connait pas la nature de v à ce niveau (v pourrait contenir une couleur, une longueur, un nom, etc.)

T est la nature de l'information portée par un sommet et
S est la nature de l'information portée par une arête
*/
#include "gelement.h"
#include "sommet.h"


template <class ArcCost, class VertexType>
class Arete : public GElement {

public:

    Sommet <VertexType> *debut, *fin;
    ArcCost valeur;
	
    Arete(int clef, Sommet<VertexType> * debut, Sommet<VertexType> * fin, const ArcCost & v):
        GElement(clef),debut(debut),fin(fin),valeur(v){}

    Arete(const Arete<ArcCost, VertexType>* ar): GElement(ar->clef), debut(ar->debut), fin(ar->fin), valeur(ar->valeur){}

	operator string () const;

    /**
     * vérifie si *this s'appuie sur s1 et s2
     *
     * DONNEES : *this, s1, s2
     *
     * RESULTATS : true si *this s'appuie sur s1 et s2 c'est-à-dire si (début == s1 et fin == s2) ou (début == s2 et fin == s1), false sinon
     *
     * */
    bool estEgal( const Sommet<VertexType> * s1, const Sommet<VertexType> * s2) const;

    bool estEgal(const Arete<ArcCost,VertexType> &a) const;

};

template <class S, class T>
Arete<S,T>::operator string () const {
	ostringstream oss;
	oss << "Arete  (" << endl;
	oss << GElement::operator string() << endl;
    oss << "clef debut = " << debut->valeur << endl;
    oss << "clef fin = " << fin->valeur << endl;
	oss << "v = " << valeur << endl;
	oss << ")";
	return oss.str();
}

template <class S, class T>
ostream & operator << (ostream & os, const Arete<S,T> & arete) { return os << (string) arete; }

template <class S, class T>
bool Arete<S,T>::estEgal( const Sommet<T> * s1, const Sommet<T> * s2) const { 
    return (s1->valeur == debut->valeur && s2->valeur == fin->valeur) || (s1->valeur == fin->valeur && s2->valeur == debut->valeur);
}

template <class ArcCost, class VertexType>
bool Arete<ArcCost,VertexType>::estEgal(const Arete<ArcCost,VertexType> &a) const{
    return estEgal(a.debut,a.fin);
}

#endif // ARETE
