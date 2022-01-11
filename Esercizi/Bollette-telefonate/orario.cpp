#include "orario.h"
#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

int orario::Ore() const { // l'implementazione di una funzione che usa parametri della classe orario fuori dalla classe orario deve avvenire con "orario::" SCOPING
    return sec / 3600;
}

int orario::Minuti() const {
    return (sec / 60) % 60;
}

int orario::Secondi() const {
    return sec % 60;
}

orario::orario(int o, int m, int s) {
    if (o < 0 || o > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
        sec = 0;
    }   
    else 
    sec = o * 3600 + m * 6 + s;
}
int orario::Secondi_this(orario* x) {return ((*this).sec) %60;}   // (*this).sec == this->sec
orario orario::UnOraPiuTardi() {
    orario aux;
    aux.sec = (sec + 3600) % 86400;
    return aux;
}   // non provoca side effect

void orario::AvanzaUnOra() {sec = (sec + 3600) % 86400;}   // provoca side effect poiche modifica il campo dati di un oggetto

void orario::StampaSecondi() const {cout << sec << endl;}
orario orario::OraDiPranzo() {return orario(13,15);}

orario orario::operator+(orario o) {
    orario aux;
    aux.sec = (sec + o.sec) % 86400;
    return aux;
}

ostream& operator<<(ostream& os, const orario& o) {
    return os << o.Ore() << ":" << o.Minuti() << ":" << o.Secondi() << endl; 
}

bool operator==(const orario& x, const orario& y) {
    return x.Ore() == y.Ore() && x.Minuti() == y.Minuti() && x.Secondi() == y.Secondi();
}
