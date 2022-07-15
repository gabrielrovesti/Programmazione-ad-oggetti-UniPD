#include <iostream>

using namespace std;

template <class X, class Y>

X* Fun(X*p){return dynamic_cast<Y*>(p);}

main(){
	C c; fun<A,B>(&c);
	if(fun<A,B>(new C()==0)) cout<<"Alan";
	if(dynamic_cast<C*>(new B())==0) cout<<"Turing";
	A*p=fun<D,B>(new D());
}

