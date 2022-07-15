// APPELLO DEL 26-01-2015
// QUESITO 1 - FitApp(C)

#include <string>
#include <vector>
#include <math.h>

using std::string;
using std::vector;

class Allenamento {
protected:
	double durata;
public:
	virtual Allenamento* clone() const = 0;
	virtual int calorie() const = 0;
	virtual ~Allenamento() {};
};

class Ciclismo: public Allenamento {
private:
	double distanza, salita;
public:
	Allenamento* clone() const {
		return new Ciclismo(*this);
	}
	int calorie() const {
		return (200*pow(distanza,2))/durata + 100*salita;
	}
	double getDistanza() const {
		return distanza;
	}
	double getSalita() const {
		return salita;
	}
};

class Corsa: public Allenamento {
private:
	double distanza, sterrato;
public:
	Allenamento* clone() const {
		return new Corsa(*this);
	}
	int calorie() const {
		return (600*pow(distanza,2))/durata;
	}
	double getSterrato() const {
		return sterrato;
	}
};

class Nuoto: public Allenamento {
private:
	double vasche;
	string stile;
public:
	Allenamento* clone() const {
		return new Nuoto(*this);
	}
	int calorie() const {
		return 35*vasche;
	}
	string getStile() const {
		return stile;
	}
};

class FitApp {
private:
	vector<const Allenamento*> a;
public:
	vector<Ciclismo> salita(double perc) const {
		vector<Ciclismo> v;
		for (int i = 0; i < a.size(); ++i) {
			Ciclismo* c = dynamic_cast<Ciclismo*>(const_cast<Allenamento*>(a[i]));
			if (c && (100/c->getDistanza())*c->getSalita() > perc)
				v.push_back(*c);
		}
		return v;
	}
	vector<Allenamento*> calorie(int x) const {
		vector<Allenamento*> v;
		for (int i = 0; i < a.size(); ++i) {
			if (a[i]->calorie() > x) {
				Nuoto* n = dynamic_cast<Nuoto*>(const_cast<Allenamento*>(a[i]));
				if (n && n->getStile() == "libero")
					v.push_back(a[i]->clone());
				else
					v.push_back(a[i]->clone());
			}
		}
	}
	void insert(Corsa* p) {
		double record = 0;
		for (int i = 0; i < a.size(); ++i) {
			Corsa* c = dynamic_cast<Corsa*>(const_cast<Allenamento*>(a[i]));
			if (c && c->getSterrato() > record)
				record = c->getSterrato();
		}
		if (p->getSterrato() > record)
			a.push_back(p);
	}
	int conta(double lim) {}
};
