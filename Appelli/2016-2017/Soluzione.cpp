#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
using namespace std;

class Workout{
private:
    double durata;

public:
    double getDurata() const {return durata;}
    virtual Workout* clone() const =0;
    virtual int calorie() const =0;
};

class Corsa: public Workout{
private:
    double distanza; //km

public:
    double getDistanza() const {return distanza;}
    virtual Workout* clone() const {
        return new Corsa(*this);
    }
    virtual int calorie() const {
        return (500*(distanza*distanza)/getDurata());
    }

};

class Nuoto: public Workout{
private:
    int numVasche;

public:
    int getNumVasche() const {return numVasche;}
};

class StileLibero: public Nuoto{
public:
    virtual Workout* clone() const {
        return new StileLibero(*this);
    }
    virtual int calorie() const {
        if(getDurata()<10)
            return 35*getNumVasche();
        else
            return 40*getNumVasche();
    }
};

class Dorso: public Nuoto{
public:
    virtual Workout* clone() const {
        return new Dorso(*this);
    }
    virtual int calorie() const {
        if(getDurata()<15)
            return 30*getNumVasche();
        else
            return 35*getNumVasche();
    }
};

class Rana: public Nuoto{
public:
    virtual Workout* clone() const {
        return new Rana(*this);
    }
    virtual int calorie() const {
        return 25*getNumVasche();
    }
};

class Informa{
private:
    vector<const Workout*> allenamenti;

public:
    vector<Nuoto*> vasche(int v) const {
        vector<Nuoto*> aux;
        for(vector<const Workout*>::const_iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Nuoto* p=dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(p && p->getNumVasche()>v)
                aux.push_back(p);
        }
        return aux;
    }

    vector<Workout*> calorie(int x) const {
        vector<Workout*> aux;
        for(vector<const Workout*>::const_iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Rana* p=dynamic_cast<Rana*>(const_cast<Workout*>(*it));
            if(!p && (*it)->calorie()>x)
                aux.push_back((*it)->clone());
        }
        return aux;
    }

    void removeNuoto(){
        double max=0;
        bool trovato=false;
        for(vector<const Workout*>::iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            if((*it)->calorie()>max)
                max=(*it)->calorie();
        }

        for(vector<const Workout*>::iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Nuoto* p=dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(p && p->calorie()==max){
                trovato=true;
                delete p;
                it=allenamenti.erase(it);
            }
        }
    }
};

int main(){}


/*
class A {
protected:
    virtual void h() {cout<<"A::h ";}
public:
    virtual void g() const {cout <<"A::g ";}
    virtual void f() {cout <<"A::f "; g(); h();}
    void m() {cout <<"A::m "; g(); h();}
    virtual void k() {cout <<"A::k "; h(); m(); }
    virtual A* n() {cout <<"A::n "; return this;}
};
class B: public A {
protected:
    virtual void h() {cout <<"B::h ";}
public:
    virtual void g() {cout <<"B::g ";}
    void m() {cout <<"B::m "; g(); h();}
    void k() {cout <<"B::k "; g(); h();}
    B* n() {cout <<"B::n "; return this;}
};
class C: public B {
protected:
    virtual void h() const {cout <<"C::h ";}
public:
    virtual void g() {cout <<"C::g ";}
    void m() {cout <<"C::m "; g(); k();}
    void k() const {cout <<"C::k "; h();}
};

int main(){
    A* p2 = new B(); //TS A, TD B
    A* p3 = new C(); //TS A, TD C
    B* p4 = new B(); //TS B, TD B
    B* p5 = new C(); //TS B, TD C
    const A* p6 = new C(); //TS A, TD C

    p2->f(); cout<<endl; //A::f A::g B::h
    p2->m(); cout<<endl; //A::m A::g B::h
    p3->k(); cout<<endl; //B::k C::g B::h
    p3->f(); cout<<endl; //A::f A::g B::h
    p4->m(); cout<<endl; //B::m B::g B::h
    p4->k(); cout<<endl; //B::k B::g B::h
    p4->g(); cout<<endl; //B::g
    p5->g(); cout<<endl; //C::g
    //p6->k(); cout<<endl; //ERRORE
    p6->g(); cout<<endl; //A::g
    (p3->n())->m(); cout<<endl; //B::n A::m A::g B::h
    (p3->n())->g(); cout<<endl; //B::n A::g
    (p3->n())->n()->g(); cout<<endl; //B::n B::n A::g
    (p5->n())->g(); cout<<endl; //B::n C::g
    (p5->n())->m(); cout<<endl; //B::n B::m C::g B::h
    (dynamic_cast<B*>(p2))->m(); cout<<endl; //B::m B::g B::h
    (static_cast<C*>(p3))->k(); cout<<endl; //C::k C::h
    (static_cast<B*>(p3->n()))->g(); cout<<endl; //B::n C::g
}
*/











