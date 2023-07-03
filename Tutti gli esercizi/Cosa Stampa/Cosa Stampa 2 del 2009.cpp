#include <iostream>
using namespace std;

class D;

class B { 
public:
	virtual D* f() = 0; 
};

class C { 
public:
	virtual C* g();
	virtual B* h()=0;
};

class D: public B, public C { 
public:
	D* f() {cout << "D::f "; return new D;}
	D* h() {cout << "D::h "; return dynamic_cast<D*>(g());} 
};

C* C::g() { 
	cout << "C::g "; 
	B* p = dynamic_cast<B*>(this); 
	if(p) return p->f(); 
	else return this;
}

class E: public D { 
public:
	E* f() { 
		cout << "E::f "; 
		E* p = dynamic_cast<E*>(g()); 
		if(p) return p; else return this;
	} 
};

class F: public E { 
public:
	E* g() {cout << "F::g "; return new F;} 
	E* h() {
		cout << "F::h "; 
		E* p = dynamic_cast<E*>(E::g()); 
		return ( p ? p : new F);
	} };

main(){
	
	B* p; C* q; D* r;

	// p = new E; p->h();			//  'class B' has no member named 'h'
	// p = new E; p->f();			//	ERRORE RUN TIME E::f -> C::g -> E::f -> C::g -> ...
	// p = new D; 
	// (dynamic_cast<D*>(p))->h();	//	D::h  C::g  D::f 
	// q = new D; q->g();			//	C::g  D::f
	// q = new E; q->h();			//	ERRORE RUN TIME D::h  C::g  E::f  C::g  E::f  C::g -> ...
	// q = new F; q->g();			//	F::g
	// r = new E; r->f();			//	ERRORE RUN TIME E::f -> C::g -> E::f -> C::g -> ...
	// r = new F; r->f();			//	E::f  F::g
	// r = new F; r->g();			//  F::g  
	// r = new F; r->h();			//	F::h  C::g  E::f  F::g  
}