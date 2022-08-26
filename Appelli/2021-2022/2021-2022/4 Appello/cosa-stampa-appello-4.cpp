#include<iostream>

using namespace std;

class Z{
    public: Z(int x){}
};

class A{
public:
    void f(int) {cout << "A::f(int) "; f(true);}
    virtual void f(bool) {cout <<"A::f(bool) ";}
    virtual A* f(Z) {cout <<"A::f(Z) "; f(2); return this;}
    A() {cout <<"A() ";}
};

class B: virtual public A{
public:
    void f(const bool&){cout<< "B::f(const bool&) ";}
    void f(const int&){cout<< "B::f(const int&) ";}
    virtual B* f(Z) {cout <<"B::f(Z) "; return this;}
    virtual  ~B() {cout << " ̃B ";}
    B() {cout <<"B() "; }
};

class C: virtual public A{
public:
    C* f(Z){cout <<"C::f(Z) "; return this;}
    C() {cout <<"C() "; }
};

class D: virtual public A{
public:
    virtual void f(bool) const {cout <<"D::f(bool) ";}
    A* f(Z) {cout << "D::f(Z) "; return this;}
    ~D() {cout <<" ̃D ";}
    D() {cout <<"D() ";}
};

class E: public C{
public:
    C* f(Z){cout <<"E::f(Z) "; return this;}
    ~E() {cout <<" ̃E ";}
    E() {cout <<"E() ";}
};

class F: public B, public E, public D {
public:
    void f(bool){cout<< "F::f(bool) ";}
    F* f(Z){cout <<"F::f(Z) "; return this;}
    F() {cout <<"F() "; }
    ~F() {cout <<" ̃F ";}
};

B* pb=new B; C* pc = new C; D* pd = new D; E* pe = new E;
F* pf = new F; B *pb1= new F;
A *pa1=pb, *pa2=pc, *pa3=pd, *pa4=pe, *pa5=pf;

int main(){

    cout<<"\n\n";cout<<"---------";

    cout<<"01:";pa3->f(3);cout<<"\n";
    cout<<"02:";pa5->f(3);cout<<"\n";
    cout<<"03:";pb1->f(true);cout<<"\n";
    cout<<"04:";pa4->f(true);cout<<"\n";
    cout<<"05:";pa2->f(Z(2));cout<<"\n";
    cout<<"06:";pa5->f(Z(2));cout<<"\n";
    cout<<"07:";(dynamic_cast<E*>(pa4))->f(Z(2));cout<<"\n";
    cout<<"08:";(dynamic_cast<C*>(pa5))->f(Z(2));cout<<"\n";
    cout<<"09:";pb->f(3);cout<<"\n";
    cout<<"10:";pc->f(3);cout<<"\n";
    cout<<"11:";(pa4->f(Z(3)))->f(4);cout<<"\n";
    cout<<"12:";(pc->f(Z(3)))->f(4);cout<<"\n";
    cout<<"13:";E* puntE = new F;cout<<"\n";
    cout<<"14:";delete pa5;cout<<"\n";
    cout<<"15:";delete pb1;cout<<"\n";

    return 0;
}

