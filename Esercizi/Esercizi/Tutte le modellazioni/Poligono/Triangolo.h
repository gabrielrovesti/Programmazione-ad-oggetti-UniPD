/*
 * Triangolo.h
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */
#include "Pol.h"
#ifndef TRIANGOLO_H_
#define TRIANGOLO_H_
class Triangolo: public Poligono{
public:
 Triangolo(const Punto*);
 double area() const;
};
class Tri_Rettangolo: public Triangolo {
public:
	Tri_Rettangolo(const Punto*);
	double area() const;
};
class Tri_Equi: public Triangolo {
public:
	Tri_Equi(const Punto*);
	double area() const;
	double perimetro()const;
};






#endif /* TRIANGOLO_H_ */
