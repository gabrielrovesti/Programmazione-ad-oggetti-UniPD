#include<iostream>
using std::cout; using std::endl; 

class A {
    protected:
        virtual void h(){ cout << "A::h ";}
    public:
        virtual void g() const {cout << "A::g ";} 
        virtual void f() {cout << "A::f "; g(); h();}
        void m() {cout<< "A::m "; g(); h();}
        virtual void k() {cout << "A::k "; h(); m();}
        virtual A* n() {cout << "A::n "; return this;}
};

class B : public A {
    protected:
        virtual void h(){ cout << "B::h ";}
    public:
        virtual void g() {cout << "B::g ";} 
        void m() {cout<< "B::m "; g(); h();}
        void k() {cout << "B::k "; g(); h();}
        B* n() {cout << "B::n "; return this;}
};

class C : public B {
    protected:
        virtual void h(){ cout << "C::h ";}
    public:
        virtual void g() {cout << "C::g ";} 
        void m() {cout<< "C::m "; g(); k();}
        void k() {cout << "C::k "; h();}
};

int main(){ 
    A* p2 = new B();
    A* p3 = new C();
    B* p4 = new B();
    B* p5 = new C();
    const A* p6 = new C();

    p2->f(); cout << endl;
    p2->m(); cout << endl;
    p3->k(); cout << endl;

    p3->f(); cout << endl;
    p4->m();cout << endl;
    p4->k();cout << endl;

    p4->g(); cout << endl;
    p5->g(); cout << endl;
    //p6->k(); //non compila

    p6->g(); cout << endl;
    (p3->n())->m(); cout << endl;
    (p3->n())->g(); cout << endl;

    ((p3->n())->n())->g(); cout << endl;
    (p5->n())->g(); cout << endl;
    (p5->n())->m(); cout << endl;

    (dynamic_cast<B*>(p2))->m(); cout << endl;
    (static_cast<C*>(p3))->k(); cout << endl;
    (static_cast<B*>(p3->n()))->g(); cout << endl;
}