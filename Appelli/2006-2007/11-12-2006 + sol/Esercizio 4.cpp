#include <iostream>
using namespace std;

class A { 
public:
	virtual void m() {cout << " A::m() ";} 
	virtual void m(int x) {cout << " A::m(int) ";}
};

class B: public A { 
public:
	virtual void m(bool b) {m(3); cout << " B::m(bool) ";} 
	void m(int x) {cout << " B::m(int) ";}
}; 
	
class C: public A { 
public:
		virtual void m(bool b) {cout << " C::m(bool) ";}
}; 

class D: public B { 
public:
	void m() {B::m(false); cout << " D::m() "; }
	void m(int x) {cout << " D::m(int) ";}
}; 

class E: public D { 
public:
	void m(int x) {cout << " E::m(int) ";}
};	
	
A a; B b; C c; D d; E e;

int main(){

	//B* pb=&c; pb->m(3);						// NON CONVERTIBILE C->B
	
	//B* pb=&e; pb->m(true);					// E::m(int)  B::m(bool) 

	//B* pb=&e; pb->m(3);						// E::m(int)
	
	//A* pa=&e; pa->m();						// E::m(int)  B::m(bool)  D::m() 

	//A* pa=&d; pa->m();						// D::m(int)  B::m(bool)  D::m() 

	//D* pd=&e; pd->m(true);					// E::m(int) [ converte in automatico bool in int ]
	
	/*
	B* pb=&e; 
	D* pd=dynamic_cast<D*>(pb); pd->m(true);	// E::m(int)
	*/
	
	//A* pa=&b; pa->m(false);					// B::m(int) [ converte bool->int ]
	
	//D* pd=&e; pd->m(4);						// E::m(int)
	
	//B* pb=&d; pb->m(true);					// D::m(int)  B::m(bool)
	
	//B* pb=&d; pb->m(5);						// D::m(int)
	
	return 0;

}

