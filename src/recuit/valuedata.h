#ifndef VALUEDATA
#define VALUEDATA
#include "vector2d.h"

class ValueData {
public:
    string nom;
    Vecteur2D position;

    ValueData(const string & nom, const Vecteur2D position):nom(nom),position(position){}
    operator string() const;
    bool operator==(const ValueData&) const;
    bool operator!=(const ValueData&) const;
};

ostream& operator<<(ostream & os, const ValueData& valuedata);

#endif // VALUEDATA

