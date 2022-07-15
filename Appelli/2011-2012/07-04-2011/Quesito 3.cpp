#include <iostream>
#include <vector>
using namespace std;

class ElementoTestuale {
	private:
	
	int l;	//larghezza
	
	public:

	virtual ~ElementoTestuale() ;
	virtual int altezza() const = 0;
	int getLarghezza() const {return l;}
	
	virtual string getInfo() const =0;
};

class Spaziatura : public ElementoTestuale {
	private:
	
	static int alt;

	public :
	
	virtual int altezza() const { return alt; }
	virtual ostream& stampa() const {
		ostream& o;
		o << "SPAZIATURA =" << "Altezza:" << alt << " Larghezza:" << getLarghezza() <<endl; 
		return o;
	}
	
};
int Spaziatura::alt=0;

class Carattere : public ElementoTestuale {
	private:

	unsigned int ASCII;	// Carattere compreso tra [0 , 255]
	int hS;				// Altezza superiore la linea di base
	int hI;				// Altezza inferiore la linea di base

	public:

	unsigned int getASCII() const { return ASCII; }
	int getHS() const { return hS; }
	int getHi() const { return hI; }
	
	virtual int altezza() const { return hS + hI; }
	virtual ostream& stampa() const {
		return << "CARATTERE =" << "Tipo:" << ASCII << " Altezza:" << altezza() << " Larghezza:" << getLarghezza() <<endl; 
	}
};

class Immagine : public ElementoTestuale {
	private:

	int h;
	string nome;
	static int margineS, margineD;

	public:

	string getNome () const { return nome; }
	
	virtual int altezza() const { return h; }
	int getLarghezza() const { return ElementoTestuale::getLarghezza() + margineS + margineD ; }
	virtual ostream& stampa() const {
		return << "IMMAGINE =" <<" Nome:" << nome << "Altezza:" << altezza() << " Larghezza:" << getLarghezza() <<endl; 
	}

};


class Paragrafo {
	friend ostream& operator<<(ostream& , const Paragrafo&);

	private:

	int larghezzaP;	//larghezza paragrafo
	vector<ElementoTestuale*> testo;

	public:

	ElementoTestuale* searchMaxHeight() const {
		int hmax = 0;
		ElementoTestuale* et = 0;
		for(vector<ElementoTestuale*>::const_iterator cit = testo.begin(); cit != testo.end(); ++cit){
			Carattere* pc = dynamic_cast<Carattere*>(*cit);
			if(pc && (pc->altezza() > hmax)) et = pc;
		}

		if(!et) throw "Non Presente";
		else return et;
	}

	vector < vector < ElementoTestuale* > > render() const {
		vector< vector < ElementoTestuale* > > ris;
		for(vector<ElementoTestuale*>::const_iterator cit = testo.begin(); cit != testo.end(); ++cit){
			int lung = larghezzaP;
			vector<ElementoTestuale*> riga;
			while(lung > 0){
				riga.push_back(*cit);
				if( dynamic_cast<Immagine*>(*cit) ) lung -= (*cit)->getLarghezza();
				else lung -= (*cit)->getLarghezza();
			}
			ris.push_back(riga);
		}
		
		return ris;
	}
	
	int heght() const{
		
		vector< vector < ElementoTestuale* > > render; 
		render = render();
		
		int tot = 0;
		
		
		vector< vector< ElementoTestuale* > >::const_iterator cit = render.begin();
        
		for (; cit != render.end(); ++cit) { //scorro le righe
            int hmax=0;
            vector< ElementoTestuale* >::const_iterator el = cit->begin();
            for (; el != cit->end(); ++el) { //scorro gli elementi della riga;
                if ( (*el)->getHeight() > hmax ) {
                    hmax = (*el)->getHeight();
                }
            }
			tot += hmax;
		}
		return tot;
		
	}
	
};

ostream& operator<<(ostream& os, const Paragrafo& par){
	for(vector<ElementoTestuale*>::const_iterator cit = par.testo.begin(); cit != par.testo.end(); ++cit){
		os << (*cit)->stampa();
	}
}

int main(){

	return 0;

}
	
		
				