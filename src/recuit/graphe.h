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


        static CycleEulerien changement_aleatoire(const CycleEulerien &cycle){
            /* TODO attention il ne faut surtout pas modifier le cycle d'entrée, il y aura donc certainement
             * des choses à revoir dans cet algo */
            Arete<ArcCost,VertexType>* first = randomArc(cycle);
            Arete<ArcCost,VertexType>* second = randomArc(cycle);
            /*TODO vérif */
            while(   second->fin->clef    ==  first->debut->clef
                  or second->fin->clef    ==  first->fin->clef
                  or second->debut->clef  ==  first->fin->clef
                  or second->debut->clef  ==  first->debut->clef){

                second = randomArc(cycle);
            }
            //On viens de tirer deux arcs au hasard qui ne sont ni égaux ni un à la suite de l'autre

            //On change A->C et B->D en A->B et B->D
            Sommet<VertexType>* C = first->fin;
            first->fin = second->debut;

            //On trouve le chemin de B vers C
            PElement<Arete<ArcCost,VertexType> >* cheminBC = return_path(cycle.arcsList,second->debut,C); //TODO
            //On l'inverse
            invert_path(cheminBC);

            //On change A->B et B->D en A->B et C->D
            second->fin = C;



        }

        static PElement< Arete<ArcCost, VertexType> >* invert_path(const PElement< Arete<ArcCost, VertexType> >* p){
            /*TODO*/
        }

        /**
         * @brief return_path un sous ensemble de la liste d'arc passé en paramètre
         * @param arcsList
         * @param from
         * @param to
         * @return
         */
        static PElement< Arete<ArcCost, VertexType> >* return_path(const PElement< Arete<ArcCost, VertexType> >* arcsList,const Sommet<VertexType>* from,const Sommet<VertexType>* to){
            // Arete<ArcCost, VertexType> > tmp = from->;
            /* TODO */

        }

        static Arete<ArcCost,VertexType>* randomArc(const CycleEulerien &c){
            int nbIte = random() * PElement<Arete<ArcCost, VertexType> >::taille(c.arcsList);
            PElement<Arete<ArcCost, VertexType> >* ret = c.arcsList;
            for( int i = 0; i <nbIte ;ret = ret->suivant);
            if(ret == NULL){
                throw Exception("Huston on a un problème");
            }
            return ret->valeur;
        }



    };


	PElement< Arete<ArcCost, VertexType> > * lAretes; // liste d'arêtes
	PElement< Sommet<VertexType> > * lSommets; // liste de sommets



    CycleEulerien getFirstCycle()const{
        /* TODO achtung graphe avec un élément */
        /* TODO: en fait ça doit être random donc v'la */
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
     * Crée les arcs manquant pour faire un graphe complet, les arcs manquants sont initialisé représentant l'infini dans le type du poids des aretes
     * @brief add_missing_arcs
     */
    void add_missing_arcs(const ArcCost &infini);

    /**
     * @brief containsArc renvoie vrai si l'arete est dans la liste d'aretes du graphe
     * @param a
     * @return
     */
    bool containsArc(const Arete<ArcCost,VertexType> &a);

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



template<class ArcCost,class VertexType>
void Graphe<ArcCost,VertexType>::add_missing_arcs(const ArcCost &infini){

    for(PElement<Sommet<VertexType> >* p = lSommets; p != NULL ; p = p->suivant){
        for(PElement<Sommet<VertexType> >* q = p; q != NULL; q = q->suivant){
            Arete<ArcCost,VertexType>* a =new  Arete<ArcCost,VertexType>(prochaineClef,p->valeur,q->valeur,infini);
            if( ! containsArc(*a) ){
                lAretes = new PElement<Arete<ArcCost,VertexType> >(a,lAretes);
                prochaineClef++;
            }
            else{
                delete a;
            }

        }
    }
}

template<class ArcCost,class VertexType>
bool Graphe<ArcCost,VertexType>::containsArc(const Arete<ArcCost,VertexType> &a){
    for(PElement<Arete<ArcCost,VertexType> >* ia = lAretes; ia != NULL ; ia = ia->suivant){
        if(ia->valeur->estEgal(a.debut,a.fin)){
            return true;
        }
    }
    return false;
}

/**
 *Crée le premier cycle eulerien du graphe choisi aléatoirement
 */
template<class ArcCost,class VertexType>
Graphe<ArcCost,VertexType> solutionInitiale(const Graphe<ArcCost,VertexType> &g){
    /*TODO: choisir aléatoirement */
}



#endif // GRAPHE
