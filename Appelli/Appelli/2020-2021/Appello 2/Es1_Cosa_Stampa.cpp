#include <iostream>
using namespace std;

class Z{
    public: Z(int x){}
};

class A{
    public:
    void f(int){cout << "A::f(int) " ; f(true);}
    virtual void f(bool){cout << "A::f(bool) ";}
    virtual A* f(Z){cout << "A::f(Z) "; f(2); return this;}
    A() {cout << "A() ";}
};

class B: virtual public A{
    public:
    void f(const bool&){cout << "B::f(const bool&) " ;}
    void f(const int&){cout << "B::f(const int&) " ;}
    virtual B* f(Z){cout << "B::f(Z) "; return this;}
    B() {cout << "B() ";}
    virtual ~B() {cout << "~B ";}
};

class C: virtual public A{
    public:
    C*f(Z) {cout << "C::f(Z) "; return this;}
    C() {cout << "C() "; }
};

class D:virtual public A{
    public:
    virtual void f(bool) const {cout << "D::f(bool) ";}
    A*f(Z) {cout << "D::f(Z) "; return this;}
    D() {cout << "D() ";}
    virtual ~D() {cout << "~D ";}
};

class E: public C{
    public:
    C*f(Z) {cout << "E::f(Z) "; return this;}
    E() {cout << "E() ";}
    ~E() {cout << "~E ";}
};

class F: public B, public E, public D{
    public:
    void f(bool) {cout << "F::f(bool) ";}
    F*f(Z) {cout << "F::f(Z) "; return this;}
    F() {cout << "F() "; }
    ~F() {cout << "~F ";}
};

int main(){
    B*pb1 = new F; B*pb2 = new B;
    C*pc = new C; E*pe = new E;
    A*pa1 = pc,*pa2 = pe,*pa3 = new F;
    cout << endl;

    /*
                Gerarchia:
                                        A
    (virtual public da A)       B       C       D   
                                    \   E   /
                                        |
    (F da B,E,D)                        F            

    (fuori dalla gerarchia di prima)    Z
    */

    /*
    Ordine di costruzione oggetti:
    A() B() C() E() D() F() A() B() A() C() A() C() E() A() B() C() E() D() F() 
    */

    pa3->f(3);                              cout<<endl;
    //A::f(int) F::f(bool)
    /*
    pa3 = tipo statico A, tipo dinamico F (sottotipo a runtime/esecuzione).
    Guardiamo in F; non c'è un metodo che prenda un intero.
    Su A sì, pertanto sapendo chiama A::f(int) (1).
    Deve chiamare un bool (f(true)) e il metodo f
    è virtuale in A; su F esiste e chiama quello di F (2).
    */
    
    pb1->f(true);                           cout<<endl;
    //B::f(const bool&) 
    /*
    pb1 = tipo statico B, tipo dinamico F (sottotipo a runtime/esecuzione).
    La classe B non mette virtual davanti a f(const bool &) e quindi
    non andiamo a vedere in F; chiamiamo quello di B (1).
    */
    pa2->f(true);                           cout<<endl;
    //A::f(bool) 
    /*
    pa2 = tipo statico A, tipo dinamico E (sottotipo a runtime/esecuzione).
    La classe E non presenta un metodo f(bool) tale da poter
    usare quello della sottoclasse (E appunto);
    lo possiede solo A e viene chiamato quello (1).
    */
    pa1->f(Z(2));                           cout<<endl;
    //C::f(Z) 
    /*
    pa1 = tipo statico A, tipo dinamico C (sottotipo a runtime/esecuzione).
    Stiamo chiamando Z(2), che sarebbe un intero e, in particolare,
    ci aspettiamo di trovare un metodo A* f(z) che corrisponda a questo.
    Esiste in A ed è marcato "virtual"; si va quindi a vedere
    se esiste in C. Il metodo è presente con la stessa firma e si sceglie
    quello di C (1).
    */
    (dynamic_cast<E*>(pa2))->f(Z(2));       cout<<endl;
    //E::f(Z) 
    /*
    pa2 = tipo statico A, tipo dinamico E (sottotipo a runtime/esecuzione).
    Ora forziamo esplicitamente la conversione ad E
    grazie al solito "dynamic_cast".
    Quindi, la chiamata di f(Z(2)), andrà in E 
    a cercarsi il metodo corrispondente e lo trova
    senza troppi problemi.
    */
    (dynamic_cast<C*>(pa3))->f(Z(2));       cout<<endl;
    //F::f(Z) 
    /*
    pa3 = tipo statico A, tipo dinamico F (sottotipo a runtime/esecuzione).
    Ora forziamo esplicitamente la conversione a C
    grazie al solito "dynamic_cast".
    Se non ci fosse "return this", lui si fermerebbe a C* f(Z),
    che è quello che fa match in C, ma esegue "return";
    questo vuol dire che il tipo di ritorno diventa F
    ed esegue la chiamata di F::f(Z), originando
    l'unica stampa (1).
    */
    pb2->f(3);                              cout<<endl;
    //B::f(const int&) 
    /*
    pb2 = tipo statico e dinamico B (sottotipo a runtime/esecuzione).
    Qua non ci sta pezza, guarda solo in B
    e cerca un metodo che prenda un intero.
    Questo metodo può essere solo:
    void f(const int&), che viene chiamato (1).
    */
    (pa2->f(Z(3)))->f(4);                   cout<<endl;
    //E::f(Z) A::f(int) A::f(bool) 
    /*
    pa2 = tipo statico A, tipo dinamico E (sottotipo a runtime/esecuzione).
    Cerchiamo un metodo intero costante per Z (che è un intero
    a tutti gli effetti) ed in A esiste il metodo
    A* f(Z) che è virtuale e quindi viene
    cercato in E, generando la prima stampa (1).
    Successivamente, il metodo invocato dalla prima
    deve chiamare f(4); esiste in A
    con "void f(int)" che non ha il virtual davanti
    e, pertanto, solo quello di A può essere chiamato (2).
    Similmente, dovremo chiamare f(true) e il metodo
    viene cercato in A. Ha il virtual davanti e lo
    cerchiamo in E. In E non è presente 
    e quindi viene chiamato quello di A (3).
    */
    (pc->f(Z(3)))->f(4);                    cout<<endl;
    //C::f(Z) C::f(Z) 
    /*
    pc = tipo statico e dinamico C (sottotipo a runtime/esecuzione).
    Cerchiamo solo in C, pertanto qui è easy.
    Vediamo se ci sta un metodo che matcha con f(z(3))
    in C ed esiste, cioè C* f(z), dando luogo alla 
    prima stampa (1). Successivamente, chiamiamo f(4).
    Come sempre, 4 è un intero e, di fatto Z
    è classe che costruisce solo interi, in questo caso,
    di tipo C.
    Chiamiamo lo stesso metodo di prima,
    dando luogo alla seconda stampa.
    */
    E*puntE = new F;                        cout<<endl;
    //A() B() C() E() D() F() 
    /*
    Stiamo costruendo un E che diventa F quando eseguito a runtime
    e quindi letteralmente segue l'ordine di costruzione della
    gerarchia sopra.
    Parte da F (1), che deriva, partendo da destra,
    da D (2), poi E (3).
    Esegue la chiamata di B perché, nell'ordine
    di discendenza da A, abbiamo B e C sullo stesso livello,
    ma per lo stesso ragionamento di sopra, si guarda da destra
    anche nella derivazione virtuale e viene chiamato
    prima C (4) e poi B (5), infine A (6) la superclasse.
    */
    delete pa3;                             cout<<endl;
    //Nulla
    /*
    Il programma non è concluso, quindi
    non partiamo a distruggere tutti gli oggetti presenti;
    nel caso di pa3, comunque, 
    l'ordine di distruzione è l'esatto opposto della creazione
    (dipende se nelle classi si ha la stampa esplicita
    del distruttore, come ad esempio:
    ~F() {cout << "~F() ";})
    Si nota che né in A né in C è presente la stampa;
    quindi, la distruzione sarebbe, se fosse stampata
    a seguito di "delete pa3", seguendo la 
    gerarchia al contrario:
    ~F ~D ~E ~B 
    */
    delete pb1;                             cout<<endl;
    //~F ~D ~E ~B 
    /*
    Qui le stampe vengono mostrate appunto perché usciamo
    dalla stessa classe e, seguendo il ragionamento
    appena mostrato, si hanno queste esatte stampe.
    */
}
