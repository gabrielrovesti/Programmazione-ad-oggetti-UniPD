#include <iostream>

using namespace std;

class Z {
    public: Z(int x) {}
};

class A{
public:
    void f(int) { cout << "A::f(int) "; f(true); }  
    virtual void f(bool) { cout << "A::f(bool) "; }
    virtual A* f(Z) { cout << "A::f(Z) "; f(2); return this;  }
    A() { cout << "A() "; }
};

class B: virtual public A {
public:
    void f(const bool&) { cout << "B::f(const bool&) "; }
    void f(const int&) { cout << "const int& "; }
    virtual B* f(Z) { cout << "B::f(Z) "; return this; }
    virtual ~B() { cout << "~B "; }
    B() { cout << "B() "; }
};

class C: virtual public A {
public:
    C* f(Z) { cout << "C::f(Z) "; return this; }
    C() { cout << "C() "; }
};

class D: public B {
public:
    virtual void f(bool) const { cout << "D::f(bool) "; }
    B* f(Z) { cout << "D::f(Z) ";  return this; }
    ~D() { cout << "~D "; }
    D() { cout << "D()"; }
};

class E: public D, public C {
public:
    void f(bool) { cout << "E::f(bool) "; }
    E* f(Z) { cout << "E::f(Z) "; return this; }
    E() { cout << "E() "; }
    ~E() { cout << "~E "; }
};

int main() {
    B*pb=new B; C*pc = new C; D*pd = new D; E*pe = new E; A*pa1=pb,*pa2=pc,*pa3=pd,*pa4=pe; B*pb1=pe;
    
    cout << endl;
    
    E* puntE = new E;   cout << endl;
    D* puntD = new D;   cout << endl;
    pa3->f(3);          cout << endl;
    pa4->f(3);          cout << endl;
    pb1->f(true);       cout << endl;
    pa4->f(true);       cout << endl;
    pa2->f(Z(2));       cout << endl;
    pa4->f(Z(2));       cout << endl;
    pb->f(3);           cout << endl;
    pc->f(3);           cout << endl;
    
    (pa4->f(Z(3)))->f(4);   cout << endl; 
    (pc->f(Z(3)))->f(4);    cout << endl; 
    
    delete pa4;     cout << endl; 
    delete pd;      cout << endl; 
}








