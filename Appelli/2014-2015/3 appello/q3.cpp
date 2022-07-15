#include <iostream>
using namespace std;

class Empty{};

template <class T> class Coda;
template <class T> ostream& operator<< (ostream& os, const Coda<T>& t);

template <class T=double>
class Coda{
	friend class const_iterator;
	friend ostream& operator<< <T>(ostream&, const Coda<T>&);
private:
	class Nodo{
	public:
		Nodo* next;
		T info;
		
		Nodo(T i=T(), Nodo* n=0) : next(n), info(i) {}
		~Nodo() { delete next;}
		Nodo* copy(){ //testata
			T t=info;
			return new Nodo(t);
		}
		bool operator==(const Nodo& n){ //testata 
			if (info==n.info) return true;
			return false;
		}
	};
	
	Nodo* first;
	Nodo* last;
	
public:
	Coda() : first(0), last(0) {} //testata
	Coda(int k, const T& t=T()) { //testato
		if (k>1) {
			first = new Nodo(t);
			last=first;
			--k;
			while (k) {
				insert(t);
				--k;
			}
		}
		else{
			first=0;
			last=0;
		}
	}
	
	Coda(const Coda& c){ //testato
		if(!c.first){ first=0; last=0; }
		else{
			Nodo* aux=c.first;
			first=aux->copy();
			Nodo* ris=first;
			while(aux->next){
				aux=aux->next;
				ris->next=aux->copy();
				ris=ris->next;
			}
			last=ris;
		}
	}
	
	Coda& operator=(const Coda& c){ //testato
		if (this!=&c){
			delete first;
			if(!c.first){ first=0; last=0; }
			else{
				Nodo* aux=c.first;
				first=aux->copy();
				Nodo* ris=first;
				while(aux->next){
					aux=aux->next;
					ris->next=aux->copy();
					ris=ris->next;
				}
			last=ris;
			}
		}
		return *this;
	}
	
	~Coda(){ delete first; } //poi ci pensa il distruttore di nodo
	
	void insert(const T& t = T()){ //testata
		if(!last){
			first=new Nodo(t);
			last=first;
		}
		else{
			last->next=new Nodo(t);
			last=last->next;
		}
	}
	
	T removeNext() { //testata
		if(!first) throw Empty();
		Nodo* aux = first;
		first = first->next;
		T t = aux->info;
		delete aux;
		return t;
	}
	
	T* getNext() const { //testata
		if (!first) return 0;
		char c;
		return &(first->info);
	}
	
	bool operator!=(const Coda& c) const{ //testata
		Nodo *auxc=c.first;
		Nodo *aux=first;
		while(auxc && aux){
			if (*auxc==*aux){
				auxc=auxc->next;
				aux=aux->next;
			}
			else{return true;}
		}
		if (!aux && !auxc){ return false;}
		return true;
	}
	
	Coda& operator+(const Coda& d){ //testato
		last->next=d.first;
		return *this;
	}
	
	//questa parte e' un casino, non riesco a dichiarare gli iteratori nel main, spero almeno le dichiarazioni siano giuste...
	class const_iterator{
	friend class Coda<T>;
	private:
		const Coda::Nodo* punt;
	public:
		const_iterator(Coda::Nodo* n=0): punt(n)  {}
		
		const_iterator& operator++() {
			if (punt) punt=punt->next;
			return *this;
		}
		
		bool operator!=(const_iterator it){
			if (punt==it.punt) return false;
			return true;
		}
		
		const T& operator*() const {
			return punt->info;
		}
		
		const T& operator[](const_iterator i) {
			return (i.punt)->info;
		}
	};
	
	const_iterator& begin() const{ return new const_iterator(first);	}
	const_iterator& end() const{ return new const_iterator(0);	}
};

template <class T> ostream& operator<< (ostream& os, const Coda<T>& t){ //testata
	typename Coda<T>::Nodo* aux=t.first;
	if (!aux) return os<<"lista vuota"<<endl;
	int k=1;
	while(aux){
		os<<"k = "<<k<<"   info = "<<aux->info<<endl;
		aux=aux->next;
		k++;
	}
	return os;
}

int main(){
}
