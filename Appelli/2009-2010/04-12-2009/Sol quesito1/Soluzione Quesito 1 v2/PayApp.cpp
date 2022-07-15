#include "PayApp.h"
PayApp::PayApp(double mem,bool i,double p)throw(Exc):App(mem,i),prezzo(p)
{
    if(p<=0)
        throw Exc();
}
double PayApp::GetPrezzo() const
{
    return prezzo;
}