/*
 NON VI E' CONSEGNA NEL PDF DELL'APPELLO. PERSONALMENTE INTERPRETATA ANCHE SE E' FORSE TROPPO SEMPLICE
 */

#include <iostream>
using namespace std;

class A{ public: virtual ~A(){} };

class B: virtual public A{};

class C: virtual public A{};

class D: public B{};

class E: public D, public C{};


template <class T>
void Fun(T* pt){
	bool b=0;
	try{ throw T(*pt); }
	catch(E){ cout<<"E"; b=1;} 
	catch(B){ cout<<"B"; b=1;}
	catch(D){ cout<<"D"; b=1;}
	catch(C){ cout<<"C"; b=1;}
	catch(A){ cout<<"A"; b=1;}
    if(!b)	cout<<"NO";
}

int main(){
	A a; B b; C c; D d; E e;
	A* pa1=&b, *pa2=&c, *pa3=&d, *pa4=&e;
	B* pb1=dynamic_cast<B*>(pa1);	
	B* pb2=dynamic_cast<B*>(pa2);
	B* pb3=dynamic_cast<D*>(pa3);
	B* pb4=dynamic_cast<D*>(pa4);
	
	Fun(pa1); cout << endl;			//	A
	
	Fun(pa2); cout << endl;			//	A
	
	Fun(pa3); cout << endl;			//	A
	
	Fun(pa4); cout << endl;			//	A
	
	Fun(pb1); cout << endl;			//	B
	
	//Fun(pb2); cout << endl;		//	Errore Run Time
	
	Fun(pb3); cout << endl;			//	B
	
	Fun(pb4); cout << endl;			//	B
}


