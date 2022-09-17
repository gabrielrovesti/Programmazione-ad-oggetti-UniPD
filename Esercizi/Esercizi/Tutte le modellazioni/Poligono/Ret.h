/*
 * Ret.h
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */

#ifndef RET_H_
#define RET_H_
#include"Pol.h"
class Rettangolo: public Poligono{
public:
	Rettangolo(const Punto*);
	  double perimetro() const;
	  double area() const;
};




#endif /* RET_H_ */
