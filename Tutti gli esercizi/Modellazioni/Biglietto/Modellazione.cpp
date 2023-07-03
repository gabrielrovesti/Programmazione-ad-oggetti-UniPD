#include <iostream>
#include <vector>
using namespace std;

class Biglietto {
private:
	unsigned int km;
	static double prezzoBase;
public:
	Biglietto();
	Biglietto(unsigned int k): km(k){}
	int getKm() const {return km;}
	double getBase() const {return prezzoBase;}
	
	virtual double prezzo() const = 0;
	virtual ~Biglietto();
};
double Biglietto::prezzoBase = 0.1;	// Euro

class BigliettoPrimaClasse : public Biglietto {
public:
	BigliettoPrimaClasse();
	BigliettoPrimaClasse(unsigned int k): Biglietto(k) {}
	
	virtual double prezzo() const { return getKm()*getBase() * ( getKm()<100 ? 1.30 : 1.20 );}
};

class BigliettoSecondaClasse : public Biglietto {
private:
	bool prenotato;
	static double costoFisso;
public:
	BigliettoSecondaClasse();
	BigliettoSecondaClasse(int k, bool p=false): Biglietto(k), prenotato(p) {}
	bool isPrenotato() const {return prenotato;}
	double getCostoPrenotazione() const {return costoFisso;}

	virtual double prezzo() const { return getKm()*getBase() + ( isPrenotato() ? costoFisso : 0 );}
};
double BigliettoSecondaClasse::costoFisso = 5.0;	// Euro


class BigliettoSmart {
public:
	Biglietto* b;
	BigliettoSmart(const Biglietto& bi) { b = const_cast<Biglietto*>(&bi) ;}
};


class TrenoPieno{
private:
	int classePiena;
public:
	int getClassePiena() const {return classePiena;}
	TrenoPieno(int i): classePiena(i) { 
		if(i==1) cout << "Prima Classe Piena" << endl;
		else if(i==2) cout << "Seconda Classe Piena" << endl;
		else if(i==3) cout << "Treno Completamente Pieno" << endl;
		else cout << "Errore" << endl;
	}
};


class Treno {

private:
	
	vector<BigliettoSmart> venduti;
	int maxPrima;	// massimo numero di posti in prima classe
	int maxSeconda;	// massimo numero di posti in seconda classe prenotati
	
public:
	
	int* bigliettiVenduti() const {
		int* bv = new int[3];
		bv[0] = bv[1] = bv[2] = 0;
		for(vector<BigliettoSmart>::const_iterator cit = venduti.begin(); cit != venduti.end(); ++cit){
			BigliettoPrimaClasse* pbpc = dynamic_cast<BigliettoPrimaClasse*>(cit->b);
			if( pbpc ) bv[0]++;
			BigliettoSecondaClasse* pbsc = dynamic_cast<BigliettoSecondaClasse*>(cit->b);
			if( pbsc ) pbsc->isPrenotato() ? bv[1]++ : bv[2]++ ;
		}
		return bv;
	}
	
	void vendiBiglietto(const Biglietto& biglietto){
		int* nBiglietti = bigliettiVenduti();
		BigliettoPrimaClasse* pbpc = dynamic_cast<BigliettoPrimaClasse*>(const_cast<Biglietto*>(&biglietto));
		if( pbpc ){
			if (nBiglietti[0] < maxPrima) {
				venduti.push_back(biglietto);
				return;
			}
			else {
				throw TrenoPieno(1);
			}
		}
		BigliettoSecondaClasse* pbsc = dynamic_cast<BigliettoSecondaClasse*>(const_cast<Biglietto*>(&biglietto));
		if( pbsc ){
			if (pbsc->isPrenotato() || (pbsc->isPrenotato() && nBiglietti[1] < maxSeconda)) {
				venduti.push_back(biglietto);
				return;
			}
			else {
				throw TrenoPieno(2);
			}
		}
	}
	
	double incasso() const {
		double tot=0;
		for(vector<BigliettoSmart>::const_iterator cit = venduti.begin(); cit != venduti.end(); ++cit){
			tot += (*cit).b->prezzo();
		}
		return tot;
	}

};

main(){
	Treno t;
	BigliettoPrimaClasse b10(200);
	BigliettoPrimaClasse b11(300);
	BigliettoSecondaClasse b20(50);
	BigliettoSecondaClasse b21(150);
	BigliettoSecondaClasse b22(250);
}