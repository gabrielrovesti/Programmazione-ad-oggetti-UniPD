/*
 * Pol.h
 *
 *  Created on: Nov 16, 2021
 *      Author: marco
 */

#ifndef POL_H_
#define POL_H_
class Punto{
public:
	double x,y;
public:
	Punto(double=0,double=0);
	static double Lung(const Punto&,const Punto&);
};
class Poligono{
public:
	unsigned int nvertici;
	Punto* p;
	static Punto* copia( const Poligono&);
public:
	Poligono(unsigned int, const Punto* );
	virtual  ~Poligono();
	Poligono(const Poligono&);
	Poligono& operator=(const Poligono&);
	virtual double perimetro() const;
	virtual double area() const =0 ;
};

#endif /* POL_H_ */
