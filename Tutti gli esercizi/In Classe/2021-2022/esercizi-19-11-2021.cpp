class A {
private:
  void h() {cout<<" A::h ";}
public:
  virtual void g() {cout <<" A::g ";}
  virtual void f() {cout <<" A::f "; g(); h();} 
  void m() {cout <<" A::m "; g(); h();}
  virtual void k() {cout <<" A::k "; g(); h(); m(); } 
  A* n() {cout <<" A::n "; return this;}
};

class B: public A {
private:
  void h() {cout <<" B::h ";}
public:
  virtual void g() {cout <<" B::g ";}
  void m() {cout <<" B::m "; g(); h();}
  void k() {cout <<" B::k "; g(); h(); m();}
  B* n() {cout <<" B::n "; return this;}
};

B* b = new B(); A* a = new B();

int main() {
  b->f(); // A::f B::g A::h
  b->m(); // B::m B::g B::h
  b->k(); // B::k B::g B::h B::m B::g B::h
  a->f(); // A::f B::g A::h
  a->m(); // A::m B::g A::h
  a->k(); // B::k B::g B::h B::m B::g B::h
  (b->n())->g(); // B::n B::g
  ((b->n())->n())->g(); // B::n B::n B::g
  (a->n())->g(); // A::n B::g
  (a->n())->m(); // A::n  A::m B::g A::h 
}
