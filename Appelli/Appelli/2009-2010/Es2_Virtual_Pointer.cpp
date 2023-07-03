/*
Scrivere un programma esempio che dimostri con opportune stampe su "cout" la presenza del virtual pointer in una classe polimorfa.
*/

#include <iostream>
using namespace std;

class Forma {
public:
  virtual void disegna() {
    cout << "Disegno una forma generica." << endl;
  }
};

class Cerchio : public Forma {
public:
  void disegna() {
    cout << "Disegno un cerchio." << endl;
  }
};

int main() {
  Forma* f;
  Cerchio c;

  f = &c;

  // Stampa l'indirizzo della funzione disegna()
  cout << "Indirizzo di disegna() della classe Forma: " << &Forma::disegna << endl;
  cout << "Indirizzo di disegna() della classe Cerchio: " << &Cerchio::disegna << endl;
  cout << "Indirizzo di disegna() del puntatore virtuale nella classe Forma: " << *(void**)(&f) << endl;

  // Chiama la funzione disegna() tramite il puntatore virtuale
  f->disegna();

  return 0;
}

/*
In questo programma, abbiamo definito una classe Forma che contiene una funzione virtuale disegna(). La classe Cerchio eredita da Forma e ridefinisce la funzione disegna().

Nella funzione main(), abbiamo dichiarato un puntatore f di tipo Forma* e una variabile c di tipo Cerchio. Abbiamo assegnato il puntatore f all'indirizzo della variabile c, che è un oggetto di tipo Cerchio, ma il puntatore è di tipo Forma*.

In seguito, abbiamo stampato gli indirizzi delle funzioni disegna() nella classe Forma e Cerchio, e anche l'indirizzo del puntatore virtuale nella classe Forma.

Infine, abbiamo chiamato la funzione disegna() tramite il puntatore virtuale f, che ha eseguito la versione ridefinita della funzione disegna() nella classe Cerchio.

L'output del programma dovrebbe essere:

Indirizzo di disegna() della classe Forma: 0x4005b0
Indirizzo di disegna() della classe Cerchio: 0x4005c0
Indirizzo di disegna() del puntatore virtuale nella classe Forma: 0x4005c0
Disegno un cerchio.

Output reale:
Indirizzo di disegna() della classe Forma: 1
Indirizzo di disegna() della classe Cerchio: 1
Indirizzo di disegna() del puntatore virtuale nella classe Forma: 0x165ddffa00
Disegno un cerchio.

*/

/*
Altro esempio semplice:

#include <iostream>

using namespace std;

class A{
public:
    virtual void f() = 0;
};

class B: public A{
public:
    void f(){
        cout << "B::f()" << endl;
    }
};

class C: public A{
public:
    void f(){
        cout << "C::f()" << endl;
    }
};

int main(){
    A* p = new B();
    p->f();
    p = new C();
    p->f();
}

Il programma ritorna il seguente output:
B::f()
C::f()
*/