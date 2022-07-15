#include "App.h"
App::App(double m,bool i):memMB(m),internet(i)
{
}
double App::GetMem() const
{
    return memMB;
}
bool App::GetInternet() const
{
    return internet;
}
App::~App()
{
}