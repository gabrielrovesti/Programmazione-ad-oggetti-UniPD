#include <iostream>
#include <vector>
using namespace std;


class Exc {
private:
	string err;
public:
	Exc(string e): err(e){ cout << e << endl; }
};


class App {
private:
	double MB;
	bool internet;
public:
	App(double m=0, bool i=false) : MB(m), internet(i) {}
	App(const App& a) : MB(a.MB), internet(a.internet) {}
	virtual ~App();
						   
	double getMB() const {return MB;}
	bool needConnect() const {return internet;}			   
};

class FreeApp : public App {
private:
	bool openSource;
public:
	FreeApp(bool oS=false, double m=0, bool i=false) : openSource(oS), App(m, i){}
	FreeApp(const FreeApp& fa) : openSource(fa.openSource), App(fa.getMB(), fa.needConnect()){}
	
	bool isOpenSource() const {return openSource;}
};

class PayApp : public App {
private:
	double prezzo;
public:
	PayApp(double p=1, double m=0, bool i=false) : prezzo(p), App(m, i) { if(p<=0) throw Exc("Errore Prezzo");}
	PayApp(const PayApp& pa) : prezzo(pa.prezzo), App(pa.getMB(), pa.needConnect()){}
	
	double getPrezzo() const {return prezzo;}
};


class aiPhone {
private:
	vector<const App*> mem;
	double maxMB;

public:
	double installaApp(const App& a){
		if (maxMB > a.getMB()) {
			maxMB -= a.getMB();
			mem.push_back(&a);
			return maxMB;
		}
		else {
			throw Exc("Memoria non sufficiente");
		}
	}
	
	vector<PayApp> F(double x) const {
		vector<PayApp> rit;
		for (vector<const App*>::const_iterator cit=mem.begin(); cit != mem.end(); ++cit) {
			PayApp* ppa = dynamic_cast<PayApp*> (const_cast<App*> (*cit));
			if (ppa && ppa->needConnect() && ppa->getPrezzo() < x) {
				PayApp* ai = new PayApp(*ppa);
				rit.push_back(*ai);
			}
		}
		return rit;
	}
	
	FreeApp* G() const {
		FreeApp* rit = 0;
		double maxPeso = 0;
		for (vector<const App*>::const_iterator cit = mem.begin(); cit != mem.end(); ++cit) {
			FreeApp* pfa = dynamic_cast<FreeApp*> (const_cast<App*> (*cit));
			if (pfa && pfa->isOpenSource() && maxPeso < pfa->getMB()) {
				rit = pfa;
				maxPeso = pfa->getMB();
			}
		}
		
		if (rit) return rit;
		else throw Exc("Nessuna Applicazione Open Source");
	}
};


int main(){

}