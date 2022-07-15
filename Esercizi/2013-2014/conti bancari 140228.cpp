class ContoBancario {
private:
  double saldo;
public:
  double  preleva(double p) {
    return saldo -= p;
  }
  double deposita(double d) {
    return saldo+= d;
  }
  double getSaldo() const {return saldo;}
  ContoBancario(double c=0): saldo(c) {}
};
 
class ContoCorrente: public ContoBancario {
private:
  static double commissione;
public:
  double preleva(double p) {
    return ContoBancario::preleva(p+commissione);
  }
  double deposita(double d) {
    return ContoBancario::deposita(d-commissione);    
  }
  ContoCorrente(double c=0): ContoBancario(c) {}
};
double ContoCorrente::commissione = 1.0;
 
class ContoDiRisparmio: public ContoBancario {
public:
  double preleva(double p) {
    if(p>getSaldo()) return getSaldo();
    return ContoBancario::preleva(p);
  }
  // eredito deposita() dalla base
  ContoDiRisparmio(double c=0): ContoBancario(c) {}
};
 
class ContoArancio: public ContoDiRisparmio {
private:
  ContoCorrente& contoDiAppoggio;
public:
  ContoArancio(double c, ContoCorrente& cc):
    ContoDiRisparmio(c), contoDiAppoggio(cc) {}
  double deposita(double d) {
    contoDiAppoggio.preleva(d);
    return ContoDiRisparmio::deposita(d);
  }
  double preleva(double p){
    double s=getSaldo();
    if(p>s) return getSaldo();
    contoDiAppoggio.deposita(p);
    return ContoDiRisparmio::preleva(p);
  }
};