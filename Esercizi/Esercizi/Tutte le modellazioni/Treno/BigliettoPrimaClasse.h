#ifndef BIGLIETTOPRIMA_H
#define BIGLIETTOPRIMA_H
#include "Biglietto.h"
class BigliettoPrimaClasse:public Biglietto
{
private:
    static double sogliaKM;
    
public:
    BigliettoPrimaClasse(double=0);
    virtual double prezzo() const;
};
#endif