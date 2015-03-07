#ifndef GRAPHE
#define GRAPHE
#include "pelement.h"
#include "sommet.h"
#include "arete.h"
#include <fstream>


template <class ArcCost, class VertexType>
class Graphe {


protected:
	int prochaineClef;

public:


    class CycleEulerien{

    public:

        PElement< Arete<ArcCost, VertexType> >* arcsList;

        void insert(const Arete<ArcCost, VertexType> * arete){
            arcsList = new PElement<Arete<ArcCost, VertexType> >(arete, arcsList);
        }



    };


	PElement< Arete<ArcCost, VertexType> > * lAretes; // liste d'arêtes
	PElement< Sommet<VertexType> > * lSommets; // liste de sommets



    CycleEulerien getFirstCycle()const{
        /* TODO achtung graphe avec un élément */
        CycleEulerien c;
        //Sommet<VertexType>* last = lSommets->valeur;
		for (PElement< Sommet<VertexType> >* sommet = lSommets->suivant; sommet != NULL; sommet = sommet->suivant){
			if (sommet->suivant == NULL){
                //si suivant est null on fait l'arrête sommet -> last
                //c.insert();
				/*TODO */
				//   c.arcsList = new PElement<

			}

		}
        return c;
	}

	Graphe();

	/**
	* constructeur de copie obligatoire car la classe comporte une partie dynamique
	* */
	Graphe(const Graphe<ArcCost, VertexType> & graphe);

	/**
	* opérateur = obligatoire car la classe comporte une partie dynamique
	* */
	const Graphe<ArcCost, VertexType> & operator = (const Graphe<ArcCost, VertexType> & graphe);

	/**
	* destructeur obligatoire car la classe comporte une partie dynamique
	* */
	~Graphe();

	int nombreSommets() const;
	int nombreAretes() const;

	/**
	* crée un sommet isolé
	* */
	Sommet<VertexType> * creeSommet(const VertexType & info);

	/**
	* crée une arête joignant les 2 sommets debut et fin
	*
	* * met à jour les champs degré de debut et de fin
	* */
	Arete<ArcCost, VertexType> * creeArete(Sommet<VertexType> * debut, Sommet<VertexType> * fin, const ArcCost & info);

	/**
	recherche la liste des paires (voisin, arête) adjacentes de sommet dans le graphe
	*/
	PElement< pair< Sommet<VertexType> *, Arete<ArcCost, VertexType>* > >  *
		adjacences(const Sommet<VertexType> * sommet) const;
	operator string() const;

	/**
	* cherche l'arête s1 - s2 ou l'arête s2 - s1 si elle existe
	*
	* DONNEES : s1 et s2 deux sommets quelconques du graphe
	* RESULTATS : l'arête s'appuyant sur s1 et s2 si elle existe, NULL sinon
	*
	* */
	Arete<ArcCost, VertexType> * getAreteParSommets(const Sommet<VertexType> * s1, const Sommet<VertexType> * s2) const;

    void toFile(string filename, string titre, string legende, string resume);
};

template <class S, class T>
Graphe<S, T>::Graphe() : prochaineClef(0), lAretes(NULL), lSommets(NULL){}

template <class S, class T>
Graphe<S, T>::Graphe(const Graphe<S, T> & graphe) {
	throw Exception("pas encore écrit : reste à faire");
}

template <class S, class T>
const Graphe<S, T> & Graphe<S, T>::operator = (const Graphe<S, T> & graphe) {
	throw Exception("pas encore écrit : reste à faire");
}

template <class S, class T>
Graphe<S, T>::~Graphe() {
	PElement< Arete<S, T> >::efface2(this->lAretes);
	PElement<Sommet<T> >::efface2(this->lSommets);
}

template <class S, class T>
Sommet<T> * Graphe<S, T>::creeSommet(const T & info) {
	Sommet<T> * sommetCree = new Sommet<T>(prochaineClef++, info);
	lSommets = new PElement< Sommet<T> >(sommetCree, lSommets);
	return sommetCree;
}

template <class S, class T>
Arete<S, T> * Graphe<S, T>::creeArete(Sommet<T> * debut, Sommet<T> * fin, const S & info) {
	Arete<S, T> * nouvelleArete;

	// ici tester que les 2 sommets sont bien existants dans le graphe
	if (!PElement< Sommet<T> >::appartient(debut, lSommets)) throw Exception("début d'arête non défini");
	if (!PElement< Sommet<T> >::appartient(fin, lSommets)) throw Exception("fin d'arête non définie");

	nouvelleArete = new Arete<S, T>(prochaineClef++, debut, fin, info);
	lAretes = new PElement< Arete<S, T> >(nouvelleArete, lAretes);
	debut->degre++; fin->degre++;
	return nouvelleArete;
}

template <class S, class T>
int Graphe<S, T>::nombreSommets() const{
	return PElement< Sommet<T> >::taille(lSommets);
}


template <class S, class T>
int Graphe<S, T>::nombreAretes() const {
	return PElement< Arete<S, T> >::taille(lAretes);
}

template <class S, class T>
Graphe<S, T>::operator string() const{
	ostringstream oss;
	oss << "Graphe( \n";
	oss << "prochaine clef = " << this->prochaineClef << endl;
	oss << "nombre de sommets = " << this->nombreSommets() << "\n";
	oss << PElement<Sommet<T> >::toString(lSommets, "", "\n", "");
	oss << "nombre d'arêtes = " << this->nombreAretes() << "\n";
	oss << PElement<Arete<S, T> >::toString(lAretes, "", "\n", "");
	oss << ")";
	return oss.str();
}



template <class S, class T>
ostream & operator<<(ostream & os, const Graphe<S, T> & graphe) {
	return os << (string)graphe;
}

template <class S, class T>
Arete<S, T> * Graphe<S, T>::getAreteParSommets(const Sommet<T> * s1, const Sommet<T> * s2) const{
	PElement<Arete<S, T> > * l;
	for (l = this->lAretes; l; l = l->s) {
		if (l->v->estEgal(s1, s2)) return l->v;
	}
	return NULL;
}


// Retourne la liste des voisins d'un Sommet => Pair(Sommet - Arete)
template <class S, class T>
PElement<pair<Sommet<T>*, Arete<S, T>*> >* Graphe<S, T>::adjacences(const Sommet<T> * sommet) const{
	const PElement< Arete<S, T> > * l;
	PElement< pair< Sommet<T> *, Arete<S, T>* > > * r;

	for (l = lAretes, r = NULL; l; l = l->suivant)

		if (sommet == l->v->debut)
			r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >(new pair<Sommet<T>*, Arete<S, T>*>(l->v->fin, l->v), r);
		else
			if (sommet == l->valeur->fin)
				r = new PElement< pair< Sommet<T> *, Arete<S, T>* > >
				(new pair< Sommet<T> *, Arete<S, T>* >
				(l->valeur->debut, l->valeur), r);
	return r;
}


template <class S, class ValueData>
void Graphe<S, ValueData>::toFile(string filename, string titre, string legende, string resume){
    ofstream fichier("../../docs/bsplines/" + filename + ".txt", ios::out | ios::trunc);

    if(fichier){
        fichier << "titre = " << titre << endl;
        fichier << "legende = " << legende << endl;
        fichier << "resume = " << resume << endl;
        fichier << "type de scene = courbes" << endl;
        fichier << "coin bas gauche de la figure sur l'écran en coordonnées monde = ( -1, -1)" << endl;
        fichier << "coin haut droit de la figure sur l'écran en coordonnées monde = ( 10, 10)" << endl;
        fichier << "nombre de points remarquables =" << nombreSommets() << endl;
        PElement<Sommet<ValueData> > *tempsom = lSommets;
        while (tempsom != NULL) {
            fichier << "point remarquable = 2 black (" << tempsom->valeur->valeur.position.x << "," << tempsom->valeur->valeur.position.y << ") " << tempsom->valeur->valeur.nom << endl;
            tempsom = tempsom->suivant;
        }

        fichier << "nombre de courbes = " << nombreAretes() << endl;
        PElement<Arete<double,ValueData> > *temp = lAretes;
        while (temp != NULL) {
            fichier << "couleur =  green" << endl;
            fichier << "nombre de points = 2" << endl;
            fichier << "( " << temp->valeur->debut->valeur.position.x << ", " << temp->valeur->debut->valeur.position.y << ")" << endl;
            fichier << "( " << temp->valeur->fin->valeur.position.x << ", " << temp->valeur->fin->valeur.position.y << ")" << endl;
            temp = temp->suivant;
        }
        fichier.close();
    } else cerr << "Impossible d'ouvrir le fichier !" << endl;
}



#endif // GRAPHE
