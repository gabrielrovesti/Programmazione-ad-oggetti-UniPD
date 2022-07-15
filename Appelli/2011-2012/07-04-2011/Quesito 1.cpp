#include <iostream>
using namespace std;

class A { 
		int x[10];
};
class B : virtual public A { 
	public:
		int y; 
};

class C : virtual public A { 
	public:
		int z; 
};

class D : public B, public C { 
	public:
		int w; 
};


int main() {
	
	cout << sizeof(A) << endl;	//40
	cout << sizeof(B) << endl;	//48
	cout << sizeof(C) << endl;	//48
	cout << sizeof(D) << endl;	//60
	return 0;

}