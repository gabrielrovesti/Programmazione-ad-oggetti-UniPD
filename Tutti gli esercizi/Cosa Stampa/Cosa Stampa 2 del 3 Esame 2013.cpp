#include <iostream>

using namespace std;

class A {
protected:
	string s;
public:
	A(string str="") : s(str) { cout << "A(" << s << ") "; }
};

class B : virtual public A {
private:
	A a;
public:
	B(string s="x") : A(s), a("xyz") { cout << "B(" << s << ") "; }
};

class C : virtual public A {
private:
	static A a;
public:
	C(string s="y") : A(s) { cout << "C(" << s << ") "; }
};
A C::a("pluto");

class D : public B, public C {
public:
	D() : B("pippo"), C("paperino") { cout << "D(" << s << ") "; }
};

int main() {
	D d;
	// Stampa: A(pluto) A() A(xyz) B(pippo) C(paperino) D()
}
