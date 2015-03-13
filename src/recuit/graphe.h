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
    static int last_cost;

public:


    class CycleEulerien{

    public:

        PElement< Arete<ArcCost, VertexType> >* arcsList;
<<<<<<< HEAD
        const Graphe<ArcCost, VertexType>* graphe;
=======
        const Graphe* associatedGraphe;
>>>>>>> origin/master

        void insert(const Arete<ArcCost, VertexType> & arete){
            for(PElement<Arete<ArcCost, VertexType> >* it = arcsList; it != NULL; it = it->suivant){
                if(arete.debut->clef == it->valeur->debut->clef
                   || arete.fin->clef == it->valeur->fin->clef){
                    throw Exception( "l'arete :" + PElement<Arete<ArcCost, VertexType> >::toString(it) + "est déjà présente dans ce cycle");
                }
            }
            arcsList = new PElement<Arete<ArcCost, VertexType> >(new Arete<ArcCost,VertexType>(arete), arcsList);
        }


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

<<<<<<< HEAD
        CycleEulerien(const Graphe<ArcCost, VertexType>* g):arcsList(NULL), graphe(g){}
=======
        CycleEulerien(const Graphe *g):arcsList(NULL),associatedGraphe(g){}
>>>>>>> origin/master

        /**
         * @brief CycleEulerien construit un cycle à partir d'un autre, pas de copie des éléments
         * @param c
         */
<<<<<<< HEAD
        CycleEulerien(const CycleEulerien &c): arcsList(c.arcsList->copy()), graphe(c.graphe) {}
=======
        CycleEulerien(const CycleEulerien &c):
            arcsList(NULL),
            associatedGraphe(c.associatedGraphe)
        {
            if(c.arcsList != NULL)
                arcsList = new PElement<Arete<ArcCost,VertexType> >(*c.arcsList);
            //arcsList = c.arcsList->copy();
            /*
            for(PElement< Arete<ArcCost, VertexType> >* p = c.arcsList; p != NULL ; p = p->suivant){
                insert(p->valeur);
            }*/
        }
>>>>>>> origin/master


        double cout_cycle2(const CycleEulerien &c) const{
            double total = 0;
            for (PElement< Arete<ArcCost, VertexType> >* i = c.arcsList; i != NULL; i = i->suivant){
                if (c.graphe != NULL) total +=  c.graphe->getAreteParSommets(i->valeur->debut, i->valeur->fin)->valeur;
            }
            return total;
        }

        CycleEulerien operator =(const CycleEulerien &c){
            return CycleEulerien(c);
        }

        static CycleEulerien changement_aleatoire(const CycleEulerien &cycle){
            cout << to_string(cycle.cout_cycle2(cycle)) << endl;
            double init_cost = cycle.cout_cycle2(cycle);

            CycleEulerien ret(cycle);

<<<<<<< HEAD
            Arete<ArcCost,VertexType>* first = ret.arcsList->randomElement();
            Arete<ArcCost,VertexType>* second = ret.arcsList->randomElement();
=======
            CycleEulerien ret = CycleEulerien(cycle);
            pair<Arete<ArcCost,VertexType>*,int> first = ret.arcsList->randomElement();
            pair<Arete<ArcCost,VertexType>*,int> second = ret.arcsList->randomElement();
>>>>>>> origin/master
            /*TODO vérif */
            while(   second.first->fin->clef    ==  first.first->debut->clef
                  || second.first->debut->clef  ==  first.first->fin->clef
                  || second.first->debut->clef == first.first->debut->clef
                  || second.first->fin->clef == first.first->fin->clef){

                second = ret.arcsList->randomElement();
            }

<<<<<<< HEAD
            system("pause");

            ArcCost a;
            ArcCost b;
            a = cycle.graphe->getAreteParSommets(first->debut, first->fin)->valeur + cycle.graphe->getAreteParSommets(second->debut, second->fin)->valeur;
            b = cycle.graphe->getAreteParSommets(first->debut, second->debut)->valeur + cycle.graphe->getAreteParSommets(first->fin, second->fin)->valeur;
            if (a > b) {
                cout << "before : " << to_string(init_cost) << endl;
                cout << "after  : " << to_string(init_cost - a + b) << endl;

                //On trouve le chemin de C vers B et on l'inverse
                invert_path(first->fin, second->debut, ret);

                //On change A->C et B->D en A->B et C->D
                Sommet<VertexType>* C = first->fin;
                first->fin = second->debut;
                second->debut = C;

                cout << "Cycle_cost-> " << to_string(cycle.cout_cycle2(cycle)) << endl;
                cout << "Ret_cost  -> " << to_string(cycle.cout_cycle2(ret)) << endl;

                /* Partie correcte mais non fonctionnelle
                Arete<ArcCost,VertexType>* first2 = cycle.graphe->getExactAreteParSommets(first->debut, second->debut);
                Arete<ArcCost,VertexType>* second2 = cycle.graphe->getExactAreteParSommets(first->fin, second->fin);

                PElement< Arete<ArcCost, VertexType> >* temp = ret.arcsList;
                PElement< Arete<ArcCost, VertexType> >* temp2 = ret.arcsList;
                //On atteind le point from
                for(; temp->valeur != first; temp = temp->suivant);
                for(; temp2->valeur != second; temp2 = temp2->suivant);

                temp->valeur = first2;
                temp2->valeur = second2;
                */
                Connexion::commit("o{clear}", true);
                cycle.graphe->ServeurSend(ret);
            }
=======
            //On viens de tirer deux arcs au hasard qui ne sont pas l'un à la suite de l'autre

            //cycle.toFile("cycleInit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");
            //ret.toFile("retInit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");

            //On trouve le chemin de B vers C et on l'inverse
            invert_path(first.first->fin, second.first->debut, ret);

            //On change A->C et B->D en A->B et B->D
            Sommet<VertexType>* C = first.first->fin;
           // first->fin = second->debut;
            PElement<Arete< ArcCost, VertexType > > *tmp = ret.arcsList;
            for(int i = 0 ; i < first.second; i++){
                tmp = tmp->suivant;
            }
            tmp->valeur = ret.associatedGraphe->getExactAreteParSommets(first.first->debut,second.first->debut);
            if(tmp->valeur == NULL){
                throw Exception("lol");
            }

            //On change A->B et B->D en A->B et C->D
          //  second->debut = C;
            tmp = ret.arcsList;
            for(int i = 0; i < second.second; i++){
                tmp = tmp->suivant;
            }
            tmp->valeur = ret.associatedGraphe->getExactAreteParSommets(C,second.first->fin);
            if(tmp->valeur == NULL){
                throw Exception("lol");
            }
           // delete tmp;
            //cout << "cycle sortie: " << ret.arcsList;

          //  cycle.toFile("cycleEndit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");
           // ret.toFile("retEndit" + to_string(first->clef) +to_string(second->clef), "b", "c", "d");

>>>>>>> origin/master

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
            if ( temp->valeur->fin->clef == to->clef) {
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
        CycleEulerien c(this);
<<<<<<< HEAD
        Sommet<VertexType>* last = lSommets->valeur;
        PElement<Sommet<VertexType> >* remaining = lSommets->copy();
=======
        PElement<Sommet<VertexType> >* remaining = new PElement<Sommet<VertexType> >(*lSommets); //lSommets->copy();
        Sommet<VertexType>* last = remaining->randomElement().first;
        Sommet<VertexType>* first = last;
>>>>>>> origin/master
        PElement<Sommet<VertexType> > ::retire(last,remaining); //enlève le premier sommet TODO: attention que lsommet ne soit pas modifié !
        while(PElement<Sommet<VertexType> >::taille(remaining) > 0  ){
                Sommet<VertexType>* sommet = remaining->randomElement().first;
                if(sommet->valeur == last->valeur){
                    throw Exception("il y a une boucle parmi les arcs possible");
                }

                c.insert(*(getExactAreteParSommets(last,sommet)));
                last = sommet;
                PElement<Sommet<VertexType> > ::retire(last,remaining);
        }
        c.insert(*getExactAreteParSommets(last,first)); //Pour refermer la boucle
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
    void ServeurSend(const CycleEulerien&) const;


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
        if (l->valeur->debut->clef == s1->clef
             && l->valeur->fin->clef == s2->clef){
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
void Graphe<S, ValueData>::ServeurSend(const CycleEulerien& c) const {
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
