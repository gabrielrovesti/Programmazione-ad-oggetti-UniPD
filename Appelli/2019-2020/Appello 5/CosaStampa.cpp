using namespace std;
#include <iostream> 

class B{
protected:
	virtual void h() {cout<<"B::h";}
public:
	virtual void f() {cout<<"B::f"; g(); h();}
	virtual void g() const {cout<<"B::g";}
	virtual void k() {cout<<"B::k"; h(); m();}
	void m() {cout<<"B::m"; g(); h();}
	virtual B* n() {cout<<"B::n"; return this;}

};

class C: public B{
public:
	virtual void g() const {cout<< "C::g";}
	void k() {cout<< "C::k"; B::n();}
	virtual void m() {cout<< "C::m"; g(); h();}
	B* n() {cout<<"C::n"; return this;}
};

class D: public B{
protected:
	void h() {cout<< "D::h";}
public:
	virtual void g() {cout<<"D::g";}
	void k() const {cout<<"D::k"; k();}
	void m() {cout<< "D::m"; g(); h();}
};

class E: public C{
protected:
	void h() {cout<<"E::h";}
public:
	void m() {cout<<"E::m"; g(); h();}
	C* n() {cout<<"E::n"; return this;}
};


int main(){
	const B* p1= new D();
	B* p2= new C ();
	B* p3= new D ();
	C* p4= new E ();
	B* p5= new E ();


	p1->g();
	(p1->n())->g();
	p2->f();
	p2->m();
	(static_cast<D*>(p2))->k();
	p3->k();
	p3->f();
	(p3->n())->m();
	(p3->n())->n()->g();
	(static_cast<C*>(p3->n()))->g();
	p4->m();
	p4->k();
	(p4->n())->m();
	p5->g();
	p5->k();
	(dynamic_cast<C*>(p5))->m();

}

