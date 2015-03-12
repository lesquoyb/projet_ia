#ifndef GRAPHE
#define GRAPHE
#include "pelement.h"
#include "connexion.h"
#include "sommet.h"
#include "arete.h"
#include <fstream>
#include <iostream>
#include <string>


template <class ArcCost, class VertexType>
class Graphe {


protected:
    int prochaineClef;

public:


    class CycleEulerien{

    public:

        PElement< Arete<ArcCost, VertexType> >* arcsList;

        void insert(const Arete<ArcCost, VertexType> & arete){
            for(PElement<Arete<ArcCost, VertexType> >* it = arcsList; it != NULL; it = it->suivant){
                if(arete.debut->valeur == it->valeur->debut->valeur
                   || arete.fin->valeur == it->valeur->fin->valeur){
                    throw Exception( "l'arete :" + PElement<Arete<ArcCost, VertexType> >::toString(it) + "est déjà présente dans ce cycle");
                }
            }
            arcsList = new PElement<Arete<ArcCost, VertexType> >(new Arete<ArcCost,VertexType>(arete), arcsList);
        }

        /*
        void insert(const Arete<ArcCost, VertexType> & arete,PElement<Arete<ArcCost, VertexType> >* next ){
            insert(arete);
            arcsList->suivant = next;
        }
        */

        void toFile(string filename, string titre, string legende, string resume) const{
            ofstream fichier("../../docs/bsplines/" + filename + ".txt", ios::out | ios::trunc);

            if(fichier){
                fichier << "titre = " << titre << endl;
                fichier << "legende = " << legende << endl;
                fichier << "resume = " << resume << endl;
                fichier << "type de scene = courbes" << endl;
                fichier << "coin bas gauche de la figure sur l'écran en coordonnées monde = ( -1, -1)" << endl;
                fichier << "coin haut droit de la figure sur l'écran en coordonnées monde = ( 10, 10)" << endl;
                fichier << "nombre de points remarquables = 0" << endl;
                /*PElement<Sommet<ValueData> > *tempsom = lSommets;
                while (tempsom != NULL) {
                    fichier << "point remarquable = 2 black (" << tempsom->valeur->valeur.position.x << "," << tempsom->valeur->valeur.position.y << ") " << tempsom->valeur->valeur.nom << endl;
                    tempsom = tempsom->suivant;
                }*/

                fichier << "nombre de courbes = " << arcsList->taille(arcsList) << endl;
                PElement<Arete<ArcCost,VertexType> > *temp = arcsList;
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

        CycleEulerien():arcsList(NULL){}

        /**
         * @brief CycleEulerien construit un cycle à partir d'un autre, pas de copie des éléments
         * @param c
         */
        CycleEulerien(const CycleEulerien &c):
            arcsList(NULL)
        {
            arcsList = c.arcsList->copy();
            /*
            for(PElement< Arete<ArcCost, VertexType> >* p = c.arcsList; p != NULL ; p = p->suivant){
                insert(p->valeur);
            }*/
        }



        CycleEulerien operator =(const CycleEulerien &c){
            return CycleEulerien(c);
        }

        static CycleEulerien changement_aleatoire(const CycleEulerien &cycle){
            /* TODO attention il ne faut surtout pas modifier le cycle d'entrée, il y aura donc certainement
             * des choses à revoir dans cet algo */

            /*
             *TODO: en fait on ne change pas vraiment l'arc, on change juste le sommet pointé par l'arc n, donc pas de changement de poids
             */

            CycleEulerien ret = CycleEulerien(cycle);
            Arete<ArcCost,VertexType>* first = ret.arcsList->randomElement();
            Arete<ArcCost,VertexType>* second = ret.arcsList->randomElement();
            /*TODO vérif */
            while(   second->fin->valeur    ==  first->debut->valeur
                  || second->debut->valeur  ==  first->fin->valeur
                  || second->debut->valeur == first->debut->valeur
                  || second->fin->valeur == first->fin->valeur){

                second = ret.arcsList->randomElement();
            }

            //On viens de tirer deux arcs au hasard qui ne sont pas l'un à la suite de l'autre

            cycle.toFile("cycleInit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");
            ret.toFile("retInit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");

            //On trouve le chemin de B vers C et on l'inverse
            invert_path(first->fin, second->debut, ret);

            //On change A->C et B->D en A->B et B->D
            Sommet<VertexType>* C = first->fin;
            first->fin = second->debut;


            //On change A->B et B->D en A->B et C->D
            second->debut = C;
            //cout << "cycle sortie: " << ret.arcsList;

          //  cycle.toFile("cycleEndit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");
           // ret.toFile("retEndit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");


            return ret;
        }


/*
        bool containsArc(const Arete<ArcCost,VertexType> &arete){
            Arete<ArcCost, VertexType>* inv = new Arete<ArcCost, VertexType>(arete.clef,arete.fin,arete.debut,arete.valeur);
            bool ret =     PElement<Arete<ArcCost, VertexType> >::appartient(&arete,arcsList)
                        || PElement<Arete<ArcCost, VertexType> >::appartient(inv,arcsList);
            delete inv;
            return ret;
        }
        */

        /**
         * comme on est dans un cycle, pas de detection des boucles et autres, on avance juste jusqu'a arrivé au point voulu.
         * @brief invert_path un sous ensemble de la liste d'arc passé en paramètre
         * @param arcsList
         * @param from
         * @param to
         * @return
         */
        static void invert_path( Sommet<VertexType>* from,const Sommet<VertexType> *to, const CycleEulerien &c){
            PElement< Arete<ArcCost, VertexType> >* temp = c.arcsList;
            //On atteind le point from
            for(; temp->valeur->debut->valeur != from->valeur; temp = temp->suivant);

            // récursivité
            Sommet<VertexType>* tmp;
            if ( temp->valeur->fin->valeur == to->valeur) {
                tmp = temp->valeur->debut;
                temp->valeur->debut = temp->valeur->fin;
                temp->valeur->fin = tmp;
            } else {
                invert_path(temp->valeur->fin, to, c); // récursivité
                tmp = temp->valeur->debut;
                temp->valeur->debut = temp->valeur->fin;
                temp->valeur->fin = tmp;
            }
        }
    };



    PElement< Arete<ArcCost, VertexType> > * lAretes; // liste d'arêtes
    PElement< Sommet<VertexType> > * lSommets; // liste de sommets



    CycleEulerien getFirstCycle()const{
        /* TODO achtung graphe avec un élément */
        /* TODO vérif que ça sort bien un cycle hamiltonien */
        CycleEulerien c;
        Sommet<VertexType>* last = lSommets->valeur;
        PElement<Sommet<VertexType> >* remaining = lSommets->copy();
        PElement<Sommet<VertexType> > ::retire(last,remaining); //enlève le premier sommet TODO: attention que lsommet ne soit pas modifié !
        for (int i = 1; i < PElement<Sommet<VertexType> >::taille(lSommets); i++){
                Sommet<VertexType>* sommet = remaining->randomElement();
                if(sommet->valeur == last->valeur){
                    throw Exception("il y a une boucle parmi les arcs possible");
                }

                c.insert(*(getExactAreteParSommets(last,sommet)));
                last = sommet;
                PElement<Sommet<VertexType> > ::retire(last,remaining);
        }
        c.insert(*getExactAreteParSommets(last,lSommets->valeur)); //Pour refermer la boucle
        return c;
    }


    void creerLien(Sommet<VertexType> *debut,Sommet<VertexType> *fin, const ArcCost &cost){
        creeArete(debut,fin,cost);
        creeArete(fin,debut,cost);
    }


	Graphe();
    Graphe(const Graphe<ArcCost, VertexType> & graphe);

    const Graphe<ArcCost, VertexType> & operator = (const Graphe<ArcCost, VertexType> & graphe);

    ~Graphe();

    int nombreSommets() const;
    int nombreAretes() const;

    void add_missing_arcs(const ArcCost &infini);

   // bool containsArc(const Arete<ArcCost,VertexType> &a);

    Sommet<VertexType> * creeSommet(const VertexType & info);



    /**
    * crée une arête joignant les 2 sommets debut et fin
    *
    * * met à jour les champs degré de debut et de fin
    * */
    Arete<ArcCost, VertexType> * creeArete(Sommet<VertexType> * debut, Sommet<VertexType> * fin, const ArcCost & info);
    Arete<ArcCost, VertexType> * creeArete(Arete<ArcCost, VertexType> *arete);

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

    Arete<ArcCost, VertexType> * getExactAreteParSommets(const Sommet<VertexType> * s1, const Sommet<VertexType> * s2) const;


    void toFile(string filename, string titre, string legende, string resume, const CycleEulerien&);
    void ServeurSend(const CycleEulerien&);


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
Arete<S, T> * Graphe<S, T>::creeArete(Arete<S, T> *arete) {
    lAretes = new PElement< Arete<S, T> >(arete, lAretes);
    return arete;
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
    for (l = this->lAretes; l; l = l->suivant) {
        if (l->valeur->estEgal(s1, s2)){
            return l->valeur;
        }
    }
    return NULL;
}

template <class ArcCost, class VertexType>
Arete<ArcCost, VertexType> * Graphe<ArcCost, VertexType>::getExactAreteParSommets(const Sommet<VertexType> * s1, const Sommet<VertexType> * s2) const{
    PElement<Arete<ArcCost, VertexType> > * l;
    for (l = this->lAretes; l; l = l->suivant) {
        if (l->valeur->debut == s1
             && l->valeur->fin == s2){
            return l->valeur;
        }
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
void Graphe<S, ValueData>::toFile(string filename, string titre, string legende, string resume, const CycleEulerien& c){
    ofstream fichier("../../docs/bsplines/" + filename + ".txt", ios::out | ios::trunc);

    if(fichier){
        fichier << "titre = " << titre << endl;
        fichier << "legende = " << legende << endl;
        fichier << "resume = " << resume << endl;
        fichier << "type de scene = courbes" << endl;
        fichier << "coin bas gauche de la figure sur l'écran en coordonnées monde = ( -1, -1)" << endl;
        fichier << "coin haut droit de la figure sur l'écran en coordonnées monde = ( 10, 10)" << endl;
        fichier << "nombre de points remarquables =" << (nombreSommets() + nombreAretes()) << endl;

        // Affichage des points
        PElement<Sommet<ValueData> > *tempsom = lSommets;
        while (tempsom != NULL) {
            fichier << "point remarquable = 2 black (" << tempsom->valeur->valeur.position.x << "," << tempsom->valeur->valeur.position.y << ") " << tempsom->valeur->valeur.nom << endl;
            tempsom = tempsom->suivant;
        }

        // Affichage des poids
        PElement<Arete<double,ValueData> > *temp = lAretes;
        while (temp != NULL) {
            int x_middle = (temp->valeur->fin->valeur.position.x - temp->valeur->debut->valeur.position.x) /2 + temp->valeur->debut->valeur.position.x;
            int y_middle = (temp->valeur->fin->valeur.position.y - temp->valeur->debut->valeur.position.y) /2 + temp->valeur->debut->valeur.position.y;
            fichier << "point remarquable = 2 black (" << x_middle << "," << y_middle << ") " << temp->valeur->valeur << endl;
            temp = temp->suivant;
        }

        // Affichage moche des lignes bleues
        fichier << "nombre de courbes = " << (nombreAretes() + 0) << endl;
        temp = lAretes;
        string couleur;
        while (temp != NULL) {
            if (lAretes->appartient2(temp->valeur, c.arcsList)) couleur = "blue" ;
            else couleur = "green";
            fichier << "couleur =  " << couleur << endl;
            fichier << "nombre de points = 2" << endl;
            fichier << "( " << temp->valeur->debut->valeur.position.x << ", " << temp->valeur->debut->valeur.position.y << ")" << endl;
            fichier << "( " << temp->valeur->fin->valeur.position.x << ", " << temp->valeur->fin->valeur.position.y << ")" << endl;
            temp = temp->suivant;
        }

        fichier.close();
    } else cerr << "Impossible d'ouvrir le fichier !" << endl;
}


template <class S, class ValueData>
void Graphe<S, ValueData>::ServeurSend(const CycleEulerien& c) {
    PElement<Arete<double,ValueData> > *temp = lAretes;
    string couleur;
    while (temp != NULL) {
        if (lAretes->appartient2(temp->valeur, c.arcsList)) couleur = "#235CA1" ;
        else couleur = "#222222";
        double x1 = 2*temp->valeur->debut->valeur.position.x;
        double x2 = 2*temp->valeur->fin->valeur.position.x;
        double y1 = 2*temp->valeur->debut->valeur.position.y;
        double y2 = 2*temp->valeur->fin->valeur.position.y;
        Connexion::commit("s{" + std::to_string(x1) + "," + std::to_string(y1) + "," + std::to_string(x2) + "," + std::to_string(y2) + "," + couleur + "}");

        temp = temp->suivant;
    }

    PElement<Sommet<ValueData> > *tempS = lSommets;
    while (tempS != NULL) {
        double x = 2*tempS->valeur->valeur.position.x;
        double y = 2*tempS->valeur->valeur.position.y;
        string nom = tempS->valeur->valeur.nom;

        Connexion::commit("t{" + nom + "," + to_string(x) + "," + to_string(y) + ",#222222}");
        Connexion::commit("p{" + to_string(x) + "," + to_string(y) + ",#3399FF}");
        tempS = tempS->suivant;
    }

    Connexion::push();
}


/**
 *Si l'arc manquant a un arc "opposé", on lui donne la valeur de cet arc opposé, sinon +infini
 */
template<class ArcCost,class VertexType>
void Graphe<ArcCost,VertexType>::add_missing_arcs(const ArcCost &infini){

    for(PElement<Sommet<VertexType> >* p = lSommets; p != NULL ; p = p->suivant){
        for(PElement<Sommet<VertexType> >* q = p->suivant; q != NULL; q = q->suivant){
            if(getAreteParSommets(p->valeur,q->valeur) == NULL){
                //lAretes = new PElement<Arete<ArcCost,VertexType> >(new  Arete<ArcCost,VertexType>(prochaineClef,p->valeur,q->valeur,infini),lAretes);
                creerLien(p->valeur,q->valeur,infini);
            }
        }
    }
}


/*
template<class ArcCost,class VertexType>
bool Graphe<ArcCost,VertexType>::containsArc(const Arete<ArcCost,VertexType> &a){
    for(PElement<Arete<ArcCost,VertexType> >* ia = lAretes; ia != NULL ; ia = ia->suivant){
        if(ia->valeur->estEgal(a.debut,a.fin)){
            return true;
        }
    }
    return false;
}

*/



#endif // GRAPHE
