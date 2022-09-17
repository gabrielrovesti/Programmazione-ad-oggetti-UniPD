#include "Treno.h"
Treno::Treno(int nprima,int nsecpren):numpostiprima(nprima),numpostisecprenotaz(nsecpren)
{
}
int* Treno::bigliettiVenduti() const
{
    int* ret=new int[3];
    for(int i=0;i<3;++i)
        ret[i]=0;
    vector<BigliettoSmart>::const_iterator it=venduti.begin();
    for(;it!=venduti.end();++it)
        if(dynamic_cast<BigliettoPrimaClasse*>(**it))
            ret[0]++;
        else
        {
            BigliettoSecondaClasse* p=dynamic_cast<BigliettoSecondaClasse*>(**it);
            if(p && p->IsPrenotazione())
                ret[1]++;
            else
                if(p&& !(p->IsPrenotazione()))
                    ret[2]++;
        }
    return ret;
}
void Treno::VendiBiglietto(const Biglietto& b) throw(TrenoPieno)
{
    Biglietto* biglietto=& const_cast<Biglietto&>(b);
    int * p=bigliettiVenduti();
    if(dynamic_cast<BigliettoPrimaClasse*>(biglietto))
        if(p[0]<numpostiprima)
            venduti.push_back(BigliettoSmart(biglietto));
        else
            throw TrenoPieno(true);
    else
    {
        BigliettoSecondaClasse* sec=dynamic_cast<BigliettoSecondaClasse*>(biglietto);
        if(sec)
            if(sec->IsPrenotazione() && p[1]<numpostisecprenotaz)
                venduti.push_back(BigliettoSmart(sec));
            else
                throw TrenoPieno(false);
    }
}
double Treno::incasso() const
{
    double ret=0.0;
    for(vector<BigliettoSmart>::const_iterator it=venduti.begin();it!=venduti.end();++it)
        ret+=(*(*it))->prezzo();
    return ret;
}