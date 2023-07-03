#include "data.h"
#include <iostream>
#include <string>
using std::string;
using std::ostream;

int data::Giorno() const
{
    return giorno;
}

int data::Mese() const
{
    return mese;
}

int data::Anno() const
{
    return anno;
}

string data::Giorno_Sett() const
{
    return nome_giorno;
}

bool data::operator==(const data& d) const
{
    return giorno==d.giorno && mese==d.mese && anno==d.anno && nome_giorno==d.nome_giorno;
}

bool data::operator<(const data& d) const
{
    if(anno<d.anno) return true;
    if((anno==d.anno) && (mese<d.mese)) return true;
    if((anno==d.anno) && (mese==d.mese) &&(giorno<d.giorno)) return true;
    return false;
}

ostream& operator<<(ostream& os, const data& d)
{
    return os<<d.Giorno()<<"/"<<d.Mese()<<"/"<<d.Anno()<<d.Giorno_Sett();
}
