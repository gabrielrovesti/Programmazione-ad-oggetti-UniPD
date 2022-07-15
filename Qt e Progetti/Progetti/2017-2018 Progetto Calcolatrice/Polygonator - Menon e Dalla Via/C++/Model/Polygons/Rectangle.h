#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Parallelogram.h"

class Rectangle : virtual public Parallelogram {
public:
    explicit Rectangle(const list<Point> &);

    //Returns whether a polygon is a rectangle or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the height of a rectangle (the side adjacent to the base)
    double getHeight() const;

    //Returns the perimeter of a rectangle
    double getPerimeter() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif
