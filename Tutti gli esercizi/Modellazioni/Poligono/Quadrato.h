#ifndef QUADRATO_H_
#define QUADRATO_H_
#include "Ret.h"

class Quadrato: public Rettangolo{
public:
	Quadrato(const Punto*);
	double perimetro() const; //Perimetro quadrato = lato (l) * 4 oppure l+l+l+l
	double area() const; //Area = l^2
};

#endif /* QUADRATO_H_ */
