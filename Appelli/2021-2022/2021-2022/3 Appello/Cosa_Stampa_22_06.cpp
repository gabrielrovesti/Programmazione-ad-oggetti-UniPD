#include<iostream>

using namespace std;

/*
Gerarchia:
        B
    /       \
    C        D      (virtuale - tratteggiato (convenzione di Ranzato) tra C e D)
    |       /
    |    /
    E
    |
    F
*/

class B{
	public:
		B() { cout<<" B() "; }
		virtual ~B() { cout<<" ~B() "; }
		virtual void f() { cout<<" B::f "; g(); j(); }
		virtual void g() const { cout<<" B::g "; }
		virtual const B* j() { cout<<" B::j "; return this; }
		virtual void k() { cout<<" B::k "; j(); m(); }
		void m() { cout<<" B::m "; g(); j(); }
		virtual B& n() { cout<<" B::n "; return *this; }
};
class C:virtual public B{
	public:
		C(){ cout<<" C() "; }
		~C(){ cout<<" ~C() "; }
		virtual void g() const override{ cout<<" C::g "; }
		void k() override{ cout<<" C::k "; j(); m(); }
		virtual void m(){ cout<<" C::m "; g(); j(); }
		B& n() override{ cout<<" C::n "; return *this; }
};
class D:virtual public B{
	public:
		D(){ cout<<" D() "; }
		~D(){ cout<<" ~D() "; }
		virtual void g(){ cout<<" D::g "; }
		const B* j(){ cout<<" D::j "; return this;}
		void k() const{ cout<<" D::k "; k(); }
		void m(){ cout<<" D::m "; g(); j(); }
};
class E:public C,public D{
	public:
		E(){ cout<<" E() "; }
		~E(){ cout<<" ~E() "; }
		virtual void g() const{ cout<<" E::g "; }
		const E* j(){ cout<<" E::j "; return this;}
		void m(){ cout<<" E::m "; g(); j(); }
		D& n() final{ cout<<" E::n "; return *this; }
};
class F:public E{
	public:
		F(){ cout<<" F() "; }
		~F(){ cout<<" ~F() "; }
		F(const F& x): B(x) {cout<<" Fc ";}
		void k() { cout<<" F::k "; g(); }
		void m() { cout<<" F::m "; j(); }
};

B* p1 = new E(); B* p2 = new C(); B* p3 = new D(); C* p4 = new E();
const B* p5 = new D(); const B* p6 = new E(); const B* p7 = new F(); F f;
//Nota sui costruttori:
//le stampe prendono ciascuno il tipo dinamico
//Es. -->  B()  C()  D()  E() - B* p1 = new E();

int main(){
	cout<<endl;
	cout<<"1) ";p4->f();cout<<endl;
	/*
	B::f  E::g  E::j 
	p4: tipo statico C, tipo dinamico E.
	Si cerca il tipo statico (B), dopodiché va in B e trova f() (1)
	poi deve chiamare g ed è virtuale, dunque chiamerà quello ridefinito
	dal tipo dinamico (E), in questo caso senza side-effects (const). (2)
	Similmente, deve chiamare j(). Il tipo che lui ha è un const B*,
	cosa che sussiste infatti dalla dichiarazione. Anche questo è virtuale
	e cercherà subito nel sottotipo, chiamando j di E (3).
	*/
    cout<<"2) ";(p4->n()).m();cout<<endl;
	/*
	E::n  B::m  E::g  E::j 
	Si ha una dereferenziazione su n e quindi cerca il tipo B dereferenziato (B&)
	nel tipo C, a sua volta ridefinito come final da E ed esegue la prima stampa (1).
	Si ha poi m() che non viene ridefinito e chiama quello di B (2), poi
	deve chiamare g() e j(). Per il primo, chiamerà il metodo ridefinito da E
	in quanto virtuale (3) e anche j, in quanto const B* come tipo statico.
	Essendo un const E* come tipo dinamico e non ridefinito, chiamerà E::j (4).
    */
	cout<<"3) ";p3->k();cout<<endl;
	/*
	B::k  D::j  B::m  B::g  D::j 
	p3: tipo statico B, tipo dinamico D.
	La prima chiamata si ha su k() che non viene ridefinito da d() e quindi
	è portato a chiamare B, in quanto è anche un const B*, implicitamente.
	Ora dovrà chiamare j(), che è virtuale e, come detto, abbiamo un const B*.
	Andrà, quindi, a chiamare il metodo j() di D (2).
	A questo punto, avremo il metodo m(), sempre non virtuale e chiama b::m (3).
	Chiamando g(), allora, chiamerà il primo metodo che vede e, quindi,
	chiamerà quello di B, dato che in D non viene ridefinito (4).
	Successivamente, dovrà chiamare j. Come detto, abbiamo un tipo statico B,
	implicitamente costante, in quanto il sottooggetto viene definito con lui da parte di D
	(D usa il costruttore di B). Quindi, essendo virtuale, si nota che la classe D
	ridefinisce il metodo ma con il const B* davanti, quindi correttamente
	chiama quello di D (5).
	Infatti, il metodo prevede "return". Quando ritorna, il puntatore è
	in realtà ridefinito dalla sottoclasse.
	*/
	cout<<"4) ";(p3->n()).m();cout<<endl;
	/*
	B::n  B::m  B::g  D::j
	Il primo metodo che chiama è n, dereferenziando p3, quindi chiamerà B
	e, se è ridefinito, andrà in D. In D non esiste n e chiamerà quella di B (1).
	Similmente, B non ridefinisce con virtual il metodo m(); chiamerà quello di B,
	anche perché l'operatore (.) (punto), si riferisce a p3, quindi B (2).
	A questo livello, dovrà chiamare un metodo g. Esso è virtuale anche in D, ma
	viene preferito quello di B perché non fa side effects (const) (3).
	Come visto finora, il tipo di p3 staticamente è B, ma implicitamente è come
	se fosse const. Quindi, richiamerà il metodo j() presente nella sottoclasse.
	Infatti, il metodo prevede "return". Quando ritorna, il puntatore è
	in realtà ridefinito dalla sottoclasse.
	*/
	cout<<"5) ";(dynamic_cast<D&>(p3->n())).g();cout<<endl;
	/*
	B::n  D::g 
	Si nota che il puntatore viene già castato (convertito) a D una volta
	dereferenziato, chiamando g(); si presume quindi che, quando deve chiamare g()
	chiamerà quello di D.
	Ad ogni modo, deve chiamare un metodo n che, come prima, non è presente in D
	e viene chiamato quello di B (1). Similmente, avremo che questa volta 
	la chiamata di g() prevede l'esecuzione grazie al cast di quello di D.
	Sarebbe portato a preferire per la mancanza di modifiche/side effects quello di B
	ma esiste la conversione esplicita.
	*/
	cout<<"6) ";p2->f();cout<<endl;
	/*
	B::f  C::g  B::j
	p2: tipo statico B, tipo dinamico C.
	Deve chiamare f(); esso non viene ridefinito da C e chiama quello di B (1).
	Si nota che il metodo g() è correttamente ridefinito come const con un override;
	ciò comporta la chiamata della sottoclasse rispetto alla superclasse B.
	Infatti, questo ridefinisce il comportamento di B (2).
	Infine, dovrà chiamare j, che non esiste in c ed è con un const B*, cosa
	che come visto finora è proprio B (3).
	*/
	cout<<"7) ";p2->m();cout<<endl;
	/*
	B::m  C::g  B::j
	Deve chiamare m(); esso non viene ridefinito da B con un virtual e chiama
	quello di B.
	Si nota che il metodo g() è correttamente ridefinito come const con un override;
	ciò comporta la chiamata della sottoclasse rispetto alla superclasse B.
	Infatti, questo ridefinisce il comportamento di B (2).
	Infine, dovrà chiamare j, che non esiste in c ed è con un const B*, cosa
	che come visto finora è proprio B (3).
	*/
	cout<<"8) ";(p2->j())->g();cout<<endl;
	/*
	B::j  C::g 
	Si deve chiamare j(); si dereferenzia e abbiamo un riferimento
	costante a B e, infatti, non essendo ridefinito in C chiama quello di B (1).
	Successivamente deve chiamare g() e si ha un'altra deferenziazione.
	Come prima, b è ben ridefinito virtuale nella sottoclasse C
	perché si ha la marcatura const corretta e override (uguale a virtual) (3).
	*/
	cout<<"9) ";//(p5->n()).g();//cout<<"NON COMPILA"<<endl;
	/*
	p5 = tipo statico const B*, tipo dinamico D.
	error: passing 'const B' as 'this' argument discards qualifiers [-fpermissive]
	Si nota che p5 è const; il fatto stesso della chiamata di N comporta che ci
	debba essere un metodo che lo ridefinisca const oppure debba essere const stesso
	quando è su B.
	Quindi, in questo caso, bisognerebbe avere il metodo const su B e quindi
	il compilatore capirebbe cosa e dove punta il riferimento costante.
	Di più a:
	https://stackoverflow.com/questions/26963510/error-passing-const-as-this-argument-of-discards-qualifiers
	*/
	cout<<"10) ";F x;cout<<endl;
	/*
	B()  C()  D()  E()  F() 
	Qui semplicemente si assiste alla chiamata dei costruttori
	per ordine di ereditarietà.
	F deriva da E, il quale deriva prima da D poi da C e infine usa
	la superclasse B.
	*/
	cout<<"11) ";C* p = new F(f);cout<<endl;
	/*
	C()  D()  E()  Fc
	Come visto, il tipo statico è C e il tipo dinamico è F;
	dato che "f" risulta essere una f, usa il costruttore
	di copia ridefinito e, in cascata, i costruttori.
	*/
	cout<<"12) ";p1->m();cout<<endl;
	/*
	B::m  E::g  E::j 
	p1: tipo statico B, tipo dinamico E.
	Come sempre, deve chiamare m, ma non è ridefinito da nessuno (1).
	Dovrà poi chiamare g(), correttamente ridefinito come const in E
	e chiama quello (2). Similmente, dovrà chiamare j, che ritorna un this.
	Questo this è un const E* e chiama j di E (3).
	*/
	cout<<"13) ";//(p1->j())->k();//cout<<"NON COMPILA"<<endl;
	/*
	error: passing 'const B' as 'this' argument discards qualifiers [-fpermissive]
	p1 è un B statico e, implicitamente, un const B. Il problema è che non 
	esiste un metodo const B* k che lo riceve; non compila.
	*/
	cout<<"14) ";//(dynamic_cast<const F*>(p1->j()))->g();//cout<<"ERRORE RUNTIME"<<endl;
	/*
	exited with code=3221225477 in 0.742 seconds
	"In both cases, the chars member of MyString is a pointer, and the constructors do nothing to initialise it, 
	let alone ensure it points at a valid area of memory, before copying data to it. 
	That gives undefined behavior."
	Il problema, qui, è che g() rende tutto un UB (undefine behaviour).
	Stiamo convertendo in un const F* p1, chiamando j(); chiamerebbe B.
	Poi, però, stiamo cercando di forzare la chiamata senza side effect di g
	verso E; non possiamo sapere se questo const F*, 
	sia correttamente definito, perché non c'è sempre certezza se sarà B o se sarà E.
	Quindi, comportamente indefinito.
	*/
	cout<<"15) ";//(dynamic_cast<E*>(p6))->j();//cout<<"NON COMPILA"<<endl;
	/*
	p6: tipo statico const B*, tipo dinamico E.
	error: cannot 'dynamic_cast' 'p6' (of type 'const class B*') to type 'class E*' (conversion casts away constness)
	Servirebbe un const cast dopo il dynamic cast per fare in modo possa essere
	chiamato il sottotipo E in modo safe.
	L'esercizio, quindi, richiede un cast in più per poter convertire in E.
	*/
	cout<<"16) ";(dynamic_cast<C*>(const_cast<B*>(p7)))->k();cout<<endl;
	/*
	F::k  E::g 
	p6: tipo statico const B*, tipo dinamico F.
	Qui viene fatto una cosa simile a quella che dovrebbe essere fatta a 15 e.
	essendo fatta correttamente (p6 è esplicitamente const B*),
	allora deve chiamare k(), che viene rifefinita solo da f() come virtuale di B,
	dato che tutte le superclassi hanno override o virtuale o non hanno il metodo.
	A cascata, quindi, chiama quello della sottoclasse.
	*/
	cout<<"17) ";delete p7;cout<<endl;
	/*
	~F()  ~E()  ~D()  ~C()  ~B() 
	P7 è come tipo dinamico F; pertanto, ordine dei distruttori
	al contrario della costruzione (da F a B).
	*/

	/*
	Distruzioni finali:  ~F()  ~E()  ~D()  ~C()  ~B()  ~F()  ~E()  ~D()  ~C()  ~B() 
	Le distruzioni avvengono nell'ordine inverso alle costruzioni.
	Esiste la variabile f di tipo F che viene cancellato; quindi abbiamo la prima serie di stampe:
	~F()  ~E()  ~D()  ~C()  ~B()
	Similmente, però, notiamo che esiste x di tipo F;
	quindi la stessa serie di stampe.
	*/
}

