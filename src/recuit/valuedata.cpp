#include "valuedata.h"

ValueData::operator string() const {
    ostringstream oss;
    oss << "nom = " << nom << ", position = " << position << endl;
    return oss.str();
}

ostream & operator << ( ostream & os, const ValueData& valuedata) {
    return os << (string)valuedata;
}

