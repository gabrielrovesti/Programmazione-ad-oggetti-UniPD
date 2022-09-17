#ifndef TELEFONATA_H
#define TELEFONATA_H

#include <iostream>
#include "orario.h"
#include "numero.h"
using namespace std;

class telefonata
{
    public:
        telefonata(const orario&, const orario&, const numero&);
        telefonata();
        orario Inizio() const;
        orario Fine() const;
        numero Numero() const;
        bool operator==(const telefonata&);

    private:
        orario inizio, fine;
        numero n;
};

ostream& operator<<(ostream&, const telefonata&);

#endif // TELEFONATA_H
