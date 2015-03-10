#include "valuedata.h"
#include <sstream>

ValueData::operator string() const {
    ostringstream oss;
    oss << "nom = " << nom << ", position = " << position << endl;
    return oss.str();
}

ostream & operator << ( ostream & os, const ValueData& valuedata) {
    return os << (string)valuedata;
}

bool ValueData::operator==(const ValueData& v) const {
    return ((v.nom == nom) && (v.position.x == position.x) && (v.position.y == position.y));
}


bool ValueData::operator!=(const ValueData& v) const {
    return ((v.nom != nom) || (v.position.x != position.x) || (v.position.y != position.y));
}
