#include <iostream>
using namespace std;

class A { 
	public:
		A() { cout << "A ";} 
		A(const A&) {cout << "Ac ";} 
		virtual ~A() {cout << " ̃A ";}
};
		
class B : virtual public A {
	public:
		B() { cout << "B "; }
		~B() {cout << " ̃B "; } 
};

class C : virtual public A { 
	public:
		static A x; 
		C() { cout << "C "; } 
		C(const C&) {cout << "Cc";}
}; 
A C::x;
			
class D : public B, public C {
	public:
		D() { cout << "D "; } 
		D& operator=(const D& d) {cout << "D= "; return *this;}
		~D() {cout << " ̃D "; }
};
			
int main() {
	
	cout << "START" << endl; 
	D *b=new D(); cout << "UNO" << endl; 
	D d,e; cout << "DUE" << endl; 
	e=d;cout << "TRE" << endl;
	return 0;

}
/*
A						START
A B C D					UNO
A B C D A B C D			DUE
D=						TRE
̃D  ̃B  ̃A  ̃D  ̃B  ̃A  ̃A