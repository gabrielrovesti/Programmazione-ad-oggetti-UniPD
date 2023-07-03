#include <iostream>
#include <typeinfo>

using namespace std;

class A {
public:
virtual void m() =0;
};

class B: virtual public A {};

class C: virtual public A {
public:
virtual void m() {}
};

class D: public B, public C {
public:
virtual void m() {}
};
class E: public D {};

class F: public E {};

char G(A* p, B& r) {

C* pc = dynamic_cast<E*>(&r);

if(pc && typeid(*p)==typeid(r)) return 'G';  // 1 == 2

if(!dynamic_cast<E*>(&r) && dynamic_cast<D*>(p)) return 'Z';//  !E == D

if(!dynamic_cast<F*>(pc)) return 'A';   //!F2

else if(typeid(*p)==typeid(E)) return 'S'; // F2  && 1E

return 'E';
}

int main ()
{
  cout << G(new E,*new F) << G(new D,*new E) << G(new F,*new F) << G(new E,*new E)
<< G(new C,*new F) << G(new D,*new D) << G(new F,*new D) << G(new C,*new D);

}
