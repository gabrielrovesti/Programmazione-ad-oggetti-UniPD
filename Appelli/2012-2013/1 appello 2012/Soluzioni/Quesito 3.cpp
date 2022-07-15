#include <iostream>
#include <vector>
using namespace std;

class Opera {
private:
	string titolo;
	bool inPrestito;
public:
	string getTitolo() const { return titolo; }
	bool isPrestato() const { return inPrestito; } 
	
	void setPrestato() { inPrestito=true; }
	void setRitornato() { inPrestito=false; }
	
	virtual ~Opera() ;
	virtual bool disponibile(int currentAnno) const =0 ;
	virtual bool operator==(Opera*) const = 0;
	virtual string stampa() const = 0;
};

class Libro : public Opera {
private:
	string autore;
public:
	string getAutore() const { return autore; }
	
	virtual bool disponibile(int currentAnno = 2016) const { return !isPrestato(); }
	virtual bool operator==(Libro* o) const { return typeid(*this)==typeid(o) 
		&& autore==o->getAutore() && getTitolo()==o->getTitolo();}
	virtual string stampa() const { return "LIBRO - Titolo: " + getTitolo() + " Autore: " + getAutore(); }
};

class Rivista : public Opera {
private:
	int anno;
	static int maxAnni;
public:
	int getAnno() const { return anno; }
	
	virtual bool disponibile(int currentAnno = 2016) const { return currentAnno-maxAnni >= anno; }
	
	virtual bool operator==(Rivista* o) const { return typeid(*this)==typeid(*o) && anno==o->getAnno() && getTitolo()==o->getTitolo();}
	virtual string stampa() const { return "RIVISTA - Titolo: " + getTitolo() + " Anno: " + static_cast<const char>(getAnno());}
};

class DVD : public Opera {
private:
	vector<string> lingue;
public:
	vector<string> getLingue() const { return lingue; }
	bool cerca(string w) const {
		for (vector<string>::const_iterator cit = lingue.begin(); cit != lingue.end(); ++cit) {
			if (w == *cit) {
				return true;
			}
		}
		return false;
	}
	
	virtual bool disponibile(int currentAnno = 2016) const { return false; }
	
	virtual bool operator==(DVD* o) const { 
		if(typeid(*this)==typeid(*o) && getTitolo()==o->getTitolo()){
			for (int i; i != lingue.size(); ++i) {
				if( lingue[i] != o->getLingue()[i] ) return false;
			}
			return true;
		}
	}
	
	virtual string stampa() const { string s= "DVD - Titolo: " + getTitolo() + "Lingue :" ; for(int i; i != lingue.size(); ++i){ s += "-"+lingue[i];} return s;}
	};


class Biblioteca {
	friend ostream& operator<<(ostream& , const Biblioteca&);
private:
	vector<const Opera*> collezione;
	vector<Opera*> prestiti;
public:
	void presta(Opera* o) { 
		bool presente = false;
		for (vector<const Opera*>::const_iterator cit = collezione.begin(); cit != collezione.end(); ++cit) {
			if (o == *cit) {
				presente=true;	
			}
		}
		if (presente) {
			o->setPrestato();
			prestiti.push_back(o);
		}
		else {
			throw string("NonPresente");
		}
	}
	
	void aggiungi(Opera* o) {
		for (vector<Opera*>::iterator it = prestiti.begin(); it != prestiti.end(); ++it) {
			if (*it == o) {
				delete *it;
				prestiti.erase(it);
				}
		}
		o->setRitornato();
		const Opera* po(o);
		collezione.push_back(po);
	}
	
	vector<Opera*> consultabili(int anno) {
		vector<Opera*> ris;
		for (vector<const Opera*>::const_iterator cit = collezione.begin(); cit != collezione.end(); ++cit) {
			if((*cit)->disponibile(anno) && !(*cit)->isPrestato()) ris.push_back(const_cast<Opera*>(*cit));
		}
		return ris;
	}

	vector<Opera*> cerca(string s) const {
		vector<Opera*> ris;
		for (vector<const Opera*>::const_iterator cit = collezione.begin(); cit != collezione.end(); ++cit){
			if (s == (*cit)->getTitolo()) {
				ris.push_back(const_cast<Opera*>(*cit));
			}
			else if (Libro* pl = dynamic_cast<Libro*>(const_cast<Opera*>(*cit)) && pl->getAutore() == s) {
				ris.push_back(pl);
			}
			else if (Rivista* pr = dynamic_cast<Rivista*>(const_cast<Opera*>(*cit)) && pr->getAnno() == s){
				ris.push_back(pr);
			}
			else if (DVD* pd = dynamic_cast<DVD*> (const_cast<Opera*>(*cit))){
			vector<string> l = pd->getLingue();
				bool presente = false;
				for (int i; i != l.size(); ++i) if (s == l[i]) presente = true;
				if (presente) {
					ris.push_back(pd);
				}
			}
				  
		}
		return ris;
	}
				  
};
				  
	ostream& operator<<(ostream& os , const Biblioteca& b){
		for (int i; i < b.collezione.size(); ++i) {
			os << i <<") "<< b.collezione[i]->stampa() << endl;
		}
		return os;
	}
				  
					  
int main(){

	return 0;

}
	
		
				