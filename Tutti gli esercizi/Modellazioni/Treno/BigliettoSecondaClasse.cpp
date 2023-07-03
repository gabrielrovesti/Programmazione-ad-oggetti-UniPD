#include "BigliettoSecondaClasse.h"
BigliettoSecondaClasse::BigliettoSecondaClasse(double km,bool p):Biglietto(km),prenotazione(p)
{
}
double BigliettoSecondaClasse::prezzo() const
{
    return prenotazione? GetKm()*GetPrezzoKm()+costoprenotazione : GetKm()*GetPrezzoKm();
}
bool BigliettoSecondaClasse::IsPrenotazione() const
{
    return prenotazione==true;
}
double BigliettoSecondaClasse::costoprenotazione=5.0;
