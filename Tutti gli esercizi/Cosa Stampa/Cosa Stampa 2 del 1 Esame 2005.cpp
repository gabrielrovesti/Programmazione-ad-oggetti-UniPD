#include <iostream>
using namespace std;

class N;

class S { 
	friend ostream& operator<<(ostream&, const S&); 
	friend void stampa(N*);
private: 
	string z;
public: 
	S(string x = ""): z(x) {}
}; 
ostream& operator<<(ostream& os, const S& x) {return os << x.z;}

class N { 
	friend class C; 
	friend void stampa(N*);
public: 
	N* next;
private: 
	S s;
	N(S t, N* p): s(t), next(p) {}
}; 

class C { 
public:
	N* punt; 
	C( N* x = new N(string("ROSSO"),0) ) : punt(x) {} 
	void G() {if(punt) punt = punt->next;} 
	void F(string s1, string s2 = "BLU") {
		punt = new N(s1,punt); punt = new N(s2,punt);
	}
};
	
void Fun(C* p1, C* p2) { if(p1 != p2) {*p1 = *p2; p1->G(); }} 

void stampa(N* p) { if(p) { cout << p->s << ' '; stampa(p->next); } }	

int main(){ 
	C* p = new C; p->F("VERDE"); 
	C* q = new C((p->punt)->next); q->F("BIANCO","NERO"); 
	stampa(p->punt); cout << "**1 " << endl;				//	BLU VERDE ROSSO **1 
	stampa(q->punt); cout << "**2 " << endl;				//	NERO BIANCO VERDE ROSSO **2 
	C* t = new C(p->punt); Fun(p,q);
	stampa(p->punt); cout << "**3 " << endl;				//	BIANCO VERDE ROSSO **3 
	stampa(q->punt); cout << "**4 " << endl;				//	NERO BIANCO VERDE ROSSO **4
	Fun(q,t); 
	stampa(p->punt); cout << "**5 " << endl;				//	BIANCO VERDE ROSSO **5
	stampa(q->punt); cout << "**6 " << endl;				//	VERDE ROSSO **6 
	q->F("GIALLO"); p->F("GIALLO"); 
	stampa(p->punt); cout << "**7 " << endl;				//	BLU GIALLO BIANCO VERDE ROSSO **7
	stampa(q->punt); cout << "**8 " << endl;				//	BLU GIALLO VERDE ROSSO **8
}
		
/*
BLU VERDE ROSSO **1 
NERO BIANCO VERDE ROSSO **2
BIANCO VERDE ROSSO **3
NERO BIANCO VERDE ROSSO **4
BIANCO VERDE ROSSO **5
VERDE ROSSO **6
BLU GIALLO BIANCO VERDE ROSSO **7
BLU GIALLO VERDE ROSSO **8
*/				