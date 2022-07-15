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
private: double bonus; // campo dati proprio
public: 
  programmatore(double b): bonus(b) {}
  virtual double stipendioBase() const {return impiegato::stipBase;}
  double getBonus() const {return bonus;}; // metodo non virtuale
};

class MicrosoftAdmin {
public:
  static double stipendio(const impiegato& p) {
    const programmatore* q = dynamic_cast<const programmatore*>(&p);
    // se il cast ha successo, 
    // cioe` il tipo dinamico di &p e` sottotipo di programmatore* 
    if(q) return q->stipendioBase() + q->getBonus();
    // altrimenti (q==0), 
    // cioe' il tipo dinamico di &p non e` sottotipo di programmatore* 
    else return p.stipendioBase(); 
  }
};