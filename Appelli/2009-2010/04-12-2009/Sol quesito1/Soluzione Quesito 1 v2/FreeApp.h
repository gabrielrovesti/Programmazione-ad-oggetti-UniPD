#ifndef FREEAPP_H
#define FREEAPP_H
#include "App.h"
class FreeApp:public App{
private:
    bool open;
public:
    FreeApp(double,bool,bool);
    bool GetOpen() const;
};
#endif