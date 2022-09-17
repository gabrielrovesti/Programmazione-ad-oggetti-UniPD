#include "bolletta.h"
#include "telefonata.h";

bolletta::smartp::smartp(nodo* p) : punt(p) {if(punt) punt->riferimenti++;}

bolletta::smartp::smartp(const smartp& s) : punt(s.punt) {if(punt) punt->riferimenti++;}

bolletta::smartp::~smartp()
{
    if(punt)
    {
        punt->riferimenti--;
        if(punt->riferimenti==0)
            delete punt;
    }
}

bolletta::smartp& bolletta::smartp::operator=(const smartp& s)
{
    if(this!=&s)
    {
        nodo* t=punt;
        punt=s.punt;
        if(punt) punt->riferimenti++;
        if(t)
        {
            t->riferimenti--;
            if(t->riferimenti==0) delete t;
        }
    }
    return *this;
}

bolletta::nodo& bolletta::smartp::operator*() const {return *punt;}

bolletta::nodo* bolletta::smartp::operator->() const {return punt;}

bool bolletta::smartp::operator==(const smartp& s) const {return punt==s.punt;}

bool bolletta::smartp::operator!=(const smartp& s) const {return punt!=s.punt;}

bolletta::nodo::nodo(): riferimenti(0) {}      //COSTRUTTORE DEFAULT

bolletta::nodo::nodo(const telefonata& t, const smartp& p): info(t), next(p), riferimenti(0) {}     //COSTRUTTORE DI NODO

bolletta::bolletta(const bolletta& b) : first(b.first) {if(first->next!=0) first->riferimenti++;}

bool bolletta::Vuota() const {return first==0;}     //CONTROLLA SE VUOTA

void bolletta::Aggiungi_Telefonata(telefonata t)    //AGGIUNGE UNA TEL ALLA BOLLETTA
{
    first=new nodo(t, first);
}

void bolletta::Togli_Telefonata(telefonata t)   //TOGLIE DALLA BOLLETTA UNA TELEFONATA T
{
    smartp p=first, prec, q;
    smartp original=first;
    first=0;
    while(p!=0 && !(p->info==t))
    {
        q=new nodo(p->info, p->next);
        if(prec==0) first=q;
        else prec->next=q;
        prec=q; p=p->next;
     }

        if(p==0) {first=original;}

        else if (prec==0) first=p->next;
        else prec->next=p->next;
}

void bolletta::Sostituisci(const telefonata& t1, const telefonata& t2)
{
    smartp p=first, prec, q;
    smartp original=first;
    first=0;
    while(p!=0 && !(p->info==t1))
    {
        q=new nodo(p->info, p->next);
        if(prec==0) first=q;
        else prec->next=q;
        prec=q; p=p->next;
    }
    if(p==0) {first=original;}
    else if(prec==0) first->info=t2;
    else p->info=t2;
}


ostream& operator<<(ostream& os, const bolletta& b)
{
    if(b.Vuota()) os<<"BOLLETTA VUOTA"<<endl;
    else
    {
        os<<"TELEFONATE IN BOLLETTA"<<endl;
        bolletta::smartp p=b.first;
        int i=1;
        while(p!=0)
        {
            os<<i++<<") "<<p->info<<endl;
            p=p->next;
        }
    }
    return os;
}

telefonata bolletta::Estrai_Una()       //ESTRAE UNA TELEFONATA DALLA BOLLETTA
{
    telefonata aux=first->info;
    first=first->next;
    return aux;
}

bolletta& bolletta::operator=(const bolletta& b)    //OPERATORE =
{
    if(this!=&b)
        first.~smartp();
    first = b.first;
    return *this;
}

orario Somma_Durate(bolletta b)
{
    orario durata;
    while(!b.Vuota())
    {
        telefonata t=b.Estrai_Una();
        durata=durata+t.Fine()-t.Inizio();
    }
    return durata;
}


bolletta Chiamate_A(numero num, bolletta& b)
{
    bolletta selezionate, resto;
    while(!b.Vuota())
    {
        telefonata t=b.Estrai_Una();
        if(t.Numero()==num)
            selezionate.Aggiungi_Telefonata(t);
        else
            resto.Aggiungi_Telefonata(t);
    }
    b=resto;
    return selezionate;
}

bool bolletta::iteratore::operator==(iteratore i) const
{
    return p==i.p;
}

bool bolletta::iteratore::operator!=(iteratore i) const
{
    return p!=i.p;
}

bolletta::iteratore& bolletta::iteratore::operator++()
{
    if(p.punt) p=p->next;
    return *this;
}

bolletta::iteratore bolletta::iteratore::operator++(int)
{
    iteratore aux=*this;
    if(p.punt) p=p->next;
    return aux;
}

bolletta::iteratore bolletta::begin() const
{
    iteratore aux;
    aux.p=first;
    return aux;
}

bolletta::iteratore bolletta::end() const
{
    iteratore aux;
    aux.p=0;
    return aux;
}

telefonata& bolletta::operator[](bolletta::iteratore it) const
{
    return (it.p)->info;
}

telefonata& bolletta::iteratore::operator*(bolletta::iteratore it) const
{
    return (it.p)->info;
}

