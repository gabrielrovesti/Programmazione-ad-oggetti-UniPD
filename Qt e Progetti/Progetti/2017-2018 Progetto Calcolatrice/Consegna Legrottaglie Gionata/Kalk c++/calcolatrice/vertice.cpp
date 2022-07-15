#include "vertice.h"
Vertice::Vertice(double a,double b):Punto::Punto(a,b){}
Vertice::Vertice(const Vertice& v):Punto::Punto(v){}
// calcolo dell'angolo del vertice b
double Vertice::get_Angolo(const Vertice &b, const Punto &a, const Punto &c){
    Punto ab( b.get_X() - a.get_X(), b.get_Y() - a.get_Y() );
    Punto cb( b.get_X() - c.get_X(), b.get_Y() - c.get_Y() );

    double dot = (ab.get_X() * cb.get_X() + ab.get_Y() * cb.get_Y() );
    double cross = (ab.get_X() * cb.get_Y() - ab.get_Y() * cb.get_X());

    double alpha = atan2(cross, dot);
    return abs((alpha * 180 / M_PI));
}

QString Vertice::toString()const{
  return QString("V," + to_string_nozero(get_X()) + to_string_nozero(get_Y()));
}



