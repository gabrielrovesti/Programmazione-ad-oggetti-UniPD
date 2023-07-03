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
	~N() {if(next) delete next; cout << info << "  ̃N ";}
};
	
class Lista { 
private:
	N* last; 
public:
	Lista() : last(0) {} 
	
	~Lista() {
		if(last) { 
			while(last->prev) last = last->prev; 
			delete last;
			}
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

main() {
	Lista* p = new Lista;
	Lista* q = new Lista;
	p->add(3); p->add(4); p->add(5); p->add(6);
	q->add(7); 
	*q=*p; 
	--(*q); 
	p->print(); cout << " **1\n"; 
	q->print(); cout << " **2\n"; 
	p->add(8); 
	p->print(); cout << " **3\n"; 
	(*q)--; cout << " **4\n"; 
	q->print(); cout << " **5\n"; 
	--(*q); delete q; cout << " **6\n"; 
}

/*
3 4 5 6  **1
3 4 5 6  **2
3 4 5 6 8  **3
8  ̃N 6  ̃N 5  ̃N  **4
3 4  **5
4  ̃N 3  ̃N  **6
*/