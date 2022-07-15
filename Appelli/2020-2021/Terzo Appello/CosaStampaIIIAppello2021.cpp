#include<iostream>
using namespace std;

class A{
public:
    virtual ~A() {}
};

class B : public A{};
class C : public A{};
class D : public C{};

template<class T>
void Fun(T* pt){
    bool b = 0;
    try{ throw T(*pt); }
    catch(B){cout << "B " << endl; b=1;}
    catch(C){cout << "C " << endl; b=1;}
    catch(C){cout << "C " << endl; b=1;}
    catch(D){cout << "D " << endl; b=1;}
    catch(A){cout << "A " << endl; b=1;}
    if(!b) cout<<"NO ";
}

int main(){
    B b;
    C c;
    D d;
    A*pa1 = &b, *pa2 = &d;
    B* pb1 = dynamic_cast<B*>(pa1);
    B* pb2 = dynamic_cast<B*>(pa2);

    cout << "01 "; Fun(&c);                     //01 C
    cout << "02 "; Fun(&d);                     //02 C
    cout << "03 "; Fun(pa1);                    //03 A
    cout << "04 "; Fun(pa2);                    //04 A
    cout << "05 "; Fun(pb1);                    //05 B
    cout << "06 "; Fun(pb2);                    //06 B
    cout << "07 "; Fun<A>(pb1);                 //07 A
    cout << "08 "; Fun<A>(pa2);                 //08 A
    cout << "09 "; Fun<B>(pb1);                 //09 B
    cout << "10 "; Fun<C>(pa2);                 //10 NON COMPILA
    cout << "11 "; Fun<C>(&d);                  //11 C
    cout << "12 "; Fun<D>(pa2);                 //12 NON COMPILA
}