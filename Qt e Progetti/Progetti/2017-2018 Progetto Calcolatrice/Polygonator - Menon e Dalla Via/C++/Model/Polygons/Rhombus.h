#ifndef RHOMBUS_H
#define RHOMBUS_H

#include "Parallelogram.h"
#include "Kite.h"

class Rhombus : virtual public Parallelogram, public Kite {
public:
    explicit Rhombus(const list<Point> &);

    //Returns whether a polygon is a rhombus or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the area of a rhombus using the diagonals
    double getArea() const;

    //Returns the perimeter of a rhombus (the sides are all equals)
    double getPerimeter() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif
