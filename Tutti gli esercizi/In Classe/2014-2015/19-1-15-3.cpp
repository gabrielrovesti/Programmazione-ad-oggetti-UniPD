#include<iostream>
#include<fstream>
#include<typeinfo>
using namespace std;

class C { 
	public:
	virtual ~C(){}
};

template<class T1, class T2> 			//T1 e T2 tipi polimorfi
	bool Fun(T1*p, T2&r){
		return((typeid(T1) == typeid(T2)) && (typeid(*p) == typeid(r)
		&& dynamic_cast<ios*>(p)));		//&& typeid(ios) != typeid(*p) inutile ios è astratta
	}

main(){
	ifstream f("pippo"); 
	fstream g("pluto"), h("zagor");
	iostream* p = &h;
	C c1, c2;
	cout << Fun(&cout,cin) << endl; 	//stampa: 0
	cout << Fun(&cout, cerr) << endl;	//stampa: 1
	cout << Fun(p,h) << endl;			//stampa: 0
	cout << Fun(&f,*p) << endl;			//stampa: 0
	cout << Fun(&g,h) << endl;			//stampa: 1
	cout << Fun(&c1,c2) << endl;		//stampa: 0
	
	//queste tre righe servono solo per tenere aperto il terminale in windows
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();
}