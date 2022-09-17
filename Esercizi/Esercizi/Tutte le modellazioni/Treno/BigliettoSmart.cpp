#include "BigliettoSmart.h"
BigliettoSmart::BigliettoSmart(Biglietto* b):punt(b)
{
}
Biglietto* BigliettoSmart::operator*() const
{
    return punt;
}