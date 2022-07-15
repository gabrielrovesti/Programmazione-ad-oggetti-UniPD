#include <iostream>
using namespace std;


class A{};

class B : public A { virtual ~B() = 0; };

class C : virtual public B {};

class D : virtual public B, public C {};

int main(){
}