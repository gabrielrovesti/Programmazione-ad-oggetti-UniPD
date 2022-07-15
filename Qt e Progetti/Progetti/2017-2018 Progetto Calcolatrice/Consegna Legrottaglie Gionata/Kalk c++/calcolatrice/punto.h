#ifndef PUNTO_H
#define PUNTO_H


#include <ostream>
#include <cmath>
#include<QString>
#include<ostream>
class Punto
{
	private:
		double x,y;
	public:
		Punto();
		Punto(double,double);
		Punto(const Punto&);
		virtual ~Punto()=default;
		double get_X()const;
		double get_Y()const;

        virtual QString toString() const;

//		overraiding operatori
		virtual bool operator==(const Punto&)const;
		virtual bool operator!=(const Punto&)const;
        virtual bool operator<(const Punto&)const;

};
QString to_string_nozero(double a);
double distanza(const Punto&, const Punto&);
std::ostream& operator<<(std::ostream&,const Punto&);

#endif // PUNTO_H
