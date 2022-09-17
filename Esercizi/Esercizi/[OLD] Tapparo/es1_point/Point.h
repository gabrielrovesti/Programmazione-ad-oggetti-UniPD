#ifndef _POINT_H
#define _POINT_H

class Point{
public:
    Point();
    Point(double x,double y, double z);
    Point negate() const;
    double norm() const;
    void print() const;    
private:
    double x,y,z;
    
};

#endif;
