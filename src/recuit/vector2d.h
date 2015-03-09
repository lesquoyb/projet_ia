#ifndef VECTOR2D_H
#define VECTOR2D_H


/*
 * Vecteurs2D.h
 *
 *  Created on: 1 juil. 2011
 *      Author: Dominique
 */

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Vecteur2D
{

public:

    double x,y;

    inline explicit Vecteur2D(const double & x = 0, const double & y = 0);

    inline const Vecteur2D operator + (const Vecteur2D & u) const;
    inline const Vecteur2D operator * (const double & a) const;
    inline const Vecteur2D operator - () const;
    /**
     * produit scalaire
     * */
    inline double operator * (const Vecteur2D & u) const;



    inline const Vecteur2D & operator +=(const Vecteur2D & u);
    inline const Vecteur2D & operator *=(const double & a);

    operator string() const;

};



inline const Vecteur2D operator *(const double & a, const Vecteur2D & u) { return u*a;}

/**
 * calcule |u|_sup, c-à-d max(|x|,|y|)
 * */
inline double normeSup(const Vecteur2D& u);

ostream & operator << (ostream & os, const Vecteur2D & u);

void fusionne(const double x[], const double y[], int m, Vecteur2D v[]);

//----------------------------- implémentation des fonctions inline ----------------------------------

inline  Vecteur2D::
Vecteur2D(const double & x, const double & y): x(x),y(y){}

inline const Vecteur2D Vecteur2D::operator + (const Vecteur2D & u) const
{
return Vecteur2D( x+u.x, y+u.y);
}
inline const Vecteur2D Vecteur2D::operator * (const double & a) const
{
return Vecteur2D( x*a, y*a);
}
inline const Vecteur2D Vecteur2D::operator - () const
{
return Vecteur2D(-x,-y);
}
/**
 * produit scalaire
 * */
inline double Vecteur2D::operator * (const Vecteur2D & u) const
{
return x*u.x + y*u.y;
}

inline const Vecteur2D & Vecteur2D::operator +=(const Vecteur2D & u)
{
x+=u.x;
y+=u.y;
return *this;
}

inline const Vecteur2D & Vecteur2D::operator *=(const double & a)
{
x*=a;
y*=a;
return *this;
}

inline double maax(double a, double b) { return (a > b) ? a : b; }
/**
 * calcule |u|_sup, c-à-d max(|x|,|y|)
 * */
inline double normeSup(const Vecteur2D& u){
return maax(abs(u.x),abs(u.y));
}


#endif // VECTOR2D_H
