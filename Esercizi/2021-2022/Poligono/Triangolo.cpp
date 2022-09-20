/*
 * Triangolo.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */
#include "Triangolo.h"
#include <math.h>
Triangolo::Triangolo(const Punto* p): Poligono(3,p){}

double Triangolo::area() const{
	double per=perimetro()/2;
	double a=Punto::Lung(p[0],p[1]), b=Punto::Lung(p[1],p[2]),  c=Punto::Lung(p[2],p[0]);
	return sqrt(per*(per-a)*(per-b)*(per-c));
}


