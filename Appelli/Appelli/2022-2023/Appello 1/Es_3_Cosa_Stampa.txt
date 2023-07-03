#include <iostream>

using namespace std;

class B {
    public:
        B() {cout<<"B() ";}
        virtual ~B() {cout<<"~B() ";}
        virtual void g() const {cout <<"B::g ";}
        virtual const B* j() {cout <<"B::j "; n(); return this;}
        virtual void k() {cout <<"B::k "; j(); m();}
        void m() {cout <<"B::m "; g(); j();}
        virtual B& n() {cout <<"B::n "; return *this;}
};

class C: virtual public B {
    public:
        C() {cout<<"C() ";}
        ~C() {cout<<"~C() ";}
        void g() const {cout <<"C::g ";}
        void k() override {cout <<"C::k "; B::n();}
        virtual void m(){ cout<<"C::m ";g(); j();}
        B& n() override {cout <<"C::n "; return *this;}
};

class D: virtual public B {
    public:
        D() {cout<<"D() ";}
        ~D() {cout<<"~D() ";}
        virtual void g() {cout <<" D::g ";}
        const B* j() {cout<<"D::j "; return this;}
        void k() const {cout <<"D::k "; k();}
        void m(){ cout<<"D::m ";g(); j();}
};

class E: public C, public D {
    public:
        E() {cout<<"E() ";}
        ~E() {cout<<"~E() ";}
        virtual void g() const {cout <<"E::g ";}
        const E* j(){cout<<"E::j ";return this;}
        void m(){ cout<<"E::m ";g(); j();}
        D& n() final {cout <<"E::n "; return *this;}
};

class F: virtual public E {
    public:
        F() {cout<<"F() ";}
        ~F() {cout<<"~F() ";}
        F(const F& x): B(x) {cout<<"Fc ";}
        void k(){cout <<"F::k "; g();}
        void m(){ cout<<"F::m "; j();}
};


B* p1=new E(); B* p2=new C(); B* p3=new D();
C* p4=new E(); const B* p5=new E(); const B* p6=new F();

int main()
{
    cout << endl;
    cout << endl;
    cout <<"1:"; cout << endl; //E::n B::m E::g E::j 
    (p4->n()).m(); cout << endl;
    cout <<"2:"; cout << endl; //B::k D::j B::m B::g D::j 
    p3->k(); cout << endl;
    cout <<"3:"; cout << endl; //B::n B::m B::g D::j 
    (p3->n()).m(); cout << endl;
    cout <<"4:"; cout << endl; //B::m C::g B::j C::n 
    p2->m(); cout << endl;
    cout <<"5:"; cout << endl; //B::j C::n C::g
    (p2->j())->g(); cout << endl;
    cout <<"6:"; cout << endl; 
    C* p=new F(F()); cout << endl; //B() C() D() E() F()
    cout <<"7:"; cout << endl;
    //(p1->j())->k(); cout << endl; non compila const
    cout <<"non compila"; cout << endl;
    cout <<"8:"; cout << endl;
    //(dynamic_cast<const F*>(p1->j()))->g();cout << endl;
    cout <<"undefined"; cout << endl;
    cout <<"9:"; cout << endl;
    //(dynamic_cast<E*>(p5)->j(); 
    //error: cannot 'dynamic_cast' 'p5' (of type 'const class B*') to type 'class E*' (conversion casts away constness)
    cout <<"non compila"; cout << endl;
    cout <<"10:"; cout << endl;
    (dynamic_cast<C*>(const_cast<B*>(p6)))->k(); cout << endl; //F::k E::g
}
