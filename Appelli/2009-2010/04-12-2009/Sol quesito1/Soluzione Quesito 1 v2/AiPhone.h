#ifndef AIPHONE_H
#define AIPHONE_H
#include <vector>
#include "App.h"
#include "FreeApp.h"
#include "PayApp.h"
#include "Exc.h"
using std::vector;
class AiPhone{
private:
    vector<App*> p;
    double memmax;
public:
    AiPhone(double);
    double installaApp(const App&)throw(Exc);
    vector<PayApp> F(double) const;
    FreeApp* G() const throw(Exc);
};
#endif