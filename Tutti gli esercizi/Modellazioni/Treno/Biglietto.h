#ifndef BIGLIETTO_H
#define BIGLIETTO_H
class Biglietto{
private:
    double distanzaKM;
    static double prezzoKM;
public:
    Biglietto(double=0);
    double GetKm() const;
    static double GetPrezzoKm();
    virtual double prezzo() const=0;
    virtual~ Biglietto();
};
#endif