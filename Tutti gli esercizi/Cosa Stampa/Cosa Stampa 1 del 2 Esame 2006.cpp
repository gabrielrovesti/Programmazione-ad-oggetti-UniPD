#include <iostream>
using namespace std;

class B { 
protected:
	int i; 
public:
	B(int x = 5): i(x) {} 
	int f() const {return i;} 
	virtual int m(int x) const {return i+x;} 
	int f(double x) {return i - static_cast<int>(x);}
};

/*
class D: public B { 
private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	int m(B b) {return (k + b.i);} 
};

int main() { D d; B b; cout << d.m(b); }

//	NON COMPILA ESSENDO int B::i protected
*/


/*
class D: public B {
private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	int m(D d) { B::m(4); return k+d.i;} 
};

int main() { D d1, d2; cout << d1.m(d2); }

//	6
*/


/*
class D: public B { 
private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	int m(int x) const {return m(x);} 
};

int main() { D d; B* p=&d; cout << p->m(6); }

// ERRORE RUN-TIME / CICLO CONTINUO
*/


/*
class D: public B { private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	int f(int x) {return x + i;} 
};

int main() { D d; B* p=&d; cout << p->f(2); }

// 1
*/


/*
class D: public B { 
private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	double f(int x) {f(); return k+x;} 
};

int main() { D d; cout << d.f(); }

// ERRORE DI COMPILAZIONE -> HA BISOGNO DI UN INT
*/


/*
class D: public B {
	private: int k;
	public: 
	D(int x = 3): B(x), k(x) {}
	int f(int x) {return B::f();}
}

main() { D d; B* p=&d; cout << p->f(5.4);}

// ERRORE DI COMPILAZIONE - New types may not be defined in a return type
*/


/*
class D: public B { 
private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	int f() {B b(4); return m(b.i);} 
};

main() { D d; cout << d.f(); }

//	ERRORE DI COMPILAZIONE - PERCHE' PROTETTO B::i
*/


/*
class D: public B { 
private: int k;	 
public:
	D(int x = 3): B(x), k(x) {}
	double f(int x) {D d(4); return m(d.i);}
};

main() { D d; cout << d.f(2); }

//	7
*/


/*
class D: public B { 
private: int k; 
public:
	D(int x = 3): B(x), k(x) {} 
	int m(int x) const {
		const B* p = static_cast<const B*>(this);
		return p->m(x);
	}
};

main() { D d; B* p=&d; cout << p->m(8); }

// ERRORE RUN TIME
*/


/*
class D: public B { 
private: int k; 
public:
	D(int x = 3): B(x), k(x) {}
	int m(int x) const {return f(x);} 
};

main() { D d; B* p=&d; cout << p->m(5); }

// ERRORE DI COMPILAZIONE passing 'const D' as 'this' argument of 'int B::f(double)' discards qualifiers
*/

