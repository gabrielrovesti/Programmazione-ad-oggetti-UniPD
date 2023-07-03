#include "BigliettoPrimaClasse.h"
BigliettoPrimaClasse::BigliettoPrimaClasse(double km):Biglietto(km)
{
}
double BigliettoPrimaClasse::prezzo() const
{
    return (GetKm()<sogliaKM) ? (GetKm()*GetPrezzoKm()*1,3) : (GetKm()*GetPrezzoKm()*1,2);
}
double BigliettoPrimaClasse::sogliaKM=100;