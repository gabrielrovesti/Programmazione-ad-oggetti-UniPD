#include <iostream>

using namespace std;



class B {
public:
    B() {cout<<"B() ";}
	virtual ~B() {cout<<"~B() ";}
    virtual void f() {cout << "B::f "; g(); j();}
    virtual void g() const {cout <<"B::g ";}
    virtual const B* j() {cout<<"B::j " ; return this;}
    virtual void k() {cout<<"B::k "; j(); m(); }
    void m() {cout <<"B::m "; g(); j();}
    virtual B& n() { cout<<"B::n "; return *this;}
};

class C: virtual public B {
public:
	C() {cout<<"C() ";}
	~C() {cout<<"~C() ";}
	virtual void g() const override {cout << "C::g ";}
	virtual void m() {cout <<"C::m "; g(); j();}
	void k() override {cout <<"C::k "; B::n();}
	B& n() override {cout <<"C::n "; return *this; }
};


class D: virtual public B {
public:
	D() {cout<<"D() ";}
	~D(){ cout<<"~D() ";}
	virtual void g(){cout <<"D::g ";}
	const B* j() {cout <<"D::j "; return this;}
	void k() const {cout <<"D::k "; k();}
    void m() {cout<<"D::m "; g(); j(); }
};


class E: public C, public D {
public:
	E() {cout<<"E() ";}
	~E(){cout<<"~E() ";}
    virtual void g() const{cout << "E::g ";}
    const E* j(){cout<<"E::j "; return this;}
    void m() {cout <<"E::m "; g(); j();}
    D& n() final{cout <<"E::n "; return *this;}
};

class F: public E{
public:
	F() {cout<<"F() ";}
	~F() {cout<<"~F() ";}
	F (const F& x): B(x) {cout<<"Fc ";}
	void k() {cout<<"F::k "; g();}
	void m() {cout<<"F::m "; j();}
};


int main() {
    B *p1 = new E();
    B *p2 = new C();
    B *p3 = new D();
    C *p4 = new E();
    const B *p5 = new D();
    const B *p6=new E();
    const B *p7=new F();
    F f;
    cout<<endl;
//stampe
	cout<<"STAMPE"<<endl;
	F x;cout<<endl;    							//stampa B() C() D() E() F()
	C *p=new F(f);cout<<endl;					//stampa C() D() E() Fc
	p1->f();cout<<endl;							//stampa B::f E::g E::j
	p1->m();cout<<endl;							//stampa B::m E::g E::j
	//(p1->j())->k(); 							//NON COMPILA "error: passing ‘const B’ as ‘this’ argument discards qualifiers"
	//(dynamic_cast<const F*>(p1->j()))->g();		//RUNTIME ERROR
	p2->f();cout<<endl;							//stampa B::f C::g B::j
	p2->m();cout<<endl;							//stampa B::m C::g
	(p2->j())->g();cout<<endl;					//stampa B::j C::g
	p3->f();cout<<endl;							//stampa B::f B::g D::j
	p3->k();cout<<endl;							//stampa B::k D::j B::m B::g D::j
	(p3->n()).m();cout<<endl;					//B::n B::m B::g D::j
	(dynamic_cast<D&>(p3->n())).g();cout<<endl; //stampa B::n D::g
	p4->f();cout<<endl;							//stampa B::f E::g E::j
	p4->k();cout<<endl;							//stampa C::k B::n
	(p4->n()).m();cout<<endl;					//stampa E::n B::m E::g E::j
	//(p5->n()).g();cout<<endl;					//NON COMPILA "error: passing ‘const B’ as ‘this’ argument discards qualifiers"
	//(dynamic_cast<E*>(p6))->j();cout<<endl;		//NON COMPILA "cannot dynamic_cast ‘p6’ (of type ‘const class B*’) to type ‘class E*’"
	(dynamic_cast<C*>(const_cast<B*>(p7)))->k();cout<<endl; //stampa F::k E::g
	delete p7;cout<<endl;						//stampa ~F() ~E() ~D() ~C() ~B()
	cout<<"FINE STAMPE"<<endl;
	    
}