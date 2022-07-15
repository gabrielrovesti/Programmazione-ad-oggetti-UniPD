#include <iostream>
#include "AiPhone.h"
#include "App.h"
#include "PayApp.h"
#include "FreeApp.h"
using std::cout;
using std::endl;
int main()
{
    App* p1=new PayApp(20,true,5);
    App* p2=new FreeApp(30,true,true);
    AiPhone a(300);
    a.installaApp(*p1);
    a.installaApp(*p2);
    FreeApp* fa=a.G();
    cout<<fa->GetOpen()<<endl<<fa->GetMem()<<endl<<fa->GetInternet()<<endl;
}