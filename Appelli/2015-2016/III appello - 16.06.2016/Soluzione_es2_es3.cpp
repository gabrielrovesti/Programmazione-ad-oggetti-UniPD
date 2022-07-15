#include <iostream>

//3 Appello 2016

//Esercizio 2
class A{
    public:
    virtual void method()=0;
    virtual ~A();
};

class B: public A{};

class C: public B{
    public:
    virtual void method(){
        std::cout<<"Hello";
    }
};

class D{
    private:
    int num;
    protected:
    D(int n): num(n) {}
};

class E: virtual public D{
    private:
    int number;
    public:
    E& operator=(const E& e){
        if(this != &e){
            number=e.number;
        }
        return *this;
    }
};

//Esercizio 3
/*
A<=B    Falso
A<=C    Falso
A<=D    Falso
B<=A    Vero
B<=C    Vero
B<=D    Vero
C<=A    Vero
C<=B    Falso
C<=D    Possibile
D<=A    Vero
D<=B    Falso
D<=C    Possibile
*/