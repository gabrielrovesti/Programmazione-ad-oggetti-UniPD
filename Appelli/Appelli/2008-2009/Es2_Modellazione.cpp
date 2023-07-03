#include <iostream>
using namespace std;

class Nodo {};

template <class T>
class albero{
	friend ostream& operator<< <T>(ostream& , const albero<T> &);
private:
	class Nodo{
	public:
		Nodo* sx, cx, dx;
		T info;
		
		Nodo(Nodo* s, Nodo* c, Nodo* d, T i) : sx(s), cx(c), dx(d), info(i) {}
	
		static Nodo* copia(Nodo* copy) { 
			if ( !copy ) return 0;
			else return new Nodo(copia(copy->sx), copia(copy->cx), copia(copy->dx), copy->info);
		}
		
		~Nodo() {
			if(sx) delete sx; 
			if(cx) delete cx; 
			if(dx) delete dx;
		}
		
		static bool confronta(const Nodo* n1,const Nodo* n2) const {
			if(!n1 && !n2)	return true;
			else if ((!n1 && n2) || (n1 && !n2))	return false;
			else	return (n1->info == n2->info && confronta(n1->sx, n2->sx) && confronta(n1->cx, n2->cx) && confronta(n1->dx, n2->dx));
		}
		
		string stampa(const Nodo* n) const { 
			string s;
			if (n) {
				s = n->info + " " + stampa(n->sx) + stampa(n->cx) + stampa(n->dx);
			}
			return s;
		}
	};
	
	Nodo* radice;
	
public:
	albero(Nodo* r=0) : radice(r){}
	
	albero(const albero& a) { if(a) radice(copia(a.radice)); }
	
	~albero() { if(radice) delete radice; }
	
	albero<T>& operator=(const albero<T>& a){ 
		if(this != &a){
			delete *this;
			radice(a.copia());
		}
		return *this;
	}
	
	bool operator==(const albero& a) const {
		if(!radice && !a.radice) return true;
		else return confronta(radice, a.radice);
	}
		
};

template<class T>
ostream& operator<<(ostream& os, const albero<T>& a){
	os << stampa(a.radice);
	return os;
}

main(){

}