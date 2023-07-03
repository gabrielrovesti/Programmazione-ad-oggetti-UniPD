#ifndef DATAORA_H
#define DATAORA_H
#include "orario.h"
class dataora : public orario
{
public:
    int Giorno() const;
    int Mese() const;
    int Anno() const;
    dataora operator+(const orario& o) const;
    void AvanzaUnGiorno();
private:
    int giorno;
    int mese;
    int anno;
};
#endif // DATAORA_H
