 #ifndef CERCHIO_H
#define CERCHIO_H
#include "shape.h"
#include <cmath>
class Cerchio : public Shape
{
	private:
		Vertice origine;
		double raggio;
	public:
		Cerchio(const Vertice&, double);
		Cerchio(const Cerchio&);
		double get_raggio() const;
		Vertice get_origine()const;
		void set_origine(const Vertice&);
		double get_perimetro()const;
		double get_area()const;
		QString get_nomeClasse() const;
		QString toString() const;
		Cerchio& operator+= (double);
		Cerchio& operator =(const Cerchio&);
		bool operator==(const Cerchio&)const;
		bool operator!=(const Cerchio&)const;
		bool operator<(const Cerchio&)const;
		bool operator>(const Cerchio&)const;
		bool operator<=(const Cerchio&)const;
		bool operator>=(const Cerchio&)const;

};
ostream& operator<<(ostream&,const Cerchio&);
Cerchio operator+(const Cerchio&,double);
Cerchio operator-(const Cerchio&,double);

#endif // CERCHIO_H
