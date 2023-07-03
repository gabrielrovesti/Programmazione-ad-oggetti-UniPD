#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
using namespace std;


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
    C* p3 = new C(); //TS A, TD C
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












