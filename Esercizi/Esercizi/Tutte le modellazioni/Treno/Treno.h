#ifndef TRENO_H
#define TRENO_H
#include <vector>
#include "TrenoPieno.h"
#include "BigliettoSmart.h"
#include "BigliettoSecondaClasse.h"
using std::vector;
class Treno{
private:
    vector<BigliettoSmart> venduti;
    int numpostiprima;
    int numpostisecprenotaz;
public:
    Treno(int =0,int =0);
    int* bigliettiVenduti()const;
    void VendiBiglietto(const Biglietto&) throw(TrenoPieno);
    double incasso() const;
};
#endif