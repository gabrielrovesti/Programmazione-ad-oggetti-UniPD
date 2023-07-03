#include<iostream>
using namespace std;
class A{
	public: A() { cout << "A" ;}
};

class B: virtual public A{
	public: B() { cout << "B" ;}
};

class C: virtual public A{
	public: C(): A() { cout << "C" ;}
};

class D: virtual public B, virtual public C{
	public: D(): C(), B() { cout << "D" ;}
};

int main(){
    F f;
    /*
        1-ABCEF
        2-ABECF
        3-ABCDEF
        4-ABCDEF
        5-ACBF
        6-NON COMPILA (errore nei :)
    */
}
