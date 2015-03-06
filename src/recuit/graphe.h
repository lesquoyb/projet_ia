#ifndef GRAPHE
#define GRAPHE
#include "pelement.h"
#include "sommet.h"
#include "arete.h"


template <class S, class T>
class Graphe {
protected:
	int prochaineClef;

public:
	PElement< Arete<S,T> > * lAretes; // liste d'arêtes
	PElement< Sommet<T> > * lSommets; // liste de sommets

	Graphe();
	Graphe(const Graphe<S,T> & graphe);
	const Graphe<S,T>& operator=(const Graphe<S,T> & graphe);

	~Graphe();

	int nombreSommets() const;
	int nombreAretes() const;

	Sommet<T>* creeSommet(const T & info);
	Arete<S,T>* creeArete( Sommet<T> * debut, Sommet<T> * fin, const S & info);

	/**
	recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
	*/
	PElement<pair<Sommet<T>*, Arete<S,T>*>>* adjacences(const Sommet<T> * sommet) const;
	operator string() const;

	Arete<S,T>* getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const;
};

template <class S, class T>
Graphe<S,T>::Graphe(): prochaineClef(0),lAretes(NULL),lSommets(NULL){}

template <class S, class T>
Graphe<S,T>::Graphe(const Graphe<S,T> & graphe) {
	throw Exception("pas encore écrit : reste à faire");
}

template <class S, class T>
const Graphe<S,T> & Graphe<S,T>::operator = (const Graphe<S,T> & graphe) {
	throw Exception("pas encore écrit : reste à faire");
}

template <class S, class T>
Graphe<S,T>::~Graphe() {
	PElement< Arete<S,T> >::efface2(this->lAretes);
	PElement<Sommet<T> >::efface2(this->lSommets);
}

template <class S, class T>
Sommet<T> * Graphe<S,T>::creeSommet( const T & info) {
	Sommet<T> * sommetCree = new Sommet<T>( prochaineClef++,info);
	lSommets = new PElement< Sommet<T> >( sommetCree, lSommets);
	return sommetCree;
}

template <class S, class T>
Arete<S,T> * Graphe<S,T>::creeArete( Sommet<T> * debut, Sommet<T> * fin, const S & info) {
	Arete<S,T> * nouvelleArete;

	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (! PElement< Sommet<T> >::appartient(debut,lSommets) ) throw Exception("début d'arête non défini");
	if (! PElement< Sommet<T> >::appartient(fin,lSommets)) throw Exception("fin d'arête non définie");

	nouvelleArete = new Arete<S,T>(prochaineClef++, debut, fin,  info);
	lAretes = new PElement< Arete<S,T> >( nouvelleArete, lAretes);
	debut->degre++; fin->degre++;
	return nouvelleArete;
}

template <class S, class T>
int Graphe<S,T>::nombreSommets() const{
    return PElement< Sommet<T> >::taille(lSommets);
}


template <class S, class T>
int Graphe<S,T>::nombreAretes() const {
    return PElement< Arete<S,T> >::taille(lAretes);
}

template <class S, class T>
Graphe<S,T>::operator string() const{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = "<< this->prochaineClef << endl;
	oss <<"nombre de sommets = "<< this->nombreSommets()<<"\n";
	oss << PElement<Sommet<T> >::toString( lSommets, "", "\n", "");
	oss <<"nombre d'arêtes = " << this->nombreAretes()<<"\n";
	oss << PElement<Arete<S,T> >::toString( lAretes, "", "\n", "");
	oss <<")";
	return oss.str();
}

template <class S, class T>
ostream & operator<<(ostream & os, const Graphe<S,T> & graphe) {
	return os << (string)graphe;
}

template <class S, class T>
Arete<S,T> * Graphe<S,T>::getAreteParSommets( const Sommet<T> * s1, const Sommet<T> * s2) const{
	PElement<Arete<S,T> > * l;
	for (l = this->lAretes; l; l = l->s) {
        if ( l->v->estEgal(s1,s2)) return l->v;
	}
    return NULL;
}


// Retourne la liste des voisins d'un Sommet => Pair(Sommet - Arete)
template <class S, class T>
PElement<pair<Sommet<T>*, Arete<S,T>*>>* Graphe<S,T>::adjacences(const Sommet<T> * sommet) const{
    const PElement< Arete<S,T> > * l;
    PElement< pair< Sommet<T> *, Arete<S,T>* > > * r;

    for ( l = lAretes, r = NULL; l; l = l->s)

        if ( sommet == l->v->debut)
            r = new PElement< pair< Sommet<T> *, Arete<S,T>* > > (new pair<Sommet<T>*, Arete<S,T>*>(l->v->fin, l->v), r);
        else
            if ( sommet == l->v->fin)
               r = new PElement< pair< Sommet<T> *, Arete<S,T>* > >
               ( new pair< Sommet<T> *, Arete<S,T>* >
                (l->v->debut,l->v),r);
    return r;
}


#endif // GRAPHE 