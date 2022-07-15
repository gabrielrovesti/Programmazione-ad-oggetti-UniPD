class impiegato { // classe astratta
protected: static double stipBase;
public:    virtual double stipendioBase() const =0;
};
double impiegato::stipBase = 1500;

class manager : public impiegato {
public:   
  virtual double stipendioBase() const {return 2*impiegato::stipBase;}
};

class programmatore : public impiegato {
private: double bonus;
public: 
  programmatore(double b): bonus(b) {}
  virtual double stipendioBase() const {return impiegato::stipBase;}
  double getBonus() const {return bonus;}; // metodo non virtuale
};

class MicrosoftAdmin {
public:
static double stipendio(impiegato* p) {
    if(typeid(*p)==typeid(programmatore)) { // non e' codice estendibile!
      programmatore* q = dynamic_cast<programmatore*>(p);
      return q->stipendioBase() + q->getBonus();
    }
    else return p->stipendioBase(); 
  }
};