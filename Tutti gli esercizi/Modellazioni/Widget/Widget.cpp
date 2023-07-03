/*
Si consideri il seguente modello concernente alcune componenti di una libreria grafica. 

(A) Definire la seguente gerarchia di classi.

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
• un std::vector NoButtons di oggetti di tipo const Widget* che contiene tutti i widget di una Gui che non sono un pulsante. 
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
  bool visible;
public:
  virtual void setStandardSize() =0;

  Widget(unsigned int height=0, unsigned int width=0, bool vis =true):
    h(height), w(width), visible(vis) {}

  virtual ~Widget() =default;
  
  void setHeight(unsigned int height) {h=height;}
  void setWidth(unsigned int width) {w=width;}
};

#include<string>

class AbstractButton: public Widget {
private:
  std::string label;
public:
  AbstractButton(unsigned int height=0, unsigned int width=0, bool vis =true,
		 const std::string& l=nullptr): Widget(height,width,vis), label(l) {}
  
  std::string getLabel() const {return label;}
};

class PushButton: public AbstractButton {
public:
  static const unsigned int standardHeight = 80;
  static const unsigned int standardWidth = 20;

  void setStandardSize() override {
    setHeight(standardHeight); setWidth(standardWidth); 
  }
  
  PushButton(unsigned int height=standardHeight, unsigned int width= standardWidth,
	     bool vis =true, const std::string& l=nullptr): AbstractButton(height,width,vis,l) {}
};

class CheckBox: public AbstractButton {
private:
  bool checked;
public:
  static const unsigned int standardHeight = 5;
  static const unsigned int standardWidth = 5;

  void setStandardSize() override {
    setHeight(standardHeight); setWidth(standardWidth); 
  }

  CheckBox(unsigned int height=standardHeight, unsigned int width= standardWidth,
	   const std::string& l=nullptr, bool check=false):
    AbstractButton(height,width,true,l), checked(check) {}

  bool isChecked() const {return checked;}  
};

#include<vector> 
#include<list>

class Gui {
private:
  std::vector<const Widget*> NoButtons;
  std::list<const AbstractButton*> Buttons;
public:
  void insert(Widget* pw) {
    if(pw == nullptr) throw std::string("NoInsert");
    if(dynamic_cast<AbstractButton*>(pw) != nullptr)
      Buttons.push_back(static_cast<AbstractButton*>(pw));
    else NoButtons.push_back(pw);
  }
  
  void insert(unsigned int pos, PushButton& pb) {
    if(pos > Buttons.size()) throw std::string("NoInsert");
    auto it = Buttons.begin(); 
    for( ; pos>0; pos--, it++);
    Buttons.insert(it, &pb);
  }
  
  std::vector<AbstractButton*> removeUnchecked() {
    std::vector<AbstractButton*> v;
    CheckBox* p;
    for(auto it=Buttons.begin(); it!=Buttons.end(); ++it) {
      p=const_cast<CheckBox*>(dynamic_cast<const CheckBox*>(*it));
      if(p && !(p->isChecked())) {
	v.push_back(p);
	it=Buttons.erase(it); --it;
      }
    }
    return v;
  }
  
  void setStandardPushButton() {
    for(auto it = Buttons.begin(); it != Buttons.end(); ++it)
      if(dynamic_cast<const PushButton*>(*it) != nullptr && !((*it)->getLabel().empty()))
	 (const_cast<AbstractButton*>(*it))->setStandardSize();
  }
};

int main(){
  
}