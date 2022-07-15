#ifndef SQUARE_H
#define SQUARE_H

#include "Rectangle.h"
#include "Rhombus.h"

class Square : public Rectangle, public Rhombus {
public:
    explicit Square(const list<Point> &);

    //Returns whether a polygon is a square or not
    static bool canBeCreatedWith(const Polygon &);

    //Returns the apothemConstant when the polygon is regular (ratio apothem/side)
    double getApothemConstant() const;

    //Returns the area of a square (the sides are all equals)
    double getArea() const;

    //Returns the perimeter of a square
    double getPerimeter() const;

    //Returns the name of the polygon
    string getName() const;
};


#endif
