#include <iostream>

class A{
    public:
    virtual ~A();
};
class B{
    public:
    virtual void metodo() const=0;
};
class C: virtual public B{
    public:
    virtual void metodo() const{}
};

class D: virtual public B, public C{};

int main(){

}