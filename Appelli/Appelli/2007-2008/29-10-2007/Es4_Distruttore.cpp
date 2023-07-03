#include <iostream>
using namespace std;

class N { 
	friend class Lista;
private: 
	int info; 
	N* prev; 
	N* next;
public: 
	N(int y, N* p = 0, N* q = 0): info(y), prev(p), next(q) {} 
	~N() {
		N* temp = prev;
		while(!prev){
			temp = prev;
			prev = temp->prev;
			delete temp; 
			cout << info << "  ̃N ";
		}
	}
};
	
class Lista { 
private:
	N* last; 
public:
	Lista() : last(0) {} 
	
	~Lista() {
		delete last;
	} 
	
	void add(int x) {
			N* p = new N(x,0,0); 
		if(last) {last->next = p; p->prev = last;} 
		last = p;
	} 

	void operator--() { if(last) last = last->prev; }
	
	void operator--(int) { 
		if(last){ 
			N* p = last; 
			last = last->prev; 
			last->next = 0; 
			delete p;	
		}
	} 

	void print() {
			if(last) { 
				N* p = last; 
				while(p->prev) p = p->prev; 
				while(p){ 
					cout << p->info << " "; p = p->next; 
				}
			}
	}
	
}; 

/*
 Si considerino le classi N e Lista definite nell’Esercizio 3. 
 Si supponga che il distruttore della classe Lista venga ridefinito nel seguente modo:  ̃Lista(){ delete last; }. 
 Si chiede di ridefinire il distruttore della classe N in modo tale che la distruzione di un oggetto di tipo Lista comporti la distruzione profonda della lista.
*/

main() {
	Lista* p = new Lista;
	p->add(3); p->add(4); p->add(5); p->add(6); p->add(7);
	p->print(); cout << " **STAMPA\n";
	delete p;	cout << " **CANCELLA\n";
	//p->print();	cout << " **VERIFICA\n";
	
}

