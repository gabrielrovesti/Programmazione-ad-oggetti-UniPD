#include "dataora.h"

dataora dataora::operator+(const orario& o) const
{
    dataora aux=*this;
    aux.sec=sec+3600*o.Ore()+60*o.Minuti()+o.Secondi();
    if(aux.sec>=86400)
    {
        aux.sec=aux.sec-86400;
        aux.AvanzaUnGiorno();
    }
    return aux;
}

void dataora::AvanzaUnGiorno()
{   /*
    if(giorno<GiorniDelMese()) giorno++;
    else if (mese<12) {giorno=1; mese=1;}
    else{giorno=1;mese=1;anno++;}
    */
}

