//Esercizio 1
Risposta (A)

//Esercizio 2
Risposta (D)

//Esercizio 3
BO12 UNO
Bc BO12 Bc 3 C012 DUE
BO12 BO12 Bc 0 C012 TRE
Bc Bc QUATTRO
i  i  CINQUE

//Esercizio 4
Risposta (C)

//Esercizio 5
Stampa: 0 6 7 8

//Esercizio 6
Risposta (D)

//Esercizio 7
pxxw pxxw xxhx UNO
ptkw ptkw xxhx ptkw DUE

//Esercizio 8 - Modellazione


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
};

ostream& operator<<(ostream&, const data&);

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
    return os<<d.Giorno()<<"/"<<