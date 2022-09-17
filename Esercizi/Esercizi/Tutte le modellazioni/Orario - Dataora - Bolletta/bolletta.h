#ifndef BOLLETTA_H
#define BOLLETTA_H
#include "telefonata.h"

class bolletta
{
    friend class iteratore;
private:
    class nodo;

    class smartp
    {
    public:
        nodo* punt;
        smartp(nodo* p=0);
        smartp(const smartp&);
        ~smartp();
        smartp& operator=(const smartp&);
        nodo& operator*() const;
        nodo* operator->() const;
        bool operator==(const smartp&) const;
        bool operator!=(const smartp&) const;
    };

    class nodo
    {
        public:
            nodo();
            nodo(const telefonata&, const smartp&);
            telefonata info;
            smartp next;
            int riferimenti;
    };

public:
    class iteratore
    {
        friend class bolletta;
    private:
        bolletta::smartp p;
    public:
        bool operator==(iteratore) const;
        bool operator!=(iteratore) const;
        iteratore& operator++();
        iteratore operator++(int);
        telefonata& operator*(iteratore) const;
    };
    bolletta(): first(0) {}
    bolletta(const bolletta&);
    bool Vuota() const;
    void Aggiungi_Telefonata(telefonata);
    void Togli_Telefonata(telefonata);
    void Sostituisci(const telefonata& t1, const telefonata& t2);
    telefonata Estrai_Una();
    bolletta& operator=(const bolletta&);
    iteratore begin() const;
    iteratore end() const;
    telefonata& operator[](iteratore) const;
    static nodo* copia(nodo*);
    static void distruggi(nodo*);
    smartp first;
    friend ostream& operator<<(ostream&, const bolletta&);


};

orario Somma_Durate(bolletta b);
bolletta Chiamate_A(int num, bolletta& b);
#endif // BOLLETTA_H
