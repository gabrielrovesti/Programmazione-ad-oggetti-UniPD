//IV appello 07072016

#include<iostream>
using namespace std;

class A{
public:
    A() { cout << 'A' ;}
};

class B: virtual public A{
public:
    B() { cout << 'B' ;}
};

class C: virtual public A{
public:
    C(): A() { cout << 'C' ;}
};

class D: virtual public B, virtual public C{
public:
    D(): C(), B() { cout << 'D' ;}
};

//1
/*class E: virtual public B{
public:
    E() { cout << 'E' ;}
};

class F: public E, virtual public C {
public:
    F() { cout << 'F' ;}
};*/

//2
/*class E: public B{
public:
    E() { cout << 'E' ;}
};

class F: virtual public E, virtual public C {
public:
    F() { cout << 'F' ;}
};*/

//3
/*class E: public D{
public: E(): B() { cout << 'E' ;}
};

class F: virtual public E {
public: F() { cout << 'F' ;}
};*/

//4
/*class E: public D {
public:
    E(): B() { cout<< 'E' ; }
};

class F: public E {
public:
    F() { cout<< 'F' ; }
};*/

//5
/*class F: public B, virtual public C { //prima c perchè virtual
public:
    F() { cout<< 'F' ; }
};*/

//6
/*class E: public B{
public:
    E(): { cout<< 'E' ;}  //non compila per i 2 punti
};

class F: public E, virtual public C{
public:
    F() { cout<< 'F' ; }
};*/

int main(){
    F f;
}
