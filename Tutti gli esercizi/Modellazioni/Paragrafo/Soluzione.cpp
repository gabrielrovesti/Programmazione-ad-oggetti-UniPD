#include <iostream>
#include <vector>
using namespace std;

class ElementoTestuale {
	private:
		int l;	//larghezza
	public:
		virtual ~ElementoTestuale() = default;
		virtual int altezza() const = 0;
		int getLarghezza() const {return l;}
};

class Spaziatura : public ElementoTestuale {
	private:
		static int alt;
	public:
		virtual int altezza() const { return alt; }
		//operatore di stampa
		friend ostream& operator<<(ostream& os, const Spaziatura& sp);
};

ostream& operator<<(ostream& os, const Spaziatura& sp){
	os << "SPAZIATURA =" << "Altezza:" << sp.altezza() << " Larghezza:" << sp.getLarghezza() <<endl;
	return os;
}

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
		//operatore di stampa
		friend ostream& operator<<(ostream& os, const Carattere& c);
};

ostream& operator<< (ostream& os, const Carattere& c){
	os << "CARATTERE =" <<" ASCII:" << c.ASCII << " Altezza:" << c.altezza() << " Larghezza:" << c.getLarghezza() <<endl;
	return os;
}

class Immagine : public ElementoTestuale {
	private:
		int h;
		string nome;
		static int margineS, margineD;
	public:
		string getNome () const { return nome; }
		virtual int altezza() const { return h; }
		int getLarghezza() const { return ElementoTestuale::getLarghezza() + margineS + margineD ; }
		//operatore di stampa
		friend ostream& operator<<(ostream& os, const Immagine& i);
};

int Immagine::margineS = 10;
int Immagine::margineD = 10;

ostream& operator<<(ostream& os, const Immagine& i){
	os << "IMMAGINE =" <<" Nome:" << i.nome << " Altezza:" << i.altezza() << " Larghezza:" << i.getLarghezza() <<endl;
	return os;
}

class Paragrafo {
	friend ostream& operator<<(ostream&, const Paragrafo&);
	private:
		int larghezzaP;	//larghezza paragrafo
		vector<ElementoTestuale*> testo;
	public:
		Paragrafo(int l) : larghezzaP(l) {}
		~Paragrafo() {
			for(vector<ElementoTestuale*>::iterator it = testo.begin(); it != testo.end(); ++it){
				delete *it;
			}
		}
		void addElemento(ElementoTestuale* et) { testo.push_back(et); }
	
		ElementoTestuale* searchMaxHeight() const {
			int hmax = 0;
			ElementoTestuale* et = 0;
			for(vector<ElementoTestuale*>::const_iterator cit = testo.begin(); cit != testo.end(); ++cit){
				Carattere* pc = dynamic_cast<Carattere*>(*cit);
				if(pc && (pc->altezza() > hmax)) et = pc;
			}
			if(!et) throw string("Non Presente");
			else return et;
		}

		vector<vector<ElementoTestuale*>> render() const {
			vector<vector<ElementoTestuale*>> res;
			vector<ElementoTestuale*> riga;
			int larghezzaRiga = 0;
			for(vector<ElementoTestuale*>::const_iterator cit = testo.begin(); cit != testo.end(); ++cit){
				if(larghezzaRiga + (*cit)->getLarghezza() <= larghezzaP){
					riga.push_back(*cit);
					larghezzaRiga += (*cit)->getLarghezza();
				}
				else{
					res.push_back(riga);
					riga.clear();
					riga.push_back(*cit);
					larghezzaRiga = (*cit)->getLarghezza();
				}
			}
			res.push_back(riga);
			return res;
		}

		int height() const {
			int h = 0;
			for(vector<vector<ElementoTestuale*>>::const_iterator cit = render().begin(); cit != render().end(); ++cit){
				int hmax = 0;
				for(vector<ElementoTestuale*>::const_iterator cit2 = (*cit).begin(); cit2 != (*cit).end(); ++cit2){
					if((*cit2)->altezza() > hmax) hmax = (*cit2)->altezza();
				}
				h += hmax;
			}
			return h;
		}
	
};

ostream& operator<<(ostream& os, const Paragrafo& par){
	os << "PARAGRAFO =" <<" Larghezza:" << par.larghezzaP <<endl;
	return os;
}

int main(){

	return 0;

}
	
		
				