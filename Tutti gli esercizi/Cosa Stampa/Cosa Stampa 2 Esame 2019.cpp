#include <iostream>
#include<vector>
using namespace std;



class B {

public:
  int x;
  B(int z=1):x(z){}
  virtual void f() const {cout << x <<"B::f  ";}
  virtual bool operator<=(const B& r) const {return true;}

};

class C :virtual  public B {

public:
    virtual void f() const {cout <<"C::f  ";}
     virtual bool operator<=(const B& r) const {return dynamic_cast<const C*>(&r) != 0 ? true : false;}
};

class D:virtual public B{

public:
    virtual void g() const {cout <<"D::g  ";}
    virtual void h() const {cout <<"D::h  "; g();}
    virtual bool operator<=(const B& r) const {return dynamic_cast<const D*>(&r) != 0 ? true : false;}
};

class E:public D{

public:
    virtual void f() const {cout <<"E::f  ";}
    virtual void h() const {cout <<"E::h  ";}
    virtual bool operator<=(const B& r) const {return dynamic_cast<const E*>(&r) != 0 ? true : false;}
};

class F:public C,public E{

public:
    F():B(2){}
    virtual void f() const {cout <<x<<"F::f  ";}
    virtual void g() const {cout <<"F::g  "; D::g();}
    virtual bool operator<=(const B& r) const {return dynamic_cast<const F*>(&r) != 0 ? true : false;}
};

void fun(const vector<B*>& v){
    D* p;
    for(int k=0;k!=v.size();++k){
        v[k]->f();
        if(k+1< v.size() && *v[k] <=*v[k+1]) 
            v[k+1]->f();
        p=dynamic_cast<E*>(v[k]);
        if(p){
            static_cast<E*>(p)->g();
            p->h();
        }
        cout<<"   **" << k << endl;

    }

}

int main() {
  B b;
  C c;
  D d;
  E e;
  F f;
  vector<B*> v;
  v.push_back(&d);
  v.push_back(&f);
  v.push_back(static_cast<D*>(&e)); 
  v.push_back(&d);
  v.push_back(&c);
  v.push_back(&d);
  v.push_back(&d);
  v.push_back(&b);
  v.push_back(&b);
  v.push_back(&c);
  v.push_back(&b);
  v.push_back(&f);
  v.push_back(static_cast<E*>(&f));
  v.push_back(&e);
  v.push_back(&c);

  fun(v);
}

/*
STAMPA

1B::f  2F::f                        **0
2F::f  F::g  D::g  E::h             **1
E::f  D::g  E::h                    **2
1B::f                               **3
C::f                                **4
1B::f  1B::f                        **5
1B::f                               **6
1B::f  1B::f                        **7
1B::f  C::f                         **8
C::f                                **9
1B::f  2F::f                        **10
2F::f  2F::f  F::g  D::g  E::h      **11
2F::f  F::g  D::g  E::h             **12
E::f  D::g  E::h                    **13
C::f                                **14



*/
