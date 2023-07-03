#include "Pol.h"
#ifndef TRIANGOLO_H_
#define TRIANGOLO_H_

class Triangolo: public Poligono{
	public:
		Triangolo(const Punto*);
		double area() const; //Area = (b*h)/2
};

class Tri_Rettangolo: public Triangolo {
	public:
		Tri_Rettangolo(const Punto*);
		double area() const; //Area = (b*h)/2
};

class Tri_Equi: public Triangolo {
	public:
		Tri_Equi(const Punto*);
		double area() const; //Area = (b*h)/2
		double perimetro() const; //perimetro = lato * 3; c1 + c2 + i (cateto1 + cateto2 + ipotenusa)
		//oppure, semplicemente, somma di tutti i lati
};


#endif /* TRIANGOLO_H_ */
