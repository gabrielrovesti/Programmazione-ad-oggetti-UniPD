#include <iostream>

using namespace std;

class A{
    bool x;
public:
    virtual ~A() =default;
};
     
     
class B {
    bool y;
public:
    virtual  void f() const { cout << "B::f "; }
};

class C: public A {};

class D : public B {
public:
    void f() const { cout << "D::f "; }
};

class E: public D {
public:
    void f() const { cout << "E::f "; } 
};

template <class T>
void Fun(const T& ref) {
    try{ throw ref; }    
    catch(const C& c) { cout << "C "; }
    catch(const E& e) { cout << "E "; e.f(); }
    catch(const B& b) { cout << "B "; b.f(); }
    catch(const A& a) { cout << "A "; }
    catch(const D& E) { cout << "D "; }
    catch(...) { cout << "GEN "; }
}

int main() {
    
    C c; D d; E e; A& a1 = c; B& b1 = d; B& b2 = e; D& d1 = e; D*pd = dynamic_cast<E*>(&b2);
    
    Fun(c); cout << endl;
    Fun(d); cout << endl;
    Fun(e); cout << endl;
    Fun(a1); cout << endl;
    Fun(b1); cout << endl;
    Fun(d1); cout << endl;
    Fun(*pd); cout << endl;
    Fun<D>(*pd); cout << endl;
    Fun<D>(e); cout << endl;
    // Fun<E>(*pd); cout << endl; --> NON COMPILA
    Fun<E>(e); cout << endl;
    // Fun<E>(d1); cout << endl; --> NON COMPILA
    Fun<A>(c); cout << endl;     
}

