#include<string>
#include<vector>
using std::string;
using std::vector;

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










