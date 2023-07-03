//Esercizio 3
#include <iostream>
using namespace std;

class A {
protected:
virtual void h() {cout<<" A::h ";}
public:
virtual void g() const {cout <<" A::g ";}
virtual void f() {cout <<" A::f "; g(); h();}
void m() {cout <<" A::m "; g(); h();}
virtual void k() {cout <<" A::k "; h(); m(); }
virtual A* n() {cout <<" A::n "; return this;}
};
class B: public A {
protected:
virtual void h() {cout <<" B::h ";}
public:
virtual void g() {cout <<" B::g ";}
void m() {cout <<" B::m "; g(); h();}
void k() {cout <<" B::k "; g(); h();}
B* n() {cout <<" B::n "; return this;}
};
class C: public B {
protected:
virtual void h() const {cout <<" C::h ";}
public:
virtual void g() {cout <<" C::g ";}
void m() {cout <<" C::m "; g(); k();}
void k() const {cout <<" C::k "; h();}
};
A* p2 = new B(); A* p3 = new C(); B* p4 = new B(); B* p5 = new C(); const A* p6 = new C();


int main(){
p2->f(); cout << endl;
p2->m(); cout << endl;
p3->k(); cout << endl;
p3->f(); cout << endl;
p4->m(); cout << endl;
p4->k(); cout << endl;
p4->g(); cout << endl;
p5->g(); cout << endl;
//p6->k(); cout << endl;
p6->g(); cout << endl;
(p3->n())->m(); cout << endl;
(p3->n())->g(); cout << endl;
(p3->n())->n()->g(); cout << endl;
(p5->n())->g(); cout << endl;
(p5->n())->m(); cout << endl;
(dynamic_cast<B*>(p2))->m(); cout << endl;
(static_cast<C*>(p3))->k(); cout << endl;
( static_cast<B*>(p3->n()) )->g(); cout << endl;

}

/*
A::f  A::g  B::h 
A::m  A::g  B::h 
B::k  C::g  B::h 
A::f  A::g  B::h 
B::m  B::g  B::h 
B::k  B::g  B::h 
B::g 
C::g 
A::g 
B::n  A::m  A::g  B::h 
B::n  A::g 
B::n  B::n  A::g 
B::n  C::g 
B::n  B::m  C::g  B::h 
B::m  B::g  B::h 
C::k  C::h 
B::n  C::g 
*/

//Esercizio 6

/*
Si considerino i seguenti fatti concernenti la libreria di I/O standard.
• Si ricorda che ios e la classe base di tutta la gerarchia di classi della libreria di I/O, che la classe ` istream e derivata direttamente e `
virtualmente da ios e che la classe ifstream e derivata direttamente da ` istream.
• La classe base ios ha il distruttore virtuale. La classe ios rende disponibile un metodo costante e non virtuale bool fail() con il
seguente comportamento: una invocazione s.fail() ritorna true se e solo se lo stream s e in uno stato di fallimento (cio ` e, il failbit `
di s vale 1).
• La classe istream rende disponibile un metodo non costante e non virtuale long tellg() con il seguente comportamento: una
invocazione s.tellg():
1. se s e in uno stato di fallimento allora ritorna -1; `
2. altrimenti, cioe se ` s non e in uno stato di fallimento, ritorna la posizione della cella corrente di input di ` s.
• La classe ifstream rende disponibile un metodo non costante e non virtuale bool is_open() con il seguente comportamento: una
invocazione s.is_open() ritorna true se e solo se il file associato allo stream s e aperto. `
Definire una funzione long Fun(const ios&) con il seguente comportamento: una invocazione Fun(s):
(1) se s e in uno stato di fallimento lancia una eccezione di tipo ` Fallimento; si chiede anche di definire tale classe Fallimento;
(2) se s non e in uno stato di fallimento allora: `
(a) se s non e un ` ifstream ritorna -2;
(b) se s e un ` ifstream ed il file associato non e aperto ritorna -1; `
(c) se s e un ` ifstream ed il file associato e aperto ritorna la posizione della cella corrente di input di ` s.
*/

long Fun(const ios& s){
    //Der* der2 = dynamic_cast<Der*>(const_cast<Base*>(base));
    ifstream* i=dynamic_cast<ifstream*>(const_cast<ios*>(&s));
    if(i->fail()) throw Fallimento("Errore");
    if(!i) return -2; //non è un ifstream
    //Variante se ifstream fosse const (const ifstream)
    //if(!dynamic_cast<const ifstream*>(&s)) return -2;
    if(!i && !i->is_open()) return -1; //non è un ifstream e il file non è aperto
    if(i && i->is_open()) return i->tellg(); //i è istream e ritorna la posizione della cella corrente
    return 0;
}

//Esercizio 7

/*
Definire un template di classe Coda<T> i cui oggetti rappresentano una struttura dati coda per elementi di uno stesso tipo T, ossia la coda
implementa l’usuale politica FIFO (First In First Out) di inserimento/estrazione degli elementi: gli elementi vengono estratti nello stesso
ordine in cui sono stati inseriti. Il template Coda<T> deve soddisfare i seguenti vincoli:
1. Coda<T> non puo usare i contenitori STL come campi dati (inclusi puntatori e riferimenti a contenitori STL). `
2. Il parametro di tipo del template Coda<T> ha come valore di default int.
3. Gestione della memoria senza condivisione.
4. Deve essere disponibile un costruttore di default che costruisce la coda vuota.
5. Deve essere disponibile un costruttore Coda(int k, const T& t) che costruisce una coda contenente k copie dell’elemento t.
6. Deve essere disponibile un metodo void insert(const T&) con il seguente comportamento: c.insert(t) inserisce l’elemento
t in coda a c in tempo costante.
5
7. Deve essere disponibile un metodo T removeNext() con il seguente comportamento: se la coda c non e vuota, ` c.removeNext()
rimuove l’elemento in testa alla coda c in tempo costante e lo ritorna; se invece c e vuota allora solleva una eccezione di tipo ` Empty,
una classe di eccezioni di cui e richiesta la definizione. `
8. Deve essere disponibile un metodo T* getNext() con il seguente comportamento: se la coda c non e vuota, ` c.getNext() ritorna
un puntatore all’elemento in testa a c in tempo costante; se invece c e vuota ritorna il puntatore nullo. `
9. Overloading dell’operatore di uguaglianza.
10. Overloading dell’operatore di somma che agisca come concatenazione: c + d e la coda che si ottiene aggiungendo ` d in coda a c.

*/

#include <iostream>

using namespace std;

class ErrorQueue{
    public:
    ErrorQueue(){cout << "Errore: ";}
};

template<class T = double>
class Coda{
    private:
    class Nodo{
        public:
        T info;
        Nodo* next;

        Nodo(const T& t=T(), Nodo*n=nullptr): info(t), next(n){}
        ~Nodo(){delete next;}
    };
    Nodo* first, *last;
    static Nodo* copy(Nodo* n){
        if(!n)  return nullptr;
        else    return new Nodo*(n->info, copy(n->next));
    }
    public:
    Coda(): first(nullptr), last(nullptr){}
    Coda(int k, const T& t){
        if(!k) first=last=nullptr;
        else{
            first=last=new Nodo(t);
            for(; k>0; k--){
                Nodo* aux=new Nodo(t, first);
                first=aux;
            }
        }
    }
    void insert(const T& t){
        Nodo* aux=new Nodo(t);
        if(first == nullptr) first=last=aux;
        else{
            if(last->next){
                last->next=aux;
                last=aux;
            }
            else{
                last=aux;
            }
        }
    }
    T removeNext(){
        if(!first) throw ErrorQueue();
        else{
            T info_ret=first->info;
            Nodo* x=first;
            first=first->next;
            x->next = nullptr;
            delete x;
            return info_ret;
        }
    }
    T* getNext() const{
        T info_ret;
        if(!first)  return nullptr;
        return &first->info;    //ritorno & in accordo con il tipo T*, occhio a quello
    }
    static bool ifminus(Nodo*p1, Nodo*p2){
        if(!p1 && !p2) return true;
        if(!p1 || !p2)  return false;
        else return p1->info < p2->info && ifminus(p1->next, p2->next);
    }
    bool operator<(const Coda& c) const{
        return ifminus(first, c.first);
    }
    Coda& operator+(const Coda& c) const{
        Coda aux=new Coda();
        aux.first=first;
        aux.last=last;
        aux.last->next=c.first;
        return aux;
    }
    class const_iter{
        private:
        const Nodo* n;
        public:
        const_iter operator++(){
            if(!n)  n=n->next;
            return *this;
        }
        const T& operator*() const{
            return (*n)->info;
        }
        const T* operator->() const{
            return n;
        }
        const T operator[](const_iter i){
            return (i.n->info);
        }
    };
};

int main(){
    Coda<double> a;
    double x = 1.2;
    a.insert(x);
    
    double* p = a.getNext();
}

//Esercizio 8

class A {
public:
virtual ˜A() {}
};
class B: public A {};
class C: public A {};
class D: public C {};
template<class T>
void Fun(T* pt){
bool b=0;
try{ throw T(*pt); }
catch(B){cout << "B "; b=1;}
catch(C){cout << "C "; b=1;}
catch(D){cout << "D "; b=1;}
catch(A){cout << "A "; b=1;}
if(!b) cout << "NO ";
}
A a; B b; C c; D d;
A *pa1 = &b, *pa2 = &c, *pa3 = &d;
B *pb1=dynamic_cast<B*>(pa1); B *pb2=dynamic_cast<B*>(pa3);

int main(){
    #include <iostream>

using namespace std;

class A {
public:
virtual ~A() {}
};
class B: public A {};
class C: public A {};
class D: public C {};
template<class T>
void Fun(T* pt){
bool b=0;
try{ throw T(*pt); }
catch(B){cout << "B "; b=1;}
catch(C){cout << "C "; b=1;}
catch(D){cout << "D "; b=1;}
catch(A){cout << "A "; b=1;}
if(!b) cout << "NO ";
}
A a; B b; C c; D d;
A *pa1 = &b, *pa2 = &c, *pa3 = &d;
B *pb1=dynamic_cast<B*>(pa1); B *pb2=dynamic_cast<B*>(pa3);

int main(){
    Fun(&a); cout << endl;//A
    Fun(&c); cout << endl; //C
    Fun(&d); cout << endl; //C
    Fun(pa1); cout << endl; //A 
    Fun(pa2); cout << endl; //A 
    Fun(pa3); cout << endl; //A 
    Fun(pb1); cout << endl; //B 
    Fun(pb2); cout << endl; //B
    Fun<A>(pb1); cout << endl; //A
    Fun<A>(pb2); cout << endl; //A
    Fun<A>(pa3); cout << endl; //A
    //Fun<B>(&d); cout << endl;
    Fun<B>(pb1); cout << endl; //B
    //Fun<C>(pa3); cout << endl;
    Fun<C>(&d); cout << endl; //C
    //Fun<D>(pa3); cout << endl;
}
}

