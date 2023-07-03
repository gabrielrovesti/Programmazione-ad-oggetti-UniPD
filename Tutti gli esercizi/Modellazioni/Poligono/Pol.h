#ifndef POL_H_
#define POL_H_

class Punto{
public:
	double x,y;	//Coordinate
public:
	Punto(double=0,double=0);
	static double Lung(const Punto&,const Punto&);	//Lunghezza --> prendo le due coordinate
};

class Poligono{
public:
	unsigned int nvertici;	//Numero vertici
	Punto* p;	//Punti
	static Punto* copia(const Poligono&);	//Copia punti e vertici
public:
	Poligono(unsigned int, const Punto*);	//Costruttore per vertici e punti
	~Poligono();
	Poligono(const Poligono&);	//Costruttore di copia
	Poligono& operator=(const Poligono&);	//Operatore di assegnazione profonda
	virtual double perimetro() const;	//Perimetro del poligono specifico
	virtual double area() const =0 ;	//Area del poligono specifico
};

#endif /* POL_H_ */
