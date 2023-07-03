#include <iostream>
using namespace std;

class A { 
	private: 
		int x;
	public: 
		A(int k=0): x(k) { cout << "A(int) ";} 
		~A() { cout << " ̃A ";}
	};

class B : public A { 
	public:
		static A a; 
		A F(A a=A()) { return a; } 
		B() : A(3) { cout << "B() ";} 
		~B() { cout << " ̃B ";}
}; 
A B::a(1);


int main() { 
											//	A(int)
	A a(1); cout << "UNO" << endl;			//	A(int)			UNO
	B b;	cout << "DUE" << endl;			//	A(int) B()		DUE
	b.F();	cout << "TRE" << endl;			//	A(int)  ̃A  ̃A	TRE
	b.F(2); cout << "QUATTRO" << endl;		//	A(int)  ̃A  ̃A	QUATTRO
											//	 ̃B  ̃A  ̃A  ̃A		
	return 0;
}