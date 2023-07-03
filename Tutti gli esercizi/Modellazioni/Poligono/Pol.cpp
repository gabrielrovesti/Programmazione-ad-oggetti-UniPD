#include "Pol.h"
#include <math.h>

Punto::Punto(double a,double b): x(a),y(b){}

// Formula della distanza tra punti --> radice tra la somma delle ascisse al quadrato
// e delle ordinate al quadrato
double Punto::Lung(const Punto& a,const Punto& b){
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}

// Costruttore per poligono con "v" vertici e punti "p" (se esistono)
Poligono::Poligono(unsigned int v, const Punto* b): nvertici(v), p(v>0? new Punto[v]: nullptr){
	for(unsigned int i=0;i<v;i++)
		p[i]=b[i];
}

// IL distruttore dealloca tutto il vettore di punti
Poligono::~Poligono(){
	delete [] p;
}

// Costruttore di copia --> praticamente uguale al costruttore precedente (punti e vertici)
// ma costruisco direttamente il poligono con una serie di "p" punti sulla base di "nvertici" vertici
Poligono::Poligono(const Poligono& l): nvertici(l.nvertici), p(l.nvertici>0 ? new Punto[l.nvertici]: nullptr){
	for (unsigned int i=0;i<l.nvertici;i++){
		p[i]=l.p[i];
	}
}

// Operatore di assegnazione profonda --> copio i punti e i vertici
Poligono& Poligono::operator=(const Poligono& q){
		if(this != &q){ 	//Controllo che non sia lo stesso oggetto
			delete p;	//Dealloco il vettore di punti (oggetto precedente)

			// Copio tutti i vertici (se esistono)
			nvertici=q.nvertici;
			// Mi creo un vettore di punti con "nvertici" vertici
			p=(nvertici==0 ? nullptr: new Punto[nvertici]);

			// Copio tutti i punti
			for(unsigned int i=0;i<nvertici;i++){
				p[i]=q.p[i];
			}
	}
	// Ritorno come sempre il riferimento all'oggetto di invocazione
	return *this;
}

// Perimetro del poligono --> somma delle lunghezze dei lati (precedente e successivo)
// attuando una divisione modulo (mod) tra i vertici
// (per assicurarsi che i vertici esistano e, a seconda del tipo di poligono, 
// faccio l'operazione che serve)

double Poligono::perimetro() const{
	double s;
	for (unsigned int i=0;i<nvertici; i++){
		s=Punto::Lung(p[i], p[(i+1) % nvertici]);
	}
	return s;
}



