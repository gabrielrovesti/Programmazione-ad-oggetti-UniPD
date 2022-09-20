#ifndef orario_h
#define orario_h

#include <iostream>

using std::ostream;

class orario {
public:
    int Ore() const;
    int Minuti() const;
    int Secondi() const;
    orario(int =0, int =0, int =0); 
    int Secondi_this(orario*);
    operator int() {return sec;}    //conversione orario -> intero. prende un oggetto orario e restituisce il suo campo sec
    orario UnOraPiuTardi(); //no side effect
    void AvanzaUnOra();
    void StampaSecondi() const; //no modifiche campo dati
    static orario OraDiPranzo(); //metodo statico visibile una sola volta
private:
    int sec;
};

ostream& operator<<(ostream&, const orario&);
bool operator==(const orario&, const orario&);

#endif
