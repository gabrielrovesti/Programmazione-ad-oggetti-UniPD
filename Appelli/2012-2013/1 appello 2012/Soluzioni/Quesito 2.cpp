#include <iostream>
using namespace std;

class A {
protected:
	int x;
public:
	A(int k=0) : x(k) {cout << "A(int) ";}
	~A() { cout << "~A ";}
	operator double() const { cout << "operator double() "; return x;}
};

class B : public A {
public:
	static A a;
	const A& a2;
	A F(A a = A() ) { return a; }
	B(int k=3, const A &a3=0)	: A(k),a2(a3) {cout << "B() ";}
	~B() { cout <<"~B ";}
	B(const B &b) : a2(b) {cout << a2 << " ";}
};
A B::a(1);


int main(){
	A a(1); cout << "UNO" << endl;
	B b; cout << "DUE" << endl;
	B b2(a); cout << "TRE" << endl;
	B b3(a,a); cout << "QUATTRO" << endl;
	B b4=b3; cout << "CINQUE" << endl;
	b.F(); cout << "SEI" << endl;
	b.F(2); cout << "SETTE" << endl;
	return 0;
}


/*

 A(int)   A(int)						UNO					// la prima A(int) è per la A statica
 A(int)   A(int)   B()   ~A				DUE
 A(int)   operator double()   B()   ~A	TRE
 operator double()   A(int)   B()		QUATTRO
 A(int)   operator double()   1			CINQUE
 A(int)   ~A   ~A						SEI
 A(int)   ~A   ~A						SETTE
 ~B   ~A  ~B   ~A  ~B   ~A  ~B  ~A  ~A   ~A					// l'ultima ~A è la A statica
 
*/