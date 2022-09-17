/* ESERCIZIO DISCUSSO NELLA LEZIONE DEL 25/11/2014

Definire una superclasse ContoBancario e due sue sottoclassi
ContoCorrente e ContoDiRisparmio che soddisfano le seguenti
specifiche:

1) Ogni ContoBancario e` caratterizzato da un saldo e rende
disponibili due funzionalita` di deposito e prelievo: double
deposita(double) e double preleva(double) che ritornano il saldo
aggiornato dopo l’operazione di deposito/prelievo.

2) Ogni ContoCorrente e` caratterizzato anche da una spesa fissa
uguale per ogni ContoCorrente che deve essere detratta dal saldo ad
ogni operazione di deposito e prelievo.

3) Ogni ContoDiRisparmio deve avere un saldo non negativo e pertanto
non tutti i prelievi sono permessi; d’altra parte, le operazioni di
deposito e prelievo non comportano costi aggiuntivi e restituiscono il
saldo aggiornato.

4) Si definisca inoltre una classe ContoArancio derivata da
ContoDiRisparmio. La classe ContoArancio deve avere un ContoCorrente
di appoggio: quando si deposita una somma S su un ContoArancio, S
viene prelevata dal ContoCorrente di appoggio; d’altra parte, i
prelievi di una somma S da un ContoArancio vengono depositati nel
ContoCorrente di appoggio.
*/


class ContoBancario {
private:
  double saldo;
public:
  double deposita(double x) {if(x>=0) then return saldo+=x; else return saldo;}
  double preleva(double x) {return if(x>=0) saldo-=x; else return saldo;}
  double getSaldo() const {return saldo;}
  ContoBancario(double init=0): saldo(init) {if(saldo<0) saldo=0;}
};

class ContoCorrente: public ContoBancario {
private:
  static double spesaFissa;
public: 
  double deposita(double x) { return ContoBancario::deposita(x-spesaFissa); }
  double preleva(double x) { return ContoBancario::preleva(x+spesaFissa); }
  ContoDiCorrente(double init=0): ContoBancario(init) {} 
};
double ContoCorrente::spesaFissa = 1.0;

class ContoDiRisparmio: public ContoBancario {
public:
  double preleva(double x) {
    if(x>getSaldo()) return getSaldo(); 
    // x <= getSaldo()
    return ContoBancario::preleva(x);
  }
  ContoDiRisparmio(double init=0): ContoBancario(init) {} 
};

class ContoArancio: public ContoDiRisparmio {
private:
  ContoCorrente& contoDiAppoggio; 
public: 
  ContoArancio(double depositioIniziale, ContoCorrente& cc): 
    ContoDiRisparmio(depositoIniziale), contoDiAppoggio(cc) {}
  double preleva(double x) {
    if(x<=getSaldo()) {
      contoDiAppoggio.deposita(x); return ContoBancario::preleva(x);
    }
    // x > getSaldo()
    return getSaldo();
  }
  double deposita(double x) {
    if(x>0) {
      contoDiAppoggio.preleva(x); return ContoBancario::deposita(x);
    }
    return getSaldo();
  }
};