// ESERCIZIO FUNZIONE

/*
Si assumano le seguenti specifiche riguardanti la libreria Qt.

– Un oggetto della classe QString rappresenta una stringa di caratteri Unicode. La classe QString fornisce un costruttore QString(const char*) con il seguente comportamento: QString(str) costruisce una QString inizializzata con la stringa ASCII str.

– La classe QPaintDevice e` la classe base di tutti gli oggetti che possono essere “dipinti” sullo schermo.
• La classe QPaintDevice e` polimorfa.
• La classe QPaintDevice rende disponibile un metodo int height() const con il seguente comportamento: pd.height() ritorna l’altezza in pixel del QPaintDevice pd. E inoltre disponibile un metodo
int width() constconanalogocomportamentoperlalarghezza.

– QWidget e` una sottoclasse di QPaintDevice i cui oggetti rappresentano delle componenti di una interfaccia grafica Qt.
• La classe QWidget rende disponibile un metodo bool hasFocus() const con il seguente comportamento: w.hasFocus() ritorna true quando la componente w detiene il keyboard focus.
• La classe QWidget rende disponibile un metodo void clearFocus() con il seguente comportamento: w.clearFocus() toglie il keyboard focus alla QWidget w.

– QAbstractButton e` derivata direttamente da QWidget ed e` la classe base astratta dei widget pulsante.
• LaclasseQAbstractButtonrendedisponibileunmetodovoid setText(const QString&)conilseguentecomportamen-
to: b.setText(s) setta l’etichetta testuale del QAbstractButton b alla stringa s. 

Definire una funzione 
vector<QWidget> fun(const vector<QPaintDevice*>&) 
con il seguente comportamento: in ogni invocazione fun(v):

1. per ogni puntatore p contenuto nel vector v:

– se p punta ad un oggetto che e` un QWidget con altezza o larghezza > a 50 pixel allora lancia una eccezione di tipo QString
che rappresenta la stringa “TooBig”;

– se p punta ad un oggetto obj che e` un QWidget avente sia l’altezza che la larghezza ≤ a 50 pixel e che detiene il keyboard focus
allora toglie il keyboard focus a obj;

– se p punta ad un oggetto obj che e` un QAbstractButton allora setta l’etichetta testuale di obj alla stringa “Pulsante”.

2. l’invocazione fun(v) deve ritornare un vector contenente tutti e soli gli oggetti puntati da un  puntatore p contenuti nel vector v che puntano ad un QWidget che non e' e` un QAbstractButton.
*/

std::vector<QWidget> fun(const std::vector<const QPaintDevice*>& v) {
  std::vector<QWidget> w;
    for(auto cit = v.begin(); cit != v.end(); ++cit) {
    QWidget* qw = dynamic_cast<QWidget*>( const_cast<QPaintDevice*>(*cit) );
    QAbstractButton* qab = dynamic_cast<QAbstractButton*>(const_cast<QPaintDevice*>(*cit));
    if(qw){
      if(qw->height() > 50) throw QString("TooBig");
    // qw->height() <= 50
    if(qw->hasFocus()) qw->clearFocus();
    if(!qab) w.push_back(*qw);
    }
    if(qab) qab->setText("Pulsante");
  }
  return w;
}

// ESERCIZIO OPERATORI/COSTRUTTORI

/*
     A
    . .
   .   .
   C   E
   |   |
   D   |
    \ /
     F
 */


#include<iostream>
using namespace std;

class Z {private: int x;};        

class A {
private:
  Z az;
};

class C: virtual public A {
private:
  Z cz;
};

class D: public C {
};

class E: virtual public A {
public:
  Z ez;
  E& operator=(const E& x) {
    A::operator=(x);
    ez=x.ez;
    return *this;
  }
}

class F: public D, public E {
private:
  Z* fz;
public:
  F(const F& f): A(f), D(f), E(f), fz(f.fz == nullptr ? nullptr : new Z(*f.fz)) {}

  ~F() {delete fz;}

  virtual F* clone() const {return new F(*this);}

  F& operator=(const F& x) {
    A::operator=(x);
    D::operator=(x);
    E::operator=(x);
    fz = x.fz;
    return *this;
  }
};

/*
(1) Ridefinire l’assegnazione della classe E in modo tale che il suo comportamento coincida con quello dell’assegnazione standard di E. Naturalmente non e` permesso l’uso della keyword default.
(2) Ridefinire il costruttore di copia profonda della classe F.
(3) Ridefinire il distruttore profondo della classe F.
(4) Definire il metodo di clonazione della classe F.
*/

// ESERCIZIO GERARCHIA

/*
Si consideri il seguente modello concernente alcune componenti di una libreria grafica. (A) Definire la seguente gerarchia di classi.

1. Definire una classe base astratta Widget i cui oggetti rappresentano un generico componente (un cosiddetto widget) di una Gui. Ogni Widget e` caratterizzato da larghezza e altezza in pixels, e dall’essere visibile o meno.
• Widget e` astratta in quanto prevede il metodo virtuale puro void setStandardSize() che deve garantire il seguente contratto: w->setStandardSize() imposta la dimensione larghezza×altezza definita come standard per il widget *w.
• Widget rende disponibile almeno un opportuno costruttore per impostare le caratteristiche dei widget.

2. Definire una classe AbstractButton derivata da Widget i cui oggetti rappresentano un generico componente pulsante. Ogni oggetto
AbstractButton e` caratterizzato dalla stringa che etichetta il pulsante.
• AbstractButton rende disponibile almeno un opportuno costruttore per impostare le caratteristiche dei pulsanti.

3. Definire una classe PushButton derivata da AbstractButton i cui oggetti rappresentano un pulsante clickabile.
• PushButton implementa il metodo virtuale puro setStandardSize() come segue: per ogni puntatore p a PushButton,
p->setStandardSize() imposta la dimensione standard 80×20 per il pulsante clickabile *p.
• PushButton rende disponibile almeno un opportuno costruttore per impostare le caratteristiche dei pulsanti clickabili.

4. Definire una classe CheckBox derivata da AbstractButton i cui oggetti rappresentano un pulsante checkabile. Ogni oggetto CheckBox e` caratterizzato dall’essere nello stato “checked” o “unchecked”; inoltre, tutti gli oggetti CheckBox sono sempre visibili.
• CheckBox implementa il metodo virtuale puro setStandardSize() come segue: per ogni puntatore p a CheckBox, p->setStandardSize() imposta la dimensione standard 5×5 per il pulsante checkabile *p.
• CheckBox rende disponibile almeno un opportuno costruttore per impostare le caratteristiche dei pulsanti checkabili.

(B) Definire una classe Gui i cui oggetti rappresentano le componenti di una Gui. Un oggetto Gui e` caratterizzato da:
• un std::vector NoButtons di oggetti di tipo const Widget* che contiene tutte i widget di una Gui che non sono un pulsante. 
• una std::list Buttons di oggetti di tipo const AbstractButton* che contiene tutte i widget di una Gui che sono un pulsante. La classe Gui rende disponibili i seguenti metodi:

1. Un metodo void insert(Widget*) con il seguente comportamento: in una invocazione g.insert(p), se p e` nullo allora viene sollevata l’eccezione “NoInsert” di tipo string; altrimenti, viene inserito il widget *p nella Gui g.

2. Un metodo void insert(unsigned int, PushButton&) con il seguente comportamento: in una invocazione g.insert(pos,pb), se pos e` un indice valido della lista Buttons della Gui g allora inserisce il puntatore a pb nella posizione pos della lista Buttons; se invece pos non e` un indice valido allora viene sollevata l’eccezione “NoInsert” di tipo string. Si ricorda che, come per tutti i contenitori, gli indici validi per una lista vanno da 0 al numero di elementi contenuti nella lista: quindi, l’indice 0 significa inserimento
in testa, mentre un indice uguale al numero di elementi contenuti significa inserimento in coda.

3. Un metodo vector<AbstractButton*> removeUnchecked() con il seguente comportamento: una invocazione g.removeUnchecked() rimuove dalla Gui g tutti i pulsanti checkabili che sono nello stato “unchecked”, e ritorna tutti i pulsanti checkabili rimossi in un vector di AbstractButton*.

4. Un metodo void setStandardPushButton() con il seguente comportamento: una invocazione g.setStandardPushButton() imposta alla dimensione standard tutti i pulsanti clickabili contenuti nella Gui g aventi etichetta diversa dalla stringa vuota.
*/

class Widget {
private:
  unsigned int h,w;
  bool isVisible;
public:
  Widget(unsigned int x=0, unsigned int y=0, bool v=true): h(x), w(y), isVisible(v) {}

  virtual void setStandardSize()=0;
  
  void setWidth(unsigned int x) {w=x;}
  void setHeight(unsigned int x) {h=x;}  
};

class AbstractButton: public Widget { // classe astratta
private:
  std::string t;
public:
  AbstractButton(unsigned int x=0, unsigned int y=0, bool v=true,
		 std::string s = ""): Widget(x,y,v), t(s) {}
};

class PushButton: public AbstractButton { // concreta
public:
  static const unsigned int standardWidth;
  static const unsigned int standardHeight;

  PushButton(unsigned int x=standardWidth, unsigned int y= standardHeight,
	     bool v=true, std::string s = ""): AbstractButton(x,y,v,s) {}

  void setStandardSize() override {
    setWidth(standardWidth); setHeight(standardHeight);
  }
};
const unsigned int PushButton::standardWidth = 80;
const unsigned int PushButton::standardHeight = 20;

class CheckBox: public AbstractButton {
private:
  bool isChecked;
public:
  static const unsigned int standardWidth;
  static const unsigned int standardHeight;
  
  CheckBox(unsigned int x=standardWidth, unsigned int y= standardHeight,
	   std::string s = ""): AbstractButton(x,y,true,s) {}  
  
  void setStandardSize() override {
    setWidth(standardWidth); setHeight(standardHeight);
  }
};
const unsigned int CheckBox::standardWidth = 5;
const unsigned int CheckBox::standardHeight = 5;

class Gui {
private:
  std::vector<const Widget*> NoButtons;
  std::list<const AbstractButton*> Buttons;
public:

  void insert(Widget* p) {
    if(!p) throw std::string("NoInsert");
    // p != nullptr
    if(dynamic_cast<AbstractButton*>(p))
      Buttons.push_back(static_cast<const AbstractButton*>(p));
    else NoButtons.push_back(p);
  }
};
