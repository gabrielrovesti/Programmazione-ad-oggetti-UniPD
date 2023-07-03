/* ESERCIZIO. 
Definire una superclasse ContoBancario e due sue sottoclassi ContoCorrente 
e ContoDiRisparmio che soddisfano le seguenti specifiche:

1) Ogni ContoBancario è caratterizzato da un saldo e rende disponibili due funzionalità di
deposito e prelievo: double deposita(double) e double preleva(double) che ritornano il saldo
aggiornato dopo l’operazione di deposito/prelievo.

2) Ogni ContoCorrente è caratterizzato anche da una spesa fissa uguale per ogni ContoCorrente che
deve essere detratta dal saldo ad ogni operazione di deposito e prelievo.

3) Ogni ContoDiRisparmio deve avere un saldo non negativo e 
pertanto non tutti i prelievi sono
permessi; d’altra parte, le operazioni di deposito e 
prelievo non comportano costi aggiuntivi e
restituiscono il saldo aggiornato.

4) Si definisca inoltre una classe ContoArancio derivata da ContoDiRisparmio.
La classe ContoArancio deve avere un ContoCorrente di appoggio: 
quando si deposita una somma S su un
ContoArancio, S viene prelevata dal ContoCorrente di appoggio; 
d’altra parte, i prelievi di una
somma S da un ContoArancio vengono depositati nel ContoCorrente di appoggio.
*/ 

/*
        Gerarchia:

        ContoBancario
        /           \
ContoCorrente   ContoDiRisparmio
                     |
                ContoArancio    
*/

#include <iostream>

class ContoBancario{
    protected:
        double saldo; //meglio protected che private qui
    public:
        double deposita(double d){    //inline --> scrivo il metodo direttamente
            return d >=0 ? saldo += d : saldo; 
            //se d è maggiore o uguale a 0, aggiungo d al saldo, altrimenti ritorno il saldo
        }
        double preleva(double p){
            return p >=0 ? saldo -= p : saldo;
            //se p è maggiore o uguale a 0, sottraggo p al saldo, altrimenti ritorno il saldo
        }
        ContoBancario(double s = 0): saldo(s>=0 ? s : 0){} // Costruttore
        double getSaldo() const {return saldo;} // Metodo di get() del campo privato
};

class ContoCorrente: public ContoBancario{
    private:
        static double spesaFissa;
    public:
        double deposita(double d){
            return ContoBancario::deposita(d - spesaFissa);
            //ritorno il saldo aggiornato dopo aver sottratto la spesa fissa
        }
        double preleva(double p){
            return ContoBancario::preleva(p + spesaFissa);
            //ritorno il saldo aggiornato dopo aver aggiunto la spesa fissa
        }
        //dato che non aggiungo altro rispetto alla superclasse,
        //uso il costruttore della stessa ContoBancario
        ContoCorrente(double s = 0): ContoBancario(s){} // Costruttore
};

double ContoCorrente::spesaFissa = 1.0;

class ContoDiRisparmio: public ContoBancario{
    public:
        double preleva(double p){
            //prelievo se effettivamente posso prelevare quella quantità
            //(cioè, se non effettuo un prelievo della quantità maggiore
            //al saldo attuale)
            if(p <= getSaldo())
                return ContoBancario::preleva(p);
            else
                return getSaldo();
        }
        //ContoBancario::deposita() non necessita di ridefinizione; 
        //inserito da me per completezza

        //double deposita(double d){
        //    return ContoBancario::deposita(d);
        //}

        //dato che non aggiungo altro rispetto alla superclasse,
        //uso il costruttore della stessa ContoBancario
        //Qua, invece, si sa che è non negativo
        ContoDiRisparmio(double s = 0.0): ContoBancario(s){}
};

class ContoArancio: public ContoDiRisparmio{
    private:
        ContoCorrente& ContoDiAppoggio; //conto di appoggio deve essere modificabile
    public:
    //Invariante (assunzione): saldo >=0
    double deposita(double d){
        if(d <= getSaldo() && d >= 0){
            ContoDiAppoggio.preleva(d);
            return ContoBancario::deposita(d);
        }
        else
            return getSaldo();
    }
    double preleva(double p){
       if(p >= 0){
            ContoDiAppoggio.deposita(p);
            return ContoBancario::preleva(p);
        }
        else
            return getSaldo();
       //ritorno il saldo aggiornato dopo le operazioni (se ho potuto fare il prelievo)
    }
    //Mi creo un ContoArancio con un ContoCorrente di appoggio
    //ed un saldo del ContodiRisparmio (si intuisce dalle operazioni richieste)
    ContoArancio(ContoCorrente& ap, double s = 0): ContoDiRisparmio(s), ContoDiAppoggio(ap){}
};

int main(){
    ContoCorrente cc(2000);
    ContoArancio ca(cc, 1500); 
    ca.deposita(350); ca.preleva(400); cc.preleva(150);
    std::cout<< cc.getSaldo() << std::endl;  //stampa: 1897
    std::cout<< ca.getSaldo() << std::endl;  //stampa: 1450
}


