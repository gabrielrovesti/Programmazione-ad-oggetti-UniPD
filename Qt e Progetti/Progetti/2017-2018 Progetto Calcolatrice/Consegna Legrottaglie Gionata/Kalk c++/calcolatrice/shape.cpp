#include "shape.h"
int Shape::n_shape=0;

//Costruttori

Shape::Shape():id(++n_shape){}
Shape::Shape(const Shape& v):id(++n_shape){}
ostream& operator<< (ostream& os,const Shape& P){
  return os<<P.toString().toUtf8().constData();
}

int Shape::get_id() const{return id;}
void Shape::reduce_n_shape(){n_shape--;}
