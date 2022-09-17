#ifndef DATA_H
#define DATA_H
#include "data.h"
#include <iostream>
#include <string>
using std::string;
using std::ostream;

class data
{
private:
    int giorno;
    int mese;
    int anno;
    string nome_giorno;
public:
    data(int g, int m, int a, string ng) : giorno(g), mese(m), anno(a), nome_giorno(ng) {}
    data(const data&);
    int Giorno() const;
    int Mese() const;
    int Anno() const;
    string Giorno_Sett() const;
    bool operator==(const data&) const;
    bool operator<(const data&) const;
    void aggiungi_uno();
};

ostream& operator<<(ostream&, const data&);

#endif // DATA_H
