class A{
    public:
    virtual ~A(){}
};

class B : virtual public A {
    public:
    virtual void f() const = 0;
};

class C : public B {
    public:
    void f() const {}
};

class D : virtual public A {
    protected:
    D();
}

classE : public C, public D {
    E& operator=(const E& e){
        C::operator=(e);
        D::operator=(e);
        return *this;
    }
}