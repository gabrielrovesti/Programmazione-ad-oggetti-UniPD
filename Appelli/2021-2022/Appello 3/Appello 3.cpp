#include<iostream>

using namespace std;

class B{
	public:
		B() { cout<<" B() "; }
		virtual ~B() { cout<<" ~B() "; }
		virtual void f() { cout<<" B::f "; g(); j(); }
		virtual void g() const { cout<<" B::g "; }
		virtual const B* j() { cout<<" B::j "; return this; }
		virtual void k() { cout<<" B::k "; j(); m(); }
		void m() { cout<<" B::m "; g(); j(); }
		virtual B& n() { cout<<" B::n "; return *this; }
};
class C:virtual public B{
	public:
		C(){ cout<<" C() "; }
		~C(){ cout<<" ~C() "; }
		virtual void g() const override{ cout<<" C::g "; }
		void k() override{ cout<<" C::k "; j(); m(); }
		virtual void m(){ cout<<" C::m "; g(); j(); }
		B& n() override{ cout<<" C::n "; return *this; }
};
class D:virtual public B{
	public:
		D(){ cout<<" D() "; }
		~D(){ cout<<" ~D() "; }
		virtual void g(){ cout<<" D::g "; }
		const B* j(){ cout<<" D::j "; return this;}
		void k() const{ cout<<" D::k "; k(); }
		void m(){ cout<<" D::m "; g(); j(); }
};
class E:public C,public D{
	public:
		E(){ cout<<" E() "; }
		~E(){ cout<<" ~E() "; }
		virtual void g() const{ cout<<" E::g "; }
		const E* j(){ cout<<" E::j "; return this;}
		void m(){ cout<<" E::m "; g(); j(); }
		D& n() final{ cout<<" E::n "; return *this; }
};
class F:public E{
	public:
		F(){ cout<<" F() "; }
		~F(){ cout<<" ~F() "; }
		F(const F& x): B(x) {cout<<" Fc ";}
		void k() { cout<<" F::k "; g(); }
		void m() { cout<<" F::m "; j(); }
};

B* p1 = new E(); B* p2 = new C(); B* p3 = new D(); C* p4 = new E();
const B* p5 = new D(); const B* p6 = new E(); const B* p7 = new F(); F f;

int main(){
	cout<<endl;
	cout<<"1) ";p4->f();cout<<endl;
	cout<<"2) ";(p4->n()).m();cout<<endl;
	cout<<"3) ";p3->k();cout<<endl;
	cout<<"4) ";(p3->n()).m();cout<<endl;
	cout<<"5) ";(dynamic_cast<D&>(p3->n())).g();cout<<endl;
	cout<<"6) ";p2->f();cout<<endl;
	cout<<"7) ";p2->m();cout<<endl;
	cout<<"8) ";(p2->j())->g();cout<<endl;
	cout<<"9) ";/*(p5->n()).g()*/cout<<"NON COMPILA"<<endl;
	cout<<"10) ";F x;cout<<endl;
	cout<<"11) ";C* p = new F(f);cout<<endl;
	cout<<"12) ";p1->m();cout<<endl;
	cout<<"13) ";/*(p1->j())->k();*/cout<<"NON COMPILA"<<endl;
	cout<<"14) ";/*(dynamic_cast<const F*>(p1->j()))->g();*/cout<<"ERRORE RUNTIME"<<endl;
	cout<<"15) ";/*(dynamic_cast<E*>(p6))->j();*/cout<<"NON COMPILA"<<endl;
	cout<<"16) ";(dynamic_cast<C*>(const_cast<B*>(p7)))->k();cout<<endl;
	cout<<"10) ";delete p7;cout<<endl;
}

