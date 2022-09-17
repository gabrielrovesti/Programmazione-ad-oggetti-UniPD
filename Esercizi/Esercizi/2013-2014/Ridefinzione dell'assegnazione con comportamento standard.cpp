/*esempio visto a lezione (e non presente nel libro) sulla ridefinizione di operator= 
in una classe derivata con comportamento uguale allo standard*/
class B {
private:
  int x;
public:
  B(int k=1): x(k) {}
  B& operator=(const B& a) {x=a.x;}
  void print() const {cout << "x="<<x;}
};
class D: public B {
private:
  int z;
public:
  D(int k=2): B(k), z(k) {}
  // assegnazione con comportamento standard
  D& operator=(const D& x) {
    this->B::operator=(x); // assegnazione per sottooggetto
    z = x.z;
  }
  void print() const {B::print(); cout <<" z="<< z;}
};
 
int main() {
  D d1(4), d2(5);
  d1.print(); cout << endl; // x=4 z=4
  d2.print(); cout << endl; // x=5 z=5
  d1=d2;
  d1.print(); // x=5 z=5
}