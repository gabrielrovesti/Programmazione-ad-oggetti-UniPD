/*Scrivere un programma che consista esattamente di tre classi A, B e C dove B è un sottotipo di A, mentre C non è in relazione di subtyping nè con A nè con B, che dimostri in un metodo di C un tipico esempio di un uso giustificato e necessario della conversione di tipo dynamic_cast per effettuare type downcasting. A questo fine si utilizzi il minor numero possibile di metodi.*/

#include<iostream>
using namespace std;

class A {
    public:
    virtual ~A();
};

A::~A() {}

class B : public A {
    public:
};

class C {
    public:
        B* fun(A* par) { return dynamic_cast<B*>(par); } 
};

/*********************************************************** II VERSIONE ***********************************************************/

#include<iostream>
using namespace std;

class A {
    public:
    virtual ~A();
};

A::~A() {}

class B : public A {
    public:
};

class C {
    private:
        B* b;
    public:
        C(A* a=new A()) : b(dynamic_cast<B*>(a)) {}
};
