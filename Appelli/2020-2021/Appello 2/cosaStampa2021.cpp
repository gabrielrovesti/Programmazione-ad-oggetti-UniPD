#include <iostream>
using namespace std;

class Z{
    public: Z(int x){}
};

class A{
    public:
    void f(int){cout << "A::f(int) " ; f(true);}
    virtual void f(bool){cout << "A::f(bool) ";}
    virtual A* f(Z){cout << "A::f(Z) "; f(2); return this;}
    A() {cout << "A() ";}
};

class B: virtual public A{
    public:
    void f(const bool&){cout << "B::f(const bool&) " ;}
    void f(const int&){cout << "B::f(const int&) " ;}
    virtual B* f(Z){cout << "B::f(Z) "; return this;}
    B() {cout << "B() ";}
    virtual ~B() {cout << "~B ";}
};

class C: virtual public A{
    public:
    C*f(Z) {cout << "C::f(Z) "; return this;}
    C() {cout << "C() "; }
};

class D:virtual public A{
    public:
    virtual void f(bool) const {cout << "D::f(bool) ";}
    A*f(Z) {cout << "D::f(Z) "; return this;}
    D() {cout << "D() ";}
    virtual ~D() {cout << "~D ";}
};

class E: public C{
    public:
    C*f(Z) {cout << "E::f(Z) "; return this;}
    E() {cout << "E() ";}
    ~E() {cout << "~E ";}
};

class F: public B, public E, public D{
    public:
    void f(bool) {cout << "F::f(bool) ";}
    F*f(Z) {cout << "F::f(Z) "; return this;}
    F() {cout << "F() "; }
    ~F() {cout << "~F ";}
};

int main(){
    B*pb1 = new F; B*pb2 = new B;
    C*pc = new C; E*pe = new E;
    A*pa1 = pc,*pa2 = pe,*pa3 = new F;
    cout << endl;

    pa3->f(3);                              cout<<endl;
    pb1->f(true);                           cout<<endl;
    pa2->f(true);                           cout<<endl;
    pa1->f(Z(2));                           cout<<endl;
    (dynamic_cast<E*>(pa2))->f(Z(2));       cout<<endl;
    (dynamic_cast<C*>(pa3))->f(Z(2));       cout<<endl;
    pb2->f(3);                              cout<<endl;
    (pa2->f(Z(3)))->f(4);                   cout<<endl;
    (pc->f(Z(3)))->f(4);                    cout<<endl;
    E*puntE = new F;                        cout<<endl;
    delete pa3;                             cout<<endl;
    delete pb1;                             cout<<endl;
}
