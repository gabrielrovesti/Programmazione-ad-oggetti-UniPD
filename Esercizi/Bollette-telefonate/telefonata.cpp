#include "telefonata.h"

telefonata::telefonata(orario i, orario f, int n) {
    inizio = i; fine = f; numero = n;
}
telefonata::telefonata() {numero = 0;}

orario telefonata::Inizio() const {return inizio;}
orario telefonata::Fine() const {return fine;}
int telefonata::Numero() const {return numero;}

bool telefonata::operator==(const telefonata& t) const {
    if (inizio == t.inizio && fine == t.fine && numero == t.numero) {
        return true;
    }
    else return false;
}

ostream& operator<<(ostream& s, const telefonata& t) {
    return s << "Inizio " << t.Inizio() << " Fine " << t.Fine() << " Numero " << t.Numero();
}
