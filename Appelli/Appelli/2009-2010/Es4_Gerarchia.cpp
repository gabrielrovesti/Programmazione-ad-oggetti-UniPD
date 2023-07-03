/*
Si scriva una gerarchia di almeno 5 classi che includa una classe D definita mediante ereditarieta` a diamente 
ed una classe B che sia una classe base virtuale per D. Scrivere inoltre un programma esempio che dimostri con 
opportune stampe su cout che i costruttori delle superclassi dirette non virtuali di D escludono di richiamare 
il costruttore della classe base virtuale B.
*/

#include <iostream>
using namespace std;

class B {
public:
  B() {
    cout << "Costruttore di B." << endl;
  }
  virtual void foo() {
    cout << "Funzione foo() di B." << endl;
  }
};

class C1 : virtual public B {
public:
  C1() {
    cout << "Costruttore di C1." << endl;
  }
  virtual void foo() {
    cout << "Funzione foo() di C1." << endl;
  }
};

class C2 : virtual public B {
public:
  C2() {
    cout << "Costruttore di C2." << endl;
  }
  virtual void foo() {
    cout << "Funzione foo() di C2." << endl;
  }
};

class D : public C1, public C2 {
public:
  D() {
    cout << "Costruttore di D." << endl;
  }
  virtual void foo() {
    cout << "Funzione foo() di D." << endl;
  }
};

int main() {
  D d;
  d.foo();

  return 0;
}

/*
Nella classe B, abbiamo dichiarato il costruttore e la funzione virtuale foo(). 
Nelle classi C1 e C2, abbiamo dichiarato il costruttore e la funzione virtuale foo() e abbiamo 
utilizzato la parola chiave virtual nella dichiarazione dell'ereditarietà da B. 
Nella classe D, abbiamo dichiarato il costruttore e la funzione virtuale foo().

Nella funzione main(), abbiamo creato un oggetto d di tipo D e abbiamo chiamato la funzione foo() su di esso.

L'output del programma è il seguente:
Copy code
Costruttore di B.
Costruttore di C1.
Costruttore di C2.
Costruttore di D.
Funzione foo() di D.

Come si può vedere dall'output, il costruttore della classe B viene 
chiamato solo una volta, dimostrando che l'utilizzo della parola chiave virtual 
nell'ereditarietà da B garantisce che il costruttore di B venga chiamato una sola volta 
nella gerarchia di ereditarietà a diamante.
*/
