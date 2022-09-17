#include <iostream>

/* ESERCIZIO. Definire una superclasse ContoBancario e due sue sottoclassi ContoCorrente 
e ContoDiRisparmio che soddisfano le seguenti specifiche:

1) Ogni ContoBancario è caratterizzato da un saldo e rende disponibili due funzionalità di
deposito e prelievo: double deposita(double) e double preleva(double) che ritornano il saldo
aggiornato dopo l’operazione di deposito/prelievo.

2) Ogni ContoCorrente è caratterizzato anche da una spesa fissa uguale per ogni ContoCorrente chedeve essere detratta dal saldo ad ogni operazione di deposito e prelievo.
3) Ogni ContoDiRisparmio deve avere un saldo non negativo e pertanto non tutti i prelievi sono
permessi; d’altra parte, le operazioni di deposito e prelievo non comportano costi aggiuntivi e
restituiscono il saldo aggiornato.4) Si definisca inoltre una classe ContoArancio derivata da ContoDiRisparmio. La classe
ContoArancio deve avere un ContoCorrente di appoggio: quando si deposita una somma S su un
ContoArancio, S viene prelevata dal ContoCorrente di appoggio; d’altra parte, i prelievi di una
somma S da un ContoArancio vengono depositati nel ContoCorrente di appoggio.*/ 

class ContoBancario{
    private:
    double saldo;      //nessun vincolo perché posso andare in negativo
    public:
    double deposita(double d){
        return d >= 0 ? saldo += d : saldo;
    }
    double preleva(double p){
        return p >= 0 ? saldo -= p: saldo;
    }
    double getSaldo() const {return saldo; }
    ContoBancario(double x=0): saldo(x) {}
};

class ContoCorrente: public ContoBancario{
    private:
        static double spesaFissa;
    public:
        double deposita(double d){
            return ContoBancario::deposita(d - spesaFissa);
        }
        double preleva (double p){
            return ContoBancario::deposita(p + spesaFissa);
        }
        ContoCorrente(double x=0): ContoBancario(x) {}      //se qui provo ad inizializzare spesaFissa sarebbe errore perché è un campo statico 
};  

double ContoCorrente::spesaFissa = 1.0;

class ContoDiRisparmio: public ContoBancario{
    //il saldo qui per invariante deve essere non negativo

    //Se io ho un campo privato, posso prendermelo con una funzione di intermezzo
    //potrebbe essere getSaldo (pensaci anche quando vai a prendere l'es di poligono)
    public:
        double preleva(double p){
            return ContoBancario::preleva(p > getSaldo() ? 0 : p);
        }
    //ContoBancario::deposita non viene ridefinita (chiaramente, perché non hai bisogno di fare altre operazioni)
    //sopra invece ho bisogno di fare lo scoping della funzione precedente per usarla
    ContoDiRisparmio(double x=0): ContoBancario(x >= 0 ? x : 0) {}
};

class ContoArancio: public ContoDiRisparmio{
    private:
        ContoCorrente& ContoDiAppoggio;
    public:
        ContoArancio(ContoCorrente& ap, double z=0): ContoDiRisparmio(z), ContoDiAppoggio(ap){}
        double deposita(double d){
            ContoDiAppoggio.preleva(d);   return ContoDiRisparmio::deposita(d);
        }
        double preleva(double p){
            if(p <= getSaldo()){
                ContoDiAppoggio.deposita(p);   return ContoDiRisparmio::preleva(p);
            }
            return getSaldo();
        }
};

int main(){
    ContoCorrente cc(2000);
    ContoArancio ca(cc, 1500);  //per quello inseriamo un alias a ContoCorrente, perché creando un conto arancio è richiesto anche il conto di appoggio
    ca.deposita(350); ca.preleva(400); cc.preleva(150);
    std::cout<< cc.getSaldo() << std::endl; //stampa 1897
    std::cout<< cc.getSaldo() << std::endl; //stampa 1450
}