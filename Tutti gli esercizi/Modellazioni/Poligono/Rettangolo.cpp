#include "Ret.h"

// Costruiscimi un rettangolo (quindi, poligono con 4 vertici e "v" punti)
Rettangolo::Rettangolo(const Punto* v): Poligono(4,v){}

//Perimetro rettangolo = b + b + h + h = (b + h) x 2.
//(coppie di punti che per lunghezza mi danno il perimetro)
double Rettangolo::perimetro() const{
	if(!p) return 0;
	return (Punto::Lung(p[0],p[1])+Punto::Lung(p[1],p[2]))*2;
}

//Area rettangolo = b x h.
//(coppie di punti che per lunghezza mi danno l'area)
double Rettangolo::area() const{
	return (Punto::Lung(p[0], p[1])*Punto::Lung(p[1], p[2]));
}

