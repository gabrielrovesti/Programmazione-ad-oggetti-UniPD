/*
Definire una classe Point i cui oggetti rappresentano punti
nello spazio (x, y, z). Includere:
un costruttore di default, un costruttore a tre argomenti
che inizializza un punto, selettori delle coordinate cartesiane,
un metodo negate() che trasforma un punto nel suo negativo,
una funzione norm() che restituisce la distanza del punto
dall'origine, l'overloading degli operatori di
somma e di output.
Separare interfaccia ed implementazione della classe.
*/

#include "Point.h"

Point::Point(){
    _x = 0.0;
    _y = 0.0;
    _z = 0.0;
}

Point::Point(double x, double y, double z){
    _x = x;
    _y = y;
    _z = z;
}

Point::~Point(){
    std::cout << "Coordinate eliminate " << std::endl;
}

double Point::getx() const{
    return _x;
}

double Point::gety() const{
    return _y;
}

double Point::getz() const{
    return _z;
}

void Point::negate(){
    _x .* = -1;
    _y .* = -1;
    _z .* = -1;
}

double Point::norm() const{
    return sqrt(_x.*_x + _y.*_y + _z.*_z);
}

Point Point::operator+(const Point& p1, const Point& p2){
    return Point(
    p1.getx() + p2.getx(),
    p1.gety() + p2.gety(),
    p1.getz() + p2.getz()
    );
}

std::ostream& operator<<(std::ostream& os, const Point& p){
    return os << "(" << p.getx() << ", " << p.gety() << ", " 
    << p.getz() << ")";
}