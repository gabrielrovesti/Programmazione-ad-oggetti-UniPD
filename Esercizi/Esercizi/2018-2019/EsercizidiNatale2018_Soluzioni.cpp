/*
Esercizio 1

Si consideri il seguente modello di realta concernente l’app InForma per archiviare allenamenti sportivi. `
(A) Definire la seguente gerarchia di classi.
1. Definire una classe base polimorfa astratta Workout i cui oggetti rappresentano un allenamento (workout) archiviabile in InForma. Ogni
Workout e caratterizzato dalla durata temporale espressa in minuti. La classe ` e astratta in quanto prevede i seguenti ` metodi virtuali puri:
• un metodo di “clonazione”: Workout* clone().
• un metodo int calorie() con il seguente contratto puro: w->calorie() ritorna il numero di calorie consumate durante l’allenamento *w.
2. Definire una classe concreta Corsa derivata da Workout i cui oggetti rappresentano un allenamento di corsa. Ogni oggetto Corsa e`
caratterizzato dalla distanza percorsa espressa in Km. La classe Corsa implementa i metodi virtuali puri di Workout come segue:
• implementazione della clonazione standard per la classe Corsa.
• per ogni puntatore p a Corsa, p->calorie() ritorna il numero di calorie dato dalla formula 500K2/D, dove K e la distanza percorsa `
in Km nell’allenamento *p e D e la durata in minuti dell’allenamento ` *p.
3. Definire una classe astratta Nuoto derivata da Workout i cui oggetti rappresentano un generico allenamento di nuoto che non specifica lo
stile di nuoto. Ogni oggetto Nuoto e caratterizzato dal numero di vasche nuotate. `
4. Definire una classe concreta StileLibero derivata da Nuoto i cui oggetti rappresentano un allenamento di nuoto a stile libero. La classe
StileLibero implementa i metodi virtuali puri di Nuoto come segue:
• implementazione della clonazione standard per la classe StileLibero.
• per ogni puntatore p a StileLibero, p->calorie() ritorna il seguente numero di calorie: se D e la durata in minuti dell’allena- `
mento *p e V e il numero di vasche nuotate nell’allenamento ` *p allora quando D < 10 le calorie sono 35V , mentre se D 
*/

#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
using namespace std;

class Workout{
private:
    double durata;

public:
    double getDurata() const {return durata;}
    virtual Workout* clone() const =0;
    virtual int calorie() const =0;
};

class Corsa: public Workout{
private:
    double distanza; //km

public:
    double getDistanza() const {return distanza;}
    virtual Workout* clone() const {
        return new Corsa(*this);
    }
    virtual int calorie() const {
        return (500*(distanza*distanza)/getDurata());
    }

};

class Nuoto: public Workout{
private:
    int numVasche;

public:
    int getNumVasche() const {return numVasche;}
};

class StileLibero: public Nuoto{
public:
    virtual Workout* clone() const {
        return new StileLibero(*this);
    }
    virtual int calorie() const {
        if(getDurata()<10)
            return 35*getNumVasche();
        else
            return 40*getNumVasche();
    }
};

class Dorso: public Nuoto{
public:
    virtual Workout* clone() const {
        return new Dorso(*this);
    }
    virtual int calorie() const {
        if(getDurata()<15)
            return 30*getNumVasche();
        else
            return 35*getNumVasche();
    }
};

class Rana: public Nuoto{
public:
    virtual Workout* clone() const {
        return new Rana(*this);
    }
    virtual int calorie() const {
        return 25*getNumVasche();
    }
};

class Informa{
private:
    vector<const Workout*> allenamenti;

public:
    vector<Nuoto*> vasche(int v) const {
        vector<Nuoto*> aux;
        for(vector<const Workout*>::const_iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Nuoto* p=dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(p && p->getNumVasche()>v)
                aux.push_back(p);
        }
        return aux;
    }

    vector<Workout*> calorie(int x) const {
        vector<Workout*> aux;
        for(vector<const Workout*>::const_iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Rana* p=dynamic_cast<Rana*>(const_cast<Workout*>(*it));
            if(!p && (*it)->calorie()>x)
                aux.push_back((*it)->clone());
        }
        return aux;
    }

    void removeNuoto(){
        double max=0;
        bool trovato=false;
        for(vector<const Workout*>::iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            if((*it)->calorie()>max)
                max=(*it)->calorie();
        }

        for(vector<const Workout*>::iterator it=allenamenti.begin(); it!=allenamenti.end(); ++it){
            Nuoto* p=dynamic_cast<Nuoto*>(const_cast<Workout*>(*it));
            if(p && p->calorie()==max){
                trovato=true;
                delete p;
                it=allenamenti.erase(it);
            }
        }
    }
};

int main(){}

//Esercizio 2 

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

int main()
{
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
( static_cast<B*>(p3->n()))->g(); cout << endl;

    return 0;
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


//Esercizio 3
#include<string>
#include<vector>
using std::string;
using std::vector;

/*
A) Definire una classe di eccezioni Anomalia che rende disponibile un costruttore Anomalia(char) con il seguente comportamento:
Anomalia(’v’) costruisce una eccezione che rappresenta una anomalia relativa al traffico voce; Anomalia(’d’) costruisce una eccezione che
rappresenta una anomalia relativa al traffico dati; Anomalia(’s’) costruisce una eccezione che rappresenta una anomalia relativa al traffico sms;
Anomalia(’c’) costruisce una eccezione che rappresenta una anomalia relativa all’addebito di un costo.
(B) Definire la seguente gerarchia di classi.
1. Definire una classe base astratta Scheda i cui oggetti rappresentano una scheda SIM ricaricabile gestita da P2. Ogni Scheda e caratterizzata `
da: un numero telefono che si suppone essere univoco e rappresentato mediante una stringa (non sono richiesti controlli di univocita e `
consistenza della stringa); il credito residuo in euro, che non puo quindi essere negativo; il costo in ` e di spedizione di un sms.
• La classe Scheda e astratta in quanto prevede i seguenti metodi virtuali puri: `
– un metodo void telefonata(unsigned int) con il seguente contratto puro: s->telefonata(n) contabilizza sulla scheda
*s una telefonata di durata n secondi; se lo stato del piano della scheda *s non permette una telefonata di n secondi allora viene
sollevata una eccezione Anomalia(’v’).
– un metodo void connessione(double) con il seguente contratto puro: s->connessione(k) contabilizza sulla scheda *s
una connessione di k MB; se lo stato del piano della scheda *s non permette una connessione di k MB allora viene sollevata una
eccezione Anomalia(’d’).
• La classe Scheda rende disponibile un metodo void messaggioSMS(unsigned int) con il seguente comportamento: per tutti i
sottotipi di Scheda, s->messaggioSMS(k) contabilizza sulla scheda *s l’invio di k messaggi sms scalando dal credito disponibile
su *s il costo di spedizione di un sms per ognuno dei k messaggi sms; se il costo dell’invio dei k messaggi sms eccede il credito
disponibile su *s allora viene sollevata una eccezione Anomalia(’s’).
2. Definire una classe concreta Mensile derivata da Scheda i cui oggetti rappresentano una scheda SIM ricaricabile con piano di tariffazione
ad abbonamento mensile per telefonate e connessioni. Ogni oggetto Mensile e quindi caratterizzato da: una soglia mensile di secondi di `
telefonate incluse; il traffico totale di secondi di telefonate effettuate nel mese corrente; una soglia mensile di MB di connessioni incluse;
il traffico totale di MB di connessioni effettuate nel mese corrente; il costo mensile di abbonamento. La classe Mensile rende disponibile
un costruttore di default che costruisce un piano ad abbonamento mensile con le seguenti caratteristiche: numero di telefono "0", credito
residuo 0 e, costo di spedizione di un sms 0.1 e, soglia mensile di telefonate 60000 secondi, soglia mensile di connessioni 2096 MB.
La classe Mensile implementa i metodi virtuali puri di Scheda come segue:
• per ogni puntatore m a Mensile, m->telefonata(n) aggiunge n secondi al traffico totale delle telefonate del mese corrente della
scheda *m, e se questa telefonata provoca il superamento della soglia mensile di telefonate della scheda *m, allora viene sollevata una
eccezione Anomalia(’v’).
• per ogni puntatore m a Mensile, m->connessione(k) aggiunge k MB al traffico totale delle connessioni del mese corrente della
scheda *m, e se questa connessione provoca il superamento della soglia mensile di connessioni della scheda *m, allora viene sollevata
una eccezione Anomalia(’d’).
3. Definire una classe concreta Consumo derivata da Scheda i cui oggetti rappresentano una scheda SIM ricaricabile con piano di tariffazione
a consumo per telefonate e connessioni. Ogni oggetto Consumo e quindi caratterizzato da: il costo in ` e di 1 secondo di telefonata; il costo
in e di 1 MB di connessione. La classe Consumo rende disponibile un costruttore di default che costruisce un piano a consumo di default
con le seguenti caratteristiche: numero di telefono "0", credito residuo 0 e, costo di spedizione di un sms 0.2 e, costo di 1 secondo di
telefonata 0.01 e, costo di 1 MB di connessione 0.1 e.
La classe Consumo implementa i metodi virtuali puri di Scheda come segue:
• per ogni puntatore c a Consumo, c->telefonata(n) addebita n secondi di telefonata sul credito residuo della scheda *c, e se questo
addebito provoca il superamento del credito residuo allora viene sollevata una eccezione Anomalia(’v’).
• per ogni puntatore c a Mensile, m->connessione(k) addebita k MB di connessione sul credito residuo della scheda *c, e se questo
addebito provoca il superamento del credito residuo allora viene sollevata una eccezione Anomalia(’d’).
(C) Definire una classe P2 i cui oggetti rappresentano un centro di gestione di schede SIM ricaricabili di P2. Un oggetto di P2 e caratterizzato da `
un contenitore di elementi di tipo Scheda* che memorizza tutte le schede SIM gestite dal centro. La classe P2 definisce i seguenti metodi:
1. Un metodo Consumo* cambioPiano(std::string) con il seguente comportamento: in una invocazione p2.cambioPiano("num"),
se il numero di telefono "num" e gestito dal centro ` p2 e corrisponde ad una scheda SIM ricaricabile con piano di tariffazione ad abbonamento
mensile allora cambia il piano di tariffazione tramutandolo in un piano di tariffazione a consumo di default che mantiene lo stesso numero
"num" e preserva il credito residuo; se l’invocazione p2.cambioPiano("num") effettivamente provoca il cambio di piano allora viene
ritornato un puntatore al nuovo piano di tariffazione a consumo, altrimenti viene ritornato il puntatore nullo.
2. Un metodo vector<Consumo> rimuoviConsumoZero() con il seguente comportamento: una invocazione p2.rimuoviConsumoZero()
rimuove dalle schede SIM gestite dal centro p2 tutte le schede con piano di tariffazione a consumo che hanno un credito residuo pari a 0 e,
e restituisce una vettore contenente una copia di tutte le schede con piano di tariffazione a consumo rimosse.
3. Un metodo double contabilizza() con il seguente comportamento: una invocazione p2.contabilizza() provoca la contabilizzazione in tutte le schede SIM gestite dal centro p2 con credito residuo positivo di una telefonata di 1 secondo, di una connessione di 1 MB
e dell’invio di 1 sms, e restituisce il guadagno ottenuto dal centro p2 mediante questa contabilizzazione (cioe la differenza del totale dei `
crediti residui di tutte le schede prima e dopo questa contabilizzazione)
*/


/* Punto A */

class Anomalia{
private:
    char codiceTipo;
    
public:
    Anomalia(char c) : codiceTipo(c){}
    char getCodice() const {
        return codiceTipo;
    }//getCodice.
}; // Anomalia.


/* Punto B */

class Scheda{
private:
    string numTel;
    double credito;
    double costoSMS;
    
public:
    // metodi virtuali puri.
    virtual void telefonata(unsigned int) =0;
    virtual void connessione(double) =0;
    
    // costruttore.
    Scheda(string s=0, double c=0, double sms=0) : numTel(s), credito(c), costoSMS(sms) {
        if(credito < 0){
            credito=0;
        }//if.
    }// costruttore scheda.
    
    // Metodi Get.
    string getNumTel() const {
        return numTel;
    }//getNumTel.
    
    double getCredito() const {
        return credito;
    }//getCredito.
    
    double getCostoSMS() const {
        return costoSMS;
    }//getCostoSMS.
    
    // Metodo messaggioSMS.
    void messaggioSMS(unsigned int k){
        if(credito >= (k*costoSMS)){
            credito=credito-(k*costoSMS);
        }//if.
        else{
            throw Anomalia('s');
        }//else.
    }//messaggioSMS.
    
    // Metodo Addebita.
    void addebita(double c){
        credito=credito-c;
    }//addebita.
    
    
    // Distruttore virtuale
    virtual ~Scheda() {}
}; // Scheda.


class Mensile : public Scheda {
private:
    const unsigned int sogliaSec; // const discutibile, perché se il piano cambiasse cambiando soglia non si potrebbe più cambiare la soglia.
    unsigned int currentSec;
    const double sogliaMB;
    double currentMB;
    
    const double costoMensile;
    
    Mensile(string nT="0", double cred=0, double costSMS=0.1, const unsigned int soglSec=60000, const double soglMB=2096, cM=10): Scheda(nT,cred, costSMS), sogliaSec(soglSec), sogliaMB(soglMB), costoMensile(cM), currentSec(0), currentMB(0){}
    
    // implementazione metodo virtuale puro telefonata.
    virtual void telefonata(unsigned int n){
        if((n+currentSec) <= sogliaSec ){
            currentSec=currentSec+n;
        }//if.
        else{
            throw Anomalia('v');
        }//else.
    }//telefonata.
    
    //implementazione metodo virtuale puro connessione.
    virtual void connessione(double k){
        if((k+currentMB) <= sogliaMB){
            currentMB=currentMB+k;
        }//if.
        else{
            throw Anomalia('d');
        }//else.
    }//connessione.
    
}; // Mensile.


class Consumo : public Scheda {
private:
    const double costoSecTel;
    const double costoMB;
    
public:
    // Costruttore di default.
    Consumo(string nT="0", double cred=0, double costSMS=0.2, const double cST=0.01, const double cMB=0.2 ): Scheda(nT,cred, costSMS), costoSecTel(cST), costoMB(cMB) {}
    
    virtual void telefonata(unsigned int n){
        if(n*costoSecTel > getCredito())
            throw Anomalia('v');
        else
            addebita(n*costoSecTel);
    }//telefonata.
    
    virtual void connessione(double k){
        if(n*costoMB > getCredito())
            throw Anomalia('d');
        else
            addebita(n*costoMB);
    }//connessione.
    
}; // Consumo.


/* Punto C */

class P2{
private:
    vector<Scheda*> vs;
    
public:
    // Metodo 1.
    Consumo* cambioPiano(string num){
        bool trovato=false;
        vector<Scheda*>::iterator it=vs.begin();
        
        // scorro tutto il vector finché non lo trovo.
        for(; it<vs.end() && !trovato; ++it){
            if((*it).getNumTel() == num){
                trovato=true;
            }//if.
        }//for.
        
        it--; // riporto l'iteratore alla posizione corretta.
        
        if(!trovato || !(dynamic_cast<Mensile*>(it))){
            return 0;
        }//if.
        else{
            Consumo* p=new Consumo((*it).getNumTel(), (*it).getCredito());
            delete *it; // Elimino il vecchio Mensile.
            *it=p; // Aggiungo il nuovo Consumo
            return p;
        }//else.
        
    }//cambioPiano.

    
    // Metodo 2.
    vector<Consumo> rimuoviConsumoZero(){
        vector<Consumo> aux;
        
        for(vector<Consumo>::iterator it=vs.begin(); it<vs.end(); ++it){
           
            if((*it)->getCredito()==0){
                Consumo* q=dynamic_cast<Consumo>((*it));
                
                if(q){
                    aux.push_back(Consumo(*q)); // utilizzo il costruttore di copia.
                    delete q; // elimino per non tenere memoria occupata.
                    it=vs.erase(it); // elimino la entry dal mio gestore.
                    it--; // ritorno alla posizione precedente dopo aver fatto l'erase.
                }//if.
            }//if.
            
        }//for.
        
        return aux;
        
    }//rimuoviConsumoZero.
    
    // Metodo 3.
    double contabilizza(){
        double totprima=0, totdopo=0;
        
        for(vector<Scheda*>::iterator it=vs.begin(); it<vs.end() && (*it)->getCredito()>0; ++it ){
            totprima=totprima+(*it)->getCredito();
            
            (*it)->telefonata(1);
            (*it)->messaggioSMS(1);
            (*it)->connessione(1);
            
            totdopo=totdopo+(*it)->getCredito();
        }//for.
        
        return totprima-totdopo;
        
    }//contabilizza.
    
}; //P2.

//Esercizio 4
#include <iostream>

using namespace std;
class A { 
    protected:
    virtual void j() { cout<<" A::j ";}; 
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
    A* n() override { cout <<" B::n "; return this;}
}; 

class C: public A{
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


int main()
{
p1->g(); cout << endl;
p1->k(); cout << endl;
p2->f(); cout << endl;
p2->m(); cout << endl;
p3->k(); cout << endl;
p3->f(); cout << endl;
p4->m(); cout << endl;
p4->k(); cout << endl;
p5->g(); cout << endl;
(p3->n())->m(); cout << endl;
(p3->n())->n()->g(); cout << endl;
(p4->n())->m(); cout << endl;
//(p5->n())->g(); cout << endl;
(dynamic_cast<B*>(p1))->m();
//(static_cast<C*>(p2))->k(); loop infinito
(static_cast<B*>(p3->n()))->g();
    return 0;
    
/*
 B::g 
 B::k  A::n 
 A::f  B::g  A::j 
 A::m  B::g  A::j 
 A::k  C::j  A::m  A::g  C::j 
 A::f  A::g  C::j 
 D::m  B::g  D::j 
 B::k  A::n 
 A::g 
 A::n  A::m  A::g  C::j 
 A::n  A::n  A::g 
 D::n  A::m  B::g  D::j 
 D::m  B::g  D::j  A::n  A::g 
*/
}











