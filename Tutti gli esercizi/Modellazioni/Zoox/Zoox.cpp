/*
Si consideri il seguente modello di realtà concernente l'azienda Zoox 
che fornisce un servizio di immagazzinamento di abbigliamento. 
1. Definire la seguente gerarchia di classi. 

(a) Definire una classe Capo i cui oggetti 
rappresentano un capo di abbigliamento che  Zoox può immagazzinare. 
Ogni Capo è caratterizzato dal designer (rappresentabile mediante una semplice stringa) 
e dalla taglia. Dotare la classe Capo di opportuni costruttore/i. 

(b) Definire una classe TShirt derivata da capo i cui oggetti rappresentano 
un capo di abbigliamento di tipologia t-shirt. 
Ogni Tshirt è caratterizzata dall'avere la manica lunga o corta. 
Dotare la classe rshirt di opportuni costruttore/i. 

(c) Definire una classe Jeans derivata da capo i cui oggetti 
rappresentano un capo di abbigliamento di tipologia jeans. 
Ogni Jeans è caratterizzato dalla larghezza del fondo in cm. 
Dotare la classe Jeans di opportuni costruttore/i. 

2. Definite una classe Zoox i cui oggetti rappresentano 
un magazzino di Zoox®. Più precisamente, un oggetto Zoox è caratterizzato 
dai capi di abbigliamento presenti nel magazzino, che sono rappresentati mediante 
un opportuno contenitore di puntatori al tipo capo. 
Naturalmente, il magazzino dovra poter contenere più articoli di uno stesso capo: 
ad esempio tre articoli dello stesso jeans di marca Diesel, taglia 48 e con larghezza del fondo 18 cm. 
Devon essere disponibili le seguenti funzionalita: 

(a) un metodo int giacenza (const Capo&) con il seguente comportamento: 
una invocazione z.giacenza (c) ritorna il numero di articoli del capo di abbigliamento c presenti nel magazzino Zoox z. 

(b) un metodo vector<Jeans> getJeans (string, int, double) con il seguente comportamento: 
una invocazione z.getJeans(marca, size, x) ritorna un vector (eventualmente vuoto) 
contenente una copia di tutti i jeans presenti nel magazzino Zoox z il cui designer
è uguale a marca, di taglia size e che hanno una larghezza del fondo > a x cm. 

(c) un metodo void scar ica (const TShirt*) con il seguente comportamento: 
una invocazione z.scarica (pt) elimina dal magazzino Zoox z un articolo della t-shirt *pt 
se *pt è presente nel magazzino in almeno un articolo; 
altrimenti viene sollevata una eccezione Exc ("assente"). 
Exc è una classe di eccezioni da definire alto scopo. 

(d) un metodo void insert (const Tshirt&, int) con il seguente comportamento: 
una invocazione z. insert(t, num) aggiunge al magazzino Zoox® z un numero num di articoli 
della t-shirt t se it magazzino non contiene già una t-shirt a manica lunge 
dello stesso designer di t; altrimenti, viene sollevata una eccezione Exc ("presente"). 

*/

#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

class Capo{
    private:
        string brand;
        int taglia;
    public:
        Capo(string b = "noBrand", int t = 40) : brand(b), taglia(t){ }
        virtual ~Capo() =0; //distr virt puro
        virtual bool operator==(const Capo& c) const{
        return brand == c.brand && taglia == c.taglia;
        }
        string getBrand() const{ return brand; }
};

class Jeans : public Capo{
    private:
        int fondo;
    public:
        Jeans(string b = "noBrand", int t = 40, int f = 20) : Capo(b,t), fondo(f){ }
        virtual bool operator==(const Capo& c) const{
            return typeid(const Jeans&) == typeid(c) && Capo::operator==(c) &&
            fondo == (static_cast<const Jeans&>(c)).fondo;
        }
        int getFondo() const{ return fondo; }
};

class Tshirt : public Capo{
    private:
        bool corta;
    public:
        Tshirt(string b = "noBrand", int t = 40, bool c = true) : Capo(b,t), corta(c){ }
        virtual bool operator==(const Capo& c) const{
            return typeid(const Tshirt&) == typeid(c) && Capo::operator==(c) &&
            corta == (static_cast<const Tshirt&>(c)).corta;
        }
        bool getManicaL() const{ return !corta; }
};

class Articolo{
    friend class Zoox;
    private:
        Capo* c; //puntatore polimorfo
        int q; //num art presenti in magazzino
    public:
        Articolo(Capo* pc, int x = 1) : c(pc), q(x){}
        int getQuantita() const{ return q; }
        void scarica(){
        if(q>1){ --q; return; }
    else delete c;
    }
    bool uguale(const Capo& c) const{
        return *(this -> c) == c;
    } 
};

class Exception{
    public:
        Exception(string s = ""){ cout << s << endl; }
};

class Zoox{ //classe contenitore
    private:
        list<Articolo> mag;
    public:
        int giacenza(const Capo& c) const{
            list<Articolo> :: const_iterator it; 
            for(it = mag.begin(); it != mag.end(); ++it)
            if(it -> uguale(c)) return it -> getQuantita();
            return 0;
        }
        vector<Jeans> getJeans(string m, int s, int f) const{
            vector<Jeans> v;
            list<Articolo>::const_iterator it;
            for(it = mag.begin(); it != mag.end(); ++it){
                Jeans* p = dynamic_cast<Jeans*>(it->c);
                if(p && Jeans(m,s).Capo::operator==(*(it->c)) && p -> getFondo() >= f)
                v.push_back(*p);
            }
            return v;
        }
        void scarica(const Tshirt* pt){
            list<Articolo> :: iterator it;
            for(it = mag.begin(); it != mag.end(); ++it){
                if(it -> uguale(*pt)){
                    it -> scarica();
                    mag.erase(it);
                    return;
                }
            }
            throw Exception("assente");
        }
        void insert(const Tshirt& t, int x){
            list<Articolo> :: const_iterator it;
            for(it = mag.begin(); it != mag.end(); ++it)
            if(typeid(*(it -> c)) == typeid(Tshirt)){
                Tshirt* p = static_cast<Tshirt*>(it -> c);
                if(p->getManicaL() && t.getBrand() == p -> getBrand())
                    throw Exception("presente");
                }
            mag.push_front(Articolo(const_cast<Tshirt*>(&t), x));
        }
};

