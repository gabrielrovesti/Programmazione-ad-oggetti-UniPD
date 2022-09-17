/* ESERCIZIO 27/11/2015

Definire una superclasse ContoBancario e due sue sottoclassi ContoCorrente e 
ContoDiRisparmio che soddisfano le seguenti specifiche:

1) Ogni ContoBancario e' caratterizzato da un saldo e rende disponibili due 
funzionalita` di deposito e prelievo: double deposita(double) e 
double preleva(double) che ritornano il saldo aggiornato dopo l'operazione 
di deposito/prelievo.

2) Ogni ContoCorrente e` caratterizzato anche da una spesa fissa uguale per ogni 
ContoCorrente che deve essere detratta dal saldo ad ogni operazione di deposito 
e prelievo.

3) Ogni ContoDiRisparmio deve avere un saldo non negativo e pertanto non tutti 
i prelievi sono permessi; d'altra parte, le operazioni di deposito e prelievo 
non comportano costi aggiuntivi e restituiscono il saldo aggiornato.

Si definisca inoltre una classe ContoArancio derivata da ContoDiRisparmio. 
La classe ContoArancio deve avere un ContoCorrente di appoggio: quando si 
deposita una somma S su un ContoArancio, S viene prelevata dal ContoCorrente 
di appoggio; d'altra parte, i prelievi di una somma S da un ContoArancio 
vengono depositati nel ContoCorrente di appoggio.
*/

#include <iostream>

class DatiAnagrafici {
  // ...
};

class ContoBancario {
private:
  double saldo; // puo` essere negativo
  DatiAnagrafici titolare;
public:
  double deposita(double x) {
    if(x<=0) return saldo+=x;
    return saldo;
  }
  double preleva(double x) {return saldo-=x;}
  ContoBancario(double i=0): saldo(i<=0 ? 0:i) {}
  double getSaldo() const {return saldo;}
};

class ContoCorrente: public ContoBancario {
private:
  static double spesaFissa;
public:
  // ridefinizioni
  double deposita(double x) {
 return ContoBancario::deposita(x-spesaFissa); 
  }
  double preleva(double x) {
    return ContoBancario::preleva(x+spesaFissa);
  }
  ContoCorrente(double init=0): ContoBancario(init) {}
};
double ContoCorrente::spesaFissa = 1.0; 

class ContoDiRisparmio: public ContoBancario {
  // invariante: this->saldo >=0
public:
  // deposita() e' ok nella versione ereditata da ContoBancario
  // ridefinzione di ContoBancario::preleva()
  double preleva(double x) {
    if(x > getSaldo()) {
      std::cerr << "occhio che ti rimane nulla" << std::endl;
      return ContoBancario::preleva(getSaldo());
    }
    // x<= getSaldo()
    return ContoBancario::preleva(x);
  }
  ContoDiRisparmio(double x=0): ContoBancario(x) {}
};

class ContoArancio: public ContoDiRisparmio {
private:
  ContoCorrente& contoDiAppoggio;
public:
  ContoArancio(ContoCorrente& x, double init=0): 
    ContoDiRisparmio(init), contoDiAppoggio(x) {}
  double preleva(double x) {
    if(x<= getSaldo()) contoDiAppoggio.deposita(x); 
    else contoDiAppoggio.deposita(getSaldo()); 
  return ContoDiRisparmio::preleva(x);
  }

  double deposita(double x) { 
    // Homework
    return 0.0;
  }
};

int main() {
  ContoCorrente cc(1000);
  cc.preleva(300);
  cc.deposita(700);
  ContoArancio ca(cc, 500);
  ca.preleva(100);
}