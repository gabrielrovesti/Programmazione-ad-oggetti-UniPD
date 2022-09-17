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
(cioè, fare due file separati: Point.h e Point.cpp)
*/

#ifndef POINT_H
#define POINT_H

#include <iostream>
class Point {
    private:
        double _x, _y, _z;
    public:
        Point();
        Point(double x=0.0, double y=0.0, double z=0.0)
        ~Point();
        double getx() const;
        double gety() const;
        double getz() const;
        void negate();
        double norm() const;
        //friend std::ostream& operator<<(std::ostream& os, const Point& p);
};
std::ostream& operator<<(std::ostream& os, const Point& p);
Point operator+(const Point& p1, const Point& p2);

#endif