/*
 * Pol.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */
#include "Pol.h"
#include <math.h>
Punto::Punto(double a,double b): x(a),y(b){}
double Punto::Lung(const Punto& a,const Punto& b){
	return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));
}

Poligono::Poligono(unsigned int v, const Punto* b): nvertici(v), p(v>0? new Punto[v]: nullptr){
for(unsigned int i=0;i<v;i++)
	p[i]=b[i];
}
Poligono::~Poligono(){
	delete [] p;
}

Poligono::Poligono(const Poligono& l): nvertici(l.nvertici), p(l.nvertici>0 ? new Punto[l.nvertici]: nullptr){
for (unsigned int i=0;i<l.nvertici;i++){
	p[i]=l.p[i];
}
}
Poligono& Poligono::operator=(const Poligono& q){
if(this!=&q){
	delete p;
	nvertici=q.nvertici;
	p= (nvertici==0 ? nullptr: new Punto[nvertici]);
	for(unsigned int i=0;i<nvertici;i++)
		p[i]=q.p[i];

}
return *this;
}
double Poligono::perimetro() const{
	double s;
	for (unsigned int i=0;i<nvertici; i++){
		s=Punto::Lung(p[i],p[(i+1)%nvertici]);
	}
	return s;
}



