#include "Biglietto.h"
Biglietto::Biglietto(double km):distanzaKM(km)
{
}
Biglietto::~Biglietto()
{
}
double Biglietto::GetKm() const
{
    return distanzaKM;
}
double Biglietto::GetPrezzoKm()
{
    return prezzoKM;
}
double Biglietto::prezzoKM=0.1;