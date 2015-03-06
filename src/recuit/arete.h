#ifndef ARETE
#define ARETE

/**
représente une arête d'un graphe en général.
Une arête est définie par un sommet-début et par un sommet-fin et par une information v.

On ne connait pas la nature de v à ce niveau (v pourrait contenir une couleur, une longueur, un nom, etc.)

T est la nature de l'information portée par un sommet et
S est la nature de l'information portée par une arête
*/

template <class S, class T>
class Arete : public GElement {
public:
	Sommet<T> *debut, *fin;
	S valeur;
	
	Arete(int clef, Sommet<T> * debut, Sommet<T> * fin, const S & v): GElement(clef), debut(debut), fin(fin), valeur(v) {}

	operator string () const;
    bool estEgal( const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template <class S, class T>
Arete<S,T>::operator string () const {
	ostringstream oss;
	oss << "Arete  (" << endl;
	oss << GElement::operator string() << endl;
	oss << "clef debut = " << debut->clef << endl;
	oss << "clef fin = " << fin->clef << endl;
	oss << "v = " << valeur << endl;
	oss << ")";
	return oss.str();
}

template <class S, class T>
ostream & operator << (ostream & os, const Arete<S,T> & arete) { return os << (string) arete; }

template <class S, class T>
bool Arete<S,T>::estEgal( const Sommet<T> * s1, const Sommet<T> * s2) const { 
	return (s1 == debut && s2 == fin) || (s1 == fin && s2 == debut);
}

#endif // ARETE
