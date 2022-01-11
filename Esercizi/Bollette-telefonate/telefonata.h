#ifndef telefonata_h
#define telefonata_h

#include <iostream>
#include "orario.h"

using std::ostream;

class telefonata {
public:
    telefonata(orario,orario,int);
    telefonata();
    orario Inizio() const;
    orario Fine() const;
    int Numero() const;
    bool operator==(const telefonata&) const;
private:
    orario inizio, fine;
    int numero;
};

ostream& operator<<(ostream&, const telefonata&);

#endif