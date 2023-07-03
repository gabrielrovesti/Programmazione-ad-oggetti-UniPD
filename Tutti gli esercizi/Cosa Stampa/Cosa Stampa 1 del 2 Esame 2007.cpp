#include <iostream>
using namespace std;

class A { 
private: 
	int x;
public: 
	A(int k=0): x(k) {} 
	A operator+(A a) const {A aux(x + a.x); return aux;} 
	operator int() const {return x;} 
	A F() {++x; return *this;}
};

class C { 
public:
	static A a; 
	static void G(A& x, A& y) {a = a + x.F() + y.F();}
};

A C::a(1);

main() { 
	A p(2), q, r; 
	C::G(p,q); cout << C::a << " "; 
	C::G(q,r); cout << C::a << " "; 
	C::G(p,r); cout << C::a;
}

//	(3)		5	8	14