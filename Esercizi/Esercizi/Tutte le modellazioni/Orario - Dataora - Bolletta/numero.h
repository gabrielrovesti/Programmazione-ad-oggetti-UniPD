#ifndef NUMERO_H
#define NUMERO_H

#include <iostream>
using namespace std;

class numero
{
private:
    string s;

public:
    numero();
    numero(string);
    string Num_Tel() const;
    bool operator==(const numero&);
};

ostream& operator<<(ostream& o, const numero& n);

#endif // NUMERO_H



