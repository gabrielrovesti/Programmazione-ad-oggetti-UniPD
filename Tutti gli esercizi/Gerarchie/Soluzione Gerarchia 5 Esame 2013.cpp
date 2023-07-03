#include <iostream>
using namespace std;


class A{}; //classe base polimorfa

class B : public A {
    virtual void metodo() const = 0; //funzione virtuale pura -> classe B astratta
};

class C : virtual public B {
    void metodo() const{} //ridefinizione di metodo -> classe C concreta
};

class D : virtual public B, public C {};

int main(){
    /*
    A a;
    B b; //cannot declare variable 'b' to be of abstract type 'B'
    C c;
    D d;
    */
}

