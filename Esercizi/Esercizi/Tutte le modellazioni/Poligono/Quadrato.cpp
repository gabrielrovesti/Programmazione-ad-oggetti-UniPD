/*
 * Quadrato.cpp
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */
#include"Quadrato.h"
double Quadrato::perimetro()const{
	return Punto::Lung(p[0],p[1])*4;
}
double Quadrato::area() const{
	return Punto::Lung(p[0],p[1])*Punto::Lung(p[0],p[1]);
}
Quadrato::Quadrato(const Punto v[]):Rettangolo(v){}



