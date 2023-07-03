#ifndef BIGLIETTOSECONDA_H
#define BIGLIETTOSECONDA_H
#include "Biglietto.h"
class BigliettoSecondaClasse:public Biglietto{
private:
    bool prenotazione;
    static double costoprenotazione;
public:
    BigliettoSecondaClasse(double=0,bool=false);
    virtual double prezzo() const;
    bool IsPrenotazione() const;
};
#endif