#include <iostream>
#include <vector>
using namespace std;

class Abbonato{
	public:
	virtual double costoAttuale() const =0;
};

class AbbonatoTempo : public Abbonato{
	private:
	unsigned int sec; //	tot secondi connesso
	static double costoxsec;
	
	public:
	int getSec() const {return sec;}
	
	virtual double costoAttuale() const { return sec * costoxsec; }
};
double AbbonatoTempo:: costoxsec = 0.2;

class AbbonatoTraffico : public Abbonato{
	private:
	unsigned int KB;
	static double costoxkb;

	public:
	int getKb() const { return KB; }
	
	AbbonatoTraffico(int k=0) : KB(k){};

	virtual double costoAttuale() const { return KB * costoxkb; }
};
double AbbonatoTraffico:: costoxkb = 0.1;


class FilialeSlowWeb{
	private:
	vector<Abbonato*> abbonati;
	static double Sc;	//	Iporto Sconto
	static int sS;		//	Soglia Secondi
	static int sKB;	//	Soglia KB

	public:

	void inserisci(const Abbonato& a){
		abbonati.push_back(const_cast<Abbonato*>(&a));
	}

	double bolletta(const Abbonato& a) const {
		double boll = 0;
		Abbonato* pa = const_cast<Abbonato*>(&a);

		AbbonatoTempo* pat = dynamic_cast<AbbonatoTempo*>(pa);
		if(pat){
			boll += pat->costoAttuale();
			if(pat->getSec() > sS) boll -= Sc;
		}

		AbbonatoTraffico* patr = dynamic_cast<AbbonatoTraffico*>(pa);
		if(patr){
			boll += patr->costoAttuale();
			if(patr->getKb() > sKB) boll -= Sc;
		}
		return boll;
	}
	
	
	double totaleBollette() const {
		double tot=0;
		for (vector<Abbonato*>::const_iterator cit = abbonati.begin(); cit != abbonati.end(); ++cit) {
			tot += bolletta(**cit);
		}
		return tot;
	}
	
};
double FilialeSlowWeb:: Sc = 10;
int FilialeSlowWeb:: sS = 2;
int FilialeSlowWeb:: sKB = 1;

int main(){
	return 0;
}

