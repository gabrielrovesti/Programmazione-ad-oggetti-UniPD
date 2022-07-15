/*
 * Rettangolo.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */
#include "Ret.h"

Rettangolo::Rettangolo(const Punto* v): Poligono(4,v){}

double Rettangolo::perimetro() const{
	if(!p) return 0;
	return (Punto::Lung(p[0],p[1])+Punto::Lung(p[1],p[2]))*2;
}
double Rettangolo::area() const{
	return (Punto::Lung(p[0], p[1])*Punto::Lung(p[1], p[2]));
}

