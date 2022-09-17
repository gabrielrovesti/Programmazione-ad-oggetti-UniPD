/*Lettera O
siamo dentro il blocco catch, cioè è fallito il dynamic_cast(r), quindi
TD(r) !<= E& (Il tipo dinamico del riferimento r non è sottotipo di E) 
e
punt != null TD(p) <= B* (Il tipo dinamico del puntatore è sottotipo di B)


/*Lettera M
Siamo all'interno del blocco catch ma punt è uguale a null
Dunque 
TD(r) !<= E&
TD(p) !<= B* (Il tipo dinamico del puntatore non è sottotipo di B)

Si ottiene M invocando F(&a,c) o 

/* Lettera R 
TD(r) <= E&
TD(p) <= B*

Si ottiene R invocando F(&b,e) o F(&c,e) o F(&d,e) o F(&e,e)

/* Lettera A 
TD(r) <= E&
TD(p) !<= B*

/**/

#include<iostream>
#include<typeinfo>
class A {
	public:
	virtual ~A(){}
};

class B: public A {};
class C: virtual public B {};
class D: virtual public B {};
class E: public C, public D {};

char F(A* p, C&r){
	B* punt = dynamic_cast<B*>(p);
	try{
		E& s= dynamic_cast<E&>(r);
	}
	catch(std::bad_cast){
		if(punt) return 'O';
		else return 'M';
	}
	if(punt) return 'R';
	return 'A';
};


using std::cout;
using std::cin;

int main(){
	A a; B b; C c; D d; E e;
	//cout << F(?,?) << F(?,?) << F(?,?) << F(?,?);
	cout << F(&b,e) << F(&b,c) << F(&a,c) << F(&a,e);
	
	//queste tre righe servono solo per tenere aperto il terminale in windows
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();
}