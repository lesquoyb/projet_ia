#ifndef PELEMENT_H
#define PELEMENT_H
#include <iostream>
#include <ostream>
#include <string>
#include <sstream>
#include "exception.h"

using std::string;
using std::ostream;
using std::ostringstream;


template <class T>
class PElement{

public :
    T * valeur;
    PElement<T> * suivant;

    /**
     * Ne crée pas de copie de *v.
    Pointe donc sur la donnée originale *v
     * */
    PElement( T * v, PElement<T> * s ): valeur(v),suivant(s){}



    PElement(const PElement<T> &it):
        valeur(new T(*it.valeur)),
        suivant(NULL)
    {
        if(it.suivant != NULL){
            suivant = new PElement<T>(*it.suivant);
        }
    }


    /**
     * crée une copie de s
     */
/*    PElement(const PElement<T>* it):
        suivant(
    {
        PElement<T>* this2 = this;
         while(it != NULL){
           new PElement(new T(*it->valeur),this);
           it = it->suivant;
         }
    }

    /*
    PElement<T>* copy(){
        PElement<T>* this2 = this;
        PElement<T>* first = new PElement<T>(this2->valeur, NULL);
        PElement<T>* temp = first;
        this2 = this2->suivant;
        while(this2 != NULL) {
            temp->suivant = new PElement<T>(this2->valeur, NULL);
            this2 = this2->suivant;
            temp = temp->suivant;
        }
        return first;
    }
    */

    static const string toString(const PElement<T> * p,
                        const char * debut="( ",
                        const char * separateur = ", ",
                        const char * fin=")"){
        PElement<T> * r;
        ostringstream oss;
        for ( r = (PElement<T>* ) p, oss << debut; r; r = r->suivant){
            oss << *(r->valeur) << separateur;
        }
        oss << fin;
        return oss.str();
    }

    static int taille(const PElement<T> * l){
        if (!l) return 0;
        else
          return 1 + PElement<T>::taille(l->suivant);
    }

    pair<T*,int> randomElement()const{
        int nbIte = rand() % PElement<T>::taille(this);
        const PElement<T>* ret = this;
        int i = 0;
        for( ; i <nbIte ; i++,ret = ret->suivant);
        if(ret == NULL){
            throw Exception("Huston on a un problème");
        }
        return pair<T*,int>(ret->valeur,i);
    }


    /* TODO maybe cet algo est utilisé pour voir si cet élément précis appartient à une liste, auquel cas il ne faut pas comparer les
     *  valeurs mais directement le pointeur
     */
    static bool appartient(const T * element,const PElement<T> * list){
        if(list == NULL){
            return false;
        }
        if(list->valeur == element){
            return true;
        }
        return appartient(element,list->suivant);
    }

    // vérifie avec l'opérateur ==
    static bool appartient2(const T * element,const PElement<T> * list){
        if(list == NULL){
            return false;
        }
        if(*(list->valeur) == *element){
            return true;
        }
        return appartient2(element,list->suivant);
    }


    /**
     * efface toute la liste l
     * mais n'efface pas les données *v
     *
     * */
    static void efface1(PElement<T>* & l){
        if (l){
           PElement<T>::efface1(l->suivant);
           delete l; l = NULL;
       }
    }

    /**
     * efface toute la liste l
     * et efface toutes les données *v
     *
     * */
    static void efface2(PElement<T>* & l){
        if (l){
           PElement<T>::efface2(l->suivant);
           delete l->valeur; delete l; l = NULL;
       }
    }


    /**
     * Insère * a dans l de telle sorte que l reste ordonnée par ordre croissant (l'élement en tête est le plus petit).
     * Ne réalise pas de copie de *a. En sortie l et a partagent donc physiquement des données.
     *
     * Données : a (l'élément à insérer), l, estPlusPetitOuEgal(la fonction de comparaison))
     * Résultats : l modifiée par l'insertion
     * Hypothèses : on suppose l ordonnée par ordre croissant à l'appel
     *
     * */
    static void insertionOrdonnee( T * a, PElement<T> * & l,
                                   bool (*estPlusPetitOuEgal)(const T * a1, const T * a2)){

        if (!l || estPlusPetitOuEgal(a,l->valeur))
           l = new PElement<T>(a,l);
        else
           PElement<T>::insertionOrdonnee(a,l->suivant,estPlusPetitOuEgal);
    }

    /**
     * retire la 1ère occurrence de a de l si a est présent dans l, sinon ne fait rien
     *
     * L'élément trouvé n'est pas effacé
     *
     * La comparaison est faite sur les pointeurs
     *
     * Données : a, l
     * Résultats : l (éventuellement modifiée), par return : true si l'élément a été trouvé, false sinon
     * */
    static bool retire(const T * a, PElement<T> * &l){
        if (!l)
           return false;
        else
           if (a == l->valeur)
              {
              PElement<T> * r = l;
              l = l->suivant;
              delete r;
              return true;
              }
           else
              return PElement<T>::retire(a,l->suivant);
    }




    /**
     * retire l'élément situé en tête de l et le renvoie. Le 1er maillon de l est effacé.
     *
     * l est donc modifiée par l'appel. En sortie l compte un élément de moins.
     * lance une exception Erreur si l == NULL à l'appel
     *
     * */
    static T * depiler(PElement<T> * & l){
        if (!l) throw Exception("impossible de dépiler une pile vide");

        T * a = l->valeur;
        PElement<T> * tete = l;

        l = l->suivant; delete tete;
        return a;
    }


    PElement<T> operator = (const PElement<T> &l){
        /* TODO: tester */
        PElement<T> ret;
        for(PElement<T>* it = &l; it != NULL; ret = PElement(*it,ret),it = it->suivant);
        return ret;
    }

};


template<class T>
ostream& operator <<(ostream & os, const PElement<T> * p){
    return os << PElement<T>::toString(p);
}


#endif
