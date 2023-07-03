/*
 Si considerino le precedenti definizioni. 
 Fornire una dichiarazione (non e` richiesta la definizione) dei membri pubblici della classe Z 
 nel minor numero possibile in modo tale che la compilazione del pre- cedente main() non produca errori. 
 Attenzione: ogni dichiarazione in Z non necessaria per la corretta compilazione del main() sara` penalizzata.
 */

#include <iostream>
using namespace std;

class Z { 
public:
	int num;
	Z& operator++(){
		num = num+1;
		return *this;
	}
	
	Z operator++(int){
		num = num+1;
		return *this;
	}
	
	Z(int i=0): num(i){}
	
	bool operator==(const Z& z) const {
		return num == z.num;
	}

};


ostream& operator<<(ostream& os, const Z& z) {
	os << z.num;
	return os;
}

template <class T1, class T2=Z> class C { 
public:
	T1 x; 
	T2* p;
};

template<class T1,class T2> 
void fun(C<T1,T2>* q) {
	++(q->p); 
	if(true == false) cout << ++(q->x); 
	else cout << q->p; (q->x)++; 
	if(*(q->p) == q->x) *(q->p) = q->x; T1* ptr = &(q->x); 
	T2 t2 = q->x;
}

int main(){ 
	C<Z> c1; fun(&c1); C<int> c2; fun(&c2);
}