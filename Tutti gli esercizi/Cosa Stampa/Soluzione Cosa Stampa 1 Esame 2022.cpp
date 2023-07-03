#include <iostream>
using namespace std;

class Z {
    public: Z(int x) {};
};

class A {
public:
    A() {cout << "A() ";};
    ~A() {cout << "~A ";};
};

class B : public A {
public:
    void f(int) {cout << "B::f(int) "; f(3.14);}
    virtual void f(double) {cout << "B::f(double) ";}
    virtual B* f(Z) {cout << "B::f(Z) "; return this;}
    B() {cout << "B() ";};
    ~B() {cout << "~B ";};
};

class C : virtual public B {
public:
    virtual void f(const int&) {cout << "C::f(const int&) ";}
    virtual C* f(Z) {cout << "C::f(Z) "; return this;}
    C() {cout << "C() ";};
    virtual ~C() {cout << "~C ";};
};

class D : virtual public B {
public:
    D* f(Z) {cout << "D::f(Z) "; f(3.14); return this;}
    virtual void f(double) {cout << "D::f(double) ";};
    D() {cout << "D() ";};
    ~D() {cout << "~D ";};
};

class E : public C {
public:
    virtual void f() {cout << "E::f() "; C::f(Z(1));}
    C* f(Z) {cout << "E::f(Z) "; f(); return this;}
    E() {cout << "E() ";};
    E(const E& e) {cout << "Ec ";};
    ~E() {cout << "~E ";};
};

class F : public E, public D {
public:
    void f() const {cout << "F::f() ";}
    F* f(Z) {cout << "F::f(Z) "; return this;}
    void f(double) {cout << "F::f(double) ";}
    F() {cout << "F() ";};
    ~F() {cout << "~F ";};
};

A* pa = new F; D* pd = new D; E* pe = new E; F* pf = new F; B *pb1=pd, *pb3=pf; C* pc=pf;


int main()
{
    cout << endl;
    cout << endl;
    F* puntF = new F; cout << endl; 
    E* puntE = new E(*pe); cout << endl; 
    pb3->f(3); cout << endl; 
    cout << "NON COMPILA" << endl; 
    pb1->f(Z(7)); cout << endl; 
    if (typeid(pb3) == typeid(F)) {
        pb3->f(Z(1));
    } else {
        cout << "NESSUNA STAMPA" << endl;
    } 
    static_cast<E*>(pc)->f(); cout << endl; 
    pe->f(2); cout << endl; 
    (pc->f(Z(3)))->f(4); cout << endl;
    (pb3->f(Z(3)))->f(4); cout << endl; 
    delete pb3; cout << endl;  
    delete pe; cout << endl; 

    return 0;
}

/*
A() B() C() E() D() F()
A() B() C() Ec
B::f(int) F::f(double)
NON COMPILA
D::f(Z) D::f(double)
NESSUNA STAMPA
E::f() C::f(Z)
E::f(Z) E::f() C::f(Z)
F::f(Z) C::f(const int&)
F::f(Z) B::f(int) F::f(double)
~B ~A
~E ~C ~B ~A
*/