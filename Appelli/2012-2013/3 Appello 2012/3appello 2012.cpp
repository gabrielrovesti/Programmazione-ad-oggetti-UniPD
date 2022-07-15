#include <iostream>
using namespace std;

class A {
public:
	A(int x=0) { cout << "A(" << x << ") ";  }
	~A() { cout << "~A "; }
};

class B : public A {
private:
	int x;
	A obj;
public:
	B() : obj(A()), x(2) { obj=2; cout << "B() "; }
	~B() { cout << "~B "; }
};

class C : public B {
public:
	static A a;
	B &b2;
	C(B y) : b2(y) { cout << "C(B) ";  }
};
A C::a;

int main() {
	A a(1); cout << "UNO" << endl;
	B b; cout << "DUE" << endl;
	C c2(b); cout << "TRE" << endl;
	
	// Stampa:
	// A(0) A(1) UNO
	// A(0) A(0) ~A A(2) ~A B() DUE
	// A(0) A(0) ~A A(2) ~A B() C(B) ~B ~A ~A TRE
	// ~B ~A ~A ~B ~A ~A ~A ~A
	 
	return 0;
}
