#include <iostream>
using namespace std;

/*
Si scriva una gerarchia di almeno 5 classi che includa una classe D definita mediante ereditarieta` a diamente 
ed una classe B che sia una classe base virtuale per D. Scrivere inoltre un programma esempio che dimostri con 
opportune stampe su cout che i costruttori delle superclassi dirette non virtuali di D escludono di richiamare 
il costruttore della classe base virtuale B.
*/

class A {
public:
	virtual ~A() =0 ;
};

class B : virtual public A {};

class C : public B {};

class D : virtual public B {};

class E : public C, public D { };

main(){
	E e;
	cout << sizeof(e);
}
