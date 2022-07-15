#include <iostream>
using namespace std;

class A { public: virtual ~A(){} }; 
class B: public A {}; 
class C: public A {}; 
class D: virtual public B {};
class E: virtual public B {}; 
class F: public D, public E {};

void f(A* p) throw(E*) { 
	if(!dynamic_cast<D*>(p)) throw new E();
}

char fun(A* p, B& r) { 
	if(typeid(*p)==typeid(r)) return '1'; 
	try{
		f(&r); 
	} catch(B*) {return '2';} 
	E* punt = dynamic_cast<F*>(&r); 
	try{
		B& ref = dynamic_cast<B&>(*p);
	} 
	catch(bad_cast) {
		if(!punt) return '3'; 
		return '4';
	} 
	if(punt) return '5'; 
	return '6';
}

main(){ 
	A a; B b; C c; D d; E e; F f; 
	//cout <<fun(?,?)<<fun(?,?)<<fun(?,?)<<fun(?,?)<<fun(?,?)<<fun(?,?);
	cout <<fun(&b,b)
	<<fun(&c,b)
	<<fun(&c,d)
	<<fun(&c,f)
	<<fun(&b,f)
	<<fun(&b,d);
}

/*
Definire opportunamente le chiamate in tale main() usando gli oggetti a, b, c, d, e, f locali al main() in 
modo tale che l’esecuzione del main() provochi la stampa 123456 su cout.
*/