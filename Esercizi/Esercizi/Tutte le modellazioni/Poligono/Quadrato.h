/*
 * Quadrato.h
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */

#ifndef QUADRATO_H_
#define QUADRATO_H_
#include "Ret.h"
class Quadrato: public Rettangolo{
public:
	Quadrato(const Punto*);
	 double perimetro() const;
	  double area() const;
};




#endif /* QUADRATO_H_ */
