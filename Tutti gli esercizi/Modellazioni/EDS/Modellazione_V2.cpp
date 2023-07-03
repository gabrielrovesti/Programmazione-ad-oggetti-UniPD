#include <vector>
#include <string>
#include <iostream>
 
class PaccoBase {
private:
  double peso; // in Kg
  std::string mittente, destinatario;
  static double tariffaPerKg; // in euro
public:
  virtual double costo() const {
    return peso*tariffaPerKg;
  }
  double getPeso() const {return peso;}
  std::string getDestinatario() const {return destinatario;}
  std::string getMittente() const {return mittente;}
  virtual ~PaccoBase() =default;
  virtual std::string getTipologia() const {return "PaccoBase";}
 
};
double PaccoBase::tariffaPerKg = 10.0;
 
class Pacco2: public PaccoBase {
private:
  static double addizionale; // in euro
public:
  virtual double costo() const override {
    return PaccoBase::costo() + addizionale;
  }
  virtual std::string getTipologia() const override {return "Pacco2";}
};
double Pacco2::addizionale = 2.0; // in euro
 
class PaccoFast: public PaccoBase {
private:
  bool overnight; // true sse paccoFast Overnight
  static double addizionalePerKg;
  static double addizionaleON;
public:
  virtual double costo() const override {
    return PaccoBase::costo() + getPeso()*addizionalePerKg
      + (overnight ? addizionaleON : 0);
  }
  virtual std::string getTipologia() const override {
    return overnight ? "PaccoFast Overnight" : "PaccoFast Non Overnight";
  }
  bool getOvernight() const {return overnight;}
  PaccoFast(const PaccoBase& pb, bool on=true): PaccoBase(pb), overnight(on) {}
 
};
double PaccoFast::addizionalePerKg = 2.0;
double PaccoFast::addizionaleON = 7.0;
 
class AgenziaEDS {
  friend std::ostream& operator<<(std::ostream&,const AgenziaEDS&);
private:
  std::vector<PaccoBase*> m;
public:
  std::vector<PaccoFast> cerca(std::string dest, double peso) const {
    std::vector<PaccoFast> ris;
    for(auto cit = m.begin(); cit < m.end(); ++cit) {
      PaccoFast* pf = dynamic_cast<PaccoFast*>(*cit);
      if(pf && pf->getOvernight() && pf->getDestinatario() == dest
     && pf->getPeso()>peso)
    ris.push_back(*pf);
    }
    return ris;
  }
 
  void modifica(std::string mit) {
    for(int i=0; i<m.size(); ++i)
      if(typeid(*m[i]) == typeid(PaccoBase) && m[i]->getMittente() ==mit) {
    PaccoBase* t= m[i];
    m[i] = new PaccoFast(*t);
    delete t;
      }
  }
};
 
std::ostream& operator<<(std::ostream& os, const AgenziaEDS& a) {
  double tot=0.0;
  for(int i=0; i<a.m.size(); ++i) {
    tot+=a.m[i]->costo();
    os << "pacco # " << i << " di tipologia = " <<
      a.m[i]->getTipologia() << " di costo = " << a.m[i]->costo() <<
      " di sovrapprezzo rispetto alla base = " <<
      a.m[i]->costo() - a.m[i]->PaccoBase::costo();
  }
  os << "\n" <<  "Il costo totale dei pacchi e` = " << tot << "\n";
  return os;
}

int main(){
    
}