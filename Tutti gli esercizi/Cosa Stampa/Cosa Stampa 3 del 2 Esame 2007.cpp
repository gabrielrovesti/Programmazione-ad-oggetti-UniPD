#include <iostream>
using namespace std;

class S { 
public:
	int s; 
	S(int x): s(x) {}
};

class N { 
private:
	S x; 
public:
	N* next; 
	N(S t, N* p): x(t), next(p) {cout << "N2 ";} 
	~N() {if (next) delete next; cout << x.s << "  ̃N ";}
};
		
class C { 
	N* pointer;
public: 
	C(): pointer(0) {} 
	~C() {delete pointer; cout << " ̃C ";} 
	void F(int a, int b = 9) {
		pointer = new N(S(a),pointer); pointer = new N(b,pointer);
	}
};


main(){ 
	
	C* p = new C; cout << "UNO\n"; 
	
	p->F(3,5); p->F(7); cout <<"DUE\n"; 

	delete p; cout <<"TRE\n";

}


/*
	......................		UNO
	
	N2 N2 N2 N2 ..........		DUE
	
	3  ̃N 5  ̃N 7  ̃N 9  ̃N  ̃C		TRE

*/