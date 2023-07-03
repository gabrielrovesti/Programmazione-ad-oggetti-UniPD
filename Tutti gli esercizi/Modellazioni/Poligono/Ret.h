#ifndef RET_H_
#define RET_H_
#include "Pol.h"

class Rettangolo: public Poligono{
public:
	Rettangolo(const Punto*);	// Costruttore di copia per i punti
	
	double perimetro() const;	//Perimetro rettangolo = b + b + h + h = (b + h) x 2.
	double area() const;		//Area rettangolo = b x h.
};

#endif /* RET_H_ */
