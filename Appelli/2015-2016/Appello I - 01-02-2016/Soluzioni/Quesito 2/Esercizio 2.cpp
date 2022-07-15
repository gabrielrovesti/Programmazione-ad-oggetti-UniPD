#include <iostream>
#include <vector>
#include <list>
using namespace std;

class B { 
private:
	list<double>* ptr;
	virtual void m() =0; 
};

class C: virtual public B {};

class D: virtual public B { 
private: 
	int x;
};

class E: public C, public D {
private:
	vector<int*> v; 
public:
	void m() {}
	
	// ridefinizione del costruttore di copia di E
 E(const E& e): B(e),C(e),D(e),v(e.v){}
};

main(){

}