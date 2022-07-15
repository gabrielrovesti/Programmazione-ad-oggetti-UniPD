#include <iostream>
using namespace std;
#include <vector>
#include <list>


/*
//esercizio 1

class B{
private: vector<bool>* ptr;
    virtual void m()=0;
};

class D: public B{
private: int x;
};

class E: public D{
private: list<int*>l;
    int& ref;
    double*p;
public: 
	void m(){}
    //ridefinire costruttore di copia
    E(const E& e): D::D(e), l(e.l), ref(e.ref), p(e.p) {}
}

*/


//esercizio 2

class A{
    bool x;
public:
    virtual ~A() {};
};

class B{
    bool y;
public:
    virtual void f() const { cout<< " B::f ";}
};

class C: public A {};

class D: public B{
public:
    void f() const{ cout<<" D::f ";}
};

class E: public D{
public:
    void f() const {cout<<" E::f ";}
};

template<class T>
void Fun(const T& ref){
    const B* pB=dynamic_cast<const B*>(&ref);
    const E* pE=dynamic_cast<const E*>(&ref);
    if(dynamic_cast<const C*>(&ref)){
        cout<<" C ";
        ref.f();
        return;
    }
    if(pE){
        cout<<" E ";
        pE->f();
        return;
    }
    if(pB){
        cout<<" B ";
        pB->f();
        return;
    }
    if(dynamic_cast<const A*>(&ref)){cout<<" A "; return;}
    if(dynamic_cast<const D*>(&ref)){cout<<" D "; return;}

}

C c; D d; E e;
A& a1=c;
B& b1=d;
B& b2=e;
B* b3=new B();
D& d1=e;
D* pd1= dynamic_cast<E*>(&b2);
D* pd2= dynamic_cast<D*>(&b2);

int main()
{
    //Fun<A>(c); cout<<endl; //stampa A
    //Fun(a1); cout<<endl; //stampa A
    Fun(b1); cout<<endl;
    Fun<D>(e); cout<<endl;
    Fun(b2); cout<<endl;

    Fun<E>(e); cout<<endl;
    Fun(*b3); cout<<endl;
    Fun(*pd1); cout<<endl;
    Fun(e); cout<<endl;
    return 0;
}


//esercizio 3
/*
class C{
public:
    C(){cout<<" C0 ";}
    C(const C&) { cout<<" Cc ";}
    C& operator=(const C& e){
        cout<<" C= ";
        return*this;
    }
};

class D{
public:
    C c;
    D() {cout<<" D0 ";}
    D(const D&){cout<< " Dc ";}
};

class E: public C{
public:
    C c;
    E() {cout<<" E0 ";}
    E& operator =(const E& e){
        *this=e;
        cout<<" E= "; return*this;
    }
};

class F: public C{
public:
    C* pc;
    F() {cout<<" F0 ";}
    F(const F&){ cout<< " Fc ";}
    F& operator=(const F& f){
        C::operator =(f);
        pc=f.pc;
        cout<<" E= "; return*this;
    }
};

int main(){
    C x1; cout<<endl;
    C x2; cout<<endl;
    E y1; cout<<endl;
    E y2; cout<<endl;
    F z1; cout<<endl;
    F z2; cout<<endl;
    cout<<endl;
    cout<<"01 ";
    D d1; cout<<endl;
    cout<<"02 ";
    D d2(d1); cout<<endl;
    cout<<"03 ";
    E e1; cout<<endl;
    cout<<"04 ";
    E e2=y1; cout<<endl;
    cout<<"05 non stampa";
    //y1=y2; cout<<endl;
    cout<<"06 ";
    F*pF= new F(); cout<<endl;
    cout<<"07 ";
    F f=z1; cout<<endl;
    cout<<"08 ";
    z1=z2; cout<<endl;
    cout<<"09 ";
    x1=y1; cout<<endl;
    //z1=x1; cout<<endl;
}
*/
