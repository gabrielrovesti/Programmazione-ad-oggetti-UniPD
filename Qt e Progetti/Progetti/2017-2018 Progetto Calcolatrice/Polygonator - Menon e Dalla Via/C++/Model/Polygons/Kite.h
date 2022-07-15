#ifndef KITE_H
#define KITE_H

#include "Quadrilateral.h"

class Kite : virtual public Quadrilateral {
public:
    explicit Kite(const list<Point> &);

    //Returns whether a polygon is a kite or not
    static bool canBeCreatedWith(const Polygon &);

    double getArea() const;

    double getPerimeter() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif
