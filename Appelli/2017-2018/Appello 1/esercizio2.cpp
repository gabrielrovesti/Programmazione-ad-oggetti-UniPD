# include <iostream>
using namespace std;


class A {
protected:
virtual void j() { cout<<" A::j "; }
public:
virtual void g() const { cout <<" A::g "; }
virtual void f() { cout <<" A::f "; g(); j(); }
void m() { cout <<" A::m "; g(); j(); }
virtual void k() { cout <<" A::k "; j(); m(); }
virtual A* n() { cout <<" A::n "; return this; }
};

class B: public A {
public:
virtual void g() const override { cout <<" B::g "; }
virtual void m() { cout <<" B::m "; g(); j(); }
void k() { cout <<" B::k "; A::n(); }
A* n() override { cout <<" B::n "; return this; }
};

class C: public A {
private:
void j() { cout <<" C::j "; }
public:
virtual void g() { cout <<" C::g "; }
void m() { cout <<" C::m "; g(); j(); }
void k() const { cout <<" C::k "; k(); }
};


class D: public B {
protected:
void j() { cout <<" D::j "; }
public:
B* n() final { cout <<" D::n "; return this; }
void m() { cout <<" D::m "; g(); j(); }
};

A* p1 = new D(); A* p2 = new B(); A* p3 = new C(); B* p4 = new D(); const A* p5 = new C();

int main () {

p1->g();   cout << endl;// 1 ............................  B::g
p1->k();   cout << endl;// 2 ............................  B::k  A::n 
p2->f();    cout << endl;// 3............................. A::f  B::g  A::j
p2->m();    cout << endl;// 4 ......................... .  A::m  B::g  A::j
p3->k();   cout << endl;// 5 ............................ A::k  C::j  A::m  A::g  C::j
p3->f();   cout << endl;// 6 ...........................  A::f  A::g  C::j 
p4->m();   cout << endl;// 7 ...........................  D::m  B::g  D::j
p4->k();   cout << endl;// 8 ...........................  B::k  A::n
p5->g();   cout << endl;// 9 ............................ A::g 
(p3->n())->m();   cout << endl;// 10 .................... A::n  A::m  A::g  C::j 
(p3->n())->n()->g();   cout << endl;// 11 ............... A::n  A::n  A::g 
(p4->n())->m();    cout << endl;// 12 ..................  D::n  A::m  B::g  D::j
//(p5->n())->g();  cout << endl;  // 13  ...............   non compila 
 (dynamic_cast<B*>(p1))->m(); // 14 ..................    D::m  B::g  D::j 
//(static_cast<C*>(p2))->k(); // 15 ........................errore run time 
//(static_cast<B*>(p3->n()))->g();  //16 .................. errore run time 


};
