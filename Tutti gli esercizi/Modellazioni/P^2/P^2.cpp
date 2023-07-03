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










