#include <iostream>
#include <vector>
using namespace std;

class PaccoBase{
private:
	string mittente, destinatario;
	double peso; // in Kg
	static double tariffaBase; //in Euro
public:
	PaccoBase(string m =" ", double p =1, string d =" "): mittente(m), peso(p), destinatario(d){}
	
	double getPeso() const {return peso;}
	string getMittente() const {return mittente;}
	string getDestinatario() const {return destinatario;}
	virtual string getTipologia() const {return "Pacco Base ";}
	
	virtual double costo() const { return peso * tariffaBase; }
};
double PaccoBase::tariffaBase = 10.0;

class PaccoDue : public PaccoBase {
private:
	static double tariffaDue;
public:
	PaccoDue(string m =" ", double p =1, string d =" "): PaccoBase(m, p, d){}
	
	virtual string getTipologia() const {return "Pacco Due ";}
	
	virtual double costo() const { return PaccoBase::costo() + tariffaDue; }
};	
double PaccoDue::tariffaDue = 2.0;

class PaccoFast : public PaccoBase {
private:
	bool overnight;
	static double tariffaFast;
	static double tariffaNight;
public:
	PaccoFast(string m , double p, string d,bool o=false): overnight(o), PaccoBase(m, p, d){}
	
	bool isOvernight() const {return overnight;}
	
	virtual string getTipologia() const {
		return overnight ? "Pacco Fast Overnight " : "Pacco Fast Standard ";
	}

	
	PaccoFast(const PaccoBase& pb, bool on = true) : PaccoBase(pb), overnight(on){}
	
	virtual double costo() const { 
		return PaccoBase::costo() + getPeso()*tariffaFast + (overnight ? tariffaNight : 0);
	}
};
double PaccoFast::tariffaFast = 5.0;	// Euro al kg
double PaccoFast::tariffaNight = 7.0;	// Euro fissi


class AgenziaEDS {
	friend ostream& operator<<(ostream& , const AgenziaEDS& );
private:
	
	vector<PaccoBase*> mag;

public:
	
	void insert(const PaccoBase& pb) { mag.push_back(const_cast<PaccoBase*>(&pb)); }
	
	vector<PaccoFast> cerca(string D, double p) const {
		vector<PaccoFast> rit;
		for(vector<PaccoBase*>::const_iterator cit = mag.begin(); cit != mag.end(); ++cit){
			PaccoFast* ppf = dynamic_cast<PaccoFast*>(*cit);
			if(ppf && ppf->getDestinatario() == D && ppf->getPeso() > p){
				rit.push_back(*ppf);
			}
		}
		return rit;
	}
	
	void modifica(string M) {
		for (vector<PaccoBase*>::iterator it = mag.begin(); it != mag.end(); ++it) {
			if (typeid(*it)==typeid(PaccoBase*) && (*it)->getMittente() == M) {
				PaccoBase* t = *it;
				*it = new PaccoFast(*t);
				delete t;
			}
		}
	}

};

ostream& operator<<(ostream& os, const AgenziaEDS& a){
	double tot;
	for(int i=0; i < a.mag.size(); ++i){
		tot += a.mag[i]->costo();
		os << "Pacco n°" << i << " di tipologia: " << a.mag[i]->getTipologia() 
		<< " di costo = " << a.mag[i]->costo() << " di sovrapprezzo = " << a.mag[i]->costo() - a.mag[i]->PaccoBase::costo()
		<< endl;
	}
	os << endl << "COSTO TOTALE = " << tot << endl;
	return os;
}

int main(){
	PaccoBase a("Gino", 2, "Bianco");
	PaccoBase b("Anna", 3, "Rosso");
	PaccoBase b1("Pippo", 20, "Franco");
	
	PaccoDue c("Luca", 5, "Verde");
	
	PaccoFast d("Marco", 2, "Blu");
	PaccoFast d1("Mario", 30, "Giallo");
	PaccoFast d2("Massimo", 40, "Giallo");
	
	AgenziaEDS EDS;
	EDS.insert(a);	
	EDS.insert(b);
	EDS.insert(c);
	EDS.insert(d);
	
	EDS.insert(b1);
	EDS.insert(d1);
	EDS.insert(d2);
	
	cout << "----------------------------- Test Cerca -------------------------------------" <<endl << endl;
	vector<PaccoFast> yellow = EDS.cerca("Giallo", 19);
	for (vector<PaccoFast>::const_iterator cit = yellow.begin(); cit != yellow.end(); ++cit) {
		cout << " Inviato da :" << cit->getMittente() << endl
		<< " Ricevuto da :" << cit->getDestinatario() << endl
		<< " Di peso =" << cit->getPeso() << endl << endl; 
	}
	cout <<endl << "------------------------------------------------------------------------------" <<endl << endl;
	
	cout << EDS;
	
}