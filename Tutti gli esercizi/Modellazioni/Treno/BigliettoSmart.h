#ifndef BIGLIETTOSMART_H
#define BIGLIETTOSMART_H
#include "Biglietto.h"
#include "BigliettoPrimaClasse.cpp"
#include "BigliettoSecondaClasse.h"
class BigliettoSmart{
private:
    Biglietto* punt;
public:
    BigliettoSmart(Biglietto* =0);
    Biglietto* operator*() const;
};
#endif