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
 Triangolo(const Punto*);
 double area() const;
};






#endif /* TRIANGOLO_H_ */
