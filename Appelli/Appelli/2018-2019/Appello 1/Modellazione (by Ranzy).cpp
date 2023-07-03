#include<vector>
#include<list>

enum Laurea {Informatica, Ingegneria, Altro};

class ICTstaff {
private: 
  bool magistrale;
  Laurea l;
  double fissoMensile;
protected:
  double getFisso() const {return fissoMensile;}
public: 
  virtual ICTstaff* clone() const =0;
  virtual double salary() const =0;
  virtual ~ICTstaff() = default;
  Laurea getLaurea() const {return l;}
  bool isMaster() const {return magistrale;}
};

class SwEngineer: public ICTstaff {
private:
  bool SwSecurity;
  static double extra;
public:
  virtual double salary() const {
    return getFisso() + (isMaster() ? extra : 0); 
  }
  virtual SwEngineer* clone() const {
    return new SwEngineer(*this);
  }
  bool isSecuritySw() const {return SwSecurity;}
};
double SwEngineer::extra = 500.0;

class HwEngineer: public ICTstaff {
private:
  unsigned int numTrasferte;
  static double extra;
public:
  virtual double salary() const {
    return getFisso() + numTrasferte*extra;
  }
  virtual HwEngineer* clone() const {
    return new HwEngineer(*this);
  }
};
double HwEngineer::extra = 300.0;

class Amazonia {
private:
  class SmartP {
  public:
    ICTstaff* p; 
    SmartP(ICTstaff* q=nullptr): p(q !=nullptr ? q->clone() : nullptr) {}
    SmartP(const SmartP& s): p(s.p !=nullptr ? (s.p)->clone() : nullptr) {}
    SmartP& operator=(const SmartP& s) {
      if(this != &s) {
	if(p) delete p; 
	p = s.p !=nullptr ? (s.p)->clone() : nullptr;
      }
      return *this;
    }
    ~SmartP() {if(p) delete p;} 
    ICTstaff* operator->() const {return p;}
    ICTstaff& operator*() const {return *p;}
  };
  
  std::list<SmartP> sp;
public:

  bool insert(SwEngineer* p, unsigned int k) {
    int num=0;
    SwEngineer* q=nullptr;
    for(auto it = sp.begin(); it != sp.end() && num <k; ++it) {
      q=dynamic_cast<SwEngineer*>(it->p);
      if(q && q->isSecuritySw()) num++;
    }
    if(num<k) {sp.push_back(p); return true;}
    return false;
  }
  
  std::vector<HwEngineer> fire(double s) {
    std::vector<HwEngineer> v;
    HwEngineer* q=nullptr;
    for(auto it = sp.begin(); it != sp.end(); it++)
      if((*it)->salary() > s) {
	q = dynamic_cast<HwEngineer*> (it->p);
	if(q) v.push_back(*q);
	// delete it->p;  NB: non serve perche' ~SmartP() e' profondo
	it=sp.erase(it); --it;
      }
    return v;
  }
  
  std::vector<SwEngineer*> masterInf() const {
    std::vector<SwEngineer*> v;
    SwEngineer* q=nullptr;
    for(auto it = sp.begin(); it != sp.end(); it++) {
      q = dynamic_cast<SwEngineer*>(it->p);
      if(q && (*it)->getLaurea()==Informatica && (*it)->isMaster()) v.push_back(q);
    }
    return v;
  }
 };
    