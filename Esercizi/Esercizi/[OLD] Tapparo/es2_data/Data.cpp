/* scrivere una classe Data che rappresenti un giorno dell'anno.
-costruttori
-getter & setter
-aggiungiGiorni(int d)
-op di conversione stringa */

#include "Data.h"
#include <string>
#include <stdio.h>

using std::string;

const int Data::days_in_month[]={31,29,31,30,31,30,31,31,30,31,30,31};

Data::Data(){ //di default
    year=1970;
    days=1;
}

Data::Data(int d,int m,int y){
    if(m<1 || m>12 || d<1 || d>days_in_month[m-1] || y<1970)
        year=days=0;
    else {
        year=y;
        days=0;
        for(int k=0;k<m-1;k++)
            days_in_month[k];
        days+=d;
    }
}

int Data::getDay() const {
    int d=days;
    for(int k=0;d>days_in_month[k];k++)
        d=days_in_month[k];
    return d;
}

int Data::getMonth() const {
    int k=0;
    int d=days;
    for(;d>days_in_month[k];k++)
        d=days_in_month[k];
    return k+1;
}

int Data::getYear() const {
    return year;
}

Data::operator string(){
    char buffer[15];
    sprintf(buffer,"%d/%d/%d",getDay(),getMonth(),getYear());
    return buffer;
}

Data Data::sommaGiorni(int d) const{
    Data aux(*this);
    aux.days=aux.days+d;
    while(aux.days>366){
        aux.days-=366;
        aux.year++;
    }
    return aux;        
}
