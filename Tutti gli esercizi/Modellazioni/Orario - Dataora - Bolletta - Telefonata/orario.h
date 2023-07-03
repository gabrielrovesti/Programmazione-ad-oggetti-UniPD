#ifndef ORARIO_H
#define ORARIO_H
#include <iostream>
using namespace std;
class orario
{
    public:
        orario();
        orario(int);
        orario(int, int);
        orario(int, int, int);
        int Ore() const;
        int Minuti() const;
        int Secondi() const;
        orario UnOraPiuTardi() const;
        void AvanzaUnOra();
        void StampaSecondi() const;
        static orario OraDiPranzo();
        orario operator+(orario);
        orario operator-(orario);
        bool operator==(const orario&);
        bool operator>(orario);
        bool operator<(orario);

    protected:
        int sec;
};

ostream& operator<<(ostream& os, const orario& o);

#endif // ORARIO_H
