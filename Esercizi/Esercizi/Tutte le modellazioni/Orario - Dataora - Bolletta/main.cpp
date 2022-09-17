#include <iostream>
#include "bolletta.h"
using namespace std;

int main()
{
    bolletta b;
    orario in(2, 30, 20);
    orario fin(3, 21, 57);
    numero num("10000000");
    telefonata t(in, fin, num);
    b.Aggiungi_Telefonata(t);

    orario in1(12, 23, 55);
    orario fin1(13, 13, 13);
    numero num1("200000000");
    telefonata t1(in1, fin1, num1);
    b.Aggiungi_Telefonata(t1);

    orario in2(14, 15, 32);
    orario fin2(23, 34, 45);
    numero num2("30000000000");
    telefonata t2(in2, fin2, num2);
    b.Aggiungi_Telefonata(t2);

    b.Sostituisci(t, t1);
    cout<<b<<endl;

    orario o= Somma_Durate(b);
    cout<<o<<endl;
}
