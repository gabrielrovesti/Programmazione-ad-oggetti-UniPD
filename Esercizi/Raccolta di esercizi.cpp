/*
Carrellata di esercizi trattati e presentati spiegando ognuno 
il perché stampa una certa cosa e per quale ragione/con che ordine 
si costruisce/distrugge nei singoli casi.

Per ogni esercizio, presentata sopra la tipologia
e sotto il codice la stampa.
Presi non solo da libro e lezioni ma anche dalla raccolta presente su Github
raccogliendo più esercizi possibile e dai tutorati.
Tutta l'inclusione delle librerie utili è svolta qui senza ripeterla quando serve.

Enjoy!
*/

#include <iostream>
#include <vector>
#include <typeinfo>
#include <fstream>
#include <sstream>
using namespace std;

//Programma sottostante: cosa stampa?

class A {
public:
   A() { cout << "A ";}
   A(const A&) {cout << "Ac ";}
   virtual  ~A() {cout << " ~A ";}
};
class B : virtual public A {
public:
   B() { cout << "B "; }
   ~B() {cout << " ~B "; }
};
class C : virtual public A {
public:
   static A x;
   C() { cout << "C "; }
   C(const C&) {cout << "Cc ";}
   ~C() {cout << " ~C "; }
};

A C::x;

class D : public B, public C {
public:
   D() { cout << "D "; }
   D& operator=(const D& d) {cout << "D= "; return *this;}
   ~D() {cout << " ~D "; }
};
int main() {
   cout << "START" << endl;
   D *b=new D(); cout << "UNO" << endl;
   D d,e; cout << "DUE" << endl;
   e=d;cout << "TRE" << endl;
   return 0;
}

/*Stampa:
A START		
perché si crea lo statico
A B C D UNO		
partendo dalla base invoca nell'ordine tutti i costruttori della derivata
A B C D A B C D DUE
due oggetti di tipo D
D= TRE
operazione di assegnazione
~D  ~C  ~B  ~A  ~D  ~C  ~B  ~A  ~A
distruzione degli oggetti di tipo D
nell'ordine del main (quindi d=e e ne distruggo uno solo)
per poi distruggere x, statico */

//Programma sottostante: cosa stampa?

class A{
    private: 
        void h() {cout << "A::h"; }
    public:
        virtual void g(){cout << "A::g"; }
        virtual void f(){cout << "A::f"; }
        void m() {cout <<"A::m "; g(); h();}
        virtual void k() {cout << "A::k"; g(); h(); m();}
        A* n(){cout << "A::n"; return this;}
};

class B: public A{
    private:
        void h() {cout << "B::h"; }
    public:
        virtual void g() {cout << "B::g";}
        void m() {cout << "B::m"; g(); h();}
        void k() {cout << "B::k"; g(); h(); m();}
        B* n(){cout << "B::n"; return this;}
};

B*b = new B(); A* a= new B();

int main(){
   b->f();     
   b->m(); 
   b->k();
   a->f();
   a->m();
   a->k();
   (b->n())->g();
   ((b->n())->n())->g();
   (a->n())->g();
   (a->n())->m();
}

/*
Per ogni riga:

1) A::f  
2) B::m B::g B::h
3) B::k B::g B::h B::m B::m B::g B::h
4) A::f B::g A::h
5) A::m B::g A::h
6) B::k B::g B::h B::m B::g B::h
7) B::n B::g
8) B::n B::n B::g
9) A::n B::g
10) A::n A::m B::g A::h
*/

/*
Stampa: attenzione a verificare se la funzione è virtuale o meno
nel qual caso segue un overriding nella funzione derivata
Altro appunto, se la funzione della classe base viene
dichiarata come virtuale, se la funzione della cl. derivata
non ha la keyword virtual, di fatto è virtuale anch'essa
e chiaramente invoca il proprio corpo. 

Altro appunto:
-dynamic binding: chiamo la base sulla base del polimorfo, se virtual
-static binding: chiama la propria funzione, perché non altrimenti ridefinita

*/

/* 
Richiesta dell'esercizio sottostante; fornire una dichiarazione dei membri pubblici della classe
nel minor numero possibile in modo tale che compilando il main
non si abbiano errori.
Si segnala poi accanto al codice se si necessita di qualcosa o no
*/

class Z {
   public:
   Z& operator++(int);  //1
   int operator++();    //2
   bool operator==(const Z& z) const{}
};
template <class T1, class T2=Z>
class C {
   public:
   T1 x;
   T2*p;
};
   
template<class T1,class T2>
void fun(C<T1,T2>*q) {
   ++(q->p);   
   if(true == false) 
   cout << ++(q->x); //1
   else cout << q->p;
   (q->x)++;         //2
   if(*(q->p) == q->x)  *(q->p) = q->x;      //servirà 3 in quanto l''operat. di assegnazione non va ridef. essendo lo stesso tipo
   T1*ptr = &(q->x);
   T2 t2 = q->x;}
   
int main(){
   C<Z> c1; 
   fun(&c1); 
   C<int> c2; 
   fun(&c2);
}

//Programma sottostante: cosa stampa?

class A {
private:
    int x;
public:
    A(int k=0): x(k) {}
    A operator+(A a) const {A aux(x + a.x); return aux;}
    operator int() const {return x;}
    A F() {++x; return *this;}
};

class C {
public:
    static A a;
    static void G(A& x, A& y) {a = a + x.F() + y.F();}
};
A C::a(1);

int main() {
A p(2), q, r;

C::G(p,q);
cout << C::a << " ";
C::G(q,r);
cout << C::a << " ";
C::G(p,r);
cout << C::a;
}

/*
Stampa: 5 8 14

Nel primo cout, a par. statico è già ad 1 e viene addizionato a 
p, che diventa 3 e q che diventa 1, quindi 5.
Nel secondo cout, q che era per riferimento è diventato 2, 
r è 1 ed a era 5, quindi stampa 8.
Nel terzo cout, a era 8, p diventa 4 ed r usato per la seconda volta, diventa 2, quindi 14
*/

//Programma sottostante: cosa stampa?

class A {
private:
   int x;
   public:
   A(int k=0): x(k) { cout << "A(int) ";}
   ~A() { cout << "~A ";}
};
class B : public A {
public:
   static A a;
   A F(A a=A()) { return a; }
   B() : A(3) { cout << "B() ";}
   ~B() { cout << "~B ";}
};
A B::a(1);

int main() {
   A a(1); cout << "UNO" << endl;
   B b; cout << "DUE" << endl;
   b.F(); cout << "TRE" << endl;
   b.F(2); cout << "QUATTRO" << endl;
}

/*
A(int) A(int) UNO
A(int) B() DUE
A(int) ~A ~A TRE
A(int) ~A ~A QUATTRO
~B ~A ~A ~A 

Nella prima riga si considera l'oggetto a creato e lo statico
Nella seconda, l'oggetto B, prima nella base poi nella derivata e infine la stampa
Nella terza riga, creo un oggetto a con il metodo F, che mi crea un altro A, che sarà poi distrutto assieme al primo
Nella quinta riga, fa la stessa cosa, andando poi a distruggere gli elementi
nell'ordine inverso all'input, quindi B, l'oggetto A nel main, l'oggetto nella classe B
e l'oggetto statico. 
*/

//Programma sottostante: cosa stampa?

class C {
   public:
      C(int x=0,int y=1) {a[0]=x; a[1]=y; cout << "C(" << a[0] << "," << a[1] << ") ";}
      C(const C&) {cout << "Cc ";}
      int a[2];
};
class D {
   private:
      C c1;
      C *c2;
      C& cr;
   public:
      D() : c2(&c1),cr(c1) { cout << "D() ";}
      D(const D& d) : cr(c1) { cout << "Dc ";}
      ~D() { cout << "~D ";}
};

int main() {
   C c; cout << "UNO" << endl;
   C x(c); cout << x.a[0] << " " << x.a[1] << " DUE" << endl;
   D d=D(); cout << "TRE" << endl;
   return 0;
}

/*

C(0,1) UNO
Cc (..) (..) DUE
C(0,1) D() TRE
~D 

Nei due (..), per come è scritto il programma, non essendo ben definiti
gli indirizzi, stamperà ogni volta due numeri casuali. 
Per il resto le stampe sono queste.

Nella prima riga, chiama il costruttore ridefinito di C, stampando UNO
Nella seconda riga, chiama il costruttore di copia, in quanto si ha un const C& e 
i due numeri casuali.
Nella terza riga, si va nel costruttore di default di D, poi si invoca il costrutt.
ridefinito di C e poi si stampa TRE
Per il resto, l'unico distruttore presente è D, e si stampa solo lui.

Se avessi avuto anche la stampa del distruttore di C,
stampava tre volte C~, poiché distruggeva il C presente nel main, in cui C x=C c, quindi 
si distrugge uno stesso indirizzo e poi i due C che esistono in D, quindi C e C*

*/

//Programma sottostante: cosa stampa?

class D;

class B {
public:
    virtual D* f() =0;
};

class C {
public:
    virtual C* g();
    virtual B* h() =0;
};

class D: public B, public C {
public:
    D* f() {cout << "D::f "; return new D;}
    D* h() {cout << "D::h "; return dynamic_cast<D*>(g());}
};

C* C::g() {
    cout << "C::g ";
    B* p = dynamic_cast<B*>(this);
    if(p) return p->f(); else return this;
}

class E: public D {
    public:
    E* f() {
    cout << "E::f ";
    E* p = dynamic_cast<E*>(g());
    if(p) return p; else return this;
    }
};

class F: public E {
public:
    E* g() {cout << "F::g "; return new F;}
    E* h() {
    cout << "F::h ";
    E* p = dynamic_cast<E*>(E::g());
    if(p) return p; else return new F;
    }
};

int main()
{
    B* p; C* q; D* r;
    p = new E; p->h(); //(2)
    p = new E; p->f(); //(3)
    p = new D; (dynamic_cast<D*>(p))->h(); //(4)
    q = new D; q->g(); //(5)
    q = new E; q->h(); //(6)
    q = new F; q->g(); //(7)
    r = new E; r->f(); //(8)
    r = new F; r->f(); //(9)
    r = new F; r->g(); //(10)
    r = new F; r->h(); //(11)
}

/*
2) Non compila--> error: ‘class B’ has no member named ‘h’
Infatti nell'invocazione, prima va il tipo B* viene convertito in E, il 
quale a sua volta discende da D. D discende da B e da C e il metodo "h" è 
ridefinito da C ma non da B, motivo per cui solleva questo errore

3) Non compila--> error: ‘class B’ has no member named ‘h’
Nell'invocazione, viene chiamato nel tipo convertito dinamicamente E
il metodo F, che invocherebbe la funzione "f" avendola.
La stampa fallisce per il mancato overriding del metodo H.

4) D::h C::g D::f
Stampa in questo modo poiché B* viene convertito dinamicamente
in E, poi si fa il dynamic cast della superclasse nella sottoclasse
quindi chiamando il metodo D->h.
A quel punto si ha un altro dynamic cast all'interno di C per il metodo G
che provoca la seconda stampa.
Si stampa poi l'ultimo metodo presente in D, quindi f. 

5) C::g D::f
Come prima, il metodo in questione deriva da B e da C. 
Il metodo f viene correttamente overridato da D, che stamperà poi f
Prima, però, sto chiamando il metodo g della classe D, che si riferisce
al metodo G della classe C, che darà luogo alla prima stampa.
Nella stessa si segnala un dynamic cast della superclasse (C)
nella sottoclasse (D), che dà luogo alla seconda stampa. 

6) Errore a runtime: Stampa senza sosta C::g E::f
Il tipo attuale è E che esegue il corpo della propria classe (quindi
stampando "f" una volta eseguita la classe base C), poi invoca C facendo
il dynamic cast del metodo g, che continua a non risolversi perché
continua a fare un dynamic cast della superclasse, quindi da C ad E.
Questo genera un loop infinito che porta alla stampa infinita di C ed E.

7) F::g
La classe base E non ha il metodo "g" e quindi chiama il metodo proprio. 

8) Errore runtime: Loop infinito di stampa di C::g E::f
Uguale a 6, stesso ragionamento. 

9) E::f F::g
L'oggetto in questione è di tipo E, quindi andrà prima di tutto a 
stamparsi il metodo "f" di E, per poi, grazie al dynamic cast
andare a stampare il metodo "g", in quanto non posseduto da E
e overridato (ridefinito) all'interno della sottoclasse.

10) F::g
Uguale a 7, stesso ragionamento. 

11)F::h C::g E::f F::g
Lui cerca il metodo H, che andrà a stampare in F
Poi deve fare il dynamic cast del metodo G, quindi andrà 
prima nella classe C da cui eredita, ne stampa il metodo "g".
Come detto eravamo in E e ne stampiamo il metodo "f".
Infine stampiamo il metodo "g" rimanente dell'altra classe ed invocazione. 
*/

class C
{
   private:
      int i;
   protected:
      int p;
   public:
      C() {cout<<"C0 ";}
      C(int x) {cout<<"C1 ";}
};

class D : private C
{
   protected:
      int j;
   public:
      D() : C(2) {cout<<"D0 ";}
      D(double x) {cout<<"D1 ";}
};

class E : public C
{
   private:
      D d;
   public:
      int k;
      E() : C(6) {cout<<"E0 ";}
};

class F : public D
{
   protected:
      E e;
   public:
      F() : D(3.2) {cout<<"F0 ";}
      F(float x) {cout<<"F1 ";}
};

class G : public E
{
   private:
      F f;
      C c;
   public:
      G() : E() {cout<<"G0 ";}
      G(char x) {cout<<"G1 ";}	
};

int main() {G g;}

/*
Stampa:
C1 C1 D0 E0 C0 D1 C1 C1 D0 E0 F0 C0 G0 

Seguendo l'ordine di tutte le chiamate:
Partiamo da G, che invoca il proprio costruttore di default (G0), ma ha due campi F e C (F0 e C0).
Deriva da E che il campo privato E (E0) e il costrutt. di default (F0).
F deriva da D che ha un campo privato D (D0) e il costruttore di default (E0).
Andiamo quindi in d a usare il costruttore per i due interi privati (due volte C1).
A questo punto esegue tutto quello che non ha già eseguito, cioè il costruttore
non usato in D (D1) e in C (C0).
Ritorna in E eseguendo il costruttore (E0) e in D (D0), che creano due oggetti di tipo C, quindi due volte (C1). 
*/

//Programma sottostante: cosa stampa?

class B {
public:
    int x;
    B(int z=1): x(z) {}
};

class D: public B {
public:
    int y;
    D(int z=5): B(z-2), y(z) {}
};

void fun(B* a, int size) {
for(int i=0; i<size; ++i) cout << (*(a+i)).x << " ";
}

int main()
{

    fun(new D[4],4); cout << "**1\n"; //(1)
    B* b = new D[4]; fun(b,4); cout << "**2\n"; //(2)
    b[0] = D(6); b[1] = D(9); fun(b,4); cout << "**3\n"; //(3)
    b = new B[4]; b[0] = D(6); b[1] = D(9); //(4)
    fun(b,4); cout << "**4\n";
}

/*
Stampa:
1) 3 5 3 5 **1

2) 3 5 3 5 **2

3) 4 7 3 5 **3

4) 4 7 1 1 **4

*/

//Programma sottostante: cosa stampa?

class B {
    public:
    int b;
    explicit B(int x=1): b(x) {}
    virtual B*m(B& x) {return new B(b + x.b);}
    virtual void print() {cout << b << " ";}
};

class C: public B {
    public:
    int c;
    explicit C(int x=2): B(x), c(x) {}
    void print() {B::print(); cout << c << " ";}
    void f() {B*x = m(*this); x->print();}
};

class D: public C {
    public:
    int d;
    explicit D(int x=3): C(x), d(x) {}
    B*m(B& x) {
        C*p = dynamic_cast<C*>(&x);
        D*q = dynamic_cast<D*>(&x);
        if(!p) return new C(d + x.b);
        if(q) return new D(d + q->d);
        return new B(x.b);
    }
    void print() {
        C::print(); 
        cout << d << " ";}
};
int main(){
    B b(1); C c; D d;
    B*p1 = new D(3); 
    B*x; B*p2 = p1->m(*p1); 
    p2->print(); cout << "**1\n";
    x = p1->m(c); x->print(); cout << "**2\n";
    x = p1->m(b); x->print(); cout << "**3\n";
    x = p2->m(*p1); x->print(); cout << "**4\n";
    x = x->m(b); x->print(); cout << "**5\n";
    C*p3 = new C(4); p3->f(); cout << "**6\n";
    p3 = &d; p3->f(); cout << "**7\n";
    (dynamic_cast<C*>(p3->m(d)))->f(); cout << "**8";
}

/*
6 6 6 **1
2 **2
4 4 **3
9 9 9 **4
10 10 **5
8 **6
6 6 6 **7
12 12 12 **8
*/

//Programma sottostante: cosa stampa?

class Z{
   public:
      Z() {cout << " Z() ";}
      Z(const Z& x) {cout << " Zc ";}
};

class A{
   private:
      Z w;
   public:
      A() {cout << " A() ";}
      A(const A& x) {cout <<" Ac ";}
};

class B: virtual public A{
   private:
      Z z;
   public:
      B() {cout << " B() ";}
      B(const B& x) {cout <<" Bc ";}
};

class C: virtual public A{
   private:
      Z z;
   public:
      C() {cout << " C() ";}
};

class D: public B, public C{
   public:
      D() {cout << " D() ";}
      D(const D& x): C(x) {cout << " Dc ";}
};

int main(){
   B b1; C c1; cout << "**0\n";
   B b2 = b1; cout << "**1\n";
   C c2 = c1; cout << "**2\n";
   D d1; cout << "**3\n";
   D d2=d1; cout << "**4";
}

/*
Stampa:
1) Z()  A()  Z()  B()  Z()  A()  Z()  C() **0
Qui si segue semplicemente l'ordine di invocazioni perché
creo un B, che deriva da A ed entrambi contengono uno Z e viene fatto nell'ordine
dei costruttori; stessa cosa per C.

2) Z()  A()  Z()  Bc **1
Anche qui ho un solo oggetto B che deriva da A ed eseguo la
costruziuone di Z, poi A, ancora uno Z in B, poi Bc perché riferimento costante 
e infine cout.

3) Z()  Ac  Zc **2
Ho la classe C, che deriva da A ed ha un oggetto in questo momento 
di tipo C; questa non possiede un costruttore di copia, quindi andrà a prenderlo
in A, che a sua volta contiene un campo privato di tipo Z.
Stiamo ancora lavorando sull'oggetto, quindi usiamo il costruttore di copia in Z
e il costruttore di copia di tipo A, oltre al costruttore di default di Z.

4) Z()  A()  Z()  B()  Z()  C()  D() **3
Qui segue il principio di ereditarietà multipla, quindi prima costruisce
per mezzo di B, facendo a catena tutta la trafila dei costruttori già descritta
per B e poi per C

5) Z()  A()  Z()  B()  Zc  Dc **4
Segue sempre il principio di ereditarietà multipla andando in A e poi B.
Per stampare Zc e poi Dc, siamo nella classe D con un tipo C&, che viene cercato in C
e non ha costruttore di riferimento, poi per ereditarietà si sale in A.
In A vi è costruttore ma per priorità di inizializzazione dei campi si va in Z,
ne si invoca il costruttore dopodiché si torna in D, stampando il corpo del costruttore.
*/

//Supponendo che il frammento sottostante esegua e compili
//Disegnare i diagrammi di tutte le possibili gerarchie
//tali che l'esecuzione del main() provochi la stampa: 0 3 4 6 8

int main(){
   A a; B b; C c; D d;
   cout << (dynamic_cast<D*>(&c) ? "0 " : "1 ");   //C <= D
   cout << (dynamic_cast<E*>(&c) ? "2 " : "3 ");   //C non è B
   cout << (!(dynamic_cast<C*>(&b) ? "4 " : "5 ");   //B non è C
   cout << (dynamic_cast<B*>(&a) || dynamic_cast<C*>(&a) ? "6 " : "7 ");   //A <= B oppure A <= C
   cout << (dynamic_cast<D*>(&b) ? "8 " : "9 ");      //B è un D
}

/*

Quelli giusti sono:

               D
             /   \
             B   C
             \   /
               A         oppure

               D
             /   \
             B   C
                 |
                 A      oppure 

               D
             /   \
             B    C
             |
             A

Potrebbe anche essere che la freccia vada da A verso D e comunque sarebbe corretto

*/

/*
Sia B una classe polimorfa e C una sottoclasse <B*>. Definire una funzione int FUn(const vector<B*>& v)
con il seguente comportamento: sia v non vuoto e sia T* il tipo dinamico di v[0]; 
allora Fun(v) ritorna il numero di elementi di v che hanno un tipo dinamico T1* tale che T1 è 
un sottotipo di C diverso da T; se v è vuoto deve quindi ritornatr 0. Ad esempio, il seguente programma deve compilare
e provocare le stampe indicate. 
*/

int Fun(const std::vector<B*>& v){
   int num=0;
   for(auto it=v.begin(); it!=v.end(); ++it){
      if(dynamic_cast<C*>(*it) && typeid(**it) != typeid(*v[0])) num++;
   return num;
   }
}

//Programma sottostante: cosa stampa?

class B{
public:
   ~B() {cout << "~B()";}
};

class D: public B{
public:
   ~D() {cout << "~D()";}
};

class B2{
public:
   virtual ~B2() {cout << "~B2()";}
};

class D2: public B2{
public:
   ~D2() {cout << "~D2()";}
};

int main(){
   B* b = new D;
   B2* b2 = new D2;
   delete b; cout << endl;
   delete b2; cout << endl;
}

/*
Basta seguire l'ordine di invocazione, sapendo 
che i distruttori vanno in ordine inverso 

~B()
~D2()~B2()
*/

//Programma sottostante: cosa stampa?

class A{
   private:
      int z;
   public:
      ~A(){cout << "~A";}
};

class B{
   public:
      A* p; 
      A a;
      ~B(){cout << "~B";}
};

class C{
   public:
      static B s;
      int k;
      A a;
      ~C(){cout << "~C";}
};

B C::s = B();

int main(){
   C c1, c2;
}

/*
(senza flag)
~C ~A ~C ~A ~B ~A
(con il flag no elide constructors)
Stampa: ~B ~A ~C ~A ~C ~A ~B ~A

I primi B ed A sono temporanei anonimi creati all'inizio,
per A e B, poi  creo un C, che contiene un campo A.
Stessa roba per l'altro campo C, che si crea un puntatore ad A
e infine la variabile di tipo B, che viene distrutta assieme
all'oggetto di tipo A.
*/

//Programma sottostante: cosa stampa?

class N {
   friend class Lista;
   private:
      int info;
      N*prev; N*next;
   public:
      N(int y, N*p = 0, N*q = 0): info(y), prev(p), next(q) {}
      ~N() {if(next) delete next; cout << info << " ~N ";}
};

class Lista {
   private:
      N*last;
   public:
   Lista() : last(0) {}
    ~Lista() {
      if(last) {
         while(last->prev) last = last->prev;
         delete last;}
   }
   void add(int x) {
   N*p = new N(x,0,0);
   if(last) {last->next = p; p->prev = last;}
   last = p;
   }
   void operator--() { if(last) last = last->prev; }
   void operator--(int) {
      if(last){ N*p = last;
      last = last->prev;
      last->next = 0;
      delete p;   }
      }
   void print() {
      if(last) {
         N*p = last;
         while(p->prev) 
         p = p->prev;
         while(p){ 
            cout << p->info << " "; 
            p = p->next; 
            }
         }
      }
};

int main() {
   Lista*p = new Lista; Lista*q = new Lista;
   p->add(3); p->add(4); p->add(5); p->add(6);
   q->add(7);
   *q=*p;
   --(*q);
   p->print(); cout << "**1\n";
   q->print(); cout << "**2\n";p->add(8);
   p->print(); cout << "**3\n";
   (*q)--; cout << "**4\n";
   q->print(); cout << "**5\n";
   --(*q); delete q; cout << "**6\n";  }

/*
3 4 5 6 **1
3 4 5 6 **2
3 4 5 6 8 **3
8 ~N 6 ~N 5 ~N **4
3 4 **5
4 ~N 3 ~N **6

Nelle prime due righe, aggiungiamo alla fine di Lista p, quindi 3 4 5 6
e in q mettiamo solo 7. Poi l'oggetto puntato da q assume i valori di
quelli puntati da p, quindi 3 4 5 6, ma ha anche 7 alla fine.
Con la quinta riga si riporta all'indice precedente perché
essendo operatore prefisso, prima sottrae poi si porta alla posizione giusta.

Le due stampe provocano quindi la stampa delle due singole liste nel modo descritto.
Aggiungendo 8 cambia poco e la lista rimane uguale.
Con l'istruzione dopo, chiamo apposito overloading dell'operatore --,
in questo caso quello senza parametri e punto sempre all'elemento
precedente rispetto a quello cancellato, finché c'è un last.
Questo provoca la stampa della riga 10 del main che distrugge i 3 elementi
con le caratteristiche dette.

Proseguo stampando solo quello che rimane, quindi 3 e 4 e poi cancello
tutta la lista rimanente con l'overloading dell'operatore --, 
che prende un intero come parametro e dealloco gli ultimi due. 

*/


/*
Si considerino le classi N e Lista definite nell’esercizio sopra. Si supponga che il distruttore della classe
Lista venga ridefinito nel seguente modo: ̃Lista(){delete last;}. Si chiede di ridefinire il
distruttore della classeNin modo tale che la distruzione di un oggetto di tipo Lista comporti la distruzione
profonda della lista.
*/

~N(){
   while(next !=0){
      nodo*x=prev;
      prev->next=next;
      delete x;
   }
}

/*
Si considerino le classi N e Lista definite nell’Esercizio sopra. Si chiede di
•definire una classe Iteratore che permette di iterare sugli elementi di una lista. La classe deve
contenere un solo metodo pubblico che ridefinisce l’operatore di incremento prefisso
•ridefinire per la classe Lista l’operatore di subscripting.
*/

class Iteratore{  
      friend class Lista;
      private:
      Lista::nodo* punt;
      public:
      Iteratore& operator++(){
            if(punt)
            punt=punt->next;
            return *this;
      }
};

//per Lista

int& Lista::operator[](Lista l){
      return l.info;
}
/*
Considerando le definizioni della classe Iteratore e dell’operatore di subscripting appena scritte, indicare 
quali delle seguenti dichiarazioni friend sono necessarie (l’indicazione di dichiarazioni non necessarie sarà penalizzata).
1. nella classe N si deve dichiarare friend class Iteratore       NO
2. nella classe Lista si deve dichiarare friend class Iteratore   NO
3. nella classe Iteratore si deve dichiarare friend class N       NO
4. nella classe Iteratore si deve dichiarare friend class Lista   SI
5. nella classe Lista si deve dichiarare friend class N           NO
*/

class S{
public:
   int s;
   S(int x): s(x) {}
};

class N{
private:
   S x;
public:
   N* next;
   N(S t, N* p): x(t), next(p) {cout << "N2 ";}
   ~N() {if(next) delete next; cout << x.s << " ~N ";}
};

class C{
N* pointer;
public:
   C(): pointer(0) {}
   ~C() {delete pointer; cout << "~C ";}
   void F(int a, int b=9){
      pointer = new N(S(a), pointer); pointer = new N(b, pointer);
   }
};

int main(){
   C* p = new C; cout << "UNO\n";
   p->F(3,5); p->F(7); cout <<"DUE\n";
   delete p; cout <<"TRE\n";
}

/*
Riga con UNO: Normale creazione dell'oggetto nello heap puntato. 
Stampa: UNO

Riga con DUE: Stampa 4 volte di N2, perché come si vede dalla riga
Stampa: N2 N2 N2 N2 DUE
si crea 4 spazi, i primi due con 3 e 5 chiamando la funzione F
e i secondi due con 7 ed un oggetto vuoto. 

Ultima riga: 
3 ~N 5 ~N 7 ~N 9 ~N ~C TRE

Distruzione di tutti gli oggetti della lista e dell'oggetto di tipo C
nell'ordine inverso. 
*/

/*
Il seguente programma compila. Cosa stampa in output? Si ricordi che dati due iteratori
first e lastsu un vector v la funzione find(first,last,value) ritorna il primo iteratore it 7
nell’intervallo [first,last) tale che *it==value, mentre se tale iteratore non esiste ritorna last
*/

class B{
public:
   int k;
   B(int x=1): k(x) {}
   virtual ~B() {}
};

class C: public B{
public:
   C(): B(2) {}
}

class D{
public:
   B* punt;

   D(B* p): punt(p) {
      if(typeid(*p) == typeid(B)) punt = new B(p->k);
   }
   D(const D& d): punt(d.punt){
      if(typeid(*(d.punt))==typeid(B)) punt = new B((d.punt)->k);
   }
   D& operator=(const D& d){
      if(this != &d){
         if((typeid(*(d.punt))==typeid(B))) punt = new B((d.punt)->k);
         else punt = d.punt;
      }
      return *this;
   }
};

int main(){
   B b1(4), b2; C c1;
   D d1(&c1), d2(&b1), d3(&b2), d4(d1), d5(d2); d5=d1;
   vector<D> v; vector<B*> w;
   v.push_back(d1); v.push_back(d2); v.push_back(d3);
   v.push_back(d3); v.push_back(d4); v.push_back(d5);
   for(int i=0; i < v.size(); i++)
      if(find(w.begin(),w.end(),v[i].punt)==w.end()) w.push_back(v[i].punt);
   for(int i=0; i< w.size(); i++)
      cout << w[i]->k << ' ';
}

//Cosa stampa il programma sotto?
class A{
   friend class C;
   private:
      int k;
   public:
      A(int x=2): k(x) {}
      void m(int x=3) {k=x;}
};

class C{
   private:
      A* p;
      int n;
   public:
      C(int k=3) {if (k>0) {p = new A[k]; n=k;}}
      A* operator->() const{return p;}
      A& operator*() const{return *p;}
      A* operator+(int i) const{return p+i;}
      void F(int k, int x){if (k<n) p[k].m(x);}
      void stampa() const{for(int i=0; i<n; i++) {cout << p[i].k << ' ';}}
};

int main(){
   C c1; c1.F(2,9);
   C c2(4); c2.F(0,8);
   *c1=*c2;
   (c2+3*c1)->m(7);
   c1.stampa(); cout << "UNO\n";
   c2.stampa(); cout << "DUE\n";
   c1=c2;
   *(c2+1)=A(3);
   c1->m(1);
   *(c2+2)=*c1;
   c1.stampa(); cout << "TRE\n";
}

/*
Stampe:

8 2 9 UNO
8 2 2 7 DUE
1 3 1 7 TRE

Viene creato c1, di default, quindi conterrà 3 elementi la stampa.
Poi ci sta la chiamata alla funzione F, con i valori 2 e 9.
Siccome 2<9 viene chiamata F, che mette nel secondo elemento di c1 il valore 9;
il valore 2 in questo momento in merito a C[1] è dato dalla creazione dell'oggetto
di tipo A*.
Poi viene creato c2, con 4 elementi di stampa e grazie alla chiamata di F
e dell'operatore -> nella funzione causa due costruzioni dell'oggetto A*
quindi sono 2 volte il 2 e alla fine come prima 7, mentre all'inizio 8
per la chiamata alla funzione F.

L'assegnazione *c1=*c2 provoca l'assegnazione del primo elemento di c2 (8)
a c1, quindi le stampe generano quell'effetto.

Le successive istruzioni modificano c1, che diventa 8 2 2 7
e poi le altre modificano nell'ordine l'indice 1 (che diventa 3)
il primo, che diventa 1 e il terzo che diventa 1, da cui la stampa che ne consegue.
*/


//Si considerino le seguenti definizioni di template di classe.
//Determinare se le singole righe compliano o meno quando messe nel main (scritto sotto come al solito)
template<class T> class D;

template<class T1, class T2>
class C{
   friend class D<T1>;
   private:
      T1 t1;
      T2 t2;
};

template<class T>
class D{
   public:
      void m() {C<T, T> c; cout << c.t1 << c.t2;}
      void n() {C<int, T> c; cout << c.t1 << c.t2;}
      void o() {C<T, int> c; cout << c.t1 << c.t2;}
      void p() {C<int, int> c; cout << c.t1 << c.t2;}
      void q() {C<int, double> c; cout << c.t1 << c.t2;}
      void r() {C<char, double> c; cout << c.t1 << c.t2;}
};

//A titolo di esempio
int main(){
   D<char> d; d.m();
}

/*
1) Si
2) No (t1 is private within this context; stesso dicasi per gli altri "No")
3) Si
4) No
5) No
6) Si
*/

/* 
Si considerino le seguenti definizioni.
Nel main() incompleto, dove ? denota un'incognita, 
definire opportunamente le chiamate in tale main() usando gli
oggetti locali a, b, c, d, e in modo tale che la sua esecuzione
non provochi errori a run-time e produca in output la stampa ROMA.
*/

class A{
   public:
      virtual ~A() {} 
};
class B: public A{};
class C: virtual public B{};
class D: virtual public B{};
class E: public C, public D{};

char F(A* p, C& r){
   B* punt = dynamic_cast<B*> (p);
   try{
      E& s=dynamic_cast<E&> (r);
   }
   catch(bad_cast){
      if(punt) return 'O';
      else return 'M';
   }
   if(punt) return 'R';
   return 'A';
}

int main(){
   A a; B b; C c; D d; E e;
   cout << F(?, ?) << F(?, ?) << F(?, ?) << F(?, ?);
}

/*
Soluzione:
cout << F(&b, e) << F(&b, c) << F(0, c) << F(&a, e);

Nella prima stampa, i due cast corrispondono.
Nella seconda, basta mettergli il tipo giusto su B, 
ma mettendo il supertipo C, così quando si andrà
a fare dynamic cast solleva bad cast come eccezione.
Nella terza basta avere sempre supertipo C ma mettendo 0 oppure 
supertipo A nel primo dynamic cast, tale da sollevare bad cast e ritornare
M perché non c'è il suo oggetto puntato.
Ora quindi, nell'ultima, metterò come supertipo A, così il primo dynamic cast
non ha il suo oggetto puntato ma il secondo dynamic cast è corretto: stamperà quindi A

Ecco come funziona la stampa.
*/

//Definire per la classe bolletta, ricordando essa composta da telefonate,
//un metodo Sotituisci, che sostituisce la prima occorrenza delle telefonata t1
//con la telefonata t2; simile anche un metodo Sostituisci_Tutte

void Sostituisci(const telefonata& t1, const telefonata &t2){
   if(!t1 || !t2) return;
   if(punt.info == t1)   punt.info=t2;
   punt=punt->next;
}

void Sostituisci_Tutte(const telefonata& t1, const telefonata &t2){
   f(!t1 || !t2) return;
   if(punt.info == t1){   while(punt->next) {punt->info=t2;  punt=punt->next;}   }
   punt=punt->next;
}

//Stampa dei vari programmi sottostanti

class C{
   string s;
   C(string x="1"): s(x){}
   ~C() {cout << s << "Cd ";}
};

C F(C p) {return p;}

C w("3");

class D{
   public:
      static C c;
};

C D::c("4");

int main(){
   cout << "PROGRAMMA UNO\n";
   C x("5"), y("6"); D d;
   y=F(x); cout << "uno\n";
   C z=F(x); cout <<"due\n";
}

/*
Stampe:

PROGRAMMA UNO
5Cd 5Cd uno
5Cd 5Cd due
5Cd 5Cd 5Cd 4Cd 3Cd
*/

/*Definire un template di funzione Fu(T1*, T2&) che ritorna un booleano con il seguente comportamento. 
Consideriamo una istanziazione implicita Fun(p, r) dove supponiamo che i parametri di tipo T1 e T2 siano istanziati
a tipi polimorfi (cioè che contengono almeno un metodo virtuale) Allora Fun(p, r) mentre true sse valgono le seguenti condizioni:

1) i parametri di tipo T1 e T2 sono istanziati allo stesso tipo;

2) siano D1* il tipo dinamico di p e d2& il tipo dinamico di r. Allora (i) D1 e D2 sono lo stesso tipo e (II) questo tipo
è un sottotipo proprio della classe ios della gerarchia delle classi di I/O (attenzione però che la classe ios è astratta!)

Ad esempio il seguente main() deve compilare e provocare le stampe indicate:
*/

template <class T1, class T2>
bool Fun(T1*p, T2& r){
//OSservazioni:

   //posso fare typeid(T1)==typeid(T2) oppure come sotto
   //il dynamic cast controlla solo che sia sottotipo
   //il sottotipo proprio significa sottotipo del tipo ma non uguale
   //ios è una classe astratta ed il tipo dinamico non potrà mai essere ios
   return typeid(p)==typeid(&r) && typeid(*p)==typeid(r) && dynamic_cast<ios>(p) != nullptr;
}


/*
   Si supponga che
   1) il main() compili correttamente ed esegua senza errori a runtime
   2) l'esecuzione del main() provochi in output su cout la stampa pippo pluto

   In tali ipotesi, per ognuna delle relazioni di sottotipo X<=Y nelle seguenti tabelle segnare con una croce l'entrata:
   (a) "Vero" per indicare che X sicuramente è sottotipo di Y;
   (b) "Falso" per indicare che X sicuramente non è sottotipo di Y;
   (c) "Possibile" altrimenti, ovvero se non valgono né (a) né (b)

   Tabelle: (considerando che se A<=B ovviamente B<=A non può essere)

(CTRL-ALT per selezionare verticalmente)

(Caso 1: dynamic cast che va bene)
Attenzione che io ricavo come informazione che B è sottotipo di A (quindi B<=A VERO)
Vale anche per dynamic cast D<=B (quindi D<=B VERO)
Vi è inoltre C<=A

Se faccio dynamic cast, essi comunque non falliscono grazie all'ereditarietà
multipla tra tipi.

(Caso 2: dynamic cast che fallisce nel try e poi anche quello sotto)
Quindi C non <= B e B non <= D.
D sarà quindi <= ad A, perché fallisce il dynamic cast, ma A non è sottotipo di B

A<=B     FALSO        
A<=C     FALSO      
A<=D     FALSO        
B<=A     VERO           
B<=C     Possibile (perché non abbiamo la certezza che non valga, può essere)        
B<=D              

C<=A     VERO
C<=B     FALSO
C<=D     Possibile
D<=A     VERO     (per transitività perché D<=B)
D<=B     VERO
D<=C     Possibile
*/

template<class X>
X& fun(X& ref){return ref;}

int main(){
   B b;
   fun<A>(b);
   B* p = new D();
   C c;
   try{
      dynamic_cast<B&>(fun<A>(c));
      cout << "topolino";
   }
   catch(bad_cast){cout << "pippo ";}
   if(!dynamic_cast<D*>(new B())) cout << "pluto";

/*
Si consideri la gerarchia di classi per l'I/0. La classe base ios ha il distruttore virtuale, costruttore di copia privato
ed un unico costruttore (a 2 parametri con valori di default) protetto. Diciamo che le classi derivate da istream ma non da ostream 
(ad esempio ifstream), e istream stessa, sono classi di input, le classi derivate da ostream ma non da istream (ad esempio I/O, esempio iostream e fstream).
Quindi ogni classe di input, output e I/O è una sottoclasse di ios. Definire una funzione int F(ios& ref)che restituisce -1 se il tipo dinamico
di ref è un riferimento ad una classe din input, 1 se il tipo dinamico diref è un riferimento ad una classe di output, 0 se il tipo dinamico
di ref è un riferimento ad una classe di I/O, in tutti gli altri casi ritorna 9.
*/

int F(ios& ref){
   if(dynamic_cast<istream*>(&ref) && !dynamic_cast<ostream*>(&ref)) return -1;
   if(dynamic_cast<ostream*>(&ref) && !dynamic_cast<istream*>(&ref)) return 1;
   if(dynamic_cast<istream*>(&ref) && !dynamic_cast<ostream*>(&ref)) return 0;
   return 9;
}

//Main di riferimento
int main(){
   istream& b = cin;
   ostream& c = cout;
   stringstream d;
   ifstream e("pippo");
   ofstream f("pluto");
   D q;
   cout << F(b) << ' ' << F(c) << ' ' << F(d) << ' ' << F(e) << ' ' << F(f) << ' ' << F(q) << endl;
   //stampa -1 1 0 -1 1 9
}

/*Esercizio 11.13 del libro

Si ricorda che nella gerarchia di classi per l'I/O la classe base atratta ios ha il distruttore virtuale.
Si definisca una classe C che soddisfa le seguenti specifiche.

1) Un oggetto della classe C è caratterizzato da un vector di puntatori a ios e dal numero
massimo di puntatori che questo vector può contenere. Deve essere disponibile un costruttore ad un argomenti intero k, con valore
di default positivo, che determina il numero massimo k di puntatori che può contenere.

2) Deve essere disponibile un metodo void insert(ios&) con il seguente comportamento:
una invocazione c.insert(s) inserisce nel vector di c un puntatore a s quando valgono entrambe le seguenti condizioni (altrimenti
lascia inalterato il vector):
(a) il vector può contenere ancora elementi rispetto al numero massimo possibile
(b) se D& è il tipo dinamico di s allora il tipo D è diverso sia da fstream che da stringstream

3) Deve essere disponibile un template di metodo int conta(T&), dove T è un parametro di tipo, con il 
seguente comportamento: ogni inovazione c.conta(t) ritorna il numero di puntatori del vector di c che hanno un tipo
dinamico D* tale che il tipo D è un sottotipo del parametro attuale t.

*/

class C{
   private:
      vector<ios*>v;
      int nmax;
   public:
      C(int k=5): nmax(k) {}
      void insert(ios& s){
         if(v.size() < nmax && typeid(s) != typeid(stringstream) && typeid(s) != typeid(fstream)){
            v.push_back(&s);
         }
      }

      template<class T>
      int conta(T& t) const{
         int cont=0;
         for(vector<ios*>::const_iterator it=v.begin(); it!=v.end(); it++){
            if(dynamic_cast<T*>(*it)) cont++;
         }
         return cont;
      }
};

int main(){
   ifstream f("pippo"); ofstream g("mandrake");
   fstream h("pluto"), i("zagor");
   ostream* p = &g;
   stringstream s;
   C c(10);
   c.insert(f); c.insert(g); c.insert(h);
   c.insert(i); c.insert(*p); c.insert(s);
   ifstream& r=f;
   cout << c.conta(r); //stampa: 1(puntatore all'oggetto f)
}

/*Esercizio 11.17 del libro

Si considerino le seguenti dichiarazioni di classi di qualche libreria grafica, dove gli oggetti delle classi
Container, Component, Button, Menuitem sono chiamati, rispettivamente, contenitori, componenti, pulsanti ed entrate di menù.

////////
class Component;

class Container{
   public:
      virtual ~Container();
      vector<Component*> getComponents() const;
};

class Component: public Container {};

class Button: public Component{

};

class MenuItem: public Button{

};

class NoButton {};
/////////

Assumiamo i seguenti fatti:

1) Il comportamento del metodo getComponents() della classe Container è il seguente:
c.getComponents() ritorna un vector di puntatori a tutte le componenti inserite nel contenitore c;
se c non ha alcuna componente allora ritorna un vector vuoto.
2) Il comportamento del metodo getContainers() della classe Button è il seguente:
b.getContainers() ritorna un vector di puntatori a tutti i contenitori che contengono il pulsante b;
se b non appartiene ad alcun contenitore allora ritorna un vector vuoto.
3) Il comportamento del metodo setEnabled() della classe MenuItem è il sguente: mi.setEnabled(b) abitilita (con b==true) o disabilita
(con b==false) l'entrata di menù mi.

Definire una funzione Button** Fun(const Container&) con il seguente comportamento: in ogni invocazione Fun(c)
1) Se c contiene almeno una componente Button allora ritorna un puntatore alla prima cella di un array dinamico
di puntatori a pulsanti contenente tutti e soli i puntatori ai pulsanti che sono componenti del contenitore c ed in cui tutte le componenti
che sono un'entrata di menù "e" sono contenute in almeno 2 contenitori vengono disabilitate.
2) Se invece c non contiene nessuna componente Button allora solleva un'eccezione di tipo NoButton

Per completezza scrivo anche i 3 metodi descritti sopra l'ultimo blocco.
*/
vector<Component*> getComponents() const{
   if(!c)   return vector();
   vector<Component*> v;
   for(int i=0; i<c.size(); i++)
   v[i]=c[i];
   return v;
}

vector<Component*> getContainers() const{
   if(!b   return vector();
   vector<Component*> v;
   for(int i=0; i<b.size(); i++)
   v[i]=b[i];
   return v;
}

void setEnabled(bool b){
   if(b) b=true; 
   else b=false; return;
}

Button **fun(const Container& c){
   vector<Component*> v=c.getComponents();
   try{
      if(!v) throw NoButton();
      int count=0;
      for(int i=0; i<v.size(); i++){
         if(dynamic_cast<Button*>(v[i])) count++;
      }
   }
   catch(NoButton){}

   Button **a=new Button[count];
   for(int i=0; i<v.size(); i++){
      if(dynamic_cast<Button*>(v[i])){
         MenuItem* mi=dynamic_cast<MenuItem*>(v[i]);
         if(mi.getContainers() > 2 && mi.setEnabled(false)){
            a[cont]=dynamic_cast<Button*>(v[i]);
            count++;
         }
      }
   }
   return a;
}

//Programma sottostante: cosa stampa?

class It{
   friend class C;
   private:
      int index;
   public:
      bool operator<(It i) const{return index < i.index;}
      It operator++(int) {It t = *this; index++; return t;}
      It operator+(int k) {index = index + k; return *this;}
};

class C{
   private:
      int* p;
      int dim;
   public:
      C(int k){
         if(k>0){dim=k; p = new int[k];}
         for(int i=0; i<k; i++) *(p+i)=i;
      }
      It begin() const{It t; t.index=0; return t;}
      It end() const{It t; t.index=dim; return t;}
      int& operator[](It i){return *(p + i.index);}
};

int main(){
   C c1(4), c2(8);
   for(It i = c1.begin(); i < c1.end(); i++) cout << c1[i] << ' ';
   cout << "UNO\n";
   It i = c2.begin();
   for(int n=0; i < c2.end(); ++n, i = i+n) cout << c2[i] << ' ';
   cout << "DUE";
}

/*
Stampa:
0 1 2 3 UNO
0 1 3 6 DUE

Nel primo caso è molto intuitivo, scorro fino alla fine passando la dimensione 4
e fine dei giochi.
Nel secondo caso, invece, uso I per portarmi all'inizio di c2 (che è 0).
Quindi faccio il for con i che punta a 0 ed n che si incrementa di i.
Quindi al primo passaggio è 0 per forza, poi al secondo è 1 perché 0+1 (per gli indici descritti prima)
poi 1+2 e infine 3+3, che danno luogo alle stampe indicate.
*/

class B{
   public:
   int x;
   B(int z=1): x(z) {}
   virtual void f() const { cout << x << "B::f() ";}
   virtual bool operator <=(const B& r) const{return true;}
};

class C: virtual public B{
   public:
   virtual void f() const { cout << x << "C::f() ";}
   virtual bool operator <=(const B& r) const{return dynamic_cast<const C*>(&r) != 0 ? true : false;}
};

class D: virtual public B{
   public:
   virtual void g() const { cout << x << "D::g() ";}
   virtual void h() const { cout << x << "D::h() "; g(); }
   virtual bool operator <=(const B& r) const{return dynamic_cast<const D*>(&r) != 0 ? true : false;}
};

class E: public D{
   public:
   virtual void f() const { cout << x << "E::f() ";}
   virtual void h() const { cout << x << "E::h() ";}
   virtual bool operator <=(const B& r) const{return dynamic_cast<const E*>(&r) != 0 ? true : false;}
};

class F: public C, public E{
   public:
   F(): B(2) {}
   virtual void f() const { cout << x << "F::f() ";}
   virtual void h() const { cout << x << "F::g() "; D::g();}
   virtual bool operator <=(const B& r) const{return dynamic_cast<const F*>(&r) != 0 ? true : false;}
};

void fun(const vector<B*>& v){
   D* p;
   for(int k=0; k != v.size(); ++k){
      v[k]->f();
      if( k+1 < v.size() && *v[k] <= *v[k+1]) v[k+1]->f();
      p=dynamic_cast<E*>(v[k]);
      if(p) {static_cast<E*>(p)->g(); p->h();}
      cout << "**" << k << endl;
   }
}

int main() {
  B b;
  C c;
  D d;
  E e;
  F f;
  vector<B*> v;
  v.push_back(&d);      //ad esempio considero &d ed &f nella 0; poi per ognuno considero il successivo
  v.push_back(&f);      //quindi quella dopo considero &f rispetto ad &e
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
STAMPA (devo avere almeno due elementi per ogni stampa, quindi riga prima e riga dopo rispetto alle stampe)
1B::f() 2F::f() **0
Qui butto dentro un D ed F, prime due righe, che stampano così perché considero 2 elementi alla volta
Essendo che il dynamic cast fallisce, genera questo risultato

2F::f() 2D::g() 2F::g() 2D::g() **1
Qui invece abbiamo un F e un E convertito in D,
quindi prima invoca il metodo f in F, poi k+1, di tipo D non ha il metodo F
e non viene stampato nulla, dopodiché una volta convertito il puntatore
con il dynamic cast nel tipo E, invoca i metodi chiamati, quindi G e poi invoca
D::g come da corpo del costruttore

1E::f() 1D::g() 1E::h() **2
Invoca f() in E non essendoci il metodo in D e dinamicamente
se lo va a prendere in E, dopodichè non essendo v[k] <= v[k+1]
non invoca v[k+1]->f().
Esegue la successiva conversione solita in E*, da cui invoca il metodo g,
non presente in E e lo invoca in D, altrimenti invoca H, questa volta
presente in E e lo invoca

1B::f() **3
Stampa solo l'invocazione di f() all'interno della superclasse B
in quanto D non ha il metodo F

1C::f() **4
Qui il metodo F c'è e viene stampato sull'oggetto C

1B::f() 1B::f() **5
Qui si ha un tipo D derivato da B che sarà certamente <= al successore, sempre un D;
pertanto stampa due volte B::f() per il primo e secondo elemento

1B::f() **6
Qui invece si ha un tipo D e subito un B, non <= e chiama solo f() in B

1B::f() 1B::f() **7
Chiama due volte B::f() perché come prima ci sono due B, prima e dopo

1B::f() 1C::f() **8
Chiama i due metodi F del tipo B e C

1C::f() **9
Poi come prima si invoca solo il metodo proprio ridefinito

1B::f() 2F::f() **10
Due oggetti di tipo B ed F e ne chiama i rispettivi f()

2F::f() 2F::f() 2D::g() 2F::g() 2D::g() **11
Qui ho un tipo F ed F convertito ad E, quindi come prima cosa esegue f() di F
poi l'elemento dopo è di nuovo F e stampa il secondo pezzo.
Il dynamic cast riesce quindi invoca G per D, tipo convertito, poi
deve invocare g(), che è già definito in F, lo invoca poi il metodo proprio

2F::f() 2D::g() 2F::g() 2D::g() **12
QUi invece ho due tipi uguali, di cui uno coonvertito staticamente, quindi due E
e in particolare invoco come sempre f() della superclasse, poi invoco dopo aver fatto
con successo il dynamic cast, il metodo g del tipo attuale, un tipo E che viene trovato in D
e stampa il metodo g(), poi viene trovato anche in F, che viene stampato.
1E::f() 1D::g() 1E::h() **13
Abbiamo il tipo E e tipo C, quindi il tipo E ha un metodo f() che viene stampato
poi ho il dynamic cast che funzione e vado a chiamare i metodi nell'if,
quindi g() ed h(), di cui g() è dentro D ed h() è dentro E, da cui tutta la stampa

1C::f() **14
Per finire ho solo il tipo C, che invoca il proprio metodo

*/

//Programma sottostante: cosa stampa?

class C {
   public:
   C(): size(1), a(new int[1]) {a[0]=0;}
   C& operator=(const C& x) {
      if(this!=&x){
         size=x.size;
         a=new int[size];
         for(int i=0;i<size;i++) a[i]=x.a[i];}
         return*this;
   }
   void add(int k) {
      int*b=a;
      a=new int[size+1];
      ++size;
      a[0]=k;
      for(int i=1;i<size;i++) a[i]=b[i-1];
      delete[] b;
   }
   int& operator[](int i) const {return a[i];}
   void stampa() const {
      for(int i=0;i<size;i++) cout<<a[i]<< ' ';
      } 
      ~C() {stampa(); cout<<" ~C "; delete[] a;}
   private:
   int size;
   int*a;
};

int main(){
   C v; 
   v.add(1);
   C w=v; w[1]=2;
   v.stampa(); cout<<"UNO\n";
   w.stampa(); cout<<"DUE\n";
   C*p=new C; p->add(3);
   *p=v;
   (*p)[0]=4; v[1]=5;
   v.stampa(); cout<<"TRE\n";
   w.stampa(); cout<<"QUATTRO\n";
   p->stampa(); cout<<"CINQUE\n";
   w=*p;w[1]=6; v[0]=7;
   v.stampa(); cout<<"SEI\n";
   w.stampa(); cout<<"SETTE\n";
   p->stampa(); cout<<"OTTO\n";
   delete p; cout<<"NOVE\n";
}

/*
Stampe prodotte:

1 2 UNO
Creazione di C messo a 0, poi C[1] viene messo ad 1 e per azione 
della add succede lo stesso a C[0]; assegnazione esplicita che va diventare 
1 e 2, da cui le stampe; uguale riga sotto
1 2 DUE

1 5 TRE
Qui invece creo un nuovo P inizializzando 3 elementi ad 1;
l'assegnazione dopo del puntatore coinvolge solo il secondo elemento di v, che quindi
stampa 1 e 5, in quanto 1 era già presente prima

1 5 QUATTRO
Essendo i puntatori identici per assegnazione, succede lo stesso a w

4 2 CINQUE
Coerentemente a prima, p ha nel primo elemento 4,
mentre nel secondo elemento, essendo stato assegnato al momento della
riga *p=v il suo valore, si noti che l'elemento puntato, secondo elemento [1]
prende valore 2, che viene stampato

7 5 SEI
Qui è immediato e si vede dalle assegnazioni di v che sono esplicite

4 6 SETTE
Anche qui assegnazioni esplicite a 4 e 6 nel codice

4 2 OTTO
Anche qui, primo elemento esplicito di p mentre il secondo è dato dall'assegnazione
precedente

4 2  ~C NOVE
Tracciata la distruzione di p con gli elementi detti, viene distrutto
4 6  ~C 7 5  ~C 
Qui invece vengono distrutti nell'ordine inverso gli altri 2 elementi
*/

//Programma sottostante: cosa stampa?
//Descriver per ogni riga se stampa, non stampa o altro

class D;

class B{
   public:
   virtual D* f()=0;
};

class C{
   public:
   virtual C* g();
   virtual B* h()=0;
};

class D: public B, public C{
   public:
   D* f() {cout << "D::f "; return new D;}
   D* h() {cout << "D::h "; return dynamic_cast<D*>(g());}
};

C* C::g(){
   cout << "C::g ";
   B* p = dynamic_cast<B*>(this);
   if(p) return p->f(); else return this;
}

class E: public D{
   public:
   E* f(){
      cout << "E::f ";
      E* p = dynamic_cast<E*>(g());
      if(p) return p; else return this;
   }
};

class F: public E{
   public:
   E* g() {cout << "F::g "; return new F;}
   E* h(){
      cout << "F::h ";
      E* p = dynamic_cast<E*>(E::g());
      if(p) return p; else return new F;
   }
};

B* p; C* q; D* r;

int main(){
   p = new E; p->h();
   p = new E; p->f();
   p = new D; (dynamic_cast<D*>(p))->h();
   q = new D; q->g();
   q = new E; q->h();
   q = new F; q->g();
   r = new E; r->f();
   r = new F; r->f();
   r = new F; r->g();
   r = new F; r->h();
}

/*
1)Il primo non compila perché B non ha nessun metodo proprio h(), nonostante in C
venga segnato come ridefinito, cosa che non avviene.

2) E::f C::g ripetutamente, poiché invoca il metodo proprio f() di E. 
Qui il dynamic cast fallisce e ritorna this.
Va in c::g() unico metodo altrimenti presente e stampa quello,
ma anche qui il dynamic cast fallisce e genera problemi quindi.

3)D::h C::g D::f 
Fa il dynamic cast con successo nel tipo D, che invoca il proprio h()
poi deriva da B che non ha h(). Va in C, che non ha h() ma ha il
metodo g() che viene eseguito e poi non fa il dynamic cast dentro g()
e quindi ritorna in D, eseguendo f().

4)C::g D::f 
Si ha un upcast alla riga 4 a D, che però non ha g() e questo
viene eseguito da C. Poi il dynamic cast in C::G() ha successo e si esegue
il metodo f() ridefinito dentro D.

5)E::f C::g ripetutamente, perché continua a cercare il metodo h()
non trovandolo. Va prima in E, dove usa il metodo f() e il dynamic_cast fallisce
essendo già di tipo E() e ritorna this.
Essendo E derivato da D e a sua volta D derivato da B e da C, cerca in b e c 
il metodo h() segnato come virtual da B ma non trovato.
Si torna quindi C eseguendo C::g() e poi ancora a ruota si ritorna nella sottoclasse
perché il tipo del cast è già C e si ritorna a cercare.

6)F::g
Il metodo è già presente e ridefinito per ereditarietà.

7)E::f C::g ripetutamente, perché i due dynamic cast continuano a fallire e 
continua a ritornare i due oggetti di invocazione sempre.

8)Qui invece il dynamic cast riesce e io sto solo
cercando il metodo f(9 che sta nella classe E in questo momento.
Il dynamic cast riesce e si ritorna poi all'oggetto di invocazione F
che invoca il metodo proprio g().

9)
F::g, stesso motivo di (6)

10)
F::h C::g E::f F::g 
Cerco h e lo eredito da E, riscritto dentro F e lo stampo.
A catena di ereditarietà ritorna nella superclasse C che è l'unica che ha
un metodo da chiamare, cioè g(). Ritorna con successo l'oggetto di tipo E
dopo il dynamic cast e poi chiama g() dentro F perché vi è già dentro.
*/


//Si consideri la seguente gerarchia di classi

class A{public: virtual ~A() {}};

class B{public: virtual ~B() {}};

class C: virtual public A, virtual public B{
   public:
      C() {cout << "C0 ";}
      C(B* x, A y = A()) {cout << "C1-2 ";}
};

class D: public C{
   public:
      D() {cout << "D0 ";}
      D(C x){cout << "D1 ";}
};

//Si considerino le seguenti definizioni di variabili globali ed i seguenti
//main composti di una singola istruzione. Per ognuno di questi
//determinare se compila o meno e la stampa che produce in output

//per comodità accorpate in un main solo e commentate poi sotto

A a; B b; C c; D d;

int main(){
   D z0(a);
   D z1(b);
   D z2(&b);
   D z3(&c);
   D z4(c);
   D z5(d);
   D z6(&a, c);
   C z7(&c);
   C z8(&d, d);
}

/*
1) Non compila perché l'unico costruttore presente è per a in D

2) Stessa cosa per z1

3) C0 C0 D0 C1-2 C0 D1 
Stampa questi valori perché sto passando un indirizzo di tipo b
e lo cerca nelle superclassi, quindi percorre D e poi C per A e B
che non hanno default tracciato e stampando due volte C0 per quello, per il default di C
A questo punto costruisce di default D, essendo la classe che avevo inizialmente
e stampa C1-2, poi stampa ancora C0 per il costruttore D(C x) e infine D1

4) C0 C0 D0 C1-2 C0 D1 
Stessa cosa di (3)

5)C0 C0 D0 C0 D1
Per i motivi di sopra, vado subito alle superclassi, che comporta due stampe C0 
e poi stampo D0 e infine il costruttore che voglio, dopo aver creato locale c
e quindi D1

6)C0 C0 D0
Torno nella superclasse solo per il default di C, 
altrimenti p la costruzione di D con il costruttore proprio con patametro C.
Questo viene eseguito, pur trattandosi di un C, per regole di ereditarietà.

7)Necessita di apposito costruttore in D, in quanto sia in D
che nelle superclassi non ce ne sta uno ad hoc.

8)C0 C0 D0 C1-2
Stessi passaggi del punto 3 praticamente, solo che ora il tipo
creato è C, quindi va subito alla creazione di C0 nella superclasse C
poi si crea l'oggetto C per D, ne stampa il default e, essendo
che vuole un indirizzo di tipo C, per ereditarietà eseguo C(B*, A)

9)C0 C0 D0 C1-2 
Stessa stampa per motivi di prima, sono oggetti diversi, ma l'unico costruttore
che può incapsulare per ereditarietà questi valori sta dentro C
*/

//Si consideri la seguente gerarchia di classi e le seguenti variabili globali:

class A{public: virtual ~A() {}};
class B: virtual public A{};
class C: virtual public A{};
class D: virtual public A{};
class E: virtual public A{};
class F: virtual public C{};
class G: public B, public E, public F{};

B b; D d; E e; F f; G g; A* pa; B* pb; C* pc; F* pf;

//Per ognuno dei main determinare se compilano o meno

int main() {pc = &e; cout << (dynamic_cast<D*> (pc) ? "OK" : "NO"); }

int main() {cout << (dynamic_cast<B*> (&g) ? "OK" : "NO"); }

int main() {pa = &f; cout << (dynamic_cast<C*> (pa) ? "OK" : "NO"); }

int main() {pb = &b; cout << (dynamic_cast<G*> (pb) ? "OK" : "NO"); }

int main() {cout << (dynamic_cast<D*> (&d) ? "OK" : "NO"); }

int main() {pf = &g; cout << (dynamic_cast<E*> (pf) ? "OK" : "NO"); }

int main() {pf = &f; cout << (dynamic_cast<E*> (pf) ? "OK" : "NO"); }

/*
1) Non compila, perché non si ha nessun passaggio da E a C
2) OK, si vede che va dalla riga class G
3) Ok, si vede che va dalla riga class C
4) OK, si vede che va dalla riga class G
5) OK, il tipo D è già un D e va per costruirlo nella superclasse A
che va senza problemi
6) OK, F viene convertito dinamicamente in G e poi va regolarmente
con la riga class G
7) Compila, ma non viene eseguito.
Questo perché F è già un F e quindi non viene fatto il dynamic cast in E
perché non è visibile. Il puntatore c'è, ma segna NO nella stampa
*/

//Il codice seguente compila?
class Z
{
private:
    int x;
};

class B
{
private:
    Z z;
public:
    B(const B& b) {z=b.z;}
};

class D : public B
{
private:
    Z y;
public:
    D& operator=(const D& d)
    {
        y=d.y;
        B::B(d);
    }
};

//NO:
//main.cpp:25:15: error: cannot call constructor ‘B::B’ directly [-fpermissive]

namespace ns { 
    class C { 
        private: 
            friend int f(); 
            int x; 
        public: 
            C(int n=0) : x(n) {}
    };
}

int f() { ns::C c; return c.x; }

int main() { 
    f();
}

// 1. non compila perchè f non può accedere alla parte privata di C
// C ha f() come amica ma nel suo namespace ns



class C { 
    public: 
        int a[2]; 
        C(int x=0,int y=1) {
            a[0]=x; 
            a[1]=y; 
            cout << "C(" << a[0] << "," << a[1] << ") ";
        }
        C(const C&) {cout << "Cc ";}
};

class D {
    private: 
        C c1; 
        C *c2;
        C& cr;
    public: 
        D() : c2(&c1), cr(c1) { cout << "D() ";} 
        D(const D& d) : cr(c1) { cout << "Dc ";} 
        ~D() { cout << "~D ";}
};

class E { 
    public: static C cs;
}; 

C E::cs=1;

int main() {
    C c; cout << "UNO" << endl;
    C x(c); cout << x.a[0] << " " << x.a[1] << " DUE" << endl;
    D d=D(); cout << "TRE" << endl;
    E e; cout << "QUATTRO" << endl;
}

/*
C(1,1) Cc C(0,1) UNO
Cc VC VC DUE
C(0,1) D() C(0,1) Dc ~D TRE
QUATTRO
~D 
*/

class C { 
    public: 
        int a; 
        void fC() { a=2; }
};
class D: public C { 
    public: 
        double a; 
        void fD() { a=3.14; C::a=4; }
};
class E: public D { 
    public: 
        char a; 
        void fE() { a='*'; C::a=5; D::a=6.28; }
};
int main() { 
    C c; D d; E e; 
    c.fC(); 
    d.fD(); 
    e.fE(); 
    D* pd = &d; 
    E& pe = e; 
    cout << pd->a << " " << pe.a << endl; 
    cout << pd->a << " " << pd->D::a << " " << pd->C::a << endl; 
    cout << pe.a << " " << pe.D::a << " " << pe.C::a << endl; 
    cout << e.a << " " << e.D::a << " " << e.C::a << endl;
}

/*
3.14 *
3.14 3.14 4
* 6.28 5
* 6.28 5
*/

class A{
    public:
        virtual ~A() = default;
};

class D: public A {};

class C: public A{};

class B: public D {};

template <class X, class Y>
X* fun(X* p) { return dynamic_cast<Y*>(p);}

int main(){
    C c; fun<A,B>(&c);
    if(fun<A,B>(new C())==0) cout << "Bjarne ";
    if(dynamic_cast<C*>(new B()) == 0) cout << "Stroustrop";
    A* p = fun<D, B>(new D());
}

/*
Stampa "Bjarne Stroustrop"

Infatti le chiamate al template e alla funzione fun() va senza problemi
facendo correttamente il dynamic cast, in questo caso a due 
classi nello stesso livello di ereditarietà.
Stiamo convertendo un tipo C ad A, da cui deriva direttamente e funziona.

Per il successivo dynamic cast, che vuole convertire nel tipo C* creandosi un B, 
non ci sta nessun collegamento tra i singoli pezzi. 
Infatti voglio convertire B in un tipo C. 
Questa fallisce perché noi abbiamo un tipo B, derivante da D e poi da A
ad un tipo C, derivante solo da A.
Non essendo polimorfa la classe A, non viene fatta la conversione.

Si vede anche da qui:

A     A
|     |
C     D
      |
      B

*/

class A {
protected:
    int x;
public:
   A(int k=0): x(k) { cout << "A(" << x << ") ";}
   ~A() { cout << "~A()";}
   operator double() const { cout << "op double(" << x << ") "; return x;}
};

class B: public A {
public:
   static A a;
   const A &a2;
   A F(A a=A()) { return a;}
   B(int k=3, const A& a3=7) : A(k), a2(a3) { cout << "B() ";}
   ~B() { cout << "~B()";}
   B(const B &b) : a2(b) { cout << a2 << " ";}
};

A B::a(1);

int main() {
   A a(1); cout << "UNO\n";
   B b; cout << "DUE\n";
   B b2(a); cout << "TRE\n";
   B b3(a,a); cout << "QUATTRO\n";
   B b4=b3; cout << "CINQUE\n";
   b.F(); cout << "SEI\n";
   b.F(2); cout << "SETTE\n";

   cout << "FINE\n";
}

/*
A(1) A(1) UNO
Creazione di default di un a con creazione del temporaneo locale (perché non passato per riferimento).

A(7) A(3) B() ~A()DUE
Va nel costruttore di default di B e non fa altre cose.

A(7) op double(1) A(1) B() ~A()TRE
Essendo che passa un oggetto "a", usa il costruttore che comprende
un a costante, quindi il costruttore B(int k=3..). Crea quindi 7 per quel motivo
e poi crea di default in A l'oggetto valorizzato ad 1. Essendo un tipo B, viene
invocato il B di default e il distruttore del temporaneo creato per A.

op double(1) A(1) B() QUATTRO
Semplicemente fa type match con il costruttore proprio 
e poi, una volta convertito, stampa le costruzioni, quindi
A con il suo valore, B di default.

A(0) op double(1) 1 CINQUE
Si crea b4 che non esiste, lo inizializza con il costruttore
della classe base A, invoca l'operazione di conversione e poi stampa il valore
utilizzato.

A(0) ~A()~A()~A()SEI
Come prima uso il tracciamento nella classe A per la
costruzione del primo elemento di default, poi altre 3 stampe che distruggono
il valore A locale, il temp. anonimo e il valore costante; stessa cosa per la riga dopo 

A(2) ~A()~A()~A()SETTE
FINE
~B()~A()~B()~A()~B()~A()~B()~A()~A()~A()
*/

class A {
protected:
	int x;
public:
	A(int k=0) : x(k) {cout << "A("<<k<<") ";}
	~A() { cout << "~A ";}
	operator double() const { cout << "operator double() "; return x;}
};

class B : public A {
public:
	static A a;
	const A& a2;
	B(int k=3, const A &a3=0) : A(k), a2(a3) {cout << "B() ";}
	B(const B &b) : a2(b) {cout << a2 << " ";}
	~B() { cout <<"~B ";}
	A F(A a = A() ) { return a; }
};
A B::a(1);

int main() {
	A a(2); cout << "UNO\n";
	B b; cout << "DUE\n";
	B b2(a); cout << "TRE\n";
	B b3(a,a); cout << "QUATTRO\n";
	B b4=b3; cout << "CINQUE\n";
	b.F(); cout << "SEI\n";/
	b.F(3); cout << "SETTE\n";/
	//
	return 0;
}

/*
A(1) A(2) UNO
A(0) A(3) B() ~A DUE
A(0) operator double() A(2) B() ~A TRE
operator double() A(2) B() QUATTRO
A(0) operator double() 2 CINQUE
A(0) ~A ~A ~A SEI
A(3) ~A ~A ~A SETTE
~B ~A ~B ~A ~B ~A ~B ~A ~A ~A
*/

/*
Scrivere un programma consistente di esattamente tre classi A, B e C della sola funzione main() che soddisfi le sguenti condizioni:

1) la classe A è definita come:
class {public: vortial ~A(){}};

2) le classi B e C devono essere definite per ereditarietà e non contengono alcun membro

3) la funzione main() definisce le tre variabili:
A* pa = new A; B* pb = new B; C* pc = new C;

4) la funzione main() può utilizzare solamente espressioni di tipo
A*, B* e C* non può sollevare eccezioni mediante throw e non può invocare l'operatore new

5) il programma deve compilare correttammente

6) l'esecuzione di main() deve provocare un errore run-time

*/

/*
Soluzione:

Creeo una gerarchia di classi, per esempio:

            A  (A polimorfa)
          /   \
         B     C

Il discorso è: il dynamic cast deve fallire, quindi sollevare un bad cast non gestito.
Ad esempio: dynamic_cast<C&>(*pb)
*/



//Per ognuno dei seguenti frammenti di codice, la loro compilazione
//prova degli errori?

C f(C& x){return x;} 
//Si, compila, perché il valore viene convertito a C senza problemi

C& g() const{return *this;}   
//No, non compila perché *this è un const C* e se lo dereferenzio sarebbe const C&, ma non è il tipo ritornato

C h() const{return *this;}
//Si, compila

C* m(){return this;}
//Si, compila, perfetto type match

C* n() const{return this;}
//No, non compila perché è const

void p() {}
void q() const{p(); }
//No, non compila perché p() non fa side effects, ma non ha il const
//termini tecnici: drop del qualifier const di this

void p(){}
static void r(C* const x){x->p();}
//Si, compila, dato che chiedo un puntatore ad un C costante e chiamo
//semplicemente p

void s(C *const x) const{*this = *x;}
//No, non compila, perché quando dereferenzio this ha const C&
//mentre operator= non è const rispetto all'espressione costante

static C& t() {return C(); }
//No, non compila perché C() non ha l-valore e la funzione chiede un indirizzo

static C *const u(C& x){return &x;}
//Si, compila perché uso un'espressione costante per costruire un'espressione non
//costante; tuttavia inizializzo un puntatore costante a C e va bene.


//Tracciare le stampe
//riporto anche la gerarchia

/*
         A
      /  |  \
     B   C   D
     \   |   /
      \  E
       \ |
         F  (tra B ed F distruzione virtuale)
*/

class Z{
   public: Z(int x){}
};
class A{
   public:
   void f(int){cout << "A::f(int) "; f(true);}
   virtual void f(bool) {cout << "A::f(bool) ";}
   virtual A* f(Z) {cout << "A::f(Z) "; return this;}
   A() {cout << "A() ";}
};

class C: virtual public A{
   public:
   C* f(Z){cout << "C::f(Z) "; return this;}
   C() {cout << "C() ";}
};

class E: public C{
   C* f(Z){cout << "E::f(Z) "; return this;}
   ~E() {cout << "~E ";}
   E() {cout << "E() ";}
};

class B: virtual public A {
   public:
   void f(const bool&){cout << "B::f(const bool&) ";}
   void f(const int&){cout << "B::f(const int&) ";}
   virtual B* f(Z) {cout << "B::f(Z) "; return this;}
   virtual ~B() {cout << "~B ";}
   B() {cout << "B() ";}
};

class D: virtual public A{
   public:
   virtual void f(bool) const {cout << "D::f(bool) ";}
   A* f(Z) {cout << "D::f(Z) "; return this;}
   ~D() {cout << "~D ";}
   D() {cout << "D() ";}
};

class F: public B, public E, public D{
   public:
   void f(bool){cout << "F::f(bool) ";}
   F* f(Z) {cout << "F::f(Z) "; return this;}
   ~F() {cout << "~F ";}
   F() {cout << "F() ";}
};

B* pb=new B; C* pc = new C; D* pd = new D; E* pe = new E;
F* pf = new F; B* pb1=new F;
A *pa1=pb, *pa2=pc, *pa3=pd, *pa4=pe, *pa5=pf;

//Istruzioni di riferimento

E* puntE = new F; //A() B() C() E() D() F()
A* puntA = new F; //A() B() C() E() D() F()

D* pd = new D;
A* pa1 = pd;
pa3->f(3);  //A::f(int) A::f(bool)

A* pa5 = new F;
pa5->f(3);  //A::f(int) F::f(bool)

B* pb1 = new F;
pb1->f(true);  //B::f(const bool&)

A* pa4 = new E;
pa4->f(true);  //A::f(bool)

A* pa2 = new C;
pa2->f(Z(2));  //C::f(Z)

A* pa5 = new F;
pa5->f(Z(2));  //F::f(Z)

(dynamic_cast<E*>(pa4))->f(Z(2));   //E::f(Z)

(dynamic_cast<C*>(pa5))->f(Z(2));   //F::f(Z)

B* pb=new B;
pb->f(3);   //B::f(const int&)

C* pc=new C;
pc->f(3);   //C::f(Z)

(pa4->f(Z(3)))->f(4);   //E::f(Z) A::f(int) A::f(bool)

(pc->f(Z(3)))->f(4);    //C::f(Z) C::f(Z)

A* pa5 = new F;
delete pa5; //nessuna stampa; ci sarebbe un errore logico, si invoca infatti il distruttore di A e fine

B* pb1=new F;
delete pb1;    //~F ~D ~E ~B
/*Ordine di costruzione: A B C E D F
e l'ordine di distruzione sarà al contrario quindi: F D E C B A 
Non ci saranno quindi A o C

Piccola nota: se una delle derivazioni da parte delle 
sottoclassi non fosse virtuale, essendo un binding statico,
avrei due volte la costruzione della classe A da parte della sottoclasse
non virtuale e anche dalle altre chiamate tutte virtuali.

Altra nota: l'operatore di scoping blocca le chiamate virtuali
*/


//Cosa stampa il seguente programma:

class C{
   public:
   int a[2];
   C(int x=0, int y=1){
      a[0]=x; a[1]=y; cout << "C(" << a[0] << "," << a[1] << ") ";
   }
};

class D{
   private:
   C c1;
   C* c2;
   C& cr;
   public:
   D(): c2(&c1), cr(c1) {cout << "D() ";}
   D(const D& d): cr(c1) {cout << "Dc ";}
   ~D(){cout << "~D ";}
};

class E{
   public:
   static C cs;
};

C E::cs;

int main(){
   C c; cout << "UNO" << endl;
   C x(c); cout << x.a[0] << " " << x.a[1] << " DUE" << endl;
   D d=D(); cout << "TRE" << endl;
   E e; cout << "QUATTRO" << endl;
}

/*
C(0,1) C(0,1) UNO
Normale costruzione in cui si ha anche un temporaneo e fa queste due stampe

0 1 DUE
Stampo poi i valori di C, che sappiamo essere 0 ed 1

C(0,1) D() TRE
Vado in C, in quanto classe base e gli butto i valori di default
e poi uso il costruttore D() default

QUATTRO
E non genera alcuna stampa, crea solo lo statico di tipo C

~D
L'unico costruttore tracciato è d, che viene stampato
*/


//I seguenti programmi compilano? Dire quali stampe provocano la loro esecuzione

class C{
   public:
   void f() {cout << "C::f" << endl;}
};

class D: public C{
   public:
   void f() {cout << "D::f" << endl;}
};

class E: public D{
   public:
   void f() {cout << "E::f" << endl;}
};

int main(){
   C c; D d; E e;
   C* pc = &c; E* pe = &e;
   c = d;
   c = e;
   d = e;
   d = c;
   C* rc=d;
   D& rd=e;
   pc->f();
   pc = pe;
   rd.f();
   c.f();
   pc->f();
}

/*
c = d;         Sì, compila, C ha come sottotipo d
c = e;         Stessa cosa
d = e;         Per binding a runtime fa tranquillamente l'assegnazione
d = c;         Essendo superclasse e non essendoci una gestione virtuale, non compila
C* rc=d;       Non compila, per static binding non riesco ad andare al sottotipo; se fosse C& rc=d compilerebbe
D& rd=e;       Compila; se fosse D* non compilerebbe per motivo sopra
pc->f();       Ambiguità nella compilazione, non sa quale chiamare e non compila
pc=pe;         Binding dinamico, a pc di tipo C* viene assegnato pe di tipo E& che funziona
rd.f();        Da prima andava  e correttamente è un tipo d, quindi stamoa D::f
c.f();         Anche qui punta al suo tipo e stampa C::f
pc->f();       Non dà problemi neanche qui e stampa questo
*/


class C{
   public:
   int a;
   void fC() {a=2;}
};

class D: public C{
   public:
   double a;
   void fD() {a=3.14; C::a=4;}
};

class E: public D{
   public:
   char a;
   void fE() {a='*'; C::a=5; D::a=6.28;}
};

int main(){
   C c; D d; E e;
   c.fC(); d.fD(); e.fE();
   D* pd = &d; E& pe = e;
   cout << pd->a << ' ' << pe.a << endl;
   cout << pd->a << ' ' << pd->D::a << ' ' << pd->C::a << endl;
   cout << pe.a << ' ' << pe.D::a << ' ' << pe.C::a << endl;
   cout << e.a << ' ' << e.D::a << ' ' << e.C::a << endl;
}

/* Stampe:

3.14 *
3.14 3.14 4
* 6.28 5
* 6.28 5

Poco da commentare, si vede proprio dal codice scritto

*/


/*
      (riferito al codice seguente questo commento)
      Definire opportunamente le incognite di tipo x1 e y1 tra i tipi A,B,C,D,E,F della seguente gerarchia in modo tale che:
      1) Lo statement non includa più di una chiamata della funzione G con gli stessi parametri attuali
      2) La compilazione dello statement non produca illegalità
      3) L'esecuzione dello statement non provochi errore a runtime
      4) L'esecuzione dello statement produca in output esattamente la parola SAGGEZZA

      Tra A e B derivazione virtuale. Anche C ha deriv,. virtuale (quindi freccia tratteggiata)
      Quindi A e B sono astratti.
      Gerarchia:
          A
         /  \
         B  C 
         \  /
           D
           |
           E
           |
           F

      Vincoli:

      Dalla seconda riga, quindi con le lettere
      Si intende con TD la dicitura Tipo Dinamico

      TD(r) in (D,E,F) TD(*p)  in [C,D,E,F]

      G = (E,E) , (F,F)
      -TD(r) <= E
      -TD (*p) = TD (r)

      Z = (C,D) (D,D)
      -!G
      -TD(r) non è <= E
      -TD(*p) <= D

      A = (C,E) (D,E), (E,D), (F,E), (F,D)
      -!Z
      -TD(r) non è <= F    (OR D diverso da F)
      
      S = (E,F)
      -!Z
      -TD(r) = F
      -TD(*p) = E

      E = (C,F) (D,F)
      !G & !Z & !A & !S

      SAGGEZZA
      (E,F) (C,E) (E,E) (F,F) (C,F) (C,D) (D,D) (D,E)

*/

class A{
   public:
   virtual void m() =0;
};

class B: virtual public A{};

class C: virtual public A{
   public:
   virtual void m();
};

class D: public B, public C{
   public:
   virtual void m() {}
}; 

class E: public D {};

class F: public E{};

//Le osservazioni fatte dal prof sono date sopra al codice 
char G(A* p, B& r){
   C* pc = dynamic_cast<E*>(&r);    //compila perché E è sottotipo di C
   if(pc && typeid(*p) == typeid(r)) return 'G';   //la & implica che devono valere entrambe, nell'ordine dato
   if(!dynamic_cast<E*>(&c) && dynamic_cast<D*>(p)) return 'E';
   if(!dynamic_cast<F*>(pc)) return 'A';
   else if (typeid(*p) == typeid(E)) return 'S';
   return 'E';
}


//Rispetto a 

template <class T> class D;

template <class T1, class T2>
class C{
   friend class D<T1>;
   private:
   T1 t1; T2 t2;
};

template <class T>
class D{
   public:
   void m() {C<T, T> c; cout << c.t1 << c.t2;}
   void n() {C<int, T> c; cout << c.t1 << c.t2;}
   void o() {C<T, int> c; cout << c.t1 << c.t2;}
   void p() {C<int, int> c; cout << c.t1 << c.t2;}
   void q() {C<int, double> c; cout << c.t1 << c.t2;}
   void r() {C<char, double> c; cout << c.t1 << c.t2;}
}; 

//I seguenti main compilano?

int main() {D<char> d; d.m();}      //Compila
int main() {D<char> d; d.n();}      //Non compila
int main() {D<char> d; d.o();}      //Compila
int main() {D<char> d; d.p();}      //Non compila
int main() {D<char> d; d.q();}      //Non compila
int main() {D<char> d; d.r();}      //Compila



//Ridefinire l'assegnazione operator= della classe D
//in modo tale che il suo comportamento coincida con quello dell'assegnazione standard di D

class Z{
   private:
   int x;
};

class B{
   private:
   Z x;
};

class D: public B{
   private:
   Z y;
   public:
   //ridefinizione di operator=
};

//Soluzione:

D& operator=(const D& d){
   B::operator=(d);  //per assegnare il sottooggetto; il tipo considerato sarebbe this
   y=d.y;
   return *this;     //ecco quindi che viene ritornato
}


//Date le seguenti definizioni di classi, ridefinire il costruttore
//di copia di E in modo che il suo costruttore 
//abbia comportamento identico a quello standard

class B{
   private:
   vector<bool>* ptr;
   virtual void m()=0;
};

class D: public B{
   private:
   int x;
};

class E: public D{
   private:
   list<int*> l;
   int& ref;
   double* p;
   public:
   void m() {}
};

//Soluzione: deve essere un'assegnazione di tutti i campi e quindi
E(const E& e): D(e), l(e.l), ref(e.ref), p(e.p) {}



//Dato il seguente programma, segnalare cosa stampa e se
//ci possono essere errori a runtime

class A{
   bool x;
   public:
   virtual ~A(){};
};

class B{
   bool y;
   public:
   virtual void f() const {cout << "B::f ";}
};

class C: public A{};

class D: public B{
   public:
   void f() const {cout << "D::f ";}
};

class E: public D{
   public:
   void f() const {cout << "D::f ";}
};

template <class T>
void Fun(const T& ref) {
   const B* pB = dynamic_cast<const B*>(&ref);
   const E* pE = dynamic_cast<const E*>(&ref);

   if(dynamic_cast<const C*>(&ref)){ cout << "C "; ref.f(); return; }
   if(pE) {cout << "E "; pE->f(); return; }
   if(pB) {cout << "B "; pB->f(); return; }
   if(dynamic_cast<const A*>(&ref)){ cout << "A "; return; }
   if(dynamic_cast<const D*>(&ref)){ cout << "D "; return; }
}

int main(){
   C c; 
   D d; 
   E e;
   A& a1 = c; 
   B& b1 = d; 
   B& b2 = e;
   B* b3 = new B(); 
   D& d1 = e; 
   D* pD1 = dynamic_cast<E*>(&b2);
   D* pD2 = dynamic_cast<D*>(&b2);

   Fun<A>(c);  //1
   Fun(a1);    //2
   Fun(b1);    //3
   Fun(d1);    //4
   Fun(*pD2);  //5
   Fun<E>(d1); //6
   Fun<E>(e);  //7
   Fun(*b3);   //8
   Fun<D>(e);  //9
   Fun(b2);    //10

   return 0;
}

/*
Commento riga per riga:

1) Non compila perché, nonostante il cast sia sensato
il tipo a (dentro ref) non ha il metodo f o anche ridefinito e quindi risulta questo

2) Stessa cosa, sempre un tipo a e non compila per lo stesso di prima

3) B D::f
Il tipo dell'oggetto è D, che deriva da B e ne stampa il costruttore poi chiama
il metodo f ridefinito

4) E D::f 
Qua invece il tipo invocato è un E che deriva da D il quale ha il proprio
metodo f ridefinito e lo invoca

5) E D::f
Il tipo D fa un safe downcast verso E, quindi stampa il suo costruttore
e poi invoca il metodo f proprio del tipo d invocato

6) Non compila perché l'oggetto d1, a differenza di c che è costante
come riferimento, non è un oggetto costante
error: invalid initialization of reference of type ‘const E&’ from expression of type ‘D’

7) E D::f
Anche qui l'oggetto è un tipo E e viene fatto tranquillamento il cast,
anche perché è già un tipo E e stampa proprio "E"
Poi stampa D::f che è il metodo ridefinito

8) B B::f
Il tipo di invocazione è un B pertanto il cast avrà certo successo
e stampa B, essendo tipo di invocazione, ed il metodo proprio f

9) E D::f
Il tipo di invocazione è un D, safe downcast al tipo E
e poi, essendo il template di tipo D, ne chiama il relativo metodo f()

10)E D::f
Anche qui il tipo di invocazione è un E, quindi ne stampa relativo E
perché il cast ha senso e poi ne invoca il metodo ridefinito dalla superclasse
*/


class A {
protected:
   virtual void j() { cout<<" A::j "; }
public:
   virtual void g() const { cout <<" A::g "; }
   virtual void f() { cout <<" A::f "; g(); j(); }
   void m() { cout <<" A::m "; g(); j(); }
   virtual void k() { cout <<" A::k "; j(); m(); }
   virtual A* n() { cout <<" A::n "; return this; }
};

class B: public A {
public:
   virtual void g() const override { cout <<" B::g "; }
   virtual void m() { cout <<" B::m "; g(); j(); }
   void k() { cout <<" B::k "; A::n(); }
   A* n() override { cout <<" B::n "; return this; }
};

class C: public A {
private:
   void j() { cout <<" C::j "; }
public:
   virtual void g() { cout <<" C::g "; }
   void m() { cout <<" C::m "; g(); j(); }
   void k() const { cout <<" C::k "; k(); }
};


class D: public B {
protected:
   void j() { cout <<" D::j "; }
public:
   B* n() final { cout <<" D::n "; return this; }
   void m() { cout <<" D::m "; g(); j(); }
};

A* p1 = new D(); A* p2 = new B(); A* p3 = new C(); B* p4 = new D(); const A* p5 = new C();

int main () {

p1->g();   // 1 ............................  B::g
p1->k();   // 2 ............................  B::k  A::n 
p2->f();   // 3.............................  A::f  B::g  A::j
p2->m();   // 4 ............................  A::m  B::g  A::j
p3->k();   // 5 ............................  A::k  C::j  A::m  A::g  C::j
p3->f();   // 6 ...........................   A::f  A::g  C::j 
p4->m();   // 7 ...........................   D::m  B::g  D::j
p4->k();   // 8 ...........................   B::k  A::n
p5->g();   // 9 ............................  A::g 
(p3->n())->m();  // 10 ....................   A::n  A::m  A::g  C::j 
(p3->n())->n()->g();   // 11 ...............  A::n  A::n  A::g 
(p4->n())->m();    // 12 ..................   D::n  A::m  B::g  D::j
(p5->n())->g();  cout << endl;  // 13  ...............   non compila 
(dynamic_cast<B*>(p1))->m(); // 14 ..................    D::m  B::g  D::j 
(static_cast<C*>(p2))->k(); // 15 ........................Errore run time 
(static_cast<B*>(p3->n()))->g();  //16 .................. Errore run time 

/* Scrivere un template di classe SmartP <T> di puntatori smart a T che definisca assegnazione profonda, 
costruzione di copia profonda, e distruzione profonda. Il template SmartP<T> dovrà essere dotato di interfaccia pubblica che permetta di compilare correttamente 
il seguente codice, la cui esecuzione dovrà provocare esattamente le stampe riportate nei commenti.*/

template <class T>
class SmartP{
   private:
   T* p;
   public:
   //default 
   SmartP(): p(nullptr);
   //costruttore di copia profondo
   SmartP(const SmartP<T>& s): p(new T(*(s.p))){}
   //costruttore ad un parametro per valore
   SmartP(const T* punt): p(new T(const_cast<T*>(punt))){}
   //assegnazione profonda
   SmartP<T>& operator=(const SmartP<T>& s){
      if(this != &s){
         delete p;
         p=new T(*s.p);
      }
      return *this;
   }
   //dereferenziazione (*)
   T& operator*() const{
      return *p;
   }
   //selezione di membro (->)
   T* operator->() const{
      return p;
   }
   //distruttore profondo
   ~SmartP(){
      if(p) delete p;
   }
   //chiamata di funzione
   SmartP<T> operator() (T*& p)const{return SmartP(p);}
};

class C{
   int*p;
   C() : p (new int(5){}
};

int main(){
   const int a=1;
   const int*p=&a;
   SmartP<int>r;
   SmartP<int>s(&a);
   SmartP<int>t(s);cout<<*s<<““<<*t<<*p;//111
   *s=2;*t=3;
   cout<<*s<<*t<<*p;//231
   r=t;*r=4;
   cout<<*r<<*s<<*t<<*p;//4231
   cout<<(s==t)<<(s!=p);//01
   C c; SmartP<c> x(&c); cout<<*(c.p)<<*(x->p);//55
   *(c.p)=6; cout<<*s(c.p)<<*(x->p);//66
   SmartP<C>*q=new SmartP<c>(&c);delete q;
   cout<<*(x->p)//6s
}

/* 
Definire un'unica gerarchia di classi che includa:

1) una classe base polimorfa A alla radice della gerarchia
2) una classe derivata astratta B
3) una sottoclasse C di B che sia concreta
4) una classe D che non permetta la costruzione pubblica
dei suoi oggetti, ma solamente la costruzione di oggetti di D
che siano sottooggetti
5)una classe E derivata direttamente da D e con l'assegnazione ridefinita
pubblicamente con comportamento identico a quello dell'assegnazione standard di E.*/

class A{
   public:
   virtual ~A();
};

class B: public A{
   virtual void method()=0;
};

class C: public B{
   virtual void method(){
      cout << "C redefines method "<<endl;
   }
};

class D;

class D{
   private:
   int d;
   public:
   D();
   D(int d1): d(d1){};
};

class E;

class E: public D{
   public:
   D d;
   E(): d(2){};
   E& operator=(const E& e1){
      if(this != &e1){
         *this = e1;
      }
      return *this;
   }
};