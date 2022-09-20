#include "Point.h"
#include<math.h>
#include<iostream>

Point::Point(double x,double y,double z){
    this->x=x;
    this->y=y;
    this->z=z;
}

Point::Point(){
    this->x=0;
    this->y=0;
    this->z=0;
}

Point Point::negate() const {
    return Point(-x,-y,-z);
}

double Point::norm() const{
    return sqrt(x*x+y*y+z*z);
}

void Point::print() const{
    std::cout<<"("<<x<<"."<<y<<"."<<z<<")";
}
