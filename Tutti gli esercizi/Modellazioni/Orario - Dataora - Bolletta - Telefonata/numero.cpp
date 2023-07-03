#include "numero.h"
#include <iostream>
using namespace std;

numero::numero() {}

numero::numero(string st)
{
    s=st;
}

string numero::Num_Tel() const
{
    return s;
}

bool numero::operator==(const numero& n)
{
    return s==n.s;
}

ostream& operator<<(ostream& o, const numero& n)
{
    return o<<n.Num_Tel();
}
