#include <iostream>
#include <vector>
#include <list>

enum Laurea{Informatica, Ingegneria, Altro};

using namespace std;
class ICTStaff{
    private:
    double stipendio;
    Laurea l;
    bool master;
    protected:
    double getStipendio() const{return stipendio;}
    public:
    virtual ICTStaff* clone() const=0;
    virtual ~ICTStaff()=default;
    virtual double salary() const=0;
    Laurea getLaurea() const{return l;}
    bool isMaster() const{return master;}
};

class SwEngineer: public ICTStaff{
    private:
    bool safe;
    static double extra;
    public:
    bool isSafe() const{return safe;}
    virtual double salary() const{
        return getStipendio() + (safe ? extra : 0);
    }
    virtual SwEngineer* clone() const{
        return new SwEngineer(*this);
    }
};
double SwEngineer::extra=500;

class HwEngineer: public ICTStaff{
    private:
    bool transfer;
    static double extra;
    public:
    bool isTransfer() const{return transfer;}
    virtual double salary() const{
        return getStipendio() + (transfer ? extra : 0);
    }
    virtual HwEngineer* clone() const{
        return new HwEngineer(*this);
    }
};
double HwEngineer::extra=300;

class Amazonia{
    private:
    class SmartP{
        public:
        ICTStaff* p;
        SmartP(ICTStaff* i=nullptr): p(i != nullptr ? i->clone() : nullptr){}
        SmartP(const SmartP& s): p(s.p!= nullptr ? (s.p)->clone() : nullptr){}
        SmartP& operator=(const SmartP& s){
            if(this != &s){
                if(p) delete p;
                p = s.p!=nullptr ? (s.p)->clone() : nullptr;
            }
            return *this;
        }
        ~SmartP(){if(p) delete p;}
        ICTStaff* operator->() const{return p;}
        ICTStaff& operator*() const {return *p;}
    };
    list<SmartP*> v;
    public:
    bool insert(SwEngineer* s, unsigned int k){
        int num=0;
        SwEngineer* q=nullptr;
        for(auto it = v.begin(); it != v.end() && num <k; ++it) {
        q=dynamic_cast<SwEngineer*>((*it)->p);
            if(q && q->isSafe()) {
                num++;
                v.push_back(*it);
            }
        }
        if(num<k) return true;
        return false;
    }
    vector<HwEngineer> fire(double s){
        vector<HwEngineer> h;
        HwEngineer *q=nullptr;
        for(auto it=v.begin(); it!=v.end(); ++it){
            if(dynamic_cast<HwEngineer*>((*it)->p)->salary() > s){
                q = dynamic_cast<HwEngineer*>((*it)->p);
                if(q) h.push_back(*q);
                it=v.erase(it); --it;
            }
        }
        return h;
    }
    vector<SwEngineer*> masterInf(){
        vector<SwEngineer*> v;
        SwEngineer* q= nullptr;
        for(auto it = v.begin(); it != v.end(); ++it){
            q = dynamic_cast<SwEngineer*>(*it); 
            if(q && q->getLaurea()==1 && q->isMaster()){
                v.push_back(q->clone());
            }
        }
        return v;
    }
};

int main(){
    return 0;
}