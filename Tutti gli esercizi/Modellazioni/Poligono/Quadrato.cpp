#include"Quadrato.h"

double Quadrato::perimetro()const{
	return Punto::Lung(p[0],p[1])*4;	//Perimetro = lato * 4
}

double Quadrato::area() const{
	return Punto::Lung(p[0],p[1])*Punto::Lung(p[0],p[1]);	//Area = lato^2 (sapendo che il lato è la distanza tra due punti)
}

Quadrato::Quadrato(const Punto v[]):Rettangolo(v){}



