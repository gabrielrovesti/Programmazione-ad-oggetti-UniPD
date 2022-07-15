#include "FreeApp.h"
FreeApp::FreeApp(double m,bool i,bool op):App(m,i),open(op)
{
}
bool FreeApp::GetOpen() const
{
    return open;
}