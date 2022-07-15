#ifndef PAYAPP_H
#define PAYAPP_H
#include "App.h"
#include "Exc.h"
class PayApp:public App{
private:
    double prezzo;
public:
    PayApp(double,bool,double)throw(Exc);
    double GetPrezzo() const;
};
#endif