#include "telefonata.h"
#include "orario.h"
#include <iostream>
#include "numero.h"

telefonata::telefonata(): n(0) {}  //COSTRUTTORE DI DEFAULT

telefonata::telefonata(const orario& i, const orario& f, const numero& num): inizio(i), fine(f), n(num) {}   //COSTRUTTORE A TRE PARAMETRI

orario telefonata::Inizio() const {return inizio;}  //RITORNA L'INIZIO DELLA TELEFONATA

orario telefonata::Fine() const {return fine;}  //RITORNA LA FINE DELLA TELEFONATA

numero telefonata::Numero() const {return n;} //RITORNA IL NUMERO DELLA TELEFONATA

bool telefonata::operator==(const telefonata& t)    //OPERATORE ==
{
    return inizio == t.inizio && fine == t.fine && n == t.n;
}

ostream& operator<<(ostream& s, const telefonata& t)   //OPERATORE <<
{
    return s<<"INIZIO "<<t.Inizio()<<" FINE "<<t.Fine()<<" NUMERO CHIAMTO "<<t.Numero();
}
