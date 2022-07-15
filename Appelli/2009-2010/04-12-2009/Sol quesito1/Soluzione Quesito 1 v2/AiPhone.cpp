#include "AiPhone.h"
AiPhone::AiPhone(double m):p(),memmax(m)
{
}
double AiPhone::installaApp(const App& a)throw(Exc)
{
    vector<App*>::const_iterator it=p.begin();
    double memocc=0;
    for(;it!=p.end();++it)
        memocc+=(*it)->GetMem();
    if(memocc+a.GetMem()<=memmax)
    {
        p.push_back(const_cast<App*>(&a));
        return memmax-(memocc+a.GetMem());
    }
    else
        throw Exc();
}
vector<PayApp> AiPhone::F(double x) const
{
    vector<PayApp> v;
    vector<App*>::const_iterator it=p.begin();
    for(;it!=p.end();++it)
    {
        if(dynamic_cast<PayApp*>(*it))
        {
            PayApp* app=dynamic_cast<PayApp*>(*it);
            if(app->GetInternet() && app->GetPrezzo()<=x)
                v.push_back(*app);
        }
    }
    return v;
}
FreeApp* AiPhone::G() const throw(Exc)
{
    FreeApp* fa=0;
    double max=0;
    vector<App*>::const_iterator it=p.begin();
    for(;it!=p.end();++it)
    {
        if(dynamic_cast<FreeApp*>(*it))
        {
            FreeApp* f=dynamic_cast<FreeApp*>(*it);
            if(f->GetOpen() && f->GetMem()>max)
            {
                max=f->GetMem();
                fa=f;
            }
    
        }
    }
    if(fa)
        return fa;
    else
        throw Exc();
}