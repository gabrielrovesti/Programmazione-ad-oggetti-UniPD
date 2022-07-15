#include <iostream>
#include <list>
#include <vector>

class Anomalia {
private:
  char p;
public:
  Anomalia(char x) : p(x) {}
  char getError() const {
    return p;
  }
};

class Scheda {
private:
  std::string numero;
  double credito_residuo;
  double costo_spedizione_sms;
public:
  virtual void telefonata(unsigned int sec) = 0;
  virtual void connessione(double mb) = 0;
  virtual ~Scheda();
  void messaggioSMS(unsigned int nr_sms) {
    double costo = nr_sms*costo_spedizione_sms;
    if(costo > credito_residuo)
      throw Anomalia('s');
    credito_residuo -= costo;
  }
  Scheda(std::string num = "0", double cr = 0.0, double css = 0.0) : numero(num), credito_residuo(cr), costo_spedizione_sms(css) {}
  double get_credito_residuo() const {
    return credito_residuo;
  }
  std::string get_numero() const {
    return numero;
  }
protected:
  void set_credito_residuo(double cr) {
    credito_residuo = cr;
  }
};


class Mensile : public Scheda {
  unsigned int soglia_mensile_secondi, traffico_secondi_mensile;
  double soglia_mensile_MB, traffico_MB_mensile, costo_mensile;
public:
  Mensile() : soglia_mensile_secondi(60000), soglia_mensile_MB(2096), Scheda("0", 0.0, 0.1) {}
  void telefonata(unsigned int sec) {
    unsigned int n_sec = sec + traffico_secondi_mensile;
    if(n_sec > soglia_mensile_secondi)
      throw Anomalia('v');
    traffico_secondi_mensile = n_sec;
  }

  void connessione(double mb) {
    double new_mb = traffico_MB_mensile + mb;
    if(new_mb > soglia_mensile_MB)
      throw Anomalia('d');
    traffico_MB_mensile = new_mb;
  }
};


class Consumo : public Scheda {
  double costo_1s_t, costo_1mb_c;
public:
  Consumo() : costo_1s_t(0.01), costo_1mb_c(0.1), Scheda("0", 0.0, 0.2) {}
  Consumo(std::string num, double credito_r) : Scheda(num, credito_r) {}
  void telefonata(unsigned int sec) {
    double addebito = sec*costo_1s_t;
    if(addebito > get_credito_residuo())
      throw Anomalia('v');
    set_credito_residuo(get_credito_residuo()-addebito);
  }
  void connessione(double mb) {
    double addebito = mb*costo_1mb_c;
    if(addebito > get_credito_residuo())
      throw Anomalia('d');
    set_credito_residuo(get_credito_residuo()-addebito);
  }
};

class P2 {
private:
  std::list<Scheda*> sim;
public:
  Consumo* cambioPiano(std::string num) {
    Consumo* ptr = 0;
    for(std::list<Scheda*>::iterator it = sim.begin(); it != sim.end() && !ptr; ++it) {
      if((*it)->get_numero() == num && dynamic_cast<Mensile*>(*it)) {
      ptr = new Consumo((*it)->get_numero(), (*it)->get_credito_residuo());
      delete *it;
      *it = ptr;
    }
  }
  return ptr;
}
  std::vector<Consumo> rimuoviConsumoZero() {
    std::vector<Consumo> rimossi;
    for(std::list<Scheda*>::iterator it = sim.begin(); it != sim.end(); ++it) {
      if(dynamic_cast<Consumo*>(*it) && (*it)->get_credito_residuo() == 0.0) {
	rimossi.push_back(*static_cast<Consumo*>(*it));
	sim.erase(it);
	--it;
      }
    }
    return rimossi;
  }

double contabilizza() {
  double tot = 0.0;
  double cont = 0.0;
  for(std::list<Scheda*>::iterator it = sim.begin(); it != sim.end(); ++it) {
    try {
      tot += (*it)->get_credito_residuo();
      (*it)->telefonata(1);
      (*it)->connessione(1);
      (*it)->messaggioSMS(1);
      cont += (*it)->get_credito_residuo();
    }
    catch(Anomalia a) {
      std::cout << a.getError() << std::endl;
    }
  }
  return tot - cont;
}
};