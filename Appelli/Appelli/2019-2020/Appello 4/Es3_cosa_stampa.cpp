// Esercizio "cosa stampa"
// Per ogni istruzione dire se compila o meno, se produce errore a run time e cosa stampa.

#include <iostream>
using namespace std;

class C {
  public:
    C() { cout << "C0 "; }
    C(const C&) { cout << "Cc "; }
    C& operator=(const C& e) {
      cout << "C= ";
      return *this;
    }
};

class D {
  public:
    C c;
    D() { cout << "D0 "; }
    D(const D&) { cout << "Dc "; }
};

class E: public C {
  public:
    C c;
    E() { cout << "E0 "; }
    E& operator=(const E& e) {
      *this = e;
      cout << "E= ";
      return *this;
    }
};

class F: public C {
  public:
    C* pc;
    F() { cout << "F0 "; }
    F(const F&) { cout << "Fc "; }
    F& operator=(const F& f) {
      C::operator=(f);
      pc = f.pc;
      cout << "E= ";
      return *this;
    }
};

int main() {
    C x1; cout<<endl;   //C0
    C x2; cout<<endl;   //C0
    E y1; cout<<endl;   //C0 C0 E0
    E y2; cout<<endl;   //C0 E0 E0
    F z1; cout<<endl;   //C0 F0
    F z2; cout<<endl;   //C0 F0
    cout<<endl;
    cout<<"01 ";
    D d1; cout<<endl;   //01 C0 D0
    cout<<"02 ";
    D d2(d1); cout<<endl; //02 C0 Dc
    cout<<"03 ";
    E e1; cout<<endl;   //03 C0 C0 E0
    cout<<"04 ";
    E e2=y1; cout<<endl; //04 Cc Cc
    cout<<"05 non stampa";
    //y1=y2; cout<<endl;
    cout<<"06 ";    
    F* pF= new F(); cout<<endl;  //06  C0  F0
    cout<<"07 ";
    F f=z1; cout<<endl; //07  C0  Fc 
    cout<<"08 ";
    z1=z2; cout<<endl;  //08  C=  E= 
    cout<<"09 ";
    x1=y1; cout<<endl;  //09  C= 
    //z1=x1; cout<<endl;
}
