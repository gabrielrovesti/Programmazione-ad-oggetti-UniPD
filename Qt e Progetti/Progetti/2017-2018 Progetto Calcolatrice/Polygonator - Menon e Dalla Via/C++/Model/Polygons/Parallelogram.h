#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H

#include "Quadrilateral.h"

class Parallelogram : virtual public Quadrilateral {
public:
    explicit Parallelogram(const list<Point> &);

    //Returns whether a polygon is a parallelogram or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the height of the parallelogram (distance between base and a point on the opposite side)
    double getHeight() const;

    //Returns the area of the parallelogram, using the height
    double getArea() const;

    //Returns the perimeter of the parallelogram (the opposite sides are always equals)
    double getPerimeter() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif
